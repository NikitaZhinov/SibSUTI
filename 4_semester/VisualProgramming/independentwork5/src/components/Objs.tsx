import { useEffect, useState } from "react";
import Obj from "./Obj";

interface ObjsProm {
  objs: Array<{
    userId: number;
    id: number;
    title: string;
  }>;
}

function Objs({ objs }: ObjsProm) {
  const [searchTermTitle, setSearchTermTitle] = useState("");
  const [sortTerm, setSortTerm] = useState("");
  const [filtredObjs, setFiltredObjs] = useState(objs);

  useEffect(() => {
    let newFiltredObjs = Array<{
      userId: number;
      id: number;
      title: string;
    }>();

    objs.forEach((obj) => {
      if (
        obj.title
          .toLocaleLowerCase()
          .search(searchTermTitle.toLocaleLowerCase()) !== -1
      )
        newFiltredObjs.push(obj);
    });

    if (sortTerm !== "default") {
      newFiltredObjs.sort((a, b) => {
        if (sortTerm === "userID_up") {
          if (a.userId > b.userId) return 1;
          if (a.userId < b.userId) return -1;
        } else if (sortTerm === "userID_down") {
          if (a.userId > b.userId) return -1;
          if (a.userId < b.userId) return 1;
        } else if (sortTerm === "ID_up") {
          if (a.id > b.id) return 1;
          if (a.id < b.id) return -1;
        } else if (sortTerm === "ID_down") {
          if (a.id > b.id) return -1;
          if (a.id < b.id) return 1;
        }
        return 0;
      });
    }

    setFiltredObjs(newFiltredObjs);
  }, [objs, sortTerm, searchTermTitle]);

  return (
    <>
      <div style={{ display: "flex", flexWrap: "wrap", gap: "10px" }}>
        <input
          id="input_book"
          type="text"
          placeholder="Search for a title..."
          onChange={(e) => setSearchTermTitle(e.target.value)}
        />
        Sort by:
        <select id="sort" onChange={(e) => setSortTerm(e.target.value)}>
          <option value="default">default</option>
          <option value="userID_up">userID up</option>
          <option value="userID_down">userID down</option>
          <option value="ID_up">ID up</option>
          <option value="ID_down">ID down</option>
        </select>
      </div>
      <br />
      <div style={{ display: "flex", flexWrap: "wrap", gap: "10px" }}>
        {filtredObjs.map((obj) => (
          <Obj userId={obj.userId} id={obj.id} title={obj.title}></Obj>
        ))}
      </div>
    </>
  );
}

export default Objs;
