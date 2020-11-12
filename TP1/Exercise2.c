//
// Created by hugo on 3/1/20.
//

#include "Exercise2.h"
#include <math.h>
#include <stdlib.h>

TAircraft *TAircraft_factory(char *manufacturer, char *matriculation, char *model, TAircraftType type, int capacity,
                             float ladenWeight, float width, float length, float averageSpeed) {
    TAircraft *aircraft = (TAircraft *)malloc(sizeof(TAircraft));
    aircraft->m_manufacturer = manufacturer;
    aircraft->m_matriculation = matriculation;
    aircraft->m_model = model;
    aircraft->m_type = type;
    aircraft->m_capacity = capacity;
    aircraft->m_ladenWeight = ladenWeight;
    aircraft->m_width = width;
    aircraft->m_length = length;
    aircraft->m_averageSpeed = averageSpeed;
    return aircraft;
}
char *TAircraft_getManufacturer(const TAircraft *aircraft) { return aircraft ? aircraft->m_manufacturer : NULL; }
char *TAircraft_getMatriculation(const TAircraft *aircraft) { return aircraft ? aircraft->m_matriculation : NULL; }
char *TAircraft_getModel(const TAircraft *aircraft) { return aircraft ? aircraft->m_model : NULL; }
TAircraftType TAircraft_getType(const TAircraft *aircraft) { return aircraft ? aircraft->m_type : (TAircraftType)0; }
int TAircraft_getCapacity(const TAircraft *aircraft) { return aircraft ? aircraft->m_capacity : 0; }
float TAircraft_getLadenWeight(const TAircraft *aircraft) { return aircraft ? aircraft->m_ladenWeight : 0; }
float TAircraft_getWidth(const TAircraft *aircraft) { return aircraft ? aircraft->m_width : 0; }
float TAircraft_getLength(const TAircraft *aircraft) { return aircraft ? aircraft->m_length : 0; }
float TAircraft_getAverageSpeed(const TAircraft *aircraft) { return aircraft ? aircraft->m_averageSpeed : 0; }

TEmployee *TEmployee_factory(char *name, TEmployeeRank rank, int id) {
    TEmployee *employee = (TEmployee *)malloc(sizeof(TEmployee));
    employee->m_name = name;
    employee->m_rank = rank;
    employee->m_id = id;
    return employee;
}
TEmployeeRank TEmployee_getRank(const TEmployee *employee) { return employee ? employee->m_rank : (TEmployeeRank)0; }
char *TEmployee_getName(const TEmployee *employee) { return employee ? employee->m_name : NULL; }
int TEmployee_getId(const TEmployee *employee) { return employee ? employee->m_id : 0; }
int TEmployee_setRank(TEmployee *employee, TEmployeeRank rank) {
    if (employee) {
        employee->m_rank = rank;
        return 0;
    }
    return 1;
}
int TEmployee_setName(TEmployee *employee, char *name) {
    if (employee) {
        employee->m_name = name;
        return 0;
    }
    return 1;
}

TCoordinate TCoordinate_factory(float x, float y) {
    TCoordinate coordinate;
    coordinate.m_x = x;
    coordinate.m_y = y;
    return coordinate;
}
float distance(TCoordinate a, TCoordinate b) { return sqrtf(powf(a.m_x - b.m_x, 2) + powf(a.m_y - b.m_y, 2)); }

TAirport *TAirport_factory(char *icaoCode, char *country, TCoordinate coordinates, int elevation, TAirportUse use) {
    TAirport *airport = (TAirport *)malloc(sizeof(TAirport));
    airport->m_icaoCode = icaoCode;
    airport->m_country = country;
    airport->m_coordinates = coordinates;
    airport->m_elevation = elevation;
    airport->m_use = use;
    return airport;
}
TCoordinate TAirport_getCoordinates(const TAirport *airport) {
    return airport ? airport->m_coordinates : TCoordinate_factory(0, 0);
}
char *TAirport_getIcaoCode(const TAirport *airport) { return airport ? airport->m_icaoCode : NULL; }
char *TAirport_getCountry(const TAirport *airport) { return airport ? airport->m_country : NULL; }
int TAirport_getElevation(const TAirport *airport) { return airport ? airport->m_elevation : 0; }
TAirportUse TAirport_getUse(const TAirport *airport) { return airport ? airport->m_use : (TAirportUse)0; }

