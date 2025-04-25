function calcStats(catsInfo) {
  let stats = [
    {
      country: catsInfo[0]["country"],
      count: 0,
    }
  ];

  for (const cat of catsInfo) {
    let is_exist = false;
    for (let stat of stats) {
      if (stat["country"] == cat["country"]) {
        is_exist = true;
        ++stat["count"];
        break;
      }
    }
    if (!is_exist) {
      stats.push({
        country: cat["country"],
        count: 1,
      });
    }
  }

  return stats;
}

module.exports = calcStats;
