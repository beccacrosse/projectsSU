import GoogleAuth from "./googleauth.js";

/* Make sure to get your own client ID. This one will be deleted soon */
const CLIENT_ID = "723067440195-7v0ubvrf42s0jett61jspf4jtiqk57ce.apps.googleusercontent.com";

let auth = null;
let API_KEY = null;

const onLogin = async (idToken) => {
  document.querySelector("#loginForm").style.display = "none";
  let data = await auth.verifyIdToken(idToken);
  console.log(data);

  let res = await fetch("/api/google", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ idToken })
  });
  let json = await res.json();
  console.log(json);
  API_KEY = json.apiKey;
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
  auth = new GoogleAuth(CLIENT_ID);
  auth.render(document.querySelector("#loginForm"), onLogin);
  document.querySelector("#protected").addEventListener("click", onProtected);
};
main();