TFlight *TFlight_factory(int flightNumber, TAircraft *aircraft, TEmployee **crew, int crew_size, long departureTime,
                         TAirport *departureAirport, TAirport *arrivalAirport) {
    TFlight *flight = (TFlight *)malloc(sizeof(TFlight));
    flight->m_flightNumber = flightNumber;
    flight->m_aircraft = aircraft;
    flight->m_crew = crew;
    flight->m_departureTime = departureTime;
    flight->m_departureAirport = departureAirport;
    flight->m_arrivalAirport = arrivalAirport;
    flight->crew_size = crew_size;
    return flight;
}
int TFlight_getFlightNumber(const TFlight *flight) { return flight ? flight->m_flightNumber : 0; }
TAircraft *TFlight_getAircraft(const TFlight *flight) { return flight ? flight->m_aircraft : NULL; }
TEmployee **TFlight_getCrew(const TFlight *flight) { return flight ? flight->m_crew : NULL; }
long TFlight_getDepartureTime(const TFlight *flight) { return flight ? flight->m_departureTime : 0; }
TAirport *TFlight_getArrivalAirport(const TFlight *flight) { return flight ? flight->m_arrivalAirport : NULL; }
long TFlight_getTravelTime(const TFlight *flight) {
    return flight ? (long)(distance(TAirport_getCoordinates(flight->m_departureAirport),
                                    TAirport_getCoordinates(flight->m_arrivalAirport)) /
                           TAircraft_getAverageSpeed(flight->m_aircraft))
                  : 0;
}
long TFlight_getArrivalTime(const TFlight *flight) {
    return flight ? TFlight_getDepartureTime(flight) + TFlight_getTravelTime(flight) : 0;
}
int TFlight_setFlightNumber(TFlight *flight, int flightNumber) {
    if (flight) {
        flight->m_flightNumber = flightNumber;
        return 0;
    }
    return 1;
}
int TFlight_setAircraft(TFlight *flight, TAircraft *aircraft) {
    if (flight) {
        flight->m_aircraft = aircraft;
        return 0;
    }
    return 1;
}
int TFlight_setCrew(TFlight *flight, TEmployee **crew) {
    if (flight) {
        flight->m_crew = crew;
        return 0;
    }
    return 1;
}
int TFlight_setDepartureTime(TFlight *flight, long time) {
    if (flight) {
        flight->m_departureTime = time;
        return 0;
    }
    return 1;
}
int TFlight_setArrivalAirport(TFlight *flight, TAirport *airport) {
    if (flight) {
        flight->m_arrivalAirport = airport;
        return 0;
    }
    return 1;
}
int TFlight_setCrewSize(TFlight *flight, int size) {
    if (flight) {
        flight->crew_size = size;
        return 0;
    }
    return 1;
}

TCompagny *TCompagny_factory(char *name, TEmployee **staff, int staff_size, TFlight **flights, int flights_size,
                             TAirport **airports, int airports_size, TAircraft **aircrafts, int aircrafts_size) {
    TCompagny *compagny = (TCompagny *)malloc(sizeof(TCompagny));
    compagny->m_name = name;
    compagny->m_staff = staff;
    compagny->staff_size = staff_size;
    compagny->m_flights = flights;
    compagny->flights_size = flights_size;
    compagny->m_airports = airports;
    compagny->airports_size = airports_size;
    compagny->m_aircrafts = aircrafts;
    compagny->aircrafts_size = aircrafts_size;
    return compagny;
}
char *TCompagny_getName(const TCompagny *compagny) { return compagny ? compagny->m_name : NULL; }
TEmployee **TCompagny_getStaff(const TCompagny *compagny) { return compagny ? compagny->m_staff : NULL; }
TFlight **TCompagny_getFlights(const TCompagny *compagny) { return compagny ? compagny->m_flights : NULL; }
TAirport **TCompagny_getAirports(const TCompagny *compagny) { return compagny ? compagny->m_airports : NULL; }
TAircraft **TCompagny_getAircrafts(const TCompagny *compagny) { return compagny ? compagny->m_aircrafts : NULL; }
int TCompagny_getFlightsSize(const TCompagny *compagny) { return compagny ? compagny->flights_size : 0; }
int TCompagny_getAirportsSize(const TCompagny *compagny) { return compagny ? compagny->airports_size : 0; }
int TCompagny_getAircraftsSize(const TCompagny *compagny) { return compagny ? compagny->aircrafts_size : 0; }
int TCompagny_getStaffSize(const TCompagny *compagny) { return compagny ? compagny->staff_size : 0; }

int TCompagny_addFlight(TCompagny *compagny, TFlight *flight) {
    if (compagny) {
        if (flight) {
            compagny->m_flights = realloc(compagny->m_flights, ++compagny->flights_size);
            compagny->m_flights[compagny->flights_size - 1] = flight;
            return 0;
        }
        return 2;
    }
    return 1;
}
int TCompagny_addEmployee(TCompagny *compagny, TEmployee *employee) {
    if (compagny) {
        if (employee) {
            compagny->m_staff = realloc(compagny->m_staff, ++compagny->staff_size);
            compagny->m_staff[compagny->staff_size - 1] = employee;
            return 0;
        }
        return 2;
    }
    return 1;
}
int TCompagny_addAirport(TCompagny *compagny, TAirport *airport) {
    if (compagny) {
        if (airport) {
            compagny->m_airports = realloc(compagny->m_airports, ++compagny->airports_size);
            compagny->m_airports[compagny->airports_size - 1] = airport;
            return 0;
        }
        return 2;
    }
    return 1;
}
int TCompagny_addAircraft(TCompagny *compagny, TAircraft *aircraft) {
    if (compagny) {
        if (aircraft) {
            compagny->m_aircrafts = realloc(compagny->m_aircrafts, ++compagny->aircrafts_size);
            compagny->m_aircrafts[compagny->aircrafts_size - 1] = aircraft;
            return 0;
        }
        return 2;
    }
    return 1;
}
int TCompagny_setName(TCompagny *compagny, char *name) {
    if (compagny) {
        compagny->m_name = name;
        return 0;
    }
    return 1;
}
