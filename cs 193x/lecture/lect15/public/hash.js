const loadProfile = () => {
  document.querySelector("#location").textContent = window.location.href;

  let title = document.querySelector("h1");
  let hash = window.location.hash;
  if (hash.length > 1) {
    title.textContent = `${hash.slice(1)}'s Profile`;
  } else {
    title.textContent = "Home";
  }
};

const main = () => {
  loadProfile();
  window.addEventListener("hashchange", loadProfile);
};
main();
