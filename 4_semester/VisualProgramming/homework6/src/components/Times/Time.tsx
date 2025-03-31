import { FC } from "react";

export interface TimeProps {
  Time: Date;
  Temperature: number;
  Icon: string;
}

const Time: FC<TimeProps> = ({ Time, Temperature, Icon }) => {
  return (
    <div className="Time">
      <p className="TimeTime">
        {Time.getHours() === new Date().getHours()
          ? "Now"
          : `${Time.getHours()}:00`}
      </p>
      <b className="TimeTemperature">{Math.round(Temperature)}°</b>
      <img className="TimeIcon" src={`https://openweathermap.org/img/wn/${Icon}@2x.png`} alt="" />
    </div>
  );
};

export default Time;
