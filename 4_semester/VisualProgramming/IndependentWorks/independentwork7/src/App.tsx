import "./App.css";
import List from "./components/List";

const Header = "Fruits";

const Fruits = ["Apple", "Banana", "Pineapple"];

const App = () => {
  return (
    <>
      <List header={Header} body={Fruits}></List>
    </>
  );
};

export default App;
