export default class Student {
  // static methods: do async work here since constructor cant be async
  static async load(id) {
    let res = await fetch(`/api/student/${id}`);
    let data = await res.json();
    return new Student(data);
  }
  constructor(data) {
    Object.assign(this, data); //assign all the variables of data into this

    this._uri = `/api/students/${this.id}`; // holds all the info we fetch
  }
  async listCourses() {
    let res = await fetch(`${this._uri}/courses`); //linked to this._uri somehow
    let json = await res.json();
  }
  
}
