import Card from "./card.js";
import Mover from "./mover.js";

export default class App {
  constructor() {
    // add event handlersand variables for the values we'll want to access later
    this.submitHandler = this.submitHandler.bind(this); // bind event handler
    this.addCard= this.addCard.bind(this); //bind addcard
    this.cardForm = document.querySelector("#addCard");
    this.titleBox = this.cardForm.querySelector("#cardTitle");
    this.colorBox = this.cardForm.querySelector("#cardColor");
    this.mover = new Mover();
    //now add listeners to the add button and each of the input boxes
    this.cardForm.addEventListener("submit", this.submitHandler);
  }

  submitHandler(event) {
    // prevent submit from auto refreshing and call card creating functions
    event.preventDefault();
    let titleText = this.titleBox.value;
    let colorText = this.colorBox.value;
    this.addCard("todo", titleText, colorText);
  }

  addCard(col, title, color) {
    // create a new card!
    let newCard = new Card(title, color);
    let colElem = document.querySelector("#"+ col);
    newCard.addToCol(colElem, this.mover);
    // now make the text boxes empty again
    this.titleBox.value = "";
    this.colorBox.value = "";
    return newCard;
  }
}
