package com.travel.TravelApi.models;

public class Flight {
    private int id;
    private String logoUrl;
    private String company;
    private String code;
    private String date;
    private String atime;
    private String dtime;
    private String acity;
    private String dcity;
    private String price;
    private int legs;

    public Flight(int id, String logoUrl, String company, String code, String date, String atime, String dtime, String acity, String dcity, String price, int legs) {
        this.id = id;
        this.logoUrl = logoUrl;
        this.company = company;
        this.code = code;
        this.date = date;
        this.atime = atime;
        this.dtime = dtime;
        this.acity = acity;
        this.dcity = dcity;
        this.price = price;
        this.legs = legs;
    }
}
