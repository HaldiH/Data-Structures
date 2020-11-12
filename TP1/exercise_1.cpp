#include <functional>
#include <iostream>
#include <string_view>
#include <utility>
#include <vector>

class Client {
    std::string m_name;
    std::string m_address;
    std::string m_phone_number;

  public:
    Client() = default;

    Client(std::string name, std::string address, std::string phone_number) noexcept
        : m_name(std::move(name)), m_address(std::move(address)), m_phone_number(std::move(phone_number)) {}

    [[nodiscard]] constexpr const std::string &getName() const noexcept { return m_name; }

    [[nodiscard]] constexpr const std::string &getAddress() const noexcept { return m_address; }

    [[nodiscard]] constexpr const std::string &getPhoneNumber() const noexcept { return m_phone_number; }

    void setName(const std::string &name) { m_name = name; }

    void setAddress(const std::string &address) { m_address = address; }

    void setPhoneNumber(const std::string &phone_number) { m_phone_number = phone_number; }
};

class Car {
  public:
    enum Status { Pending, Repaired, Paid };

    Car() = default;

    Car(std::string brand, std::string model, std::string matriculation, Client *owner)
        : m_brand{std::move(brand)}, m_model{std::move(model)},
          m_matriculation{std::move(matriculation)}, m_owner{owner}, m_status{Status::Pending} {};

    [[nodiscard]] const std::string &getBrand() const noexcept { return m_brand; }

    [[nodiscard]] const std::string &getModel() const noexcept { return m_model; }

    [[nodiscard]] const std::string &getMatriculation() const noexcept { return m_matriculation; }

    [[nodiscard]] const Status &getStatus() const noexcept { return m_status; }

    [[nodiscard]] constexpr std::string_view getStatusString() const noexcept {
        switch (m_status) {
        case Status::Repaired:
            return "Repaired";
        case Status::Paid:
            return "Paid";
        default:
            return "Pending";
        }
    }

    [[nodiscard]] Client *getOwner() const noexcept { return m_owner; }

    void setBrand(const std::string &brand) { m_brand = brand; }

    void setModel(const std::string &model) { m_model = model; }

    void setMatriculation(const std::string &matriculation) { m_matriculation = matriculation; }

    void setOwner(Client *owner) { m_owner = owner; }

    void setStatus(Status status) { m_status = status; }

    void setStatusCode(int code) { m_status = Status(code - 1); }

  private:
    std::string m_brand;
    std::string m_model;
    std::string m_matriculation;
    Client *m_owner{};
    Status m_status = Status::Pending;
};

class Garage {
  private:
    std::vector<Client *> clients;
    std::vector<Car *> cars;

    template <class T> T selector(const std::vector<T> &v) {
        if (v.empty()) {
            std::cout << "The requested resource is empty" << std::endl;
            return nullptr;
        }
        std::string line;
        std::getline(std::cin, line);
        try {
            int i = std::stoi(line);
            if (i < 1 || i > v.size()) {
                std::cout << "Input must be in the range" << std::endl;
                return selector<T>(v);
            }
            return v[i - 1];
        } catch (std::invalid_argument const &e) {
            std::cout << "Input must be a number" << std::endl;
            return selector<T>(v);
        } catch (std::out_of_range const &e) {
            std::cout << "Overflow out of range" << std::endl;
            return selector<T>(v);
        }
    }

  public:
    int listCar() {
        if (cars.empty()) {
            std::cout << "There is no car registered." << std::endl;
            return 1;
        }
        std::cout << "|   Brand   |   Model   |   Matriculation   |   Owner   |   Status   |   ID   |" << std::endl;
        int i = 1;
        for (Car *car : cars) {
            std::cout << "| " << car->getBrand() << " | " << car->getModel() << " | " << car->getMatriculation()
                      << " | " << car->getOwner()->getName() << " | " << car->getStatusString() << " | " << i++ << " |"
                      << std::endl;
        }

        return 0;
    }

    int listClient() {
        if (clients.empty()) {
            std::cout << "There is no client registered." << std::endl;
            return 1;
        }
        std::cout << "|   Name   |   Address   |   Phone number   |   ID   |" << std::endl;
        int i = 1;
        for (Client *client : clients) {
            std::cout << "| " << client->getName() << " | " << client->getAddress() << " | " << client->getPhoneNumber()
                      << " | " << i++ << " |" << std::endl;
        }
        return 0;
    }

    static int carStatusEditMenu(Car *car) {
        std::cout << "Status: " << std::endl
                  << "1- Pending" << std::endl
                  << "2- Repaired" << std::endl
                  << "3- Paid" << std::endl
                  << "Please select a status (1-3):";
        std::string line;
        std::getline(std::cin, line);
        try {
            int i = std::stoi(line);
            if (i < 1 || i > 3) {
                std::cout << "Input must be (1-3)." << std::endl;
                return carStatusEditMenu(car);
            }
            car->setStatusCode(i);
        } catch (std::invalid_argument const &e) {
            std::cout << "Input must be a number" << std::endl;
            return carStatusEditMenu(car);
        } catch (std::out_of_range const &e) {
            std::cout << "Overflow out of range" << std::endl;
            return carStatusEditMenu(car);
        }

        return 0;
    }

