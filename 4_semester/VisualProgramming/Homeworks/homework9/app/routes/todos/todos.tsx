import axios from "axios";
import { useState, useEffect } from "react";
import DataSet from "../../components/DataSet/DataSet";

async function asyncGetData() {
  let data = Array<any>();
  try {
    const promis = await axios.get(
      "https://jsonplaceholder.typicode.com/todos"
    );
    data = promis.data;
  } catch (err) {
    console.error("cant load data");
  }
  return data;
}

export default function Todos() {
  const [data, setData] = useState(Array<any>);

  useEffect(() => {
    asyncGetData().then((res) => setData(res));
  }, []);

  return (
    <div className="App">
      <DataSet
        data={data}
        columns={["userId", "id", "title", "completed"]}
        addRow={() => {
          const new_user_id = prompt("New user ID");
          if (!new_user_id) return [{}, false];

          const new_title = prompt("New title");
          if (!new_title) return [{}, false];

          const new_completed = prompt("Is completed?");
          if (!new_completed) return [{}, false];

          return [
            {
              userId: new_user_id,
              title: new_title,
              completed: new_completed,
              id: data.length,
            },
            true,
          ];
        }}
        deleteRow={(row) => {
          axios
            .delete(
              `https://jsonplaceholder.typicode.com/todos/${data[row].id}`
            )
            .then((res) => {
              console.log(res);
            })
            .catch((err) => {
              console.log(err);
            });
          return null;
        }}
        updateRow={(row) => {
          const new_user_id = prompt("New user ID");
          if (!new_user_id) return [{}, false];

          const new_title = prompt("New title");
          if (!new_title) return [{}, false];

          const new_completed = prompt("Is completed?");
          if (!new_completed) return [{}, false];

          return [
            {
              userId: new_user_id,
              title: new_title,
              completed: new_completed,
              id: data[row].id,
            },
            true,
          ];
        }}
      ></DataSet>
    </div>
  );
}
