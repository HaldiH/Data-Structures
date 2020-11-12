#include "Exercise1.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

TClient *TClient_factory() {
    TClient *client = (TClient *)malloc(sizeof(TClient));
    client->m_phone_number = NULL;
    client->m_address = NULL;
    client->m_name = NULL;
    return client;
}
char *TClient_getPhoneNumber(const TClient *client) {
    return client && client->m_phone_number ? client->m_phone_number : "";
}
char *TClient_getName(const TClient *client) { return client && client->m_name ? client->m_name : ""; }
char *TClient_getAddress(const TClient *client) { return client && client->m_address ? client->m_address : ""; }
int TClient_setName(TClient *client, char *name) {
    if (client) {
        free(client->m_name);
        client->m_name = name;
        return 0;
    }
    return 1;
}
int TClient_setAddress(TClient *client, char *address) {
    if (client) {
        free(client->m_address);
        client->m_address = address;
        return 0;
    }
    return 1;
}
int TClient_setPhoneNumber(TClient *client, char *phone_number) {
    if (client) {
        free(client->m_phone_number);
        client->m_phone_number = phone_number;
        return 0;
    }
    return 1;
}
TCar *TCar_factory() {
    TCar *car = (TCar *)malloc(sizeof(TCar));
    car->m_status = PENDING;
    car->m_owner = NULL;
    car->m_matriculation = NULL;
    car->m_model = NULL;
    car->m_brand = NULL;
    return car;
}
char *TCar_getBrand(const TCar *car) { return car && car->m_brand ? car->m_brand : ""; }
char *TCar_getModel(const TCar *car) { return car && car->m_model ? car->m_model : ""; }
char *TCar_getMatriculation(const TCar *car) { return car && car->m_matriculation ? car->m_matriculation : ""; }
TClient *TCar_getOwner(const TCar *car) { return car && car->m_owner ? car->m_owner : NULL; }
TStatus TCar_getStatus(const TCar *car) { return car && car->m_status ? car->m_status : PENDING; }
char *TCar_getStatusString(const TCar *car) {
    switch (car->m_status) {
    case PENDING:
        return "Pending";
    case REPAIRED:
        return "Repaired";
    case PAID:
        return "Paid";
    }
}
int TCar_setBrand(TCar *car, char *brand) {
    if (car) {
        free(car->m_brand);
        car->m_brand = brand;
        return 0;
    }
    return 1;
}
int TCar_setModel(TCar *car, char *model) {
    if (car) {
        free(car->m_model);
        car->m_model = model;
        return 0;
    }
    return 1;
}
int TCar_setMatriculation(TCar *car, char *matriculation) {
    if (car) {
        free(car->m_matriculation);
        car->m_matriculation = matriculation;
        return 0;
    }
    return 1;
}
int TCar_setOwner(TCar *car, TClient *owner) {
    if (car) {
        car->m_owner = owner;
        return 0;
    }
    return 1;
}
int TCar_setStatus(TCar *car, TStatus status) {
    if (car) {
        car->m_status = status;
        return 0;
    }
    return 1;
}
TGarage *TGarage_factory() {
    TGarage *garage = (TGarage *)malloc(sizeof(TGarage));
    garage->pCars = NULL;
    garage->pClients = NULL;
    garage->cars_size = 0;
    garage->clients_size = 0;
    return garage;
}
void TGarage_destructor(TGarage *garage) {
    for (int i = 0; i < garage->cars_size; i++)
        free(garage->pCars[i]);
    for (int i = 0; i < garage->clients_size; i++)
        free(garage->pClients[i]);
    free(garage->pCars);
    free(garage->pClients);
    free(garage);
}
int listCar(const TGarage *garage) {
    if (garage->pCars == NULL) {
        printf("There is no car registered.\n");
        return 1;
    }
    printf("|   Brand   |   Model   |   Matriculation   |   Owner   |   Status   "
           "|   ID   |\n");
    for (int i = 0; i < garage->cars_size; i++) {
        TCar *car = garage->pCars[i];
        printf("| %s | %s | %s | %s | %s | %i |\n", TCar_getBrand(car), TCar_getModel(car), TCar_getMatriculation(car),
               TClient_getName(TCar_getOwner(car)), TCar_getStatusString(car), i + 1);
    }

    return 0;
}
int listClient(const TGarage *garage) {
    if (garage->pClients == NULL) {
        printf("There is no client registered.\n");
        return 1;
    }
    printf("|   Name   |   Address   |   Phone number   |   ID   |\n");
    for (int i = 0; i < garage->clients_size; i++) {
        TClient *client = garage->pClients[i];
        printf("| %s | %s | %s | %i |\n", TClient_getName(client), TClient_getAddress(client),
               TClient_getPhoneNumber(client), i + 1);
    }

    return 0;
}
int carStatusEditMenu(TCar *car) {
    printf("Status:\n"
           "1- Pending\n"
           "2- Repaired\n"
           "3- Paid\n"
           "Please select a status (1-3):");
    char *buffer = (char *)malloc(STRING_MAXSIZE * sizeof(char));
    fgets(buffer, STRING_MAXSIZE, stdin);
    int status = *buffer - '0';
    free(buffer);
    if (status < 1 || status > 3) {
        printf("Input must be 1-3.\n");
        return carStatusEditMenu(car);
    }
    TCar_setStatus(car, (TStatus)(status - 1));
    return 0;
}
int carEditMenu(TCar *car, TGarage *garage) {
    int rc = listClient(garage);
    if (rc != 0)
        return rc;

    char *buffer = (char *)malloc(STRING_MAXSIZE * sizeof(char));
    TClient *owner = TCar_getOwner(car);
    printf("Please fill form :\n"
           "Owner [%s](ID):",
           TClient_getName(owner));
    fgets(buffer, STRING_MAXSIZE, stdin);
    if (*buffer != '\n') {
        int id = *buffer - '0';
        free(buffer);
        if (id < 1 || id > garage->clients_size) {
            printf("Client ID isn't in the range.\n");
            return carEditMenu(car, garage);
        }
        TCar_setOwner(car, garage->pClients[id - 1]);
    } else if (owner == NULL) {
        printf("Owner cannot be empty.\n");
        free(buffer);
        return carEditMenu(car, garage);
    }

    buffer = (char *)malloc(STRING_MAXSIZE * sizeof(char));
    printf("Brand [%s]:", TCar_getBrand(car));
    fgets(buffer, STRING_MAXSIZE, stdin);
    if (*buffer != '\n') {
        strtok(buffer, "\n");
        TCar_setBrand(car, buffer);
    }

    buffer = (char *)malloc(STRING_MAXSIZE * sizeof(char));
    printf("Model [%s]:", TCar_getModel(car));
    fgets(buffer, STRING_MAXSIZE, stdin);
    if (*buffer != '\n') {
        strtok(buffer, "\n");
        TCar_setModel(car, buffer);
    }

    buffer = (char *)malloc(STRING_MAXSIZE * sizeof(char));
    printf("Matriculation [%s]:", TCar_getMatriculation(car));
    fgets(buffer, STRING_MAXSIZE, stdin);
    if (*buffer != '\n') {
        strtok(buffer, "\n");
        TCar_setMatriculation(car, buffer);
    }
    return 0;
}
void *selector(void **v, int range_max) {
    if (v == NULL) {
        printf("The requested resource is empty.\n");
        return NULL;
    }
    char *buffer = (char *)malloc(STRING_MAXSIZE * sizeof(char));
    fgets(buffer, STRING_MAXSIZE, stdin);
    int param = *buffer - '0';
    free(buffer);
    if (param < 1 || param > range_max) {
        printf("Input must be in the range.\n");
        return selector(v, range_max);
    }
    return v[param - 1];
}
TCar *carSelectMenu(const TGarage *garage) {
    if (listCar(garage) != 0)
        return NULL;
    printf("Select a car from the list : ");
    return selector((void **)garage->pCars, garage->cars_size);
}
int clientEditMenu(TClient *client) {
    char *buffer = (char *)malloc(STRING_MAXSIZE * sizeof(char));
    printf("Please fill form :\n"
           "Name [%s]:",
           TClient_getName(client));
    fgets(buffer, STRING_MAXSIZE, stdin);
    if (*buffer != '\n') {
        strtok(buffer, "\n");
        TClient_setName(client, buffer);
        buffer = (char *)malloc(STRING_MAXSIZE * sizeof(char));
    }
    printf("Address [%s]:", TClient_getAddress(client));
    fgets(buffer, STRING_MAXSIZE, stdin);
    if (*buffer != '\n') {
        strtok(buffer, "\n");
        TClient_setAddress(client, buffer);
        buffer = (char *)malloc(STRING_MAXSIZE * sizeof(char));
    }
    printf("Phone number [%s]:", TClient_getPhoneNumber(client));
    fgets(buffer, STRING_MAXSIZE, stdin);
    if (*buffer != '\n'){
        strtok(buffer, "\n");
        TClient_setPhoneNumber(client, buffer);
    }
    return 0;
}
TClient *clientSelectMenu(const TGarage *garage) {
    if (listClient(garage) != 0)
        return NULL;
    printf("Select a client from the list : ");
    return selector((void **)garage->pClients, garage->clients_size);
}
int mainMenu(TGarage *garage) {
    printf("Actions available :\n"
           "1- List all clients\n"
           "2- List all cars\n"
           "3- Create a client\n"
           "4- Edit a client\n"
           "5- Add a car\n"
           "6- Change car status\n"
           "7- Edit car data\n"
           "q- Quit the program\n"
           "Please specify an action (1-7,q):");
    char *buffer = (char *)malloc(STRING_MAXSIZE * sizeof(char));
    fgets(buffer, STRING_MAXSIZE, stdin);
    int param = *buffer;
    free(buffer);
    switch (param) {
    case 'q':
        return -1;
    case '1':
        return listClient(garage);
    case '2':
        return listCar(garage);
    case '3': {
        TClient *client = TClient_factory();
        int rc = clientEditMenu(client);
        if (rc == 0) {
            garage->pClients = realloc(garage->pClients, ++garage->clients_size * sizeof(TClient *));
            garage->pClients[garage->clients_size - 1] = client;
            printf("Client successfully added!\n");
        } else {
            free(client);
            printf("An error occurred while adding the client!\n");
        }
        return rc;
    }
    case '4': {
        TClient *client = clientSelectMenu(garage);
        int rc = 0;
        if (client == NULL)
            rc = 1;
        else
            rc = clientEditMenu(client);
        if (rc == 0)
            printf("Client successfully edited!\n");
        else
            printf("An error occurred while editing the client!\n");
        return rc;
    }
    case '5': {
        TCar *car = TCar_factory();
        int rc = carEditMenu(car, garage);
        if (rc == 0) {
            garage->pCars = realloc(garage->pCars, ++garage->cars_size * sizeof(TCar *));
            garage->pCars[garage->cars_size - 1] = car;
            printf("Car successfully added!\n");
        } else {
            free(car);
            printf("An error occurred while adding the car!\n");
        }
        return rc;
    }
    case '6': {
        TCar *car = carSelectMenu(garage);
        int rc = 0;
        if (car == NULL)
            rc = 1;
        else
            rc = carStatusEditMenu(car);
        if (rc == 0)
            printf("Car status successfully edited!\n");
        else
            printf("An error occurred while editing the car status!\n");
        return rc;
    }
    case '7': {
        TCar *car = carSelectMenu(garage);
        int rc = 0;
        if (car == NULL)
            rc = 1;
        else
            rc = carEditMenu(car, garage);
        if (rc == 0)
            printf("Car successfully edited!\n");
        else
            printf("An error occurred while editing the car!\n");
        return rc;
    }
    default: {
        printf("Please enter a correct value (1-7,q)\n");
        return mainMenu(garage);
    }
    }
}
