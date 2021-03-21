import React from "react";
import { StyleSheet, css  } from "aphrodite";
import OfferCard from "../Components/OfferCard";
import TravelCard from "../Components/FlightCard";
import { Dropdown, DropdownToggle, DropdownMenu, DropdownItem } from 'reactstrap';
import Lake from "../assets/land.jpg";
import Sea from "../assets/sea.jpg";
import Cliff from "../assets/cliff.jpg";
import axios from 'axios';
import {Button} from 'reactstrap';
import { withRouter } from "react-router-dom";
import DatePicker from "react-datepicker";



function HomeScreen({history}){

    const [ arrival , setArrival ] = React.useState();
    const [departure , setDeparture ] = React.useState();
     const [adDropD, setadDropD ] = React.useState(false);
     const [depDropD, setddDropD ] = React.useState(false);
     const [ data, setData] = React.useState(null);
     const [filteredFlights , setFilteredFlights] = React.useState(null);
     const [ startDate, setStartDate ]= React.useState(null);
     const [ endDate, setEndDate ]= React.useState(null);
     

  const toggleAd = () => setadDropD(prevState => !prevState);
  const toggleDd = () => setddDropD(prevState => !prevState);



    React.useEffect(() => {
        axios.get( 'http://localhost:8080/TravelApi_war_exploded/api').
        then(response =>  {
            console.log(response);
            setData(response.data);
            setFilteredFlights(response.data.flights);
        })
        
        .catch( err => console.log(err));
    }, [] );

    const handleClick = (type) => (e) => {
        if ( type === 'arrival'){
            setArrival(e.target.innerText);
        }
        else{
            setDeparture(e.target.innerText);
        }
    }
    const Citydata = (type) => {
        return(
            <DropdownMenu>
                <DropdownItem onClick={handleClick(type)}>chandigarh</DropdownItem>
                <DropdownItem onClick={handleClick(type)}>bangalore</DropdownItem>
                <DropdownItem onClick={handleClick(type)}>hyderabad</DropdownItem>
                <DropdownItem onClick={handleClick(type)}>bhopal</DropdownItem>
                <DropdownItem onClick={handleClick(type)}>mumbai</DropdownItem>
                <DropdownItem onClick={handleClick(type)}>srinagar</DropdownItem>
                <DropdownItem onClick={handleClick(type)}>kerala</DropdownItem>
                <DropdownItem onClick={handleClick(type)}>kolkata</DropdownItem>
                <DropdownItem onClick={handleClick(type)}>madras</DropdownItem>
                <DropdownItem onClick={handleClick(type)}>guwahati</DropdownItem>
                <DropdownItem onClick={handleClick(type)}>delhi</DropdownItem>
            </DropdownMenu>
        )
    }

    const FilterData = () => {
        var flights = data.flights;
        if ( arrival ){
            flights = flights.filter( f => f.acity === arrival);
        }
        if ( departure ){
            flights = flights.filter(f => f.dcity === departure);
        }
        if ( startDate && endDate ){
            flights = flights.filter(function(f) { return new Date(f.date) >= startDate && new Date(f.date) <= endDate });
        }
        setFilteredFlights(flights);
    }

    const ClearFilters =() =>{
        setFilteredFlights( data.flights);
        setArrival('');
        setDeparture('');
        setStartDate(null);
        setEndDate(null);
    }




    return(
        data === null || filteredFlights === null ? <div></div> :
        <div>
            <div className={css(styles.image)} style={{backgroundImage:`url(${Lake})`}} />

            <div style={{display:"flex", width:"100%"}}>
            <div className={css(styles.heading)}>Travel-Thru-Air</div>
            <div className={css(styles.subhead)}>Booking flights have never been easier</div>
            </div>


            <div style={{width:"100%", fontSize:"3em",  height:"80px", color :"#ff7a7a", display:"flex", justifyContent:"center", alignItems:"center" }}>
            Don't miss out on the latest offers
            </div>
        



        <div style={{width:"100%" , height:"auto" , display:"flex", flexDirection:"row"}}>
          
          <OfferCard 
            image={Sea}
            offer={data.offers[0].offer_name}
            valid={data.offers[0].valid_upto}
            history={history}
            content={data.offers[0]}
          />
          <OfferCard 
            image={Lake}
            offer={data.offers[1].offer_name}
            valid={data.offers[1].valid_upto}
            history={history}
            content={data.offers[1]}
          />
          <OfferCard 
            image={Cliff}
            offer={data.offers[2].offer_name}
            valid={data.offers[2].valid_upto}
            history={history}
            content={data.offers[2]}
          />
          
        </div>

        <div style={{width:"100%" , marginTop:"3em",
        display:"flex", eflexDirection:"row", justifyContent:"center"}}>
        <Dropdown className={css(styles.dropdowns)}  isOpen={adDropD} toggle={toggleAd} color="primary">
          <DropdownToggle caret>
            { arrival ? arrival : "Select arrival city"}
          </DropdownToggle>
          { Citydata('arrival')}
        </Dropdown>

        <Dropdown className={css(styles.dropdowns)} color="primary" isOpen={depDropD} toggle={toggleDd}>
          <DropdownToggle caret>
            { departure ? departure : "Select departure city"}
          </DropdownToggle>
          {Citydata('departure')}
        </Dropdown>
        <div style={{display:"flex" , flexDirection:"column", marginRight:"12px"}}>
            <div>Start date</div>
            <DatePicker selected={startDate ? startDate : new Date()} onChange={date => setStartDate(date)}  />
        </div>
        <div style={{display:"flex" , flexDirection:"column", marginRight:"12px"}}>
            <div>End date</div>
            <DatePicker selected={endDate ? endDate : new Date()} onChange={date => setEndDate(date)} />
        </div>

        <Button color="warning" onClick={FilterData} >Filter</Button>
        <Button color="danger" onClick={ClearFilters} style={{marginLeft:"1em"}}>Clear Filters</Button>
        </div>
        

     <div style={{ display:"flex" , width :"100%" , justifyContent : "center" , height: "auto" , 
     alignItems :"center", marginTop:"5em",
     flexDirection:"column"}}>
      {/* <TravelCard /> */}
      {
          filteredFlights.map( (fl,i) => 
            <TravelCard 
                key={filteredFlights[i].id}
                image ={filteredFlights[i].logoUrl}
                legs ={filteredFlights[i].legs}
                price={filteredFlights[i].price}
                company={filteredFlights[i].company}
                acity={filteredFlights[i].acity}
                dcity={filteredFlights[i].dcity}
                atime={filteredFlights[i].atime}
                dtime={filteredFlights[i].dtime}
                date={filteredFlights[i].date}
                code={filteredFlights[i].code}
            />
          )
    }
    </div>
        </div>
    )
}

