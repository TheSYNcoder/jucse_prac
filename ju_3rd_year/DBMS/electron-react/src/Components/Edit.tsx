import { useContext, useEffect, useState } from "react";
import MainContext, { Student } from "../MainContext/MainContext";
import styles from "./styles.module.scss";
import M from "materialize-css";
import { modalNotify } from "./Notifier";
import ActionTypes from "../MainContext/ActionTypes";

const Edit = (): JSX.Element => {
  const { state, dispatch } = useContext(MainContext);
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

  useEffect(() => {
    const idx = state.students
      .map((student) => student.roll)
      .indexOf(formState.roll);
    if (idx !== -1) {
      setFormState(state.students[idx]);
    } else {
      setFormState({
        ...formState,
        deptCode: "",
        name: "",
        address: "",
        phone: "",
      });
    }
    // eslint-disable-next-line
  }, [formState.roll]);

  const handleSave = (): void => {
    if (
      state.students.map((student) => student.roll).indexOf(formState.roll) !==
      -1
    ) {
      dispatch({ type: ActionTypes.EDIT_STUDENT, payload: formState });
      modalNotify("Ok saved");
    } else {
      modalNotify("Roll number not valid.");
    }
  };

  return (
    <div className={styles.ht + " row valign-wrapper"}>
      <div className="col s12">
        <div className="center-align">
          <div className="row">
            <h2>Edit student</h2>
          </div>
          <div className="row">
            <form
              className="col s10 offset-s1"
              onSubmit={(e) => {
                e.preventDefault();
              }}
            >
              <div className="row">
                <div className="input-field col s4">
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
                <div className="input-field col s8">
                  <select
                    value={formState.deptCode}
                    onChange={(e) => {
                      setFormState({ ...formState, deptCode: e.target.value });
                    }}
                  >
                    <option value="" disabled selected>
                      Choose your department
                    </option>
                    {state.departments.map((department, index) => (
                      <option key={index} value={department.deptCode}>
                        {department.name}
                      </option>
                    ))}
                  </select>
                  <label>Select Department</label>
                </div>
              </div>
              <div className="row">
                <div className="input-field col s12">
                  <i className="material-icons prefix">account_circle</i>
                  <input
                    id="name"
                    type="text"
                    className="validate"
                    value={formState.name}
                    onChange={(e) =>
                      setFormState({ ...formState, name: e.target.value })
                    }
                  />
                  <label htmlFor="name">Name</label>
                </div>
              </div>
              <div className="row">
                <div className="input-field col s12">
                  <i className="material-icons prefix">home</i>
                  <textarea
                    id="address"
                    className="materialize-textarea"
                    value={formState.address}
                    onChange={(e) => {
                      setFormState({ ...formState, address: e.target.value });
                    }}
                  />
                  <label htmlFor="address">Address</label>
                </div>
              </div>
              <div className="row">
                <div className="input-field col s6">
                  <i className="material-icons prefix">phone</i>
                  <input
                    id="phone"
                    type="tel"
                    className="validate"
                    value={formState.phone}
                    onChange={(e) => {
                      setFormState({ ...formState, phone: e.target.value });
                    }}
                  />
                  <label htmlFor="phone">Phone</label>
                </div>
                <div className="col s3">
                  <button className="btn" onClick={handleSave}>
                    Save
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

export default Edit;
