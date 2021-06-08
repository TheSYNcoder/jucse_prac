import styles from "./styles.module.scss";

const Default = (): JSX.Element => {
  return (
    <div className={styles.ht + " row valign-wrapper"}>
      <div className="col s12">
        <div className="center-align">
          <h2>Nothing to show.</h2>
        </div>
      </div>
    </div>
  );
};

export default Default;
