//TODO: Write Department class here

export default class Department {
  constructor(name, code) {
    this.name = name;
    this.code = code;
    this.students = [];
  } //Construct a new department with the name and code passed in. Departments start with no current students

  //Returns the string representation of the department, which is just the department's name.
  toString() {
    return this.name;
  }

  /*Declares the passed-in Student instance under this department, updating the student's and department's instance variables accordingly. If the student is already declared under this department, this method will return without doing anything. But if the student is already declared under a different department, this method will throw an Error with a descriptive error message.*/
  declare(student) {
    if (student.dept !=null) {
      if ( student.dept != toString()) { // if student is declared, but not to this department, throw an error
        throw new Error("Action cannot be completed because you have already declared with another department. silly!");
      }
      return;
    } // update and push variables
    student.dept = this.toString();
    this.students.push(student);
    return;
  }

  /*Check if each current student in the department can graduate; if they can, mark them as an alum and remove them from the list of current students. Return an array of the just-graduated Student instances.*/
  graduate() {
    let graduated = [];
    for (let i=0; i< this.students.length; i++) {
      let student = this.students[i];
      if (student.canGraduate()) {
        student.isAlum = true;
        const index = this.students.indexOf(student);
        this.students.splice(index, 1); //remove from students list
        graduated.push(student); //add to graduated
      }
    }
    return graduated;
  }
}
