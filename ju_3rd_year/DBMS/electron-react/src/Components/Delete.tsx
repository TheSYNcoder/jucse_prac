import { useContext, useEffect, useState } from "react";
import MainContext from "../MainContext/MainContext";
import styles from "./styles.module.scss";
import M from "materialize-css";
import { modalNotify } from "./Notifier";
import ActionTypes from "../MainContext/ActionTypes";

const Delete = (): JSX.Element => {
  const { state, dispatch } = useContext(MainContext);
  const [formState, setFormState] = useState({ roll: "" });

  useEffect(() => {
    M.AutoInit();
  });

  const handleDelete = (): void => {
    const idx = state.students
      .map((student) => student.roll)
      .indexOf(formState.roll);
    if (idx !== -1) {
      dispatch({ type: ActionTypes.DELETE_STUDENT, payload: formState.roll });
      modalNotify("Ok deleted.");
    } else {
      modalNotify("Roll number not valid.");
    }
  };

  return (
    <div className={styles.ht + " row valign-wrapper"}>
      <div className="col s12">
        <div className="center-align">
          <div className="row">
            <h2>Delete student</h2>
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
              <div className="row">
                <div className="col s3 offset-s3">
                  <button className="btn" onClick={handleDelete}>
                    Delete
                  </button>
                </div>
                <div className="col s3">
                  <button
                    className="btn"
                    onClick={() => {
                      setFormState({
                        roll: "",
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

export default Delete;
