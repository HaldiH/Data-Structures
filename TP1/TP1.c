#include "Exercise1.h"

int main(int argc, char *argv[]) {
    TGarage *garage = TGarage_factory();
    while (mainMenu(garage) >= 0)
        ;
    return 0;
}