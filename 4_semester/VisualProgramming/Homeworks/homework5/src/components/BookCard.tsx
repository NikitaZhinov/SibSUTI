interface BookCardProps {
  title: string;
  blob: Blob;
  authors: Array<string>;
}

function BookCard({ title, blob, authors }: BookCardProps) {
  return (
    <div
      style={{
        width: "198px",
        height: "500px",
        marginBottom: "50px",
        borderStyle: "inset",
        borderBlockWidth: "1px",
      }}
    >
      <img src={URL.createObjectURL(blob)} alt="" />
      <h1>{title}</h1>
      <h2>{authors}</h2>
    </div>
  );
}

export default BookCard;
