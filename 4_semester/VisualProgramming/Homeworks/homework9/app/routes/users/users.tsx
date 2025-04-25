import axios from "axios";
import { useState, useEffect } from "react";
import DataSet from "../../components/DataSet/DataSet";

async function asyncGetData() {
  let data = Array<any>();
  try {
    const promis = await axios.get(
      "https://jsonplaceholder.typicode.com/users"
    );
    data = promis.data;
  } catch (err) {
    console.error("cant load data");
  }
  return data;
}

export default function Users() {
  const [data, setData] = useState(Array<any>);

  useEffect(() => {
    asyncGetData().then((res) => setData(res));
  }, []);

  return (
    <div className="App">
      <DataSet
        data={data}
        columns={[
          "id",
          "name",
          "username",
          "email",
          "address",
          "phone",
          "website",
          "company",
        ]}
        renderCell={(item, key) => {
          if (key === "address")
            return (
              <ul>
                <li>street: {item["address"]["street"]}</li>
                <li>suite: {item["address"]["suite"]}</li>
                <li>city: {item["address"]["city"]}</li>
                <li>zipcode: {item["address"]["zipcode"]}</li>
                <li>
                  geo:{" "}
                  {
                    <ul>
                      <li>lat: {item["address"]["geo"]["lat"]}</li>
                      <li>lng: {item["address"]["geo"]["lng"]}</li>
                    </ul>
                  }
                </li>
              </ul>
            );
          if (key === "company")
            return (
              <ul>
                <li>name: {item["company"]["name"]}</li>
                <li>catchPhrase: {item["company"]["catchPhrase"]}</li>
                <li>bs: {item["company"]["bs"]}</li>
              </ul>
            );
          return item[key].toString();
        }}
        addRow={() => {
          const new_name = prompt("New name");
          if (!new_name) return [{}, false];

          const new_username = prompt("New username");
          if (!new_username) return [{}, false];

          const new_email = prompt("New email");
          if (!new_email) return [{}, false];

          const new_address_street = prompt("New address: street");
          if (!new_address_street) return [{}, false];

          const new_address_suite = prompt("New address: suite");
          if (!new_address_suite) return [{}, false];

          const new_address_city = prompt("New address: city");
          if (!new_address_city) return [{}, false];

          const new_address_zipcode = prompt("New address: zipcode");
          if (!new_address_zipcode) return [{}, false];

          const new_address_geo_lat = prompt("New address: geo: lat");
          if (!new_address_geo_lat) return [{}, false];

          const new_address_geo_lng = prompt("New address: geo: lng");
          if (!new_address_geo_lng) return [{}, false];

          const new_phone = prompt("New phone");
          if (!new_phone) return [{}, false];

          const new_website = prompt("New website");
          if (!new_website) return [{}, false];

          const new_company_name = prompt("New company: name");
          if (!new_company_name) return [{}, false];

          const new_company_catchPhrase = prompt("New company: catchPhrase");
          if (!new_company_catchPhrase) return [{}, false];

          const new_company_bs = prompt("New company: bs");
          if (!new_company_bs) return [{}, false];

          return [
            {
              id: data.length,
              name: new_name,
              email: new_email,
              address: {
                street: new_address_street,
                suite: new_address_suite,
                city: new_address_city,
                zipcode: new_address_zipcode,
                geo: {
                  lat: new_address_geo_lat,
                  lng: new_address_geo_lng,
                },
              },
              phone: new_phone,
              website: new_website,
              company: {
                name: new_company_name,
                catchPhrase: new_company_catchPhrase,
                bs: new_company_bs,
              },
            },
            true,
          ];
        }}
        deleteRow={(row) => {
          axios
            .delete(
              `https://jsonplaceholder.typicode.com/users/${data[row].id}`
            )
            .then((res) => {
              console.log(res);
            })
            .catch((err) => {
              console.log(err);
            });
          return null;
        }}
        updateRow={(row) => {
          const new_name = prompt("New name");
          if (!new_name) return [{}, false];

          const new_username = prompt("New username");
          if (!new_username) return [{}, false];

          const new_email = prompt("New email");
          if (!new_email) return [{}, false];

          const new_address_street = prompt("New address: street");
          if (!new_address_street) return [{}, false];

          const new_address_suite = prompt("New address: suite");
          if (!new_address_suite) return [{}, false];

          const new_address_city = prompt("New address: city");
          if (!new_address_city) return [{}, false];

          const new_address_zipcode = prompt("New address: zipcode");
          if (!new_address_zipcode) return [{}, false];

          const new_address_geo_lat = prompt("New address: geo: lat");
          if (!new_address_geo_lat) return [{}, false];

          const new_address_geo_lng = prompt("New address: geo: lng");
          if (!new_address_geo_lng) return [{}, false];

          const new_phone = prompt("New phone");
          if (!new_phone) return [{}, false];

          const new_website = prompt("New website");
          if (!new_website) return [{}, false];

          const new_company_name = prompt("New company: name");
          if (!new_company_name) return [{}, false];

          const new_company_catchPhrase = prompt("New company: catchPhrase");
          if (!new_company_catchPhrase) return [{}, false];

          const new_company_bs = prompt("New company: bs");
          if (!new_company_bs) return [{}, false];

          return [
            {
              id: data[row].id,
              name: new_name,
              email: new_email,
              address: {
                street: new_address_street,
                suite: new_address_suite,
                city: new_address_city,
                zipcode: new_address_zipcode,
                geo: {
                  lat: new_address_geo_lat,
                  lng: new_address_geo_lng,
                },
              },
              phone: new_phone,
              website: new_website,
              company: {
                name: new_company_name,
                catchPhrase: new_company_catchPhrase,
                bs: new_company_bs,
              },
            },
            true,
          ];
        }}
      ></DataSet>
    </div>
  );
}
