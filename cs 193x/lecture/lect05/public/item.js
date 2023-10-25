export default class Item {
  constructor(summary) {
    this._handleDel = this._handleDel.bind(this);

    this._elem = document.createElement("li");
    this._elem.textContent = summary;
    let delBtn = document.createElement("button");
    delBtn.textContent = "Delete";
    delBtn.addEventListener("click", this._handleDel);
    /* Order matters: setting textContent also removes children */
    this._elem.append(delBtn);
  }

  /* list is a list element to append the item to */
  /* onDelete is a function that we will call when the user clicks the Delete button */
  addToList(list, onDelete) {
    list.append(this._elem);
    /* Store the callback function so we can use it when removing */
    this._onDelete = onDelete;
  }

  /* We don't want to call onDelete if the client asks us to remove ourselves, because this creates a "cycle" */
  removeFromList() {
    this._elem.remove();
  }

  _handleDel() {
    this.removeFromList();
    /* If client gave us a callback, call it with ourselves as instnace, so they know which item got deleted */
    if (this._onDelete) this._onDelete(this);
  }
}
