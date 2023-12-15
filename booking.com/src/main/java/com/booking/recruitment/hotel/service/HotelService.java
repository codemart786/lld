package com.booking.recruitment.hotel.service;

import com.booking.recruitment.hotel.exception.ElementNotFoundException;
import com.booking.recruitment.hotel.model.Hotel;

import java.util.List;
import java.util.Optional;

public interface HotelService {
  List<Hotel> getAllHotels();

  List<Hotel> getHotelsByCity(Long cityId);

  Optional<Hotel> getHotelDetail(Long id);

  Hotel deleteHotel(Hotel hotel) throws ElementNotFoundException;

  Hotel createNewHotel(Hotel hotel);
}
