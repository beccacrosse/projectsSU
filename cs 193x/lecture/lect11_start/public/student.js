export default class Student {
  static async list(search){ // static cus we want to
    let res = await fetch(`/api/students?q =${search}`); // query string
    let data = await res.json();
  }

  static async load(id) {
    /* needed an async function to load data from the server but constructor cant be static or async*/
    let res = await fetch(`/api/students/${id}`);
    let data = await res.json();
    if (res.status === 200) { // if status = valid 
      return new Student(data);
    }
    throw new Error(data.error); // display the errow that was caught. this is just something u can do ?
  }

  constructor(data) {
    /* V Copy all key/values from data and put them in this */
    Object.assign(this, data);

    this._uri = `/api/students/${this.id}`;
  }

  async listCourses() {
    let res = await fetch(`${this._uri}/courses`);
    let json = await res.json();
    return json.courses;
  }

  async declare(dept) {
    let body = { dept: dept }; // give our api info?
    await this._update(body); // want to wait for other info before updating
  }

  async addUnits(n) {
    let body = {unitsCompleted: this.unitsCompleted + n};
    await this._update(body);
  }

  async graduate(){
    let res = await fetch(`${this._uri}/graduate`, {
      method: "POST"
    });
    let data = await res.json();
    if (res.status !== 200) {
      throw new Error(data.error);
    }

    let res2 = await fetch(this._uri);
    let data2 = await res2.json();
    Object.assign(this, data2);

  }
  async _update(body){
    let res = await fetch(this._uri, {
      method: "PATCH",
      headers: { "Content-Type": "application/json" }, //tell it its type is json
      body: JSON.stringify(body)
    });
    let data = await res.json();
    if (res.status !== 200) {
      throw new Error(data.error);
    }
    this.dept = data.dept; // give our api info? so that dom is consistent with our server
    Object.assign(this, data); // update my variables with info from the server
  }
}
