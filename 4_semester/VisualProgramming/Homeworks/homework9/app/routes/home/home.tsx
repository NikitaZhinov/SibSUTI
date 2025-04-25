import axios from "axios";
import { useState, useEffect } from "react";
import DataSet from "../../components/DataSet/DataSet";
import { ErrorMessage, Field, Form, Formik } from "formik";

async function asyncGetData() {
  let data = Array<any>();
  try {
    const promis = await axios.get(
      "https://jsonplaceholder.typicode.com/comments"
    );
    data = promis.data;
  } catch (err) {
    console.error("cant load data");
  }
  return data;
}

export default function Home() {
  const [data, setData] = useState(Array<any>);

  useEffect(() => {
    asyncGetData().then((res) => setData(res));
  }, []);

  return (
    <div className="App">
      <DataSet
        data={data}
        columns={["postId", "id", "name", "email", "body"]}
        addRow={() => {
          let new_row;
          <Formik
            initialValues={{
              postId: "",
              name: "",
              email: "",
              body: "",
            }}
            onSubmit={(values) => {
              new_row = {
                postId: values.postId,
                name: values.name,
                email: values.email,
                body: values.body,
                id: data.length,
              };
            }}
          >
            <Form>
              <label htmlFor="postId">Post ID</label>
              <Field id="postId" name="postId" />

              <label htmlFor="name">Name</label>
              <Field id="name" name="name" />

              <label htmlFor="email">Email</label>
              <Field id="email" name="email" type="email" />

              <label htmlFor="body">Comment</label>
              <Field id="body" name="body" />

              <button type="submit">Submit</button>
            </Form>
          </Formik>;
          return [new_row, true];
        }}
        deleteRow={(row) => {
          axios
            .delete(
              `https://jsonplaceholder.typicode.com/comments/${data[row].id}`
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
          const new_post_id = prompt("New post ID");
          if (!new_post_id) return [{}, false];

          const new_name = prompt("New name");
          if (!new_name) return [{}, false];

          const new_email = prompt("New email");
          if (!new_email) return [{}, false];

          const new_body = prompt("New comment");
          if (!new_body) return [{}, false];

          return [
            {
              postId: new_post_id,
              name: new_name,
              email: new_email,
              body: new_body,
              id: data[row].id,
            },
            true,
          ];
        }}
      ></DataSet>
    </div>
  );
}
