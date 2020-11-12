//
// Created by hugo1 on 25.02.2020.
//
#include "exercise_2.hpp"
#include <cmath>
#include <utility>

std::string Aircraft::getManufacturer() { return m_manufacturer; }
std::string Aircraft::getMatriculation() { return m_matriculation; }
std::string Aircraft::getModel() { return m_model; }
Aircraft::Type Aircraft::getType() { return m_type; }
int Aircraft::getCapacity() { return m_capacity; }
float Aircraft::getLadenWeight() { return m_ladenWeight; }
float Aircraft::getWidth() { return m_width; }
float Aircraft::getLength() { return m_length; }
float Aircraft::getAverageSpeed() { return m_averageSpeed; }
Employee::Rank Employee::getRank() { return m_rank; }
std::string Employee::getName() { return m_name; }
int Employee::getId() { return m_id; }
void Employee::setRank(Employee::Rank rank) { m_rank = rank; }
void Employee::setName(std::string name) { m_name = std::move(name); }
int Flight::getFlightNumber() { return m_flightNumber; }
Aircraft *Flight::getAircraft() { return m_aircraft; }
std::vector<Employee *> Flight::getCrew() { return m_crew; }
long Flight::getDepartureTime() { return m_departureTime; }
Airport *Flight::getArrivalAirport() { return m_arrivalAirport; }
long Flight::getTravelTime() { // t = d / v
    return long(Coordinate::distance(m_departureAirport->getCoordinates(), m_arrivalAirport->getCoordinates()) /
                m_aircraft->getAverageSpeed());
}
long Flight::getArrivalTime() { return getDepartureTime() + getTravelTime(); }
void Flight::setFlightNumber(int flightNumber) { m_flightNumber = flightNumber; }
void Flight::setAircraft(Aircraft *aircraft) { m_aircraft = aircraft; }
void Flight::setCrew(std::vector<Employee *> crew) { m_crew = std::move(crew); }
void Flight::setDepartureTime(long time) { m_departureTime = time; }
void Flight::setArrivalAirport(Airport *airport) { m_arrivalAirport = airport; }
float Coordinate::distance(Coordinate a, Coordinate b) {
    return sqrtf(powf(a.m_x - b.m_x, 2) + powf(a.m_y - b.m_y, 2));
}
Coordinate Airport::getCoordinates() { return m_coordinates; }
std::string Compagny::getName() { return m_name; }
std::vector<Employee *> Compagny::getStaff() { return m_staff; }
std::vector<Flight *> Compagny::getFlight() { return m_flights; }
std::vector<Airport *> Compagny::getAirports() { return m_airports; }
std::vector<Aircraft *> Compagny::getAircraft() { return m_aircrafts; }
void Compagny::addFlight(Flight *flight) { m_flights.emplace_back(flight); }
void Compagny::addEmployee(Employee *employee) { m_staff.emplace_back(employee); }
void Compagny::addAirport(Airport *airport) { m_airports.emplace_back(airport); }
void Compagny::addAircraft(Aircraft *aircraft) { m_aircrafts.emplace_back(aircraft); }
void Compagny::setName(std::string name) { m_name = std::move(name); }
