import bodyParser from "body-parser";
import express from "express";
import { MongoClient } from "mongodb";

const DATABASE_NAME = "lect14_db";

let myApi = express.Router();
let Students;
let Enrollments;

const initApi = async (app) => {
  app.use("/api", myApi);

  let conn = await MongoClient.connect("mongodb://127.0.0.1");
  let db = conn.db(DATABASE_NAME);
  Students = db.collection("students");
  Enrollments = db.collection("enrollments");
};

/* Interpret request bodies as JSON and store them in req.body */
myApi.use(bodyParser.json());

myApi.get("/", (req, res) => {
  res.json({ message: "Hello, world!" });
});

myApi.get("/students", async (req, res) => {
  let allStudents = await Students.find().toArray();
  let search = req.query.q;
  let students = allStudents;
  if (search) {
    students = [];
    for (let student of allStudents) {
      /* Check if the query is contained in each student's name */
      let name = `${student.givenName} ${student.surname}`.toLowerCase();
      if (name.includes(search.toLowerCase())) students.push(student);
    }
  }
  for (let s of students) delete s._id;
  res.json({ students });
});

/* Middleware */
myApi.use("/students/:id", async (req, res, next) => {
  let id = req.params.id;
  let student = await Students.findOne({ id: id });
  if (!student) {
    res.status(404).json({ error: "Unknown student" });
    return;
  }
  /* Store the student so the handler can get it */
  res.locals.student = student;
  /* "Keep going": call the handler */
  next();
});

myApi.get("/students/:id", (req, res) => {
  let student = res.locals.student;
  res.json(student);
});

myApi.patch("/students/:id", async (req, res) => {
  let student = res.locals.student;
  student.dept = req.body.dept;
  await Students.replaceOne({ id: student.id }, student);
  res.json(student);
});

myApi.get("/students/:id/courses", async (req, res) => {
  let student = res.locals.student;
  let data = await Enrollments.find({ studentId: student.id }).toArray();
  let courses = [];
  for (let doc of data) {
    courses.push({ code: doc.code, units: doc.units });
  }
  res.json({ courses });
});

myApi.post("/students/:id/courses", async (req, res) => {
  let student = res.locals.student;
  let code = req.body.code;
  let units = req.body.units;
  /* We don't check for duplicates here */
  await Enrollments.insertOne({ studentId: student.id, code, units });
  student.units += units;
  await Students.replaceOne({ id: student.id }, student);
  res.json({ success: true });
});

export default initApi;
