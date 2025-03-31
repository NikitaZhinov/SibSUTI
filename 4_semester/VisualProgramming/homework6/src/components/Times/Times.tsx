import { FC } from "react";

import "./Times.css";

import Time, { TimeProps } from "./Time";

export interface TimesProps {
  Times: Array<TimeProps>;
}

const Times: FC<TimesProps> = ({ Times }) => {
  return (
    <div className="Times">
      {Times.map((time) => (
        <Time
          Time={time.Time}
          Temperature={time.Temperature}
          Icon={time.Icon}
        ></Time>
      ))}
    </div>
  );
};

export default Times;
