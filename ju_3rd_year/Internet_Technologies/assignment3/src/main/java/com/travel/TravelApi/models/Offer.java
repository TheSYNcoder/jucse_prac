package com.travel.TravelApi.models;

public class Offer {

    private int id;
    private String offer_name;
    private String valid_upto;
    private String type;
    private String benefits;
    private String terms;
    private String price;
    private  Flight flight;

    public Offer(int id, String offer_name, String valid_upto, String type, String benefits, String terms, String price, Flight flight) {
        this.id = id;
        this.offer_name = offer_name;
        this.valid_upto = valid_upto;
        this.type = type;
        this.benefits = benefits;
        this.terms = terms;
        this.price = price;
        this.flight = flight;
    }
}
