const getStats = require("./getStats.js");
const getDataFromAPI = require("./getDataFromAPI.js");

jest.mock("./getDataFromAPI.js");

test("test_1 getStats", async () => {
  const mocData = [
    {
      id: 12354,
      title: "string",
      description: "uh ti puh ti",
      category: "avtomobili",
      price: 2345345,
      discountPercentage: 3,
    },
    {
      id: 23,
      title: "fast time",
      description: "made in heaven",
      category: "stand",
      price: 0,
      discountPercentage: 35243,
    },
    {
      id: 1234567,
      title: "time",
      description: "the world",
      category: "stand",
      price: 1000,
      discountPercentage: 89,
    },
  ];

  getDataFromAPI.mockResolvedValue(mocData);

  const stats = await getStats();

  expect(getDataFromAPI).toHaveBeenCalledTimes(1);
  expect(stats).toEqual([
    {
      category: "avtomobili",
      count: 1,
    },
    {
      category: "stand",
      count: 2,
    },
  ]);
});
