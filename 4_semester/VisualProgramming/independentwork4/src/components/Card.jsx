import React from "react";

function Card({ object }) {
  return (
    <>
      <div style={{ backgroundColor: "#ADD8E6", width: "300px" }}>
        <b>id:</b> {object.id}
        <br />
        <b>Full Name:</b> {object.fullName}
        <br />
        <b>Name:</b>
        <br />
        <b style={{ marginLeft: "50px" }}>First Name: </b>{" "}
        {object.name.firstName}
        <br />
        <b style={{ marginLeft: "50px" }}>Last Name: </b> {object.name.lastName}
        <br />
        <b>Address:</b>
        <br />
        <b style={{ marginLeft: "50px" }}>Line: </b> {object.address.line1}
        <br />
        <b style={{ marginLeft: "50px" }}>Town: </b> {object.address.town}
        <br />
        <b style={{ marginLeft: "50px" }}>County: </b> {object.address.county}
        <br />
        <b style={{ marginLeft: "50px" }}>Country: </b> {object.address.country}
        <br />
        <b>Email: </b> {object.email}
      </div>
      <br />
    </>
  );
}

export default Card;
