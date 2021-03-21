import React from "react";
import { StyleSheet, css  } from "aphrodite";

import 'bootstrap/dist/css/bootstrap.min.css';
import "react-datepicker/dist/react-datepicker.css";
import { Row, Col } from 'reactstrap';
import "./App.css";

import HomeScreen from "./Screens/HomeScreen";
import OfferScreen from "./Screens/OfferScreen";
import { BrowserRouter as Router, Route,Switch } from "react-router-dom";
function App() {
  return (
    <div className={css(styles.top_wrap)}>
       <Router>
         <Switch>
           <Route exact path="/" render={props => <HomeScreen /> }/>
           <Route exact path="/offer" render={props => <OfferScreen /> }/>
         </Switch>
       </Router>
    </div>
  );
}

const styles= StyleSheet.create({
})

export default App;
