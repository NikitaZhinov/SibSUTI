import React, { useEffect, useState } from "react";

interface BookCardProps {
  title: string;
  url: string;
  authors: Array<string>;
}

async function asyncGetImageLink(isbn: string) {
  let url = "";

  try {
    let promis = await fetch(
      `https://www.googleapis.com/books/v1/volumes?q=isbn:${isbn}`
    );

    while (!promis.ok) {
      promis = await fetch(
        `https://www.googleapis.com/books/v1/volumes?q=isbn:${isbn}`
      );
    }

    if (promis.ok) {
      const items = (await promis.json()).items;
      url = items[0].volumeInfo.imageLinks.thumbnail;
    }
  } catch (err) {}

  return url;
}

function BookCard({ title, url, authors }: BookCardProps) {
  const [image_url, setImageUrl] = useState("");
  useEffect(() => {
    asyncGetImageLink(url).then(res => setImageUrl(res));
  });

  return (
    <div style={{ width: "198px", height: "500px", marginBottom: "50px", borderStyle: "inset", borderBlockWidth: "1px" }}>
      <img src={image_url} alt="" />
      <h1>{title}</h1>
      <h2>{authors}</h2>
    </div>
  );
}

export default BookCard;
