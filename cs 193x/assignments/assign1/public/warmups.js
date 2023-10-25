/* Replace the TODO in the next line with your sunetid */
import checkAnswer from "https://web.stanford.edu/class/cs193x/assign1/debugme.js?sunetid=crosse";

import DATA from "./data.js";

/* Call this function from the console and use the debugger to find the secret code. */
const debugExercise = () => {
  /* I learned how to use the debugger and placed a breakpoint on checkAnswer()
  I then used debugger to step into the function and step through to find the value of "correct"*/
  checkAnswer("iKF6Bswd");
};
window.debugExercise = debugExercise;

/* Return an array of the SUNetIDs of the first N students in the data. */
const firstNSunets = (n) => {
  //create empty set
  let sunets = [];
  const studentsList = DATA.students;
  //loop through the first n students
  for (let i=0; i<n; i++) {
    sunets.push(studentsList[i].sunetid);
  }
  return sunets;
};

/* Return an Object mapping department names to codes of all departments with two-character codes. */
const shortDeptCodes = () => {
  const departments = DATA.depts;
  let map = {};
  // loop through the departments and add them to the array if qualified
  for (let i=0; i< departments.length; i++) {
    const currDpt = departments[i];
    if (departments[i].code.length == 2) {
      map[currDpt.name] = currDpt.code;
    }
  }
  return map;
};

/* Return the average number of units completed by the students in the data */
const averageUnits = () => {
  //TODO
  let total = 0;
  const len = Object.keys(DATA.units).length; //amount of students
  for (let i=0; i< len; i++ ) {
    let name = DATA.students[i].sunetid; // get sunet at this index
    let value = DATA.units[name]; //find units value attached to key of sunet
    total += value;
  }
  return (total / len); // return average (total/ # of students)
};

/* Test the warmup functions */
const testWarmups = () => {
  debugExercise();

  /* These checks work by converting the return value into a string for comparison. We will talk more about JSON later in the course. */
  console.assert(JSON.stringify(firstNSunets(3)) === `["mchang91","neelk","jahchuen"]`,
    "firstNSunets() returned incorrect answer");
  console.assert(JSON.stringify(shortDeptCodes()) === `{"Computer Science":"CS","Electrical Engineering":"EE"}`,
    "shortDeptCodes() returned incorrect answer");
  console.assert(averageUnits().toFixed(3) === "176.000", "averageUnits() returned incorrect answer");

  console.log("Tests completed");
};
window.testWarmups = testWarmups;
