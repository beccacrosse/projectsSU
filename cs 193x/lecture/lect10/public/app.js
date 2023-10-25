import Student from "./student.js";

export default class App {
  constructor() {
    this._onClickBetter = this._onClickBetter.bind(this);


    let button = document.querySelector("#button");
    button.addEventListener("click", this._onClickBetter);
  }

  async _onClickBetter(event) {
    // let res = await fetch("/api/text");
    // let text = await res.text();
    // let res2 = await fetch("/api/students/mchang");
    // let obj = await res2.json();
    // console.log(obj);
    // let s = `${text}\n${obj.givenName} ${obj.surname}`;
    // document.querySelector("#results").textContent = s;

    // let res = await fetch("/api/students/mchang");
    // let obj = await res.json();
    // let student = new Student(obj);
    // console.log(student);

    // let s = new Student("mchang");
    let s = await Student.load("mchang");
    // let courses = await s.listCourses();
    // console.log(courses);
    await s.declare("CS");
    console.log(s);
  }
}
