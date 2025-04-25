import React from "react";

const ProgressBar = ({ title, percentage, onCancel }) => {
  const isCanceled = percentage === null;

  return (
    <div className="LenDumat">
      <h3>{title}</h3>
      <div className="LenDumat2">
        <div className="LenDumat3">
          <div
            style={{
              width: isCanceled ? "100%" : `${percentage}%`,
              height: "100%",
              backgroundColor: isCanceled ? "#ff6b6b" : "#76c7c0",
              borderRadius: "10px",
              transition: "width 0.3s ease",
            }}
          />
        </div>
        <span style={{ marginLeft: "10px" }}>
          {isCanceled ? "Canceled" : `${percentage}%`}
        </span>
      </div>
      <button
        onClick={onCancel}
        disabled={isCanceled}
        style={{ marginTop: "10px" }}
      >
        Cancel
      </button>
    </div>
  );
};

export default ProgressBar;
