async function loadDataFromUrl(url) {
  let promise = await fetch(url);

  if (promise.ok) {
    let json = await promise.json();
    return json["data"];
  } else {
    throw new Error("cant load data from " + url);
  }
}

async function loadData() {
  let promise = await fetch("https://catfact.ninja/breeds");
  let data = new Array();

  if (promise.ok) {
    let json = await promise.json();

    for (const link of json["links"]) {
      try {
        if (link["label"] != "Previous" && link["label"] != "Next") {
            data.push(await loadDataFromUrl(link["url"]));
        }
      } catch (err) {
        console.error("Error! Can't load data from " + link["url"]);
      }
    }
  } else {
    console.error(
      "Error! Can't load data from https://catfact.ninja/breeds -> Status: " +
        promise.status
    );
  }

  return data;
}

module.exports = loadData;
