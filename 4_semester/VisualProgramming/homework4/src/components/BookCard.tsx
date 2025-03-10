import React, { useState } from "react";

interface BookCardProps {
  title: string;
  url: string;
  authors: Array<string>;
}

function BookCard({ title, url, authors }: BookCardProps) {
  return (
    <div style={{ width: "200px", height: "500px", marginBottom: "50px" }}>
      <img src={url} alt="" />
      <h1>{title}</h1>
      <h2>{authors}</h2>
    </div>
  );
}

export default BookCard;
