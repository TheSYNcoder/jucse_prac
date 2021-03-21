package com.travel.TravelApi.models;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.HashMap;

public class SPOffers {

    private ArrayList<Offer> offersList;

    public SPOffers() {
        offersList = new ArrayList<>();
    }

    public void populateArray(Connection conncetion){

        String queryOffers = "SELECT s.id, s.offer_name, s.valid, s.type, s.customer_benifits,s.terms,s.price_change,f.logo, f.company, f.code, f.date, f.arrival_time,f.departure_time,f.arrival_city, f.departure_city, f.price,f.legs FROM flights f INNER JOIN specialoffers s ON" +
                "    f.id=s.flight_id";
        try {
            Statement statement = conncetion.createStatement();
            ResultSet offers = statement.executeQuery(queryOffers);

            while(true){
                try {
                    if (!offers.next()) break;
                    Flight newFlight = new Flight(offers.getInt("id") , offers.getString("logo"), offers.getString("company"),
                            offers.getString("code"),
                            offers.getString("date"), offers.getString("arrival_time"),
                            offers.getString("departure_time"), offers.getString("arrival_city"),
                            offers.getString("departure_city"), offers.getString("price"), offers.getInt("legs"));

                    Offer offer = new Offer( offers.getInt("id"), offers.getString("offer_name"), offers.getString("valid"), offers.getString("type"), offers.getString("customer_benifits"), offers.getString("terms"), offers.getString("price_change"), newFlight );
                    offersList.add(offer);
                } catch (SQLException throwables) {
                    throwables.printStackTrace();
                }

            }

        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }

    }

    public ArrayList<Offer> getOffersList() {
        return offersList;
    }
}
