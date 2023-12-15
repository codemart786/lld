package com.booking.recruitment.hotel.controller;

import com.booking.recruitment.hotel.exception.BadRequestException;
import com.booking.recruitment.hotel.exception.ElementNotFoundException;
import com.booking.recruitment.hotel.model.Hotel;
import com.booking.recruitment.hotel.service.HotelService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import javax.swing.text.html.Option;
import java.util.Optional;

import java.util.List;

@RestController
@RequestMapping("/hotel")
public class HotelController {
  private final HotelService hotelService;

  @Autowired
  public HotelController(HotelService hotelService) {
    this.hotelService = hotelService;
  }

  @GetMapping
  @ResponseStatus(HttpStatus.OK)
  public List<Hotel> getAllHotels() {
    return hotelService.getAllHotels();
  }

  @GetMapping(value = "/{id}")
  @ResponseStatus(HttpStatus.OK)
  public Hotel getHotel(@PathVariable("id") Long id) throws BadRequestException,ElementNotFoundException {
    Optional<Hotel> hotelDetail = hotelService.getHotelDetail(id);
    if (!hotelDetail.isPresent()) {
      throw new BadRequestException("Invalid Request");
    }
    Hotel hotel = hotelDetail.get();
    if (hotel.isDeleted()) {
      throw new ElementNotFoundException("Id not present in our DB. Please check the ID and try again");
    }
    return hotel;
  }

  @DeleteMapping(value = "/{id}")
  @ResponseStatus(HttpStatus.OK)
  public ResponseEntity<String> deleteHotel(@PathVariable("id") Long id) throws BadRequestException, ElementNotFoundException {
    Optional<Hotel> hotelDetail = hotelService.getHotelDetail(id);
    if (!hotelDetail.isPresent()) {
      throw new BadRequestException("Invalid Request");
    }
    Hotel hotel = hotelDetail.get();
    try {
      hotelService.deleteHotel(hotel);
    } catch (ElementNotFoundException e) {
      throw e;
    }
    return new ResponseEntity<>("success", HttpStatus.OK);
  }

  @PostMapping
  @ResponseStatus(HttpStatus.CREATED)
  public Hotel createHotel(@RequestBody Hotel hotel) {
    return hotelService.createNewHotel(hotel);
  }
}
