import React from "react";
import ReactDOM from "react-dom";
import "./index.css";
import { MainContextProvider } from "./MainContext/MainContext";
import App from "./App";
import reportWebVitals from "./reportWebVitals";

ReactDOM.render(
  <React.StrictMode>
    <MainContextProvider>
      <App />
    </MainContextProvider>
  </React.StrictMode>,
  document.getElementById("root")
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();
