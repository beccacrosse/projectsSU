import bodyParser from "body-parser";
import cors from "cors";
import express from "express";

let api = express.Router();

const initApi = async (app) => {
  app.set("json spaces", 2);
  app.use("/api", api);
};

api.use(bodyParser.json());
api.use(cors());

api.use((req, res, next) => {
  console.log(`${req.method} ${req.originalUrl}`);
  next();
});

api.get("/", (req, res) => {
  res.json({ message: "Hello, world!" });
});

api.get("/profiles/:id", (req, res) => {
  let id = req.params.id;
  res.json({ id, name: id });
});

/* Catch-all route to return a JSON error if endpoint not defined */
api.all("/*", (req, res) => {
  res.status(404).json({ error: `Not found: ${req.method} ${req.url}` });
});

export default initApi;
