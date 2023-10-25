import Item from "./item.js";

class List {
  constructor() {
    this._handleAdd = this._handleAdd.bind(this);

    this._form = document.forms.additem;
    //this._form.add.addEventListener("click", this._handleAdd); //bind dis above
    this._form.addEventListener("submit", this._handleAdd) //bind dis above
  }

  _handleAdd(event) {
    event.preventDefault(); // don't send info to server and refresh the page

    let summary = this._form.item.value; // get to text inside of the form item
    // let item = document.createElement("li"); V replaced by that
    let item = new item(summary); // create an item object from user's text
    //item.textContent = summary;
    let list = document.body.children.list; // add list to the body of the viewable webpage
    //list.add()
    this._form.reset();
    console.log("Clicked");
  }
}
new List();
