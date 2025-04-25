import { useEffect, useState } from "react";
import BookList from "./components/BookList";

async function asyncGetImageLink(isbn: string) {
  // let url = "";

  // try {
  //   const promis = await fetch(
  //     `https://www.googleapis.com/books/v1/volumes?q=isbn:${isbn}`
  //   );

  //   if (promis.status === 200) {
  //     const items = (await promis.json()).items;
  //     url = items[0].volumeInfo.imageLinks.thumbnail;
  //   } else {
  //     url = `https://covers.openlibrary.org/b/isbn/${isbn}-M.jpg`;
  //   }
  // } catch (err) {}

  // return url;

  return `https://covers.openlibrary.org/b/isbn/${isbn}-M.jpg`;
}

async function loadImage(url: string) {
  try {
    let promis = await fetch(url);

    if (promis.ok) {
      return promis.blob();
    }
  } catch (err) {}

  return new Blob();
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
          blob: await loadImage(await asyncGetImageLink(book.isbn)),
          authors: book.authors,
        });
      } catch (err) {}
    }
  }

  return books;
}

function App() {
  const [books, setBooks] = useState(
    Array<{ title: string; blob: Blob; authors: Array<string> }>
  );

  useEffect(() => {
    asyncGetBooks().then((res) => setBooks(res));
  });

  return <BookList books={books}></BookList>;
}

export default App;
