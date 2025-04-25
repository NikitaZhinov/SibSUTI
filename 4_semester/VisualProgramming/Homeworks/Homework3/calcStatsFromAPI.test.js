const loadData = require("./loadData.js");
const calcStatsFromAPI = require("./calcStatsFromAPI.js");

jest.mock("./loadData.js");

test("test_0 calcStatsFromAPI", async () => {
  const mockData = [
    {
      breed: "Abyssinian",
      country: "Ethiopia",
      origin: "Natural",
      coat: "Short",
      pattern: "Ticked",
    },
    {
      breed: "Aegean",
      country: "Greece",
      origin: "Natural",
      coat: "Semi-long",
      pattern: "Bi- or tri-colored",
    },
    {
      breed: "American Curl",
      country: "United States",
      origin: "Mutation",
      coat: "Short/Long",
      pattern: "All",
    },
    {
      breed: "Greece Bobtail",
      country: "Greece",
      origin: "Mutation",
      coat: "Short/Long",
      pattern: "All",
    },
  ];

  loadData.mockResolvedValue(mockData);

  const stats = await calcStatsFromAPI();

  // expect(loadData).toHaveBeenCalledTimes(1);
  expect(stats).toEqual([
    {
      country: "Ethiopia",
      count: 1,
    },
    {
      country: "Greece",
      count: 2,
    },
    {
      country: "United States",
      count: 1,
    },
  ]);
});
