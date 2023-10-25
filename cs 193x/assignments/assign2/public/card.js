/* The text to use when description is empty */
const NO_DESCRIPTION_TEXT = "(No description)";

export default class Card {
  constructor(title, color) {
    //store mover
    this.mover;
    // clone the template
    let template = document.querySelector(".template.card");
    this.card = template.cloneNode(true);
    // reset variables
    this.card.classList.remove("template");
    this.card.querySelector(".title").textContent = title;
    this.setDescription("");
    this.card.style.backgroundColor = color; //set the entire card form to have the same color
    // make an event handler for edit
    this._handleEdit = this._handleEdit.bind(this);
    this.edit = this.card.querySelector(".edit"); // get edit button
    this.edit.addEventListener("click", this._handleEdit);
    // create a handler to stop editing & bind them
    this._stopEditing = this._stopEditing.bind(this);
    let hiddenText = this.card.querySelector(".editDescription");
    hiddenText.addEventListener("blur", this._stopEditing); // stop editing when click elsewhere
    //make event handler for delete
    this._handleDelete = this._handleDelete.bind(this);
    this.delete = this.card.querySelector(".delete"); //get delete
    this.delete.addEventListener("click", this._handleDelete);
    // make event handler for mover
    this._handleMove = this._handleMove.bind(this);
    this.moveButton = this.card.querySelector(".startMove"); //get delete
    this.moveButton.addEventListener("click", this._handleMove);
  }

  // when user clicks the edit button
  _handleMove() {
    // pass in the cards article.
    this.mover.startMoving(this.card);
  }

  // when user clicks the edit button
  _handleEdit() {
    // hide the current description
    ("inside the edit!");
    let description = this.card.querySelector(".description");
    description.classList.add("hidden");
    // show the <textarea> to let them enter a new description.
    let hiddenText = this.card.querySelector(".editDescription");
    hiddenText.classList.remove("hidden");
    // The text box should be filled in with the current description (which may be empty)
    if (this.card.querySelector(".description").textContent === NO_DESCRIPTION_TEXT) {
      hiddenText.value = "";
    } else {
      hiddenText.value = this.card.querySelector(".description").textContent;
    }
    hiddenText.value = this.card.querySelector(".description").textContent;
    // It should be focused, with all text selected at the start
    hiddenText.select();
    hiddenText.focus();
    // me 115 intro to design?
  }

  _stopEditing() {
    // set the card's description to what the user entered
    let description = this.card.querySelector(".description");
    let hiddenText = this.card.querySelector(".editDescription");
    let updatedText = hiddenText.value;
    description.textContent = updatedText;
    // return the card to its normal state (text box hidden, description shown)
    description.classList.remove("hidden");
    hiddenText.classList.add("hidden");
    ("stop edit called");
  }

  _handleDelete() {
    // Clicking on the delete button for a card removes it from the board.
    this.card.remove();
  }

  addToCol(colElem, mover) {
    //take column and append to that column
    this.mover = mover;
    colElem.append(this.card);
  }

  // set the shown descriptions text to be what the user inputed
  setDescription(text) {
    if (text === "") {
      this.card.querySelector(".description").textContent = NO_DESCRIPTION_TEXT;
    } else {
      this.card.querySelector(".description").textContent = text;
    }
  }
}
