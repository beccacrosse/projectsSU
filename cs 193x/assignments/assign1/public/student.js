/*This class holds the following..
sunetid: The student's SUNetID
givenName: The student's given name
surname: The student's surname
dept: The name of the department the student is declared in (a string), or null if the student has not declared yet
unitsCompleted: The number of units the student has completed (a number)
isAlum: true if the student has graduated, false if not
An instance has the following methods (with corresponding signatures):*/

export default class Student {
  constructor(sunet, givenName, surname) {
    this.sunetid = sunet;
    this.givenName = givenName;
    this.surname = surname;
    this.dept = null;
    this.unitsCompleted = 0;
    this.isAlum = false;
  }


  fullName() {
    /*Return the student's full name, which is their given name, followed by a space, followed by their surname.*/
    return this.givenName + " " + this.surname;
  }


  addUnits(units) {
    /*Increase the number of units the student has completed by the parameter units*/
    this.unitsCompleted+= units;
  }


  toString() {
    /*Return a string representing the student, which should be their given name, a space, their surname, another space, and their SUNetID in parentheses. (For example, "Michael Chang (mchang91)")*/
    return this.givenName + " " + this.surname + " (" + this.sunetid + ")";
  }


  canGraduate() {
    /*Return a boolean indicating whether the student can graduate. A student can graduate if they have declared and have completed at least 180 units. If the student has already graduated, this method should throw an Error with a descriptive message.*/
    if (this.isAlum) {
      throw new Error("This request cannot be completed because you have already graduated silly");
    }
    if ((this.dept !== null) && (this.unitsCompleted >= 180)) {
      return true; // if able to graduate return true;
    }
    return false;
  }
}
