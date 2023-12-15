package com.booking.recruitment.hotel.service.impl;

import com.booking.recruitment.hotel.service.CityService;
import com.booking.recruitment.hotel.service.HotelService;
import com.booking.recruitment.hotel.service.SearchService;
import com.booking.recruitment.hotel.model.Hotel;
import com.booking.recruitment.hotel.model.City;
import com.booking.recruitment.hotel.util.HaversineDistance;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;


/*
* Service dealing with business logic for the application.
* This Service has dependency on cityService and hotelService and are injected
* via constructor dependency injection
* */
@Service
public class DefaultSearchService implements SearchService {

    private final CityService cityService;
    private final HotelService hotelService;

    @Autowired
    DefaultSearchService(CityService cityService, HotelService hotelService) {
        this.cityService = cityService;
        this.hotelService = hotelService;
    }

    @Override
    /*
    * fetches the closest hotels to the city center according to haversine distance formula
    * Limit by default is 3.
    * */
    public List<Hotel> getClosestHotels(City city, int limit) {
        List<Hotel> hotels = hotelService.getAllHotels();
        Collections.sort(hotels, new Comparator<Hotel>() {
            @Override
            public int compare(Hotel a, Hotel b) {
                Double dis1 = HaversineDistance.calc_haversine_distance(city.getCityCentreLatitude(), city.getCityCentreLongitude()
                        , a.getLatitude(), a.getLongitude());
                Double dis2 = HaversineDistance.calc_haversine_distance(city.getCityCentreLatitude(), city.getCityCentreLongitude()
                        , b.getLatitude(), b.getLongitude());
                if (dis1 - dis2 > 0) return 1;
                if (dis1 - dis2 == 0) return 0;
                return -1;
            }
        });

        return hotels.stream().limit(limit).collect(Collectors.toList());
    }
}
