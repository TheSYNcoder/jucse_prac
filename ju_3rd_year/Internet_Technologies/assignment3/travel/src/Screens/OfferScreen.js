import React from 'react';
import { withRouter } from 'react-router';
import {css, StyleSheet} from 'aphrodite';
import TravelCard from "../Components/FlightCard";


const OfferScreen = (props) => {

    function strikeThrough(text) {
  return text
    .split('')
    .map(char => char + '\u0336')
    .join('')
}

    const content = props.location.state.content;
    return (
        <div>
            <div className={css(styles.wrap)}>
                <div className={css(styles.heading)}>{content.offer_name.toUpperCase()}</div>
            </div>
            <div style={{ display:"flex" , width :"100%" , justifyContent : "center" , height: "auto" , 
     alignItems :"center", marginTop:"5em",
     flexDirection:"column"}}>
         <TravelCard 
                key={content.flight.id}
                image ={content.flight.logoUrl}
                legs ={content.flight.legs}
                price={content.flight.price}
                company={content.flight.company}
                acity={content.flight.acity}
                dcity={content.flight.dcity}
                atime={content.flight.atime}
                dtime={content.flight.dtime}
                date={content.flight.date}
                code={content.flight.code}
            />
     </div>
        <div className={css(styles.secondwrap)}>
            <div className={css(styles.secondheading)}>₹{strikeThrough(content.flight.price.substring(1))} <span style={{color:"green"}}>{content.price.substring(1)}</span></div>
            <div className={css(styles.secondheading)} style={{opacity:"0.5"}}>Valid upto : {content.valid_upto}</div>
        </div>
        <div className={css(styles.twrap)}>
            <div style={{fontSize:"2em" ,fontWeight:"bold", marginBottom:"3em"}}>Benefits</div>
            <ul>
                { content.benefits.split('|').map((e,i) => <li key={i} style={{fontSize:"1.2em"}}>{e}</li>)}
            </ul>
        </div>
        <div className={css(styles.twrap)}>
            <div style={{fontSize:"2em" ,fontWeight:"bold", marginBottom:"3em"}}>Terms and Conditions</div>
            <ul>
                { content.terms.split('|').map((e,i) => <li key={i} style={{fontSize:"1.2em"}}>{e}</li>)}
            </ul>
        </div>
        </div>
    )
}

const styles = StyleSheet.create({
    wrap:{
        width:"100%",
        height:"50vh",
        display:"flex",
        justifyContent:"center",
        alignItems:"center",
    },
    twrap:{
        width:"100%",
        height:"50vh",
        display:"flex",
        justifyContent:"center",
        alignItems:"center",
        flexDirection:"column",
    },
    heading : {
        fontSize:"4em",
        color:"red",
        fontWeight:"bold"
    },
    secondwrap:{
        width:"100%",
        height:"30vh",
        display:"flex",
        justifyContent:"center",
        alignItems:"center",
        flexDirection:"column"
    },
    secondheading : {
        fontSize:"3em",
        color:"red",
        fontWeight:"bold"
    },

})

export default withRouter(OfferScreen);