async function getDataFromAPI() {
  let prom = await fetch("https://dummyjson.com/products");
  let json = await prom.json();
  return json["products"];
}

module.exports = getDataFromAPI;
