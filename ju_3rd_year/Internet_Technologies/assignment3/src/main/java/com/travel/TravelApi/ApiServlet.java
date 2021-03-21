package com.travel.TravelApi;

import com.google.gson.Gson;
import com.travel.TravelApi.models.Flight;
import com.travel.TravelApi.models.Flights;
import com.travel.TravelApi.models.Offer;
import com.travel.TravelApi.models.SPOffers;

import java.io.*;
import java.sql.*;
import java.util.ArrayList;
import java.util.HashMap;
import javax.servlet.ServletContext;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "helloServlet", value = "/api")
public class ApiServlet extends HttpServlet {

    private ServletContext context;
    private Connection dbConnection;
    private String loginUser;
    private String password;
    private String dbDriver;

    public void init() {
        context = getServletContext();
        loginUser = context.getInitParameter("loginUser");
        password = context.getInitParameter("password");
        dbDriver = context.getInitParameter("driver");

        try {
            Class.forName("org.postgresql.Driver");
            dbConnection = DriverManager.getConnection( dbDriver, loginUser, password );
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        }

    }

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("application/json");

        try {
            Statement statement = dbConnection.createStatement();
            String query = "SELECT id, logo, company, code," +
                    "TO_CHAR(date, 'Mon dd, yyyy') AS date, arrival_time, departure_time, arrival_city, " +
                    "departure_city, price, legs  FROM flights";
            ResultSet rs = statement.executeQuery(query);
            Flights fl = new Flights();
            SPOffers sp = new SPOffers();
            fl.populateArray(rs);
            sp.populateArray(dbConnection);
            ArrayList<Flight>  flights= fl.getFlights();
            ArrayList<Offer> spOffers = sp.getOffersList();
            HashMap<String, ArrayList> ret = new HashMap<>();
            ret.put("flights" , flights);
            ret.put("offers" , spOffers);
            String flightsJson = new Gson().toJson(ret);
            PrintWriter out = response.getWriter();

            out.print(flightsJson);
            out.flush();
            statement.close();

        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }

    }

    public void destroy() {
    }
}