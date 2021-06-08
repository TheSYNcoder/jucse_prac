import { useContext, useEffect, useState } from "react";
import MainContext, { Student } from "../MainContext/MainContext";
import styles from "./styles.module.scss";
import M from "materialize-css";
import { modalNotify } from "./Notifier";

const Search = (): JSX.Element => {
  const { state } = useContext(MainContext);
  const [formState, setFormState] = useState<Student>({
    roll: "",
    deptCode: "",
    name: "",
    address: "",
    phone: "",
  });

  useEffect(() => {
    M.AutoInit();
  });

  const handleSearch = (): void => {
    const idx = state.students
      .map((student) => student.roll)
      .indexOf(formState.roll);
    if (idx !== -1) {
      setFormState(state.students[idx]);
    } else {
      modalNotify("Roll number not valid.");
      setFormState({
        roll: "",
        deptCode: "",
        name: "",
        address: "",
        phone: "",
      });
    }
  };

  return (
    <div className={styles.ht + " row valign-wrapper"}>
      <div className="col s12">
        <div className="center-align">
          <div className="row">
            <h2>Search student</h2>
          </div>
          <div className="row">
            <form
              className="col s10 offset-s1"
              onSubmit={(e) => {
                e.preventDefault();
              }}
            >
              <div className="row">
                <div className="input-field col s12">
                  <i className="material-icons prefix">tag</i>
                  <input
                    id="roll"
                    value={formState.roll}
                    type="text"
                    className="validate"
                    onChange={(e) => {
                      setFormState({ ...formState, roll: e.target.value });
                    }}
                  />
                  <label htmlFor="roll">Roll</label>
                </div>
              </div>
              <div className={styles.rowr + " row left-align"}>
                <div className="input-field col s12">
                  <h5>Name: {formState.name}</h5>
                </div>
              </div>
              <div className={styles.rowr + " row left-align"}>
                <div className="input-field col s12">
                  <h6>
                    Department:{" "}
                    {state.departments.filter(
                      (dept) => dept.deptCode === formState.deptCode
                    ).length
                      ? state.departments.filter(
                          (dept) => dept.deptCode === formState.deptCode
                        )[0].name
                      : ""}
                  </h6>
                </div>
              </div>
              <div className={styles.rowr + " row left-align"}>
                <div className="input-field col s12">
                  <h6>Address: {formState.address}</h6>
                </div>
              </div>
              <div className={styles.rowr + " row left-align"}>
                <div className="input-field col s12">
                  <h6>Phone: {formState.phone}</h6>
                </div>
              </div>
              <div className="row">
                <div className="col s3 offset-s3">
                  <button className="btn" onClick={handleSearch}>
                    Search
                  </button>
                </div>
                <div className="col s3">
                  <button
                    className="btn"
                    onClick={() => {
                      setFormState({
                        roll: "",
                        deptCode: "",
                        name: "",
                        address: "",
                        phone: "",
                      });
                    }}
                  >
                    Cancel
                  </button>
                </div>
              </div>
            </form>
          </div>
        </div>
      </div>
    </div>
  );
};

export default Search;
