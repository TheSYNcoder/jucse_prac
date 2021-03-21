import React from 'react';
import { css , StyleSheet} from 'aphrodite';

const OfferCard =(props) => {
    
    console.log(props);
    return (
        <div className={css(styles.card)} onClick={() => props.history.push({
            pathname :"/offer",
            state :{ content : props.content}
        })}>
              <div className={css(styles.cardimage)} style={{backgroundImage:`url(${props.image})`}}>
                <div className={css(styles.card_content)}>
                  <div className={css(styles.headingcard)}>{props.offer}</div>
                  <div className={css(styles.cardsubhead)}>Valid upto : {props.valid}</div>
                </div>
              </div>
          </div>
    );
}

export default OfferCard;

const styles= StyleSheet.create({

    card :{
      margin:"2em",
      // border:"1px solid black",
      borderRadius : 40,
      height : "250px", 
      width :"400px",
      // padding :"20px",
      boxShadow: "12px 12px 16px 0 rgba(0, 0, 0, 0.25),-8px -8px 12px 0 rgba(212, 210, 210, 0.3)",
      transition : "transform 1s",
      ":hover":{
          transform:"scale(1.2,1.2)",
      }
    },

    cardimage:{
    // position:"absolute",
    // backgroundImage: "url('./assets/lake.jpeg')",
    position:"relative",
    width :"100%",
    height:"100%",
    borderRadius : 40,
    backgroundPosition: "center", 
    backgroundRepeat: "no-repeat", 
    backgroundSize: "cover", 
    
    // filter: "blur(1px)",
  },
  card_content:{
    display:"flex",
    justifyContent:"center",
    alignItems:"center",
    padding:"1em",
    width:"100%",
    height:"100%",
    flexDirection:"column",
  },
  headingcard:{
    color :"white",
    fontSize : "3em",
    fontWeight:"bold",
  },
  cardsubhead:{
    color :"white",
    fontSize : "1em",
    fontWeight:"bold",
  },
})