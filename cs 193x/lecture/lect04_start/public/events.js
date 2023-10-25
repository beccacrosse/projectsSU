
let nClicks = 0;
const main = () => {
  // throw everything into forms with id clickcounter
  // find form with id clickcount
  let form = document.forms.clickcount;
  let clickme = form.clickme;
  let unclickme = form.unclickme;
  const handleClick = (event) =>{
    // isolate which button had its listener triggered
    let whichButton = event.currentTarget;
    if(whichButton.id === "clickme"){
      nClicks++;
      button.textContent = `Clicked ${nClicks} times`;
    }else{
      nClicks--;
      button.textContent = `Clicked ${nClicks} times`;
    }
  }
  clickme.addEventListener("click", handleClick);
  unclickme.addEventListener("click", handleClick);
};
main();

