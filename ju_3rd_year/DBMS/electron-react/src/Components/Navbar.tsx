import React from 'react';
import { Link, Redirect } from "react-router-dom";
import styles from "./styles.module.scss";
import M from "materialize-css";

const Navbar = (): JSX.Element => {

  React.useEffect(() => {
    let ele = document.querySelectorAll('.tabs tabs-transparent');
    M.Tabs.init(ele);
  }, []);
  
  return (
    <>
      <nav className="nav-extended">
        <div className="nav-wrapper blue lighten-3">
          <a href="#link" className={styles.logo + " brand-logo right"}>
            Student Database
          </a>
          <ul id="nav" className="left">
            <li>
              {/* <Link to="/add">Add</Link> */}
              <a  href="/add">Add</a>
            </li>
            <li>
              <a  href="/search">Search</a>
            </li>
            <li>
              <a  href="/edit">Edit</a>
            </li>
            <li>
              <a  href="/delete">Delete</a>
            </li>
            <li>
              <a  href="/show">Display</a>
            </li>
          </ul>
        </div>
        <div className="nav-content blue lighten-2">
        <ul className="tabs tabs-transparent">
         <li className="tab" onClick={ () => <Redirect to="/add" /> }>
              <a  href="/add">Add</a>
            </li>
            <li className="tab">
              <a  href="/search">Search</a>
            </li>
            <li className="tab">
              <a  href="/edit">Edit</a>
            </li>
            <li className="tab">
              <a  href="/delete">Delete</a>
            </li>
            <li className="tab">
              <a  href="/show">Display</a>
            </li>
        </ul>
      </div>
      </nav>
    </>
  );
};

export default Navbar;
