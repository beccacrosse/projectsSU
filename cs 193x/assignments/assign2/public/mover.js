/* Text to add to the move here button */
const MOVE_HERE_TEXT = "— Move here —";

export default class Mover {
  constructor() {
    // keep track of the card is being moved
    this.card = null;
    this.currentlyMoving = false;
    // make moving button handler
    this._handleMoveButton = this._handleMoveButton.bind(this);
  }

  // Marks a card as selected and shows the "Move Here" buttons. card is the card's element (i.e. the <article> element, not the Card instance).
  startMoving(card) {
    // make sure no other cards are being edited
    if (this.currentlyMoving = true) {
      this.stopMoving();
    }
    this.currentlyMoving = true;
    // Wwen the user clicks a card's move button, give the card the (CSS) class "moving".
    this.card = card;
    this.card.classList.add("moving");
    // add a button after each columnTitle
    let board = document.querySelector("#board");
    let columns = board.querySelectorAll(".column");
    // add buttons below every column
    for (let i = 0; i < columns.length; i++) {
      let button = document.createElement("button");
      button.classList.add("moveButton");
      button.textContent = MOVE_HERE_TEXT;
      button.addEventListener("click", this._handleMoveButton);
      columns[i].querySelector(".columnTitle").after(button);
    }
    // now add buttons below every card
    let cards = board.querySelectorAll(".card");
    for (let i = 0; i < cards.length; i++) {
      let currCard = cards[i];
      let button = document.createElement("button");
      button.classList.add("moveButton");
      button.textContent = MOVE_HERE_TEXT;
      currCard.after(button);
      // add a lil event listener too
      button.addEventListener("click", this._handleMoveButton);
    }
  }

  _handleMoveButton(event) {
    // When the user clicks on a move here button, move the selected card from its current position to where the clicked button is.
    event.currentTarget.after(this.card);
    // The card stops being selected, and all move here buttons are removed.
    let buttons = document.querySelectorAll(".moveButton");
    for (let i = 0; i < buttons.length; i++) {
      buttons[i].remove();
    }
    this.card.classList.remove("moving");
    //this.card = null;
  }

  // Called when another class wants to ensure no card is being moved, e.g. because a card is being added or deleted.
  stopMoving() {
    // if there is a card selected for moving, remove the moving class from that card
    if (this.card === null) {
      return;
    } else {
      // stop the other card from moving
      this.card.classList.remove("moving");
      // remove the move here buttons for that card which is no longer moving (reset instartMoving())
      let buttons = document.querySelectorAll(".moveButton");
      for (let i = 0; i < buttons.length; i++) {
        buttons[i].remove();
      }
      // communicate that we are no longer moving
      this.currentlyMoving = false;
    }
  }
}
