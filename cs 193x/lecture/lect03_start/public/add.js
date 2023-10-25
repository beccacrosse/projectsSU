const add = (a, b) => {
  console.log("Adding", a, "and", b);
  return a + b;
};
//window is how to make global changes. expose add to console
window.add = add;

export default add;