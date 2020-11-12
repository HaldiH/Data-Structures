#include <string>
#include <utility>
#include <vector>

class Aircraft {
  public:
    enum Type { JET, TURBOPROP, PISTON_ENGINE };

    Aircraft(std::string manufacturer, std::string matriculation, std::string model, Type type, int capacity,
             float ladenWeight, float width, float length, float averageSpeed)
        : m_manufacturer(std::move(manufacturer)), m_matriculation(std::move(matriculation)), m_model(std::move(model)),
          m_type(type), m_capacity(capacity), m_ladenWeight(ladenWeight), m_width(width), m_length(length),
          m_averageSpeed(averageSpeed){};

    std::string getManufacturer();
    std::string getMatriculation();
    std::string getModel();
    Type getType();
    int getCapacity();
    float getLadenWeight();
    float getWidth();
    float getLength();
    float getAverageSpeed();

  private:
    std::string m_manufacturer;
    std::string m_matriculation;
    std::string m_model;
    Type m_type;
    int m_capacity;
    float m_ladenWeight;
    float m_width;
    float m_length;
    float m_averageSpeed;
};

class Employee {
  public:
    enum Rank { PILOT, COPILOT, PURSES, STEWARD };

    Employee(std::string name, Rank rank, int id) : m_name(std::move(name)), m_rank(rank), m_id(id){};

    Rank getRank();
    std::string getName();
    int getId();

    void setRank(Rank rank);
    void setName(std::string name);

  private:
    int m_id;
    std::string m_name;
    Rank m_rank;
};

class Coordinate {
  public:
    Coordinate(float x, float y) : m_x(x), m_y(y){};

    static float distance(Coordinate a, Coordinate b);

  private:
    float m_x;
    float m_y;
};

class Airport {
  public:
    enum Use { PUBLIC, MILITARY };

    Airport(std::string icaoCode, std::string country, Coordinate coordinates, int elevation, Use use)
        : m_icaoCode(std::move(icaoCode)), m_country(std::move(country)), m_coordinates(coordinates),
          m_elevation(elevation), m_use(use){};

    Coordinate getCoordinates();

  private:
    std::string m_icaoCode;
    std::string m_country;
    Coordinate m_coordinates;
    int m_elevation;
    Use m_use;
};

class Flight {
  public:
    Flight(int flightNumber, Aircraft *aircraft, std::vector<Employee *> crew, long departureTime,
           Airport *departureAirport, Airport *arrivalAirport)
        : m_flightNumber(flightNumber), m_aircraft(aircraft), m_crew(std::move(crew)), m_departureTime(departureTime),
          m_departureAirport(departureAirport), m_arrivalAirport(arrivalAirport){};

    int getFlightNumber();
    Aircraft *getAircraft();
    std::vector<Employee *> getCrew();
    long getDepartureTime();
    Airport *getArrivalAirport();
    long getTravelTime();
    long getArrivalTime();

    void setFlightNumber(int flightNumber);
    void setAircraft(Aircraft *aircraft);
    void setCrew(std::vector<Employee *> crew);
    void setDepartureTime(long time);
    void setArrivalAirport(Airport *airport);

  private:
    int m_flightNumber;
    Aircraft *m_aircraft;
    std::vector<Employee *> m_crew;
    long m_departureTime;
    Airport *m_departureAirport;
    Airport *m_arrivalAirport;
};

class Compagny {
  public:
    Compagny(std::string name, std::vector<Employee *> staff, std::vector<Flight *> flights,
             std::vector<Airport *> airports, std::vector<Aircraft *> aircrafts)
        : m_name(std::move(name)), m_staff(std::move(staff)), m_flights(std::move(flights)),
          m_airports(std::move(airports)), m_aircrafts(std::move(aircrafts)){};

    std::string getName();
    std::vector<Employee *> getStaff();
    std::vector<Flight *> getFlight();
    std::vector<Airport *> getAirports();
    std::vector<Aircraft *> getAircraft();

    void addFlight(Flight *flight);
    void addEmployee(Employee *employee);
    void addAirport(Airport *airport);
    void addAircraft(Aircraft *aircraft);

    void setName(std::string name);

  private:
    std::string m_name;
    std::vector<Employee *> m_staff;
    std::vector<Flight *> m_flights;
    std::vector<Airport *> m_airports;
    std::vector<Aircraft *> m_aircrafts;
};