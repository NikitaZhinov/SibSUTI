import { FC, useEffect, useState } from "react";
import axios from "axios";

export interface ChangeData {
  status: boolean;
  data: any;
  request: () => boolean;
}

export interface DataSetProps {
  data: Array<any>;
  columns: Array<string>;
  renderCell?: (item: any, columnKey: string) => React.ReactNode;
  addRow: () => ChangeData;
  removeRow: () => ChangeData;
  updateRow: () => ChangeData;
}

function defaultRenderCell(item: any, columnKey: string) {
  return item[columnKey].toString();
}

const DataSet: FC<DataSetProps> = ({
  data,
  columns,
  renderCell = defaultRenderCell,
  addRow,
  removeRow,
  updateRow,
}) => {
  const [data_table, setDataTable] = useState(data);
  const [selectedRows, setSelectedRows] = useState(new Set<number>());

  useEffect(() => {
    setDataTable(data);
  }, [data]);

  const handleRowSelect = (index: number, ctrlPressed: boolean) => {
    const newSelected = new Set(selectedRows);

    if (ctrlPressed) {
      if (newSelected.has(index)) newSelected.delete(index);
      else newSelected.add(index);
    } else {
      if (newSelected.has(index) && newSelected.size === 1) {
        newSelected.clear();
      } else {
        newSelected.clear();
        newSelected.add(index);
      }
    }

    setSelectedRows(newSelected);
  };

  const addData = () => {
    const st = addRow();
    if (st.status) {
      // console.log(st.data);
      setDataTable((prev: any[]) => [...prev, st.data]);
      if (!st.request()) {
        
      }
      // axios
      //   .post("http://localhost:5170/comments", st.data)
      //   .then((res) => {
      //     console.log(res);
      //   })
      //   .catch((err) => {
      //     console.log(err);
      //   });
    }
  };

  const deleteData = () => {
    selectedRows.forEach((row) => {
      axios
        .delete(`http://localhost:5170/comments/${data_table[row].id}`)
        .then((res) => {
          console.log(res);
        })
        .catch((err) => {
          console.log(err);
        });
    });
    setDataTable((prev: any[]) =>
      prev.filter((data, id) => !selectedRows.has(id))
    );
    setSelectedRows(new Set<any>());
  };

  const updateData = () => {
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
        id: data_table[row].id,
      };

      axios
        .patch(`http://localhost:5170/comments/${new_data.id}`, new_data)
        .then((res) => {
          console.log(res);
        })
        .catch((err) => {
          console.log(err);
        });

      setDataTable((prev: any[]) => {
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

  return (
    <div className="data-set">
      <div>
        <button className="Button" onClick={addData}>
          Add
        </button>
        <button className="Button" onClick={deleteData}>
          Delete
        </button>
        <button className="Button" onClick={updateData}>
          Update
        </button>
      </div>
      <table>
        <thead>
          <tr>
            <th className="selector-column"></th>
            {columns.map((column) => (
              <th>{column}</th>
            ))}
          </tr>
        </thead>
        <tbody>
          {data_table.map((item, index) => (
            <tr
              key={index}
              className={selectedRows.has(index) ? "selected" : ""}
            >
              <td
                className="selector-column"
                onMouseDown={(e) => handleRowSelect(index, e.ctrlKey)}
              >
                {index + 1}
              </td>
              {columns.map((column) => (
                <td>{renderCell(item, column)}</td>
              ))}
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
};

export default DataSet;
