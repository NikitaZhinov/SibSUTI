import axios from "axios";
import "./App.css";
import DataSet from "./components/DataSet";
import { FC, useEffect, useState } from "react";

async function asyncGetData() {
  let data = Array<any>();
  try {
    const promis = await axios.get("http://localhost:5170/comments");
    data = promis.data;
  } catch (err) {
    console.error("cant load data");
  }
  return data;
}

const App: FC = () => {
  const [data, setData] = useState(Array<any>);
  const [selectedRows, setSelectedRows] = useState(new Set<number>());

  const addRow = () => {
    const post_id = prompt("Enter post ID");
    if (!post_id) return;

    const name = prompt("Enter your name");
    if (!name) return;

    const email = prompt("Enter your email");
    if (!email) return;

    const body = prompt("Your comment");
    if (!body) return;

    const new_data = {
      postId: Number(post_id),
      id: data.length + 1,
      name: name,
      email: email,
      body: body,
    };
    console.log(new_data);
    setData((prev: any[]) => [...prev, new_data]);
    axios
      .post("http://localhost:5170/comments", new_data)
      .then((res) => {
        console.log(res);
      })
      .catch((err) => {
        console.log(err);
      });
  };

  const removeRow = () => {
    selectedRows.forEach((row) => {
      axios
        .delete(`http://localhost:5170/comments/${data[row].id}`)
        .then((res) => {
          console.log(res);
        })
        .catch((err) => {
          console.log(err);
        });
    });
    setData((prev: any[]) => prev.filter((data, id) => !selectedRows.has(id)));
    setSelectedRows(new Set<any>());
  };

  const updateRow = () => {
    selectedRows.forEach((row) => {
      const new_post_id = prompt("New post ID");
      if (!new_post_id) return;

      const new_name = prompt("New name");
      if (!new_name) return;

      const new_email = prompt("New email");
      if (!new_email) return;

      const new_body = prompt("New comment");
      if (!new_body) return;

      const new_data = {
        postId: new_post_id,
        name: new_name,
        email: new_email,
        body: new_body,
        id: data[row].id,
      };

      axios
        .patch(`http://localhost:5170/comments/${new_data.id}`, new_data)
        .then((res) => {
          console.log(res);
        })
        .catch((err) => {
          console.log(err);
        });

      setData((prev: any[]) => {
        let new_table = [...prev];
        for (let i = 0; i < new_table.length; ++i) {
          if (i === row) {
            new_table[i] = new_data;
            break;
          }
        }
        return new_table;
      });
    });
  };

  useEffect(() => {
    asyncGetData().then((res) => setData(res));
  }, []);

  return (
    <div className="App">
      <DataSet
        data={data}
        columns={["postId", "id", "name", "email", "body"]}
        addRow={addRow}
        removeRow={removeRow}
        updateRow={updateRow}
      ></DataSet>
    </div>
  );
};

export default App;
