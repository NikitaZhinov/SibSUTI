import { FC } from "react";

import "./Today.css";

export interface TodayProps {
  DayOfWeek: string;
  DayNumber: number;
}

const Today: FC<TodayProps> = ({ DayOfWeek, DayNumber }) => {
  return (
    <div className="Today">
      <p>
        {DayOfWeek}, {DayNumber}
      </p>
    </div>
  );
};

export default Today;
