import Item from "./item.js";

class List {
  constructor() {
    this._handleAdd = this._handleAdd.bind(this);
    this._handleRemove = this._handleRemove.bind(this);
    this._handleClear = this._handleClear.bind(this);

    this._items = [];
    this._form = document.forms.additem;

    // Instead of:
    //this._form.add.addEventListener("click", this._handleAdd);
    // Recommended:
    this._form.addEventListener("submit", this._handleAdd);

    document.querySelector("#clearlist").addEventListener("click", this._handleClear);
  }

  _handleClear() {
    alert(`Removing ${this._items.length} items`);
    for (let item of this._items) {
      item.removeFromList();
    }
    this._items = [];
  }

  _handleAdd(event) {
    event.preventDefault();
    
    let summary = this._form.item.value;

    // Before Item class:
    //let item = document.createElement("li");
    //item.textContent = summary;
    //document.body.children.list.append(item);

    let item = new Item(summary);
    let list = document.body.children.list;
    item.addToList(list, this._handleRemove);
    this._items.push(item);
    this._form.reset();
  }

  _handleRemove(item) {
    this._items.splice(this._items.indexOf(item), 1);
  }
}
new List();
