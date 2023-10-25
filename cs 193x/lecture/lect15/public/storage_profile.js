const onLogout = (event) => {
  window.sessionStorage.removeItem("user");
  window.location.replace("storage.html");
};

const main = () => {
  let user = window.sessionStorage.getItem("user");
  document.querySelector("#user").textContent = user;
  document.querySelector("#logout").addEventListener("click", onLogout);
};
main();
