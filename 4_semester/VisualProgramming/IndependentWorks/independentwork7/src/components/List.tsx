import { FC, useState } from "react";

export interface ListProps {
  header: any;
  body: Array<any>;
  renderHeader?: (item: any) => React.ReactNode;
  renderItem?: (item: any) => React.ReactNode;
}

function defaultRender(item: any) {
  return `${item}`;
}

const List: FC<ListProps> = ({
  header,
  body,
  renderHeader = defaultRender,
  renderItem = defaultRender,
}) => {
  const [isOpen, setIsOpen] = useState(false);

  return (
    <>
      <h1 onMouseUp={(e) => setIsOpen(!isOpen)}>{renderHeader(header)} {isOpen ? "▼" : "◀"}</h1>
      <ul>
        {isOpen ? body.map((item) => <li>{renderItem(item)}</li>) : <></>}
      </ul>
    </>
  );
};

export default List;
