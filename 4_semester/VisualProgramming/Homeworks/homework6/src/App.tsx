import "./App.css";

import Today from "./components/Today/Today";
import MainInfo from "./components/MainInfo/MainInfo";
import Times from "./components/Times/Times";
import Parametrs from "./components/Parametrs/Parametrs";
import DaysOfWeek from "./components/DaysOfWeek/DaysOfWeek";
import { useEffect, useState } from "react";
import axios from "axios";
import { DayOfWeekProps } from "./components/DaysOfWeek/DayOfWeek";

const API_KEY = "89fb090b41535bd38cde27f3b2ca3ba6";

const DAYS_OF_WEEK = [
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday",
];

interface DayWeather {
  Time: Date;
  Temperature: number;
  MaxTemperature: number;
  MinTemperature: number;
  Icon: string;
  Humidity: number;
  Wind: number;
  AirPressure: number;
  UV: number;
  POD: string;
}

async function getPos(city: string) {
  try {
    const promis = await axios.get(
      `http://api.openweathermap.org/geo/1.0/direct?q=${city}&limit=1&appid=${API_KEY}`
    );
    const pos = promis.data[0];
    return [pos.lat, pos.lon];
  } catch (err) {
    console.error("cant load pos");
    return [0, 0];
  }
}

async function loadData(city: string) {
  const [lat, lon] = await getPos(city);
  let data;
  try {
    const promis = await axios.get(
      `http://api.openweathermap.org/data/2.5/forecast?lat=${lat}&lon=${lon}&units=metric&appid=${API_KEY}`
    );
    data = promis.data.list;
  } catch (err) {
    console.error("cant load weather");
  }
  return data;
}

async function getWeather(city: string) {
  let days = Array<DayWeather>();

  for (const day of await loadData(city)) {
    days.push({
      Time: new Date(day.dt * 1000),
      Temperature: day.main.temp,
      MaxTemperature: day.main.temp_max,
      MinTemperature: day.main.temp_min,
      Icon: day.weather[0].icon,
      Humidity: day.main.humidity,
      Wind: day.wind.speed,
      AirPressure: day.main.pressure * 0.75,
      UV: 0,
      POD: day.sys.pod,
    });
  }

  return days;
}

function updateWeather(
  city: string,
  days: Array<DayWeather>,
  setDays: React.Dispatch<React.SetStateAction<DayWeather[]>>,
  setBackgrounColor: React.Dispatch<React.SetStateAction<string>>,
  setBackgrounColorNextDays: React.Dispatch<React.SetStateAction<string>>,
  setNextDays: React.Dispatch<React.SetStateAction<DayOfWeekProps[]>>
) {
  getWeather(city).then((res) => setDays(res));

  if (days.length !== 0) {
    if (days[0].POD === "d") {
      setBackgrounColor("#4d71f2");
      setBackgrounColorNextDays("#708df4");
    } else {
      setBackgrounColor("#010d38");
      setBackgrounColorNextDays("#333D5F");
    }

    const cur_day = days[0].Time.getDay();
    let new_next_days = Array<DayOfWeekProps>();

    for (const day of days) {
      let is_exist = false;
      for (const next_day of new_next_days) {
        if (
          next_day.DayOfWeek === DAYS_OF_WEEK[day.Time.getDay()] ||
          cur_day === day.Time.getDay()
        ) {
          is_exist = true;
          break;
        }
      }
      if (!is_exist) {
        const day_name = day.Time.getDay();
        let max_temp = day.MaxTemperature;
        let min_temp = day.MinTemperature;
        for (const d of days) {
          if (d.Time.getDay() === day_name) {
            if (max_temp < d.MaxTemperature) max_temp = d.MaxTemperature;
            if (min_temp > d.MinTemperature) min_temp = d.MinTemperature;
          }
        }
        new_next_days.push({
          DayOfWeek: DAYS_OF_WEEK[day.Time.getDay()],
          DayNumber: day.Time.getDate(),
          WeatherIcon: day.Icon,
          MaxTemperature: max_temp,
          MinTemperature: min_temp,
        });
      }
    }

    setNextDays(new_next_days);
  }
}

const App = () => {
  const [city, setCity] = useState("");
  const [days, setDays] = useState(Array<DayWeather>);
  const [next_days, setNextDays] = useState(Array<DayOfWeekProps>);
  const [backgound_color, setBackgrounColor] = useState("");
  const [backgound_color_next_days, setBackgrounColorNextDays] = useState("");

  useEffect(() => {
    if (city === "") setCity("London");
    const timer = setTimeout(
      () =>
        updateWeather(
          city,
          days,
          setDays,
          setBackgrounColor,
          setBackgrounColorNextDays,
          setNextDays
        ),
      500
    );
    return () => clearTimeout(timer);
  }, [city, days]);

  return (
    <>
      {days.length !== 0 ? (
        <div className="App" style={{ backgroundColor: backgound_color }}>
          <Today
            DayOfWeek={DAYS_OF_WEEK[days[0].Time.getDay()]}
            DayNumber={days[0].Time.getDate()}
          ></Today>
          <MainInfo
            City={city}
            Temperature={days[0].Temperature}
            WeatherIcon={days[0].Icon}
            OnChangeCity={(new_city: string) =>
              // setTimeout(() => setCity(new_city), 1000)
              setCity(new_city)
            }
          ></MainInfo>
          <Times
            Times={[
              {
                Time: days[0].Time,
                Temperature: days[0].Temperature,
                Icon: days[0].Icon,
              },
              {
                Time: days[1].Time,
                Temperature: days[1].Temperature,
                Icon: days[1].Icon,
              },
              {
                Time: days[2].Time,
                Temperature: days[2].Temperature,
                Icon: days[2].Icon,
              },
              {
                Time: days[3].Time,
                Temperature: days[3].Temperature,
                Icon: days[3].Icon,
              },
              {
                Time: days[4].Time,
                Temperature: days[4].Temperature,
                Icon: days[4].Icon,
              },
            ]}
          ></Times>
          <Parametrs
            Humidity={days[0].Humidity}
            Wind={days[0].Wind}
            AirPressure={days[0].AirPressure}
            UV={days[0].UV}
          ></Parametrs>
          <DaysOfWeek
            Days={next_days}
            style={{ backgroundColor: backgound_color_next_days }}
          ></DaysOfWeek>
        </div>
      ) : (
        <></>
      )}
    </>
  );
};

export default App;
