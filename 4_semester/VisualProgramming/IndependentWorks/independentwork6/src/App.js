import React, { useState, useEffect } from "react";
import axios from "axios";
import ProgressBar from "./ProgressBar";
import "./App.css";

async function fetchData(canceled, setData, setLoading, setProgress) {
  const delay = (ms) => new Promise((resolve) => setTimeout(resolve, ms));

  try {
    const response = await axios.get(
      "https://fakeapi.extendsclass.com/countries"
    );
    const countries = response.data;
    for (let i = 0; i < countries.length; i++) {
      if (canceled) break;
      setData((prevData) => [...prevData, countries[i]]);
      const percentCompleted = Math.round(((i + 1) / countries.length) * 100);
      setProgress(percentCompleted);
      await delay(10);
    }

    setLoading(false);
  } catch (error) {
    console.error("Error fetching data:", error);
    setLoading(false);
  }
}

const App = () => {
  const [loading, setLoading] = useState(true);
  const [progress, setProgress] = useState(0);
  const [data, setData] = useState([]);
  const [canceled, setCanceled] = useState(false);

  useEffect(() => {
    if (!canceled) {
      fetchData(canceled, setData, setLoading, setProgress);
    }
  }, [canceled]);

  const handleCancel = () => {
    setCanceled(true);
    setProgress(null);
  };

  return (
    <div style={{ padding: "20px" }}>
      <h1>Data Loading Simulation</h1>
      {loading ? (
        <ProgressBar
          title="Loading Data"
          percentage={canceled ? null : progress}
          onCancel={handleCancel}
        />
      ) : (
        <div>
          <h2>Loaded Data:</h2>
          <pre>{JSON.stringify(data, null, 2)}</pre>
        </div>
      )}
    </div>
  );
};

export default App;
