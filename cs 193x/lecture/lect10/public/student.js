export default class Student {
  static async load(id) {
    let res = await fetch(`/api/students/${id}`);
    let data = await res.json();
    return new Student(data);
  }

  constructor(data) {
    // this.id = data.id;
    // this.givenName = data.givenName;
    // ...

    /* Copy all key/values from data and put them in this */
    Object.assign(this, data);

    this._uri = `/api/students/${this.id}`;
  }

  async listCourses() {
    let res = await fetch(`${this._uri}/courses`);
    let json = await res.json();
    return json.courses;
  }

  async declare(deptCode) {
    let body = { dept: deptCode };
    let res = await fetch(this._uri, {
      method: "PATCH",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(body)
    });
    let data = await res.json();
    if (res.status !== 200) {
      throw new Error(data.error);
    }
    this.dept = data.dept;
  }
}
