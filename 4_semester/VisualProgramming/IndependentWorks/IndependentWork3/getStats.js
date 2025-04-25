const getDataFromAPI = require("./getDataFromAPI.js");

async function getStats() {
  const data = await getDataFromAPI();
  let stats = [
    {
      category: data[0]["category"],
      count: 0,
    },
  ];

  for (const dat of data) {
    let is_exist = false;
    for (let stat of stats) {
      if (stat["category"] == dat["category"]) {
        is_exist = true;
        ++stat["count"];
        break;
      }
    }
    if (!is_exist) {
      stats.push({
        category: dat["category"],
        count: 1,
      });
    }
  }

  return stats;
}

module.exports = getStats;
