import express from "express";
const NAMES = [
  ["Michael", "Chang"], ["Neel", "Kishnani"], ["Kashif", "Nazir"]
];
const STUDENTS = {};
const COURSES = {};
for (let [givenName, surname] of NAMES) {
  let id = (givenName[0] + surname).toLowerCase();
  STUDENTS[id] = { id, givenName, surname, dept: null, units: 0 };
  COURSES[id] = [];
} // the objects created in here are imperminant if theres a crash they are gone


let myApi = express.Router();
myApi.get("/", (req, res) => { 
  let search = req.query.q;
  let students = Object.values(STUDENTS); // get student values inside STUDENTS
  if (search){
    for (let student of students) {
      if (student.id.includes(search)) students.push(student); // if a student is being searched for? from the query string
    }
  }
  res.json({students});
});

// comes in from the router not the query string V
myApi.get("/students/:id", (req, res) =>{
  let id = req.params.id;
  let student = STUDENT[id];
  if (!student) {
    res.status(404).json({error: "Unknown student"});
  }
  res.json(student);
});


// myApi.get

const initApi = (app) => { // create a function that we can add things to apps 
  //app.get();
  app.use("/api", myApi); // erve myApi under /api s. this means we don't need to add /api to anything its already covered
};
export default initApi;

