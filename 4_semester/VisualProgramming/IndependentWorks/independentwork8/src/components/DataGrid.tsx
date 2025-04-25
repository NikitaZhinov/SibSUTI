import React, { useState, FC } from "react";
import "./DataGrid.css";

export interface DataGridProps {
  node: any;
  depth?: number;
  renderHeader?: (item: any) => React.ReactNode;
  renderChildren?: (item: any) => React.ReactNode;
}

function defaultRenderHeader(item: any) {
  return `${item}`;
}

function defaultRenderChildren(item: any) {
  return `${item}`;
}

const DataGrid: FC<DataGridProps> = ({
  node,
  depth = 0,
  renderHeader = defaultRenderHeader,
  renderChildren = defaultRenderChildren,
}) => {
  const [isOpen, setIsOpen] = useState(false);
  const hasChildren = node.children && node.children.length > 0;

  const toggle = () => {
    if (hasChildren) setIsOpen(!isOpen);
  };

  return (
    <div className="tree-node" style={{ marginLeft: `${depth * 20}px` }}>
      <div
        className={`node-header ${!hasChildren ? "leaf" : "parent"}`}
        onClick={toggle}
      >
        {hasChildren && (
          <span className="toggle-icon">{isOpen ? "▼" : "▶"}</span>
        )}
        {renderHeader ? renderHeader(node) : node.header}
      </div>

      {hasChildren && isOpen && (
        <div className="children-container">
          {node.children.map((child: any, index: number) => (
            <DataGrid
              key={index}
              node={child}
              depth={depth + 1}
              renderHeader={renderHeader}
              renderChildren={renderChildren}
            />
          ))}
        </div>
      )}
    </div>
  );
};

export default DataGrid;