    int carEditMenu(Car *car) {
        auto rc = listClient();
        if (rc != 0)
            return rc;

        std::string line;

        std::cout << "Please fill form :" << std::endl

                  << "Owner [" << [&car]() -> std::string {
            auto owner = car->getOwner();
            return owner ? owner->getName() : "";
        }() << "](ID):";
        std::getline(std::cin, line);
        if (!line.empty()) {
            try {
                int i = std::stoi(line);
                if (i < 1 || i > clients.size()) {
                    std::cout << "Client ID isn't in the range." << std::endl;
                    return carEditMenu(car);
                }
                car->setOwner(clients[i - 1]);
            } catch (std::invalid_argument const &e) {
                std::cout << "Input must be a number" << std::endl;
                return carEditMenu(car);
            } catch (std::out_of_range const &e) {
                std::cout << "Overflow out of range" << std::endl;
                return carEditMenu(car);
            }
        } else if (!car->getOwner()) {
            std::cout << "Owner cannot be empty." << std::endl;
            return carEditMenu(car);
        }

        std::cout << "Brand [" << car->getBrand() << "]:";
        std::getline(std::cin, line);
        if (!line.empty())
            car->setBrand(line);

        std::cout << "Model [" << car->getModel() << "]:";
        std::getline(std::cin, line);
        if (!line.empty())
            car->setModel(line);

        std::cout << "Matriculation [" << car->getMatriculation() << "]:";
        std::getline(std::cin, line);
        if (!line.empty())
            car->setMatriculation(line);

        return 0;
    }

    Car *carSelectMenu() {
        if (listCar() != 0)
            return nullptr;
        std::cout << "Select a car from the list : ";
        return selector<Car *>(cars);
    }

    static int clientEditMenu(Client *client) {
        std::string line;
        std::cout << "Please fill form :" << std::endl << "Name [" << client->getName() << "]:";
        std::getline(std::cin, line);
        if (!line.empty())
            client->setName(line);
        std::cout << "Address [" << client->getAddress() << "]:";
        std::getline(std::cin, line);
        if (!line.empty())
            client->setAddress(line);
        std::cout << "Phone number [" << client->getPhoneNumber() << "]:";
        std::getline(std::cin, line);
        if (!line.empty())
            client->setPhoneNumber(line);

        return 0;
    }

    Client *clientSelectMenu() {
        if (listClient() != 0)
            return nullptr;
        std::cout << "Select a client from the list : ";
        return selector<Client *>(clients);
    }

    int mainMenu() {
        std::cout << "Actions available :" << std::endl
                  << "1- List all clients" << std::endl
                  << "2- List all cars" << std::endl
                  << "3- Create a client" << std::endl
                  << "4- Edit a client" << std::endl
                  << "5- Add a car" << std::endl
                  << "6- Change car status" << std::endl
                  << "7- Edit car data" << std::endl
                  << "q- Quit the program" << std::endl
                  << "Please specify an action (1-7,q):";
        std::string param;
        std::getline(std::cin, param);

        if (param == "q")
            return -1;

        if (param == "1")
            return listClient();

        if (param == "2")
            return listCar();

        if (param == "3") {
            auto *client = new Client();
            int rc = clientEditMenu(client);
            if (rc == 0) {
                std::cout << "Client successfully added!" << std::endl;
                clients.emplace_back(client);
            } else {
                std::cout << "An error occurred while adding the client!" << std::endl;
                delete client;
            }
            return rc;
        }

        if (param == "4") {
            auto client = clientSelectMenu();
            int rc;
            if (!client)
                rc = 1;
            else
                rc = clientEditMenu(client);
            if (rc == 0)
                std::cout << "Client successfully edited!" << std::endl;
            else
                std::cout << "An error occurred while editing the client!" << std::endl;
            return rc;
        }

        if (param == "5") {
            auto *car = new Car();
            int rc = carEditMenu(car);
            if (rc == 0) {
                std::cout << "Car successfully added!" << std::endl;
                cars.emplace_back(car);
            } else {
                std::cout << "An error occurred while adding the car!" << std::endl;
                delete car;
            }
            return rc;
        }

        if (param == "6") {
            auto car = carSelectMenu();
            int rc;
            if (!car)
                rc = 1;
            else
                rc = carStatusEditMenu(car);
            if (rc == 0)
                std::cout << "Car status successfully edited!" << std::endl;
            else
                std::cout << "An error occurred while editing the car status!" << std::endl;
            return rc;
        }

        if (param == "7") {
            auto car = carSelectMenu();
            int rc;
            if (!car)
                rc = 1;
            else
                rc = carEditMenu(car);
            if (rc == 0)
                std::cout << "Car successfully edited!" << std::endl;
            else
                std::cout << "An error occurred while editing the car!" << std::endl;
            return rc;
        }

        std::cout << "Please enter a correct value (1-7,q)" << std::endl;
        return mainMenu();
    }

    Garage() {
        while (mainMenu() >= 0)
            ;
    };

    ~Garage() {
        for (Car *car : cars) {
            delete car;
        }
        for (Client *client : clients) {
            delete client;
        }
    };
};

int main(int argc, char **argv) {
    Garage garage;
    return 0;
}