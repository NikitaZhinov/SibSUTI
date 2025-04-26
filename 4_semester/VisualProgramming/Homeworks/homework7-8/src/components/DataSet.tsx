import { FC, useEffect, useState } from "react";

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
  removeRow: (row_id: number) => ChangeData;
  updateRow: (row_id: number) => ChangeData;
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
      if (newSelected.has(index) && newSelected.size === 1) newSelected.clear();
      else {
        newSelected.clear();
        newSelected.add(index);
      }
    }

    setSelectedRows(newSelected);
  };

  const addData = () => {
    const st = addRow();
    if (st.status) {
      setDataTable((prev: any[]) => [...prev, st.data]);
      if (!st.request()) {
        let new_select_rows = new Set<number>();
        new_select_rows.add(data.length - 1);
        setSelectedRows(new_select_rows);
        setDataTable((prev: any[]) =>
          prev.filter((data, id) => !selectedRows.has(id))
        );
        setSelectedRows(new Set<any>());
      }
    }
  };

  const deleteData = () => {
    let ignoredRows = new Set<number>();
    selectedRows.forEach((row) => {
      if (!removeRow(row).request()) ignoredRows.add(row);
    });
    setDataTable((prev: any[]) =>
      prev.filter((data, id) => !selectedRows.has(id) || ignoredRows.has(id))
    );
    setSelectedRows(new Set<any>());
  };

  const updateData = () => {
    selectedRows.forEach((row) => {
      const st = updateRow(row);
      if (st.status) {
        const new_data = st.data;
        const old_data = data[row];
        const set_data = (new_data: any) =>
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
        set_data(new_data);
        if (!st.request()) set_data(old_data);
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
