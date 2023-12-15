package com.booking.recruitment.hotel.controller;

import com.booking.recruitment.hotel.model.Hotel;
import com.booking.recruitment.hotel.model.City;
import com.booking.recruitment.hotel.service.CityService;
import com.booking.recruitment.hotel.service.SearchService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/search")
public class SearchController {
    private final SearchService searchService;
    private final CityService cityService;

    @Autowired
    public SearchController(SearchService searchService, CityService cityService) {

        this.searchService = searchService;
        this.cityService = cityService;
    }

    @GetMapping("/{cityId}")
    @ResponseStatus(HttpStatus.OK)
    /*
    * api to fetch the closest hotel given the cityId in path variable
    * */
    public List<Hotel> getClosestHotels(@PathVariable("cityId") Long cityId) {
        City city = cityService.getCityById(cityId);
        return searchService.getClosestHotels(city, 3);
    }
}
