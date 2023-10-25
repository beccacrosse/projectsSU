let API_KEY = null;

const onLogin = async (event) => {
  event.preventDefault();
  let email = document.querySelector("#email").value;
  let password = document.querySelector("#password").value;
  let opts = {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ email, password })
  };
  let res = await fetch("/api/login", opts);
  let json = await res.json();
  if (res.status === 200) {
    document.querySelector("#loginForm").style.display = "none";
    console.log(json);
    API_KEY = json.apiKey;
  } else {
    alert(json.error);
  }
};

const onProtected = async (event) => {
  let res = await fetch("/api/protected", {
    headers: { "Authorization": `Bearer ${API_KEY}` }
  });
  let json = await res.json();
  if (res.status !== 200) {
    alert(json.error);
  } else {
    alert(json.message);
  }
};

const main = () => {
  document.querySelector("#loginForm").addEventListener("submit", onLogin);
  document.querySelector("#protected").addEventListener("click", onProtected);
};
main();
