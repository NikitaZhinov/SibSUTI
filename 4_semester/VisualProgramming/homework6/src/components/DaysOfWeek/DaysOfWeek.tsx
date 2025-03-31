import { FC, CSSProperties } from "react";

import "./DaysOfWeek.css";

import DayOfWeek, { DayOfWeekProps } from "./DayOfWeek";

export interface DaysOfWeekProps {
  Days: Array<DayOfWeekProps>;
  style?: CSSProperties
}

const DaysOfWeek: FC<DaysOfWeekProps> = ({ Days, style }) => {
  return (
    <div className="DaysOfWeek" style={style}>
      {Days.map((day) => (
        <DayOfWeek
          DayOfWeek={day.DayOfWeek}
          DayNumber={day.DayNumber}
          WeatherIcon={day.WeatherIcon}
          MaxTemperature={day.MaxTemperature}
          MinTemperature={day.MinTemperature}
        ></DayOfWeek>
      ))}
    </div>
  );
};

export default DaysOfWeek;
