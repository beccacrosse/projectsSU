const updateLocation = () => {
  document.querySelector("#location").textContent = window.location.href;
};

const onLink = (event) => {
  event.preventDefault();
  window.history.pushState(null, "", "/binky");
  updateLocation();
};

const onPop = (event) => {
  document.querySelector("h1").textContent = "Popstate";
  updateLocation();
};

const main = () => {
  updateLocation();

  document.querySelector("#histLink").addEventListener("click", onLink);
  window.addEventListener("popstate", onPop);
};
main();
