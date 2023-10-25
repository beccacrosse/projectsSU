export default class Converter {
  constructor() {
    this._form = document.forms.converter;

    // you need to add a bind if you are making an event handler
    this._handleCLick = this._handleClick.bind(this);
    this._form.convert.addEventListener("click", this._handleClick);
  }
  _handleClick(event){
    // get the number value of us units
    let usUnits = this._form.us.valueAsNumber;
    this._form.metric.value = usValue * 2.54;
    console.log("Click!");
  }
}

let app = new Converter();
window.app = app;
