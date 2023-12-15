package com.booking.recruitment.hotel.service;

import com.booking.recruitment.hotel.model.City;
import com.booking.recruitment.hotel.model.Hotel;
import java.util.List;

public interface SearchService {

    List<Hotel> getClosestHotels(City city, int limit);
}

