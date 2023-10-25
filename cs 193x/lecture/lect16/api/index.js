import bodyParser from "body-parser";
import cors from "cors";
import crypto from "crypto";
import express from "express";
import jwt from "jsonwebtoken";
import { OAuth2Client } from "google-auth-library";
import { MongoClient } from "mongodb";

/* Secret used for signing tokens */
const SECRET = "my secret string";

/* Make sure to get your own client ID. This one will be deleted soon */
const CLIENT_ID = "723067440195-7v0ubvrf42s0jett61jspf4jtiqk57ce.apps.googleusercontent.com";

let api = express.Router();
let Users;

const initApi = async (app) => {
  app.set("json spaces", 2);
  app.use("/api", api);

  let conn = await MongoClient.connect("mongodb://127.0.0.1");
  let db = conn.db("lect16_db");
  Users = db.collection("users");
};

api.use(bodyParser.json());
api.use(cors());

api.get("/", (req, res) => {
  res.json({ message: "Hello, world!" });
});

api.post("/login", async (req, res) => {
  let { email, password } = req.body;
  let user = await Users.findOne({ email, type: "password" });
  console.log("User document:", user);

  let hash = crypto.createHash("sha256");

  if (!user) { /* New user */
    let salt = crypto.randomBytes(8).toString("base64");
    hash.update(salt);
    hash.update(password);
    let hashedPassword = hash.digest("base64");
    await Users.insertOne({ email, name: "Unknown", salt, hashedPassword, type: "password" });
    user = await Users.findOne({ email });
  } else { /* Existing user */
    hash.update(user.salt);
    hash.update(password);
    let hashedPassword = hash.digest("base64");
    if (hashedPassword !== user.hashedPassword) {
      res.status(403).json({ error: "Wrong password" });
      return;
    }
  }

  let apiKey = jwt.sign({ email: user.email }, SECRET, { expiresIn: "1d" });
  res.json({ email: user.email, apiKey });
});

api.post("/google", async (req, res) => {
  let { idToken } = req.body;
  let client = new OAuth2Client();
  let data;
  try {
    /* "audience" is the client ID the token was created for. A mismatch would mean the user is
       trying to use an ID token from a different app */
    let login = await client.verifyIdToken({ idToken, audience: CLIENT_ID });
    data = login.getPayload();
  } catch (e) {
    res.status(403).json({ error: e.message });
    return;
  }

  let user = await Users.findOne({ email: data.email, type: "google" });
  if (!user) {
    await Users.insertOne({ email: data.email, name: data.name, type: "google" });
    user = await Users.findOne({ email: data.email, type: "google" });
  } else {
    user.name = data.name;
    await Users.replaceOne({ _id: user._id }, user);
  }
  let apiKey = jwt.sign({ email: user.email }, SECRET, { expiresIn: "1d" });
  res.json({ email: user.email, apiKey });
});

const checkAuth = async (req, res, next) => {
  let [type, key] = req.header("Authorization").split(" ");
  if (type !== "Bearer") {
    /* Not a recognized type. */
    res.status(401).json({ error: "Unrecognized Authorization header" });
    return;
  }

  try {
    let verified = jwt.verify(key, SECRET);
    res.locals.user = await Users.findOne({ email: verified.email });
    if (!res.locals.user) {
      res.status(403).json({ error: "User doesn't exist" });
      return;
    }
    next();
  } catch (e) {
    console.warn(e);
    res.status(403).json({ error: "Access denied" });
  }
}

api.get("/protected", checkAuth, async (req, res) => {
  let user = res.locals.user;
  res.json({ message: `Logged in as ${user.name} <${user.email}>` });
});

/* Catch-all route to return a JSON error if endpoint not defined */
api.all("/*", (req, res) => {
  res.status(404).json({ error: `Not found: ${req.method} ${req.url}` });
});

export default initApi;
