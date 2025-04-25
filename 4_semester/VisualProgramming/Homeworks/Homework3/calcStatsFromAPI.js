const loadData = require("./loadData.js");
const calcStats = require("./calcStats.js");

async function calcStatsFromAPI() {
  const cats = await loadData();
  return calcStats(cats);
}

module.exports = calcStatsFromAPI;
