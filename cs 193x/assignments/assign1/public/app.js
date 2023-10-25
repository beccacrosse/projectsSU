/* This class handles user interaction with the student and declare classes through intervention by the server*/
import Student from "./student.js";
import Department from "./dept.js";

export default class App {
  constructor(userSunet, userDept) {
    this.students = {}; //sunet:student
    this.depts = {}; // dept code: dept66
    // for interaction with the website
    this._declareBtn = document.forms.interaction.declareBtn;
    this._gradBtn = document.forms.interaction.graduateBtn;
    // set listeners and bindings for user interaction with the declare and grad buttons
    this._handleDeclare = this._handleDeclare.bind(this); //ties function to the insrance of the app
    this._handleGraduate = this._handleGraduate.bind(this);
    this._declareBtn.addEventListener("click", this._handleDeclare);
    this._gradBtn.addEventListener("click", this._handleGraduate);
  }

  /* This function resets any past data in this.students and this.depts variables, before filling them with updated instances of information using inputed data*/
  loadData(data) {
    // First, reset the students and depts instance variables to be empty. This allows loadData to "reset" the app.
    this.students = {};
    this.depts = {};
    // iterate through students
    for (let i=0; i < data.students.length; i++) {
      const currStudent = data.students[i];
      // Populate the students map with new Student instances, using the students data. sunet, givenName, surname
      let newStudent = new Student(currStudent.sunetid, currStudent.givenName, currStudent.surname);
      // update student's units
      newStudent.addUnits(data.units[currStudent.sunetid]);
      // add student object to this.students.
      this.students[newStudent.sunetid] = newStudent;
    } // now update the departments
    for (let i=0; i<data.depts.length; i++) {
      let currDpt = data.depts[i];
      // create a new department with updated values and add it to depts
      let currEntry = new Department(currDpt.name, currDpt.code);
      this.depts[currEntry.code] = currEntry;
    }
  }


  /* This funtion takes a SUNetID and department code (both strings) and tries to declare that student under that department, then returns the (updated) Student instance. If the SUNetID or department code isn't known to the app, it will throw an Error with a descriptive message. */
  declare(sunetid, deptCode) {
    let student = this.students[sunetid];
    const dept = this.depts[deptCode];
    if (dept === null || student===null ) {
      throw new Error("Unable to process request because SUNetID or department code not found");
    } else {
      // declare students within the department
      dept.declare(student);
      return student;
    }
  }

  /* Makes the department specified by the passed-in code try to graduate its students, returning the list of graduates (Student instances). If the department code doesn't match a known department, throw an Error with a descriptive message.*/
  graduate(deptCode) {
    let department = this.depts[deptCode];
    if (!department) {
      throw new Error("Department not found.");
    }
    const graduates = department.graduate();
    return graduates;
  }

  /* This function handles server request of the declare button*/
  _handleDeclare() {
    let userSunet = document.forms.interaction.sunetInput.value;
    let userDept = document.forms.interaction.deptCodeInput.value;
    try {
      this.declare(userSunet, userDept);
      alert(`${this.students[userSunet]} just declared ${this.depts[userDept]}}` );
    } catch (e) { // if declaration fails, display an alert
      alert(e.message);
    }
  }
  /* This function handles server request of the graduate button*/
  _handleGraduate() {
    let userDept = document.forms.interaction.deptCodeInput.value;
    try {
      let graduates = this.graduate(userDept);
      alert(`Graduates: ${graduates}`);
    } catch (e) { // if graduate fails, display an alert
      alert(e.message);
    }
  }
}
