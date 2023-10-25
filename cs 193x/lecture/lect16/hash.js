import crypto from "crypto";

let password = process.argv[2];
console.log("Password:", password);

let hash = crypto.createHash("sha256");
hash.update(password);
console.log("Hashed password:", hash.digest("base64"));

let salt = process.argv[3];
if (salt) console.log("Entered salt:", salt);
else {
  salt = crypto.randomBytes(8).toString("base64");
  console.log("New salt:", salt);
}
hash = crypto.createHash("sha256");
hash.update(salt);
hash.update(password);
console.log("Salted hashed password:", hash.digest("base64"));
