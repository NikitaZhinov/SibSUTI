import axios from "axios";
import "./App.css";
import DataSet, { ChangeData } from "./components/DataSet";
import { FC, useEffect, useState } from "react";

const SITE_PREFIX = "http://localhost:5127/comments";

async function asyncGetData() {
  let data = Array<any>();
  try {
    const promis = await axios.get(SITE_PREFIX);
    data = promis.data;
  } catch (err) {
    console.error("cant load data");
  }
  return data;
}

const App: FC = () => {
  const [data, setData] = useState(Array<any>);

  const addRow = () => {
    let new_data: ChangeData = {
      status: false,
      data: {},
      request: () => false,
    };

    const post_id = prompt("Enter post ID");
    if (!post_id) return new_data;

    const name = prompt("Enter your name");
    if (!name) return new_data;

    const email = prompt("Enter your email");
    if (!email) return new_data;

    const body = prompt("Your comment");
    if (!body) return new_data;

    const new_row = {
      postId: Number(post_id),
      id: data.length + 1,
      name: name,
      email: email,
      body: body,
    };

    new_data.data = new_row;
    new_data.status = true;
    new_data.request = () => {
      try {
        axios
          .post(SITE_PREFIX, new_row)
          .then((res) => {
            console.log(res);
          })
          .catch((err) => {
            console.log(err);
          });
        return true;
      } catch (err) {
        return false;
      }
    };
    return new_data;
  };

  const removeRow = (row_id: number) => {
    return {
      status: true,
      data: {},
      request: () => {
        try {
          axios
            .delete(`${SITE_PREFIX}/${data[row_id].id}`)
            .then((res) => {
              console.log(res);
            })
            .catch((err) => {
              console.log(err);
            });
          return true;
        } catch (error) {
          return false;
        }
      },
    };
  };

  const updateRow = (row_id: number) => {
    let new_data: ChangeData = {
      status: false,
      data: {},
      request: () => false,
    };

    const new_post_id = prompt("New post ID");
    if (!new_post_id) return new_data;

    const new_name = prompt("New name");
    if (!new_name) return new_data;

    const new_email = prompt("New email");
    if (!new_email) return new_data;

    const new_body = prompt("New comment");
    if (!new_body) return new_data;

    const new_row = {
      postId: new_post_id,
      name: new_name,
      email: new_email,
      body: new_body,
      id: data[row_id].id,
    };

    new_data.status = true;
    new_data.data = new_row;
    new_data.request = () => {
      try {
        axios
          .patch(`${SITE_PREFIX}/${new_row.id}`, new_row)
          .then((res) => {
            console.log(res);
          })
          .catch((err) => {
            console.log(err);
          });
        return true;
      } catch (error) {
        return false;
      }
    };
    return new_data;
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
