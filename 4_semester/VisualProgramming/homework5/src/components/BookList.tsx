import { useEffect, useState } from "react";
import BookCard from "./BookCard";

interface BookListProps {
  books: Array<{ title: string; blob: Blob; authors: Array<string> }>;
}

function BookList({ books }: BookListProps) {
  const [filtredBooks, setFiltredBooks] = useState(books);
  const [searchTermTitle, setSearchTermTitle] = useState("");
  const [searchTermAuthor, setSearchTermAuthor] = useState("");
  const [sortTerm, setSortTerm] = useState("");

  useEffect(() => {
    let newFilteredBooks = Array<{
      title: string;
      blob: Blob;
      authors: Array<string>;
    }>();

    books.forEach((book) => {
      if (
        book.authors
          .join()
          .toLocaleLowerCase()
          .search(searchTermAuthor.toLowerCase()) !== -1 &&
        book.title.toLowerCase().search(searchTermTitle.toLowerCase()) !== -1
      )
        newFilteredBooks.push(book);
    });

    if (sortTerm !== "default") {
      newFilteredBooks.sort((a, b) => {
        if (sortTerm === "title_up") {
          if (a.title > b.title) return 1;
          if (a.title < b.title) return -1;
        } else if (sortTerm === "title_down") {
          if (a.title > b.title) return -1;
          if (a.title < b.title) return 1;
        } else if (sortTerm === "author_up") {
          if (a.authors.join() > b.authors.join()) return 1;
          if (a.authors.join() < b.authors.join()) return -1;
        } else if (sortTerm === "author_down") {
          if (a.authors.join() > b.authors.join()) return -1;
          if (a.authors.join() < b.authors.join()) return 1;
        }
        return 0;
      });
    }

    setFiltredBooks(newFilteredBooks);
  }, [books, searchTermTitle, searchTermAuthor, sortTerm]);

  return (
    <>
      <div style={{ display: "flex", flexDirection: "row", gap: "10px" }}>
        <input
          id="input_book"
          type="text"
          placeholder="Search for a book..."
          onChange={(e) => setSearchTermTitle(e.target.value)}
        />
        <input
          id="input_book"
          type="text"
          placeholder="Search for a author..."
          onChange={(e) => setSearchTermAuthor(e.target.value)}
        />
        Sort by:
        <select id="sort" onChange={(e) => setSortTerm(e.target.value)}>
          <option value="default">default</option>
          <option value="title_up">title up</option>
          <option value="title_down">title down</option>
          <option value="author_up">author up</option>
          <option value="author_down">author down</option>
        </select>
      </div>
      <br></br>
      <div style={{ display: "flex", flexWrap: "wrap" }}>
        {filtredBooks.length !== 0 ? filtredBooks.map((book) => (
          <BookCard
            title={book.title}
            blob={book.blob}
            authors={book.authors}
          />
        )) : <p>Loading...</p>}
      </div>
    </>
  );
}

export default BookList;
