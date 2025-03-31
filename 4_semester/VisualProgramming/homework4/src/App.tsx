import React, { useEffect, useState } from "react";
import BookCard from "./components/BookCard";

async function asyncGetBooks() {
  let books = [];

  const promis = await fetch("https://fakeapi.extendsclass.com/books");

  if (promis.ok) {
    const json = await promis.json();

    for (const book of json) {
      try {
        books.push({
          title: book.title,
          // url: `https://covers.openlibrary.org/b/isbn/${book.isbn}-M.jpg`,
          url: book.isbn,
          authors: book.authors,
        });
      } catch (err) {}
    }
  }

  return books;
}

function App() {
  const [books, setBooks] = useState(
    Array<{ title: string; url: string; authors: Array<string> }>
  );
  useEffect(() => {
    asyncGetBooks().then((res) => setBooks(res));
  }, []);

  return (
    <div style={{display: "flex", flexWrap: "wrap"}}>
      {books.map((book) => (
        <BookCard title={book.title} url={book.url} authors={book.authors} />
      ))}
    </div>
  );
}

export default App;
