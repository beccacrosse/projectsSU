import bodyParser from "body-parser";
import express from "express";

const api = express.Router();
api.use(bodyParser.json());

api.use((req, res, next) => {
  console.log(`${req.method} ${req.originalUrl}`);
  next();
});

api.get("/", (req, res) => {
  res.json({ message: "Hello, world!", num: 193 });
});

api.get("/text", (req, res) => {
  res.send("Hello, world!");
});

const STUDENT = {
  id: "michael",
  givenName: "Michael",
  surname: "Chang",
  dept: null,
  unitsCompleted: 0
};

api.get("/students/michael", (req, res) => {
  res.json(STUDENT);
});

api.patch("/students/michael", (req, res) => {
  let u = Number(req.body.unitsCompleted);
  if (u) STUDENT.unitsCompleted = u;
  if (req.body.dept !== undefined) STUDENT.dept = req.body.dept;
  res.json(STUDENT);
});

api.get("/students/michael/canGraduate", (req, res) => {
  if (!STUDENT.dept) res.json({ result: false, reason: "Not declared" });
  else if (STUDENT.unitsCompleted < 180) res.json({ result: false, reason: "Not enough units" });
  else res.json({ result: true });
});

api.get("/protected", (req, res) => {
  res.status(403).json({ error: "You aren't allowed" });
});

export default (app) => {
  app.set("json spaces", 2);
  app.use("/api", api);
};

