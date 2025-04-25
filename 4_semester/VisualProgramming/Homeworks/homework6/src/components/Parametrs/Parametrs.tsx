import { FC } from "react";

import "./Parametrs.css";

export interface ParametrsProps {
  Humidity: number;
  Wind: number;
  AirPressure: number;
  UV: number;
}

const Parametrs: FC<ParametrsProps> = ({ Humidity, Wind, AirPressure, UV }) => {
  return (
    <div className="Parametrs">
      <div className="ParametrsParametr">
        <p className="ParametrsName">Humidity</p>
        <b className="ParametrsValue">{Humidity}%</b>
      </div>
      <div className="ParametrsParametr">
        <p className="ParametrsName">Wind</p>
        <b className="ParametrsValue">{Wind} m/s</b>
      </div>
      <div className="ParametrsParametr">
        <p className="ParametrsName">Air Pressure</p>
        <b className="ParametrsValue">{AirPressure} mm</b>
      </div>
      <div className="ParametrsParametr">
        <p className="ParametrsName">UV</p>
        <b className="ParametrsValue">{UV}</b>
      </div>
    </div>
  );
};

export default Parametrs;
