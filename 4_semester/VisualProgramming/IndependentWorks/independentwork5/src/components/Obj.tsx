interface ObjProm {
  userId: number;
  id: number;
  title: string;
}

function Obj({ userId, id, title }: ObjProm) {
  return (
    <>
      <div
        style={{ borderStyle: "dashed", borderWidth: "2px", width: "290px" }}
      >
        <h1>UserId: {userId}</h1>
        <h2>Id: {id}</h2>
        <h3>title: {title}</h3>
      </div>
    </>
  );
}

export default Obj;
