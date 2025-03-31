import { FC, useState } from "react";
import "./DataSet.css";

interface DataSetProps {
  data: Array<any>;
  columns: Array<string>;
  renderCell?: (item: any, columnKey: string) => React.ReactNode;
}

function defaultRenderCell(item: any, columnKey: string) {
  return item[columnKey].toString();
}

const DataSet: FC<DataSetProps> = ({
  data,
  columns,
  renderCell = defaultRenderCell,
}) => {
  const [selectedRows, setSelectedRows] = useState(new Set<number>());

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

  return (
    <div className="data-set">
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
          {data.map((item, index) => (
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
