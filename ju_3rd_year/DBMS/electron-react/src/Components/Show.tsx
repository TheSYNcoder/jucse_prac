import { useContext, useEffect } from "react";
import MainContext from "../MainContext/MainContext";
import styles from "./styles.module.scss";
import M from "materialize-css";
import { TablePagination } from "react-pagination-table";

const Show = (): JSX.Element => {
  const { state } = useContext(MainContext);

  useEffect(() => {
    M.AutoInit();
  });

  const Header = ["Roll", "Name", "Department", "Address", "Phone"];
  const data = state.students.map((student) => ({
    ...student,
    dept: state.departments
      .filter((dept) => dept.deptCode === student.deptCode)
      .map((dept) => dept.name),
  }));

  return (
    <div className={styles.ht + " row valign-wrapper"}>
      <div className="col s12">
        <div className="center-align">
          <div className="row">
            <h2>Show all students</h2>
          </div>
          <div className={styles.table}>
            <TablePagination
              title="Student Information"
              headers={Header}
              data={data}
              columns="roll.name.dept.address.phone"
              perPageItemCount={5}
              totalCount={data.length}
              arrayOption={[["dept", "all", " "]]}
            />
          </div>
        </div>
      </div>
    </div>
  );
};

export default Show;
