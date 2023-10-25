import Student from "./student.js";

export default class App {
  constructor() {
    this._onList = this._onList.bind(this);
    this._onLoad = this._onLoad.bind(this);
    this._onUpdate = this._onUpdate.bind(this);
    this._onGraduate = this._onGraduate.bind(this);


    let b = document.querySelector("#load");
    b.addEventListener("click", this._onLoad);
    b = document.querySelector("#list");
    b.addEventListener("click", this._onList);
    b = document.querySelector("#update");
    b.addEventListener("click", this._onUpdate);
    b = document.querySelector("#graduate");
    b.addEventListener("click", this._onGraduate);

    this._student = null;
  }

  async _onLoad(event) {
    let id = prompt("Student ID:");
    try {
      let s = await Student.load(id); /* calling this directly on student class, not creating a new Student*/
      this._student = s;
      this._showStudent();
    } catch (e){
      this._setResults(e.message); // show error message if not viable
    }

  }

  async _onList() {
    let query = prompt("Search");
    console.log(await Student.list(query));
  }

  async _onUpdate() {
    await this._student.declare("CS"); /* interact with server. server is remembering which may effect results */
    this._showStudent(); /* update reslts shown in DOM */
  }

  async _onGraduate() {
    await this._update
  }

  _showStudent() {
    let s = this._student;
    if (!s) {
      this._setResults("No student loaded");
      return;
    }
    let str = `ID: ${s.id}\nName: ${s.givenName} ${s.surname}\nDept: ${s.dept}\nUnits: ${s.unitsCompleted}\nAlum? `;
    str += s.isAlum ? "Yes" : "No";
    this._setResults(str);
  }

  _setResults(text) {
    document.querySelector("#results").textContent = text;
  }
}
