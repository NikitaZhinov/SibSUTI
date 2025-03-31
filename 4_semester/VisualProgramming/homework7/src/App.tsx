import "./App.css";
import DataSet from "./components/DataSet";

interface Product {
  id: number;
  name: string;
  price: number;
  category: string;
}

const products: Product[] = [
  { id: 1, name: "Laptop", price: 999, category: "Electronics" },
  { id: 2, name: "Smartphone", price: 699, category: "Electronics" },
  { id: 3, name: "Headphones", price: 199, category: "Accessories" },
];

const App = () => {
  return (
    <div>
      <h1>Products Table</h1>
      <DataSet
        data={products}
        columns={["id", "name", "price", "category"]}
        renderCell={(item, columnKey) => {
          if (columnKey === "price") return `$${item[columnKey].toFixed(2)}`;
          return item[columnKey];
        }}
      />
    </div>
  );
};

export default App;
