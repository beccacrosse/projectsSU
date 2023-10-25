export default class App {
  constructor() {
    this._onClick = this._onClick.bind(this);
    this.onCLickBetter = this._onClickBetter(this);

    let button = document.querySelector("#button");
    button.addEventListener("click", this._onClickBetter);
  }

  async _onClickBetter(event) { //signal that this function has asynchronous componenets
    let res = await fetch("myfile.txt"); //tells this action to wait
    let text = await res.text();
    let res2 = await fetch("person.json");
    let obj = await res2.json(); // these r awaits cus we need the results of everything to process the following line
    let s = `\n ${obj.givenName} ${obj.surname}`;
    document.querySelector("#results").textContent = s;
  }


  _onClick(event) {
    //global function fetch. can take a regular url or a path file
    let p = fetch("myfile.txt"); // <- set a variable for the promise
    // p.then(this._onResult); you could use class method if youre doing it a lot
    //since we're just doing it like once rn you can just write a function for it
    p.then((response)=> {
      let p2 = response.text();
      p2.then((text) =>{
        document.querySelector("#results").textContent = text;
      });
      //console.log(text);
    });
    //now for the json file. btw we need to wait for both to load before doing this
    /*
    p = fetch("person.json"); // <- set a variable for the promise
    p.then((res)=> {
      let p2 = res.json();
      p2.then((obj) =>{
        //console.log(obj.givenName);
        let s = `\n ${obj.givenName} ${obj.surname}`;
        //document.querySelector("#results").textContent = obj.givenName;
        document.querySelector("#results").textContent+= s;
      });
      //console.log(text);
    });*/
  }
}
