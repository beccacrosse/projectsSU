const loadProfile = () => {
  document.querySelector("#location").textContent = window.location.href;

  let userText = document.querySelector("#user");
  let path = window.location.pathname;
  let username = path.slice(path.lastIndexOf("/") + 1);
  userText.textContent = username;
};

const main = () => {
  loadProfile();
};
main();
