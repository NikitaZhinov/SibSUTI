import { useEffect, useState } from "react";
import Objs from "./components/Objs";

async function getObjects() {
  const promis = await fetch("https://jsonplaceholder.typicode.com/albums");
  let objs = Array<{
    userId: number;
    id: number;
    title: string;
  }>();
  for (const obj of await promis.json()) {
    objs.push({
      userId: obj.userId,
      id: obj.id,
      title: obj.title,
    });
  }
  return objs;
}

function App() {
  const [objs, setObjs] = useState(
    Array<{
      userId: number;
      id: number;
      title: string;
    }>
  );

  useEffect(() => {
    getObjects().then((res) => setObjs(res));
  });

  return (
    <>
      <Objs objs={objs}></Objs>
    </>
  );
}

export default App;
