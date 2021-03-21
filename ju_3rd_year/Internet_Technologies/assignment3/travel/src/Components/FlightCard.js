import React from 'react';
import { css , StyleSheet} from 'aphrodite';

const TravelCard =(props) => {
    
    
    return (
        <div className={css(styles.travel_card)}>
         <div className={css(styles.travelfirst)}>
            <img src={props.image} className={css(styles.rounded_image)} alt="plane"></img>
            <div className={css(styles.companytext)}>{props.company}</div>
         </div>
         <div className={css(styles.travelsecond)}>
           <div className={css(styles.travelcodewrap)}>
              <div className={css(styles.travelcode)}>{props.code}</div>
              <div className={css(styles.travelcode)}>{props.date}</div>
            </div>
            <div className={css(styles.travelcities)}>
              <div className={css(styles.travelcity)}>
                  <div className={css(styles.travel__city)}>{props.acity}</div>
                  <div className={css(styles.travel_dur)}>{props.atime}</div>
              </div>
              <div className={css(styles.travelcity)}>✈️</div>
              <div className={css(styles.travelcity)}>
                  <div className={css(styles.travel__city)}>{props.dcity}</div>
                  <div className={css(styles.travel_dur)}>{props.dtime}</div>
              </div>
            </div>
         </div>
         <div className={css(styles.travelthird)}>
           <div className={css(styles.travelprice)}>₹{props.price.substring(1)}</div>
           <div className={css(styles.travellegs)}>Legs:{props.legs}</div>
         </div>
       </div>
    );
}

export default TravelCard;

const styles= StyleSheet.create({
    
  // Travel Card
  travel_card :{ 
      marginBottom : "3em",
      width : "90%",
      borderRadius : 20,
      // border : "1px solid black",
      height : "200px",
      boxShadow: "12px 12px 18px 0 rgba(0, 0, 0, 0.25),-8px -8px 8px 0 rgba(212, 210, 210, 0.3)",
      display:"flex",
      flexDirection:"row",

  },

  travelfirst:{
    width : "18%",
    display : "flex",
    flexDirection : "column",
    padding  : "2em",
    height :"100%",
    // border : "1px solid black",
    justifyContent :"center",
    alignItems:"center",
  },

  rounded_image:{
    borderRadius : 40,
    height :"80px",
    width :"80px",
  },
  companytext :{
    fontSize : "2em",
  },

  travelsecond:{
    width : "68%",
    display : "flex",
    flexDirection : "column",
    padding  : "1em",
    height :"100%",
    // border : "1px solid black",
    
  },
  travelcodewrap:{
    display:"flex",
    flexDirection:"row",
    justifyContent:"space-between",
    alignItems:"center",
  },

  travelcode:{
    fontSize :"20px",
    paddingLeft : "0.8em",
    paddingRight:"0.8em",
    // marginLeft:"2em",
    fontWeight:"bold",
    height:"20%",
  },
  travelcities:{
    height:"80%",
    width:"100%",
    display:"flex",
    flexDirection:"row",
    justifyContent:"center",
    alignItems:"center",
  },
  travelcity:{
    padding:"1em",
    fontSize:"40px",
    display:"flex",
    flexDirection:"column",
  },
  travel__city:{
      fontSize:"30px",
      fontWeight:"bold"
  },
  travel_dur:{
      fontSize:"25px",
      opacity:"0.5",
  },

  travelthird:{
    width : "20%",
    display : "flex",
    flexDirection : "column",
    padding  : "1em",
    height :"100%",
    // border : "1px solid black",
    alignItems:"center",
    justifyContent:"center",
  },

  travelprice:{
    color :"orange",
    fontSize:"30px",
    
  },
  travellegs:{
    opacity:"0.7",
    fontSize:"15px",
  }

})