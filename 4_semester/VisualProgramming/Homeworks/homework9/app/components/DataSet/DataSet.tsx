import { type FC, useEffect, useState } from "react";
import "./DataSet.css";
import axios from "axios";

interface DataSetProps {
  data: Array<any>;
  columns: Array<string>;
  renderCell?: (item: any, columnKey: string) => React.ReactNode;
  addRow: () => any[];
  deleteRow: (row: number) => null;
  updateRow: (row: number) => any[];
}

function defaultRenderCell(item: any, columnKey: string) {
  return `${item[columnKey]}`;
}

const DataSet: FC<DataSetProps> = ({
  data,
  columns,
  renderCell = defaultRenderCell,
  addRow,
  deleteRow,
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
    const [new_data, is_all] = addRow();

    if (is_all) {
      setDataTable((prev: any[]) => [...prev, new_data]);
      console.log(data_table);
      // axios
      //   .post("https://jsonplaceholder.typicode.com/comments", {
      //     body: JSON.stringify(new_data),
      //     headers: {
      //       "Content-type": "application/json; charset=UTF-8",
      //     },
      //   })
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
      deleteRow(row);
    });
    setDataTable((prev: any[]) =>
      prev.filter((data, id) => !selectedRows.has(id))
    );
    setSelectedRows(new Set<any>());
  };

  const updateData = () => {
    selectedRows.forEach((row) => {
      const [new_data, is_all] = updateRow(row);

      if (is_all) {
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
      }
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
