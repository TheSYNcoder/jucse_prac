package com.travel.TravelApi.models;


import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

public class Flights {

    private ArrayList<Flight> flights;

    public Flights(){
        flights = new ArrayList<Flight>();
    }

    public void populateArray(ResultSet rs){
        while(true){
            try {
                if (!rs.next()) break;
                Flight newFlight = new Flight(rs.getInt("id") , rs.getString("logo"), rs.getString("company"),
                        rs.getString("code"),
                        rs.getString("date"), rs.getString("arrival_time"),
                        rs.getString("departure_time"), rs.getString("arrival_city"),
                        rs.getString("departure_city"), rs.getString("price"), rs.getInt("legs"));
                flights.add(newFlight);

            } catch (SQLException throwables) {
                throwables.printStackTrace();
            }

        }
    }

    public ArrayList<Flight> getFlights() {
        return flights;
    }
}
