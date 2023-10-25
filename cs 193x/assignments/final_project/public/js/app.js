import User, { Post } from "./user.js";

export default class App {
  constructor() {
    /* Store the currently logged-in user. */
    this._user = null;
    // query select different parts of the page
    this._loginForm = document.querySelector("#loginForm");
    this._logoutButton = document.querySelector("#logout");
    this._postForm = document.querySelector("#postForm");
    this._sidebar = document.querySelector("#sidebar");
    this._colors = this._sidebar.querySelector("#colorbuttons");

    // bind event handlers
    this._onListUsers = this._onListUsers.bind(this);
    this._onLogin = this._onLogin.bind(this);
    this._onLogout = this._onLogout.bind(this);
    this._onPost = this._onPost.bind(this);
    this._onEditName = this._onEditName.bind(this);
    this._onEditUrl = this._onEditUrl.bind(this);
    // buttons for color changing
    this._handlePink = this._handlePink.bind(this);
    this._handlePurple = this._handlePurple.bind(this);
    this._handleGreen = this._handleGreen.bind(this);
    this._handleBlue = this._handleBlue.bind(this);
    this._handleYellow = this._handleYellow.bind(this);
    this._handleDark = this._handleDark.bind(this);

    this._loginForm.listUsers.addEventListener("click", this._onListUsers);
    this._loginForm.addEventListener("submit", this._onLogin);
    this._logoutButton.addEventListener("click", this._onLogout);
    this._postForm.addEventListener("submit", this._onPost);
    this._sidebar.querySelector("#nameForm").addEventListener("submit", this._onEditName);
    this._sidebar.querySelector("#avatarForm").addEventListener("submit", this._onEditUrl);
    // add event listeners for colors
    this._colors.querySelector("#pink").addEventListener("click", this._handlePink);
    this._colors.querySelector("#purple").addEventListener("click", this._handlePurple);
    this._colors.querySelector("#green").addEventListener("click", this._handleGreen);
    this._colors.querySelector("#blue").addEventListener("click", this._handleBlue);
    this._colors.querySelector("#yellow").addEventListener("click", this._handleYellow);
    this._colors.querySelector("#dark").addEventListener("click", this._handleDark);
  }

  /*** Event handlers ***/

  async _onListUsers() {
    let users = await User.listUsers(); // call listusers when it hs the info for it
    let usersStr = users.join("\n"); // add newlines to the list
    alert(`List of users:\n\n${usersStr}`); // show users as an alert
  }

  // Create event handlers/callback functions here
  async _onLogin(event) {
    event.preventDefault();
    // update current user and load their profile
    let id = this._loginForm.userid.value;
    this._user = await User.loadOrCreate(id);
    await this._loadProfile();
  }

  async _handlePink(event) {
    let pink = "lavenderblush";
    this._user.color = pink;
    await this._user.save();
    await this._loadProfile();
  }
  async _handlePurple(event) {
    let purple= "lavender";
    this._user.color = purple;
    await this._user.save();
    await this._loadProfile();
  }
  async _handleGreen(event) {
    let green = "honeydew";
    this._user.color = green;
    await this._user.save();
    await this._loadProfile();
  }
  async _handleBlue(event) {
    let blue = "paleturquoise";
    this._user.color = blue;
    await this._user.save();
    await this._loadProfile();
  }
  async _handleYellow(event) {
    let yellow = "lemonchiffon";
    this._user.color = yellow;
    await this._user.save();
    await this._loadProfile();
  }
  async _handleDark(event) {
    let dark = "SlateGrey";
    this._user.color = dark;
    await this._user.save();
    await this._loadProfile();
  }

  async _onEditName(event) {
    event.preventDefault();
    // update values
    let newName = this._sidebar.querySelector("#nameForm").querySelector("#nameInput").value;
    this._user.name = newName;
    await this._user.save(); // save changed info
    await this._loadProfile();
  }

  async _onEditUrl(event) {
    event.preventDefault(); // prevent from reloading back to te default login screen
    // update values
    let newAvi = this._sidebar.querySelector("#avatarForm").querySelector("#avatarInput").value;
    this._user.avatarURL = newAvi;
    await this._user.save(); // save changed info
    await this._loadProfile();
  }

  async _onPost(event) { // add post to feed
    event.preventDefault();
    // create a post and load changes
    let text = this._postForm.querySelector("#newPost").value;
    await this._user.makePost(text);
    await this._loadProfile();
  }


  /*** Helper methods ***/

  /* Add the given Post object to the feed. */
  _displayPost(post) {
    /* Make sure we receive a Post object. */
    if (!(post instanceof Post)) throw new Error("displayPost wasn't passed a Post object");

    // clone the template post
    let elem = document.querySelector("#templatePost").cloneNode(true);
    elem.id = "";
    // get info about the avatar
    let avatar = elem.querySelector(".avatar");
    avatar.src = post.user.avatarURL;
    avatar.alt = `${post.user}'s avatar`;

    // put info into cloned template
    elem.querySelector(".name").textContent = post.user;
    elem.querySelector(".userid").textContent = post.user.id;
    elem.querySelector(".time").textContent = post.time.toLocaleString();
    elem.querySelector(".text").textContent = post.text;

    document.querySelector("#feed").append(elem); // add new post to feed
  }

  async _onLogout() {
    document.querySelector("#welcome").classList.remove("hidden");
    document.querySelector("#main").classList.add("hidden");
    //document.querySelector("#idContainer").textContent = this._user.id;
    // make logout button and unhide it
    this._logoutButton.classList.add("hidden");
    this._loginForm.classList.remove("hidden");
  }

  /* Load (or reload) a user's profile. Assumes that this._user has been set to a User instance. The _loadProfile helper method has been started. It fills in the user ID in the sidebar and the parts of the new post form, as well as wiping out the current feed.*/
  async _loadProfile() {
    document.querySelector("#welcome").classList.add("hidden");
    document.querySelector("#main").classList.remove("hidden");
    document.querySelector("#idContainer").textContent = this._user.id;
    // make logout button and unhide it
    this._logoutButton.classList.remove("hidden");
    this._loginForm.classList.add("hidden");
    /* Reset the feed. */
    document.querySelector("#feed").textContent = "";

    /* Update the avatar, name, and user ID in the new post form */
    this._postForm.querySelector(".avatar").src = this._user.avatarURL;
    this._postForm.querySelector(".name").textContent = this._user;
    this._postForm.querySelector(".userid").textContent = this._user.id;
    // add color to the page
    let color = String(this._user.color);
    document.body.querySelector("#main").style.backgroundColor = color;
    document.body.querySelector("#header").style.backgroundColor = color;
    // document.body.style.backgroundColor = color;

    // Update feed panel to show the posts by the users from newest to oldest.
    let feed = await this._user.getFeed();
    for ( let i=0; i < feed.length; i++ ) {
      this._displayPost(feed[i]);
    }
  }
}
