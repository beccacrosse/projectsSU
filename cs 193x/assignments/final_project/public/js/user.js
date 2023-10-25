import apiRequest from "./apirequest.js";

/* A small data model to represent a Post. */
export class Post {
  /* data is the post data from the API. */
  constructor(data) {
    /* Technically we don't have a full User object here (no followers list), but this is still useful. */
    this.user = new User(data.user);
    this.time = new Date(data.time);
    this.text = data.text;
  }
}

/* A data model representing a user of the app. */
export default class User {
  /* Returns an array of user IDs. */
  static async listUsers() {
    let data = await apiRequest("GET", "/users");
    return data.users;
  }

  /* Returns a User instance, creating the user if necessary. */
  static async loadOrCreate(id) { // static methds can be called on the class.
    // This static method looks up a user. If the user doesn't exist, they are created. Returns a User instance for the found or created user
    let userObject = null;
    // request a user from our API
    try {
      let user = await apiRequest("GET", `/users/${id}`);
      userObject = new User(user);
    } catch (e) { // if user doesn't exist
      let user = await apiRequest("POST", `/users`, { "id": id }); // create new user in api
      user = await apiRequest("PATCH", `/users/${id}`); // update that user in api?
      userObject = new User(user); // create actual user object
    }
    return userObject;
  }

  /* data is the user object from the API. */
  constructor(data) {
    //Creates a new instance, using the data returned by the backend for a user.
    // The keys from the API are set as (public) instance variables, e.g. id, name, etc. You can initialize any private instance variables here as well
    this.name = data.name;
    this.id = data.id;
    this.avatarURL = data.avatarURL;
    this.color = data.color;
  }

  /* The string representation of a User is their display name. */
  toString() {
    return this.name;
  }

  /* Returns an Object containing only the instances variables we want to send back to the API when we save() the user. */
  toJSON() {
    //This special method tells JavaScript how to convert an object to JSON. It returns a (plain) JavaScript object (i.e. a map) with the key/value pairs you want included in the JSON.
    return { "id": this.id, "name": this.name, "avatarURL": this.avatarURL, "color": this.color };
  }

  /* Save the current state (name and avatar URL) of the user to the server. this means a post/patch is necessary? */
  async save() {
    //(By convention / for debugging, you may want to include the id in this representation, even though the API ignores it.
    await apiRequest("PATCH", `/users/${this.id}`, this);
  }

  /* Gets the user's current feed. Returns an Array of Post objects. */
  async getFeed() {
    // get current feed. // api returns object. value of "posts" key is an array of post objects
    let feed = await apiRequest("GET", `/users/${this.id}/feed`);
    feed = feed.posts;
    let feedPosts = [];
    for (let i = 0; i< feed.length; i++) {
      feedPosts[i] = new Post(feed[i]);
    }
    return feedPosts;
  }

  /* Create a new post with hte given text. */
  async makePost(text) {
    //Make a post as this user, with the text text
    await apiRequest("POST", `/users/${this.id}/posts`, { "text": text });
  }
}
