#ifndef TP1_C_EXERCISE1_H
#define TP1_C_EXERCISE1_H
#define STRING_MAXSIZE 30

typedef struct {
    char *m_name;
    char *m_address;
    char *m_phone_number;
} TClient;

// Constructor
TClient *TClient_factory();

// Getters
char *TClient_getPhoneNumber(const TClient *client);
char *TClient_getName(const TClient *client);
char *TClient_getAddress(const TClient *client);

// Setters
int TClient_setName(TClient *client, char *name);
int TClient_setAddress(TClient *client, char *address);
int TClient_setPhoneNumber(TClient *client, char *phone_number);

typedef enum { PENDING, REPAIRED, PAID } TStatus;

typedef struct {
    char *m_brand;
    char *m_model;
    char *m_matriculation;
    TClient *m_owner;
    TStatus m_status;
} TCar;

// Constructor
TCar *TCar_factory();

// Getters
char *TCar_getBrand(const TCar *car);
char *TCar_getModel(const TCar *car);
char *TCar_getMatriculation(const TCar *car);
TClient *TCar_getOwner(const TCar *car);
TStatus TCar_getStatus(const TCar *car);
char *TCar_getStatusString(const TCar *car);

// Setters

int TCar_setBrand(TCar *car, char *brand);
int TCar_setModel(TCar *car, char *model);
int TCar_setMatriculation(TCar *car, char *matriculation);
int TCar_setOwner(TCar *car, TClient *owner);
int TCar_setStatus(TCar *car, TStatus status);

typedef struct {
    TClient **pClients;
    TCar **pCars;
    int clients_size;
    int cars_size;
} TGarage;

// Constructor
TGarage *TGarage_factory();
void TGarage_destructor(TGarage *garage);

int listCar(const TGarage *garage);
int listClient(const TGarage *garage);
static int carStatusEditMenu(TCar *car);
int carEditMenu(TCar *car, TGarage *garage);
TCar *carSelectMenu(const TGarage *garage);
static int clientEditMenu(TClient *client);
TClient *clientSelectMenu(const TGarage *garage);
int mainMenu(TGarage *garage);

#endif // TP1_C_EXERCISE1_H
