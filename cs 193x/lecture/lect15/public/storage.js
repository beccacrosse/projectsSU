const onSubmit = (event) => {
  event.preventDefault();
  let id = event.currentTarget.userid.value;
  window.sessionStorage.setItem("user", id);
  window.location.assign("storage_profile.html");
};

const main = () => {
  document.querySelector("#loginForm").addEventListener("submit", onSubmit);
};
main();
