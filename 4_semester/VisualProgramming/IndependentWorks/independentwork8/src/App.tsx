import DataGrid from "./components/DataGrid";
import "./App.css";

const treeData = {
  header: "Живые существа",
  children: [
    {
      header: "Животные",
      children: [
        {
          header: "Молоко питающиеся",
          children: null,
        },
        {
          header: "Шпиониро Голубиро",
          children: null,
        },
        {
          header: "Бомбордиро Крокодило",
          children: null,
        },
        {
          header: "Траралело Тралала",
          children: null,
        },
      ],
    },
    {
      header: "Растения",
      children: null,
    },
    {
      header: "Грибы",
      children: [
        {
          header: "Съедобные",
          children: null,
        },
        {
          header: "Голюцоногенные",
          children: null,
        },
      ],
    },
    {
      header: "Мелкие твари",
      children: [
        {
          header: "Огнемёт держите при себе",
          children: null,
        },
      ],
    },
  ],
};

function App() {
  const customHeader = (node: any) => (
    <div style={{ color: node.children ? "#2b2d42" : "#4a4e69" }}>
      {node.header}
    </div>
  );

  return (
    <div className="App">
      <DataGrid node={treeData} renderHeader={customHeader} />
    </div>
  );
}

export default App;
