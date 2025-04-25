import { FC } from "react";

export interface DayOfWeekProps {
  DayOfWeek: string;
  DayNumber: number;
  WeatherIcon: string;
  MaxTemperature: number;
  MinTemperature: number;
}

const DayOfWeek: FC<DayOfWeekProps> = ({
  DayOfWeek,
  DayNumber,
  WeatherIcon,
  MaxTemperature,
  MinTemperature,
}) => {
  return (
    <div className="DayOfWeek">
      <p className="DayOfWeekDayOfWeekDayNumber">
        {DayOfWeek}, {DayNumber}
      </p>
      <div className="DayOfWeekWeather">
        <img
          className="DayOfWeekIcon"
          src={`https://openweathermap.org/img/wn/${WeatherIcon}@2x.png`}
          alt=""
        />
        <p className="DayOfWeekMaxTemperature">
          {MaxTemperature > 0 ? "+" : ""}
          {Math.ceil(MaxTemperature)}°
        </p>
        <p className="DayOfWeekMinTemperature">
          {MinTemperature > 0 ? "+" : ""}
          {Math.floor(MinTemperature)}°
        </p>
      </div>
    </div>
  );
};

export default DayOfWeek;
