import { FC, useEffect, useState } from "react";

import "./MainInfo.css";

export interface MainInfoProps {
  City: string;
  Temperature: number;
  WeatherIcon: string;
  OnChangeCity?: any;
}

const MainInfo: FC<MainInfoProps> = ({
  City,
  Temperature,
  WeatherIcon,
  OnChangeCity,
}) => {
  const [backgound_color, setBackgrounColor] = useState("");

  useEffect(() => {
    if (WeatherIcon[WeatherIcon.length - 1] === "d")
      setBackgrounColor("#4d71f2");
    else setBackgrounColor("#010d38");
  }, [WeatherIcon]);

  return (
    <div className="MainInfo">
      <div className="MainInfoCityAndTemperature">
        <input
          className="MainInfoCity"
          type="text"
          defaultValue={City}
          style={{ backgroundColor: backgound_color }}
          onChange={(e) => OnChangeCity(e.target.value)}
        />
        <h1 className="MainInfoTemperature">
          {Temperature > 0 ? "+" : ""}
          {Math.round(Temperature)}°
        </h1>
      </div>
      <img
        className="MainInfoWeatherIcon"
        src={`https://openweathermap.org/img/wn/${WeatherIcon}@2x.png`}
        alt=""
      />
    </div>
  );
};

export default MainInfo;
