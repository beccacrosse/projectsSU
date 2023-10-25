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
app.use(express.static(publicPath));
updater(server, publicPath);

// app.get("/api/students", (req, res) => {
//   res.json(...);
// });

const main = async () => {
  initApi(app);
  server.listen(PORT, () => {
    console.log(`Server started. Now open http://localhost:${PORT}/ in your browser.`);
  });
};
main();