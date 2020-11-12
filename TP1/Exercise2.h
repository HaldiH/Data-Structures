//
// Created by hugo on 28.02.20.
//

#ifndef TP1_C_EXERCISE2_H
#define TP1_C_EXERCISE2_H

typedef enum { JET, TURBOPROP, PISTON_ENGINE } TAircraftType;

typedef struct {
    char *m_manufacturer;
    char *m_matriculation;
    char *m_model;
    TAircraftType m_type;
    int m_capacity;
    float m_ladenWeight;
    float m_width;
    float m_length;
    float m_averageSpeed;
} TAircraft;

// Constructor
TAircraft *TAircraft_factory(char *manufacturer, char *matriculation, char *model, TAircraftType type, int capacity,
                             float ladenWeight, float width, float length, float averageSpeed);

// Getters
char *TAircraft_getManufacturer(const TAircraft *aircraft);
char *TAircraft_getMatriculation(const TAircraft *aircraft);
char *TAircraft_getModel(const TAircraft *aircraft);
TAircraftType TAircraft_getType(const TAircraft *aircraft);
int TAircraft_getCapacity(const TAircraft *aircraft);
float TAircraft_getLadenWeight(const TAircraft *aircraft);
float TAircraft_getWidth(const TAircraft *aircraft);
float TAircraft_getLength(const TAircraft *aircraft);
float TAircraft_getAverageSpeed(const TAircraft *aircraft);

typedef enum { PILOT, COPILOT, PURSES, STEWARD } TEmployeeRank;

typedef struct {
    int m_id;
    char *m_name;
    TEmployeeRank m_rank;
} TEmployee;

// Constructor
TEmployee *TEmployee_factory(char *name, TEmployeeRank rank, int id);

// Getters
TEmployeeRank TEmployee_getRank(const TEmployee *employee);
char *TEmployee_getName(const TEmployee *employee);
int TEmployee_getId(const TEmployee *employee);

// Setters
int TEmployee_setRank(TEmployee *employee, TEmployeeRank rank);
int TEmployee_setName(TEmployee *employee, char *name);

typedef struct {
    float m_x;
    float m_y;
} TCoordinate;

// Constructor
TCoordinate TCoordinate_factory(float x, float y);

static float distance(TCoordinate a, TCoordinate b);

typedef enum { PUBLIC, MILITARY } TAirportUse;

typedef struct {
    char *m_icaoCode;
    char *m_country;
    TCoordinate m_coordinates;
    int m_elevation;
    TAirportUse m_use;
} TAirport;

// Constructor
TAirport *TAirport_factory(char *icaoCode, char *country, TCoordinate coordinates, int elevation, TAirportUse use);

TCoordinate TAirport_getCoordinates(const TAirport *airport);
char *TAirport_getIcaoCode(const TAirport *airport);
char *TAirport_getCountry(const TAirport *airport);
int TAirport_getElevation(const TAirport *airport);
TAirportUse TAirport_getUse(const TAirport *airport);

typedef struct {
    int m_flightNumber;
    int crew_size;
    TAircraft *m_aircraft;
    TEmployee **m_crew;
    long m_departureTime;
    TAirport *m_departureAirport;
    TAirport *m_arrivalAirport;
} TFlight;

TFlight *TFlight_factory(int flightNumber, TAircraft *aircraft, TEmployee **crew, int crew_size, long departureTime,
                         TAirport *departureAirport, TAirport *arrivalAirport);

int TFlight_getFlightNumber(const TFlight *flight);
TAircraft *TFlight_getAircraft(const TFlight *flight);
TEmployee **TFlight_getCrew(const TFlight *flight);
long TFlight_getDepartureTime(const TFlight *flight);
TAirport *TFlight_getArrivalAirport(const TFlight *flight);
long TFlight_getTravelTime(const TFlight *flight);
long TFlight_getArrivalTime(const TFlight *flight);

int TFlight_setFlightNumber(TFlight *flight, int flightNumber);
int TFlight_setAircraft(TFlight *flight, TAircraft *aircraft);
int TFlight_setCrew(TFlight *flight, TEmployee **crew);
int TFlight_setCrewSize(TFlight *flight, int size);
int TFlight_setDepartureTime(TFlight *flight, long time);
int TFlight_setArrivalAirport(TFlight *flight, TAirport *airport);

typedef struct {
    char *m_name;
    int staff_size;
    int flights_size;
    int airports_size;
    int aircrafts_size;
    TEmployee **m_staff;
    TFlight **m_flights;
    TAirport **m_airports;
    TAircraft **m_aircrafts;
} TCompagny;

TCompagny *TCompagny_factory(char *name, TEmployee **staff, int staff_size, TFlight **flights, int flights_size,
                             TAirport **airports, int airports_size, TAircraft **aircrafts, int aircrafts_size);

char *TCompagny_getName(const TCompagny *compagny);
TEmployee **TCompagny_getStaff(const TCompagny *compagny);
TFlight **TCompagny_getFlights(const TCompagny *compagny);
TAirport **TCompagny_getAirports(const TCompagny *compagny);
TAircraft **TCompagny_getAircrafts(const TCompagny *compagny);
int TCompagny_getFlightsSize(const TCompagny *compagny);
int TCompagny_getAirportsSize(const TCompagny *compagny);
int TCompagny_getAircraftsSize(const TCompagny *compagny);
int TCompagny_getStaffSize(const TCompagny *compagny);

int TCompagny_addFlight(TCompagny *compagny, TFlight *flight);
int TCompagny_addEmployee(TCompagny *compagny, TEmployee *employee);
int TCompagny_addAirport(TCompagny *compagny, TAirport *airport);
int TCompagny_addAircraft(TCompagny *compagny, TAircraft *aircraft);

int TCompagny_setName(TCompagny *compagny, char *name);

#endif // TP1_C_EXERCISE2_H
