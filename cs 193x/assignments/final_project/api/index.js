import bodyParser from "body-parser";
import cors from "cors";
import express from "express";
import { MongoClient } from "mongodb";

/* Be sure to use DATABASE_NAME in your call to .db(), so we can change the constant while grading. */
let DATABASE_NAME = "cs193x_assign3";

/* Do not modify or remove this line. It allows us to change the database for grading */
if (process.env.DATABASE_NAME) DATABASE_NAME = process.env.DATABASE_NAME;

let api = express.Router();

let Users;
let Posts;

/*
Implement a REST API using Node and Express: create api routes,
Store and retrieve data in a MongoDB database,
Work with an API specification from an implementer's perspective, and
Integrate and test an API with an existing frontend.
*/


const initApi = async (app) => {
  app.set("json spaces", 2);
  app.use("/api", api);

  //TODO: Set up database connection and collection variables
  let conn = await MongoClient.connect("mongodb://127.0.0.1");
  let db = conn.db(DATABASE_NAME);
  // add collections
  Users = db.collection("users");
  Posts = db.collection("posts");
};


/* Interpret request bodies as JSON and store them in req.body */
api.use(bodyParser.json());
api.use(cors());

api.get("/", (req, res) => {
  res.json({ message: "API is running" });
});

/*** Test routes ***/

api.get("/tests/get", (req, res) => {
  let value = req.query.value || null;
  res.json({ success: true, value });
});

api.post("/tests/post", (req, res) => {
  let value = req.body.value || null;
  res.json({ success: true, value });
});

api.get("/tests/error", (req, res) => {
  res.status(499).json({ error: "Test error" });
});

api.all("/tests/echo", (req, res) => {
  res.json({
    method: req.method,
    query: req.query,
    body: req.body
  });
});

/*** Generic Social Media API ***/

api.get("/", (req, res) => {
  let data = { "db": DATABASE_NAME, "numUsers": Users.length, "numPosts": Posts.length };
  res.json(data);
});

// Middleware function called for all requests starting with /users/:id
api.use("/users/:id", async (req, res, next) => {
  let id = req.params.id;
  let allUsers = await Users.find().toArray();
  let user = null;
  // loop through students and identify if a matching user is found
  for ( let currUser of allUsers) {
    if (currUser.id === id) {
      user = { "id": id, "name": currUser.name, "avatarURL": currUser.avatarURL, "color": currUser.color };
      res.locals.user = user; // udate user and status
      res.status(200);
      next(); // calls handler after the middleware
      return;
    }
  }
  // if no student is found throw an error
  if ( user === null) {
    res.status(404);
    res.json({ "error": `User ${id} not found` });
    return;
  }
});


// display id of all users on the webpage
api.get("/users", async (req, res) => {
  //loop thru users and put them in a printable format
  let allUsers = await Users.find().toArray();
  let users = [];
  console.log("allusers in get/users");
  console.log(allUsers);
  for ( let user of allUsers) {
    users.push(user.id);
  }
  //Returns: An object with a single key, users, mapping to an array of user IDs.
  res.json({ "users": users });
});


// GET /users/:id API Call. get a certain user by their id
api.get("/users/:id", (req, res) => {
  let user = res.locals.user;
  res.json(user);
});


// create a new user and add it to the database
api.post("/users", async (req, res) => {
  let id = req.body.id;
  // if user is already found return status 400
  let allUsers = await Users.find().toArray();
  for ( let currUser of allUsers) {
    if (currUser.id === id) {
      res.status(400);
      res.json( { "error": `user ${id} already exists` } );
      return;
    }
  }
  // if invalid id set status 400
  if (id === null) {
    res.status(400);
    res.json({ "error": `no valid user id was included` });
  } else { // otherwise create this user and insert them into the database
    let user = { "id": id, "name": id, "avatarURL": "images/default.png", "color": "light pink" };
    await Users.insertOne(user);
    //delete user._id;
    res.json(user);
    res.status(200);
  }
});

// PATCH /users/:id. Make changes to a user
api.patch("/users/:id", async (req, res) => {
  let user = res.locals.user;
  if (req.body.name !== undefined ) {
    user.name = req.body.name;
    // qeury of object wed like to find, replacement
  }
  if (req.body.avatarURL !== undefined) {
    user.avatarURL = req.body.avatarURL;
    // qeury of object wed like to find, replacement
  }
  if (req.body.color !== undefined) {
    user.color = req.body.color;
    // qeury of object wed like to find, replacement
  }
  await Users.replaceOne({ id: user.id }, user);
  res.status(200);
  console.log("user in patch user");
  console.log(user);
  res.json(user);
});


// POST /users/:id/posts... create a new post for the user
api.post("/users/:id/posts", async (req, res) => {
  if (req.body.text === undefined || req.body.text === null || req.body.text === "") {
    res.json({ "error": "no text was included" });
  } else {
    // create a new post and add it to the posts database
    let user = res.locals.user;
    let text = req.body.text;
    let date = new Date();
    let post = { userId: user.id, time: date, text: text };
    await Posts.insertOne(post);
    res.json({ "success": true });
  }
});

// GET /users/:id/feed. Get feed posts for the specified user
api.get("/users/:id/feed", async (req, res) => {
  let user = res.locals.user;
  // create feedposts object of posts by current user
  let feedposts = await Posts.find( { userId: { $in: [user.id] } }).toArray();
  // now sort the feed by date
  feedposts.sort((a, b) => {
    if (a.date > b.date) {
      return a;
    } else {
      return b;
    }
  });
  let feed = [];
  let size = feedposts.length;
  // loop through each posts, reformat it, and add to feed
  for (let i=0; i <size; i++) {
    let currPost = feedposts[i];
    let time = currPost.time;
    let text = currPost.text;
    let post = { "user": user, "time": time,
      "text": text };
    feed.push(post);
  }
  res.json({ "posts": feed });
});


/* Catch-all route to return a JSON error if endpoint not defined.
   Be sure to put all of your endpoints above this one, or they will not be called. */
api.all("/*", (req, res) => {
  res.status(404).json({ error: `Endpoint not found: ${req.method} ${req.url}` });
});

export default initApi;
