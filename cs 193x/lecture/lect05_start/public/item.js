export default class Item {
  constructor(summary) {
    this._elem = document.createElement("li");
    this._elem.textContent = summary;
    this._handleDel = this._handleDel.bind(this);
    let delBtn = document.createElement("button");
    delBtn.textContent = "Delete";
    delBtn.AddEventListener("click", this._handleDel);
    // order matters: setting textContent removes children
    this._elem.append(delBtn);

    document.querySelector("#clearlist").addEventListener("click", this._handleClear); //<- finds first thing called clearlist
  }

  handleClear(){
    for(let item of this._items) {
      item.removeFromList();
    }
    this.items=[];
    alert(`Removed ${this._items.length} items`);
  }

  //
  addToList(list) {
    list.append(this._elem);
  }

  _handleDel() {
    this._elem.remove(this._elem);
  }
}