export default withRouter(HomeScreen);

const styles = StyleSheet.create({
    top_wrap :{
    position : "relative",
  },
  image:{
    // position:"absolute",
    // backgroundImage: "url('./assets/lake.jpeg')",
    position:"relative",
    width :"100%",
    height:"100vh",
    backgroundPosition: "center", 
    backgroundRepeat: "no-repeat", 
    backgroundSize: "cover", 
  },
  heading:{
    display:"flex",
    fontFamily: "Lobster, cursive",
    position:"absolute",
    top : "0.5em",
    left :"0.3em",
    padding : "0.4em",
    fontSize :"8em",
    
    color: "white",
    width:"100%",
    '@media only screen and (max-width: 600px)':{
      fontSize : "4em",
      padding :"0em",
      left :"0.6em",
      top:"2em",
    }

  },
  subhead:{
    opacity:"0.9",
    position:"absolute",
    top : "6em",
    left :"0.3em",
    padding : "1.2em",
    fontSize :"3em",
    color: "white",
    width:"70%",
    '@media only screen and (max-width: 600px)':{
      fontSize : "1.5em",
      padding :"0em",
      left :"0.6em",
      top:"10em",
      width :"90%"
    }

  },
  dropdowns:{
      marginLeft:"1em",
      marginRight:"1em"
  }
})