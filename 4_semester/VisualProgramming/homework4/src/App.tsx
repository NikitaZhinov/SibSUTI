import React, { useEffect, useState } from "react";
import BookCard from "./components/BookCard";

async function asyncGetImageLink(isbn: string) {
  let url = "";

  try {
    const promis = await fetch(
      `https://www.googleapis.com/books/v1/volumes?q=isbn:${isbn}`
    );

    if (promis.ok) {
      const items = (await promis.json()).items;
      url = items[0].volumeInfo.imageLinks.thumbnail;
    }
  } catch (err) {}

  return url;
}

async function asyncGetBooks() {
  let books = [];

  const promis = await fetch("https://fakeapi.extendsclass.com/books");

  if (promis.ok) {
    const json = await promis.json();

    for (const book of json) {
      try {
        books.push({
          title: book.title,
          // url: await asyncGetImageLink(book.isbn),
          url: `https://covers.openlibrary.org/b/isbn/${book.isbn}-M.jpg`,
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
    <div>
      {books.map((book) => (
        <BookCard title={book.title} url={book.url} authors={book.authors} />
      ))}
    </div>
  );
}

export default App;
