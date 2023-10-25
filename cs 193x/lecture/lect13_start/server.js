import express from "express";
import http from "http";
import path from "path";

import initApi from "./api/index.js";
import updater from "./lib/server/updater.js";

const PORT = 1930;

const app = express();
const server = http.createServer(app);

const dirname = process.cwd();
const publicPath = path.join(dirname, "public");
console.log(`Serving files from ${publicPath}`);
app.use("/lib/client", express.static(path.join(dirname, "lib", "client")));
app.use(express.static(publicPath)); // how we ask web server to make string for the public
updater(server, publicPath);

app.get("/api/students", (req, res) => {
  //take in a request and a response hehe
}
)

const main = async () => {
  initApi(app); // we now have our initApi included in our server
  server.listen(PORT, () => {
    console.log(`Server started. Now open http://localhost:${PORT}/ in your browser.`);
  });
};
main();
