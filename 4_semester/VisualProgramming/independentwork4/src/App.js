import { useState } from "react";
import Card from "./components/Card";

function App() {
  const [objects, setObjects] = useState([{
    "id": 1,
    "fullName": "John Andrews",
    "name": {
    "firstName": "John",
    "lastName": "Andrews"
    },
    "address": {
    "line1": "6 Highcross Road",
    "town": "Upper Norton",
    "county": "Northshire",
    "country": "England"
    },
    "email": "john@example.com"
    },
    {
    "id": 2,
    "fullName": "Peter Munro",
    "name": {
    "firstName": "Peter",
    "lastName": "Munro"
    },
    "address": {
    "line1": "16 The Harbor",
    "town": "Newport",
    "county": "Gwent",
    "country": "Wales"
    },
    "email": "peter@example.com"
    },
    {
    "id": 3,
    "fullName": "Dave Mallon",
    "name": {
    "firstName": "Dave",
    "lastName": "Mallon"
    },
    "address": {
    "line1": "5 The Villas",
    "town": "Stourbridge",
    "county": "Devon",
    "country": "England"
    },
    "email": "dave@example.com"
    }
   ]);

  return (
    <div className="App">
      {objects.map(obj => (
        <Card object={obj}/>
      ))}
    </div>
  );
}

export default App;
