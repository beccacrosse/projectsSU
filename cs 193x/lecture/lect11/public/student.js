export default class Student {
  static async list(search) {
    let res = await fetch(`/api/students?q=${search}`);
    let data = await res.json();
    return data;
  }

  static async load(id) { // static methds can be called on the class.
    let res = await fetch(`/api/students/${id}`);
    let data = await res.json();
    if (res.status === 200) {
      return new Student(data);
    }
    throw new Error(data.error);
  }

  constructor(data) {
    /* Copy all key/values from data and put them in this */
    Object.assign(this, data);

    this._uri = `/api/students/${this.id}`;
  }

  async listCourses() {
    let res = await fetch(`${this._uri}/courses`);
    let json = await res.json();
    return json.courses;
  }

  async declare(dept) {
    let body = { dept: dept };
    await this._update(body);
  }

  async addUnits(n) {
    let body = { unitsCompleted: this.unitsCompleted + n };
    await this._update(body);
  }

  async graduate() {
    let res = await fetch(`${this._uri}/graduate`, {
      method: "POST"
    });
    let data = await res.json();
    if (res.status !== 200) {
      throw new Error(data.error);
    }
    console.log(data);
    
    /* Reload the student to update instance variables */
    let res2 = await fetch(this._uri);
    let data2 = await res2.json();
    Object.assign(this, data2);
  }
  async _update(body) {
    let res = await fetch(this._uri, {
      method: "PATCH",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(body)
    });
    let data = await res.json();
    if (res.status !== 200) {
      throw new Error(data.error);
    }
    // this.dept = data.dept;
    // this.unitsCompleted = data.unitsCompleted;
    // ...
    Object.assign(this, data);
  }
}
