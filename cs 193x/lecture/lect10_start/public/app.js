import Student from "./student.js";

export default class App {
  constructor() {
    //this._onClick = this._onClick.bind(this);
    this._onClickBetter = this._onClickBetter.bind(this);


    let button = document.querySelector("#button");
    button.addEventListener("click", this._onClickBetter);
  }

  async _onClickBetter(event) {
    let res = await fetch("/api/text"); //goes till sleep till everything is done
    let text = await res.text();
    let res2 = await fetch("/api/studnts/mchang"); // this path doesnt exist yet but server creates a fake file at /api/studnts/mchang using info that may be at other places? 
    let obj = await res2.json();
    let s = `${text}\n${obj.givenName} ${obj.surname}`;
    document.querySelector("#results").textContent = s;
  }
}
