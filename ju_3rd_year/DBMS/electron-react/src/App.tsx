import { useEffect } from "react";
import M from "materialize-css";
import Navbar from "./Components/Navbar";
import { BrowserRouter, Route, Switch } from "react-router-dom";
import Add from "./Components/Add";
import Default from "./Components/Default";
import Notifier from "./Components/Notifier";
import Edit from "./Components/Edit";
import Search from "./Components/Search";
import Delete from "./Components/Delete";
import Show from "./Components/Show";

const App = (): JSX.Element => {
  useEffect(() => {
    M.AutoInit();
  });

  return (
    <>
      <Notifier />
      <BrowserRouter>
        <Navbar />
        <Switch>
          <Route path="/add" exact component={Add} />
          <Route path="/search" exact component={Search} />
          <Route path="/edit" exact component={Edit} />
          <Route path="/delete" exact component={Delete} />
          <Route path="/show" exact component={Show} />
          <Route path="/" component={Default} />
        </Switch>
      </BrowserRouter>
    </>
  );
};

export default App;
