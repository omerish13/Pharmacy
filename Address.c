#include "Address.h"

void initAddress(Address* address) {
    setAddressCountry(address);
    setAddressCity(address);
    setAddressStreet(address);
    setAddressHouseNumber(address);
    setAddressPostalCode(address);
}

void setAddressCountry(Address* address) {
    char buffer[BUFFER_SIZE];
    printf("Enter country: ");
    myGets(buffer, BUFFER_SIZE);
    address->country = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC(address->country);
    strcpy(address->country, buffer);
}

void setAddressCity(Address* address) {
    char buffer[BUFFER_SIZE];
    printf("Enter city: ");
    myGets(buffer, BUFFER_SIZE);
    address->city = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC(address->city);
    strcpy(address->city, buffer);
}

void setAddressStreet(Address* address) {
    char buffer[BUFFER_SIZE];
    printf("Enter street: ");
    myGets(buffer, BUFFER_SIZE);
    address->street = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC(address->street);
    strcpy(address->street, buffer);
}

void setAddressHouseNumber(Address* address) {
    char buffer[BUFFER_SIZE];
    printf("Enter house number: ");
    myGets(buffer, BUFFER_SIZE);
    address->houseNumber = atoi(buffer);
}

void setAddressPostalCode(Address* address) {
    char buffer[BUFFER_SIZE];
    printf("Enter postal code (6 characters): ");
    myGets(buffer, BUFFER_SIZE);
    if (strlen(buffer) == 6) {
        strncpy(address->postalCode, buffer, 6);
        address->postalCode[6] = '\0';
    } else {
        printf("Error: Postal code must be exactly 6 characters.\n");
    }
}

void printAddressDetails(const Address* address) {
    printf("Address: %s, %s, %s, %d, %s\n", address->country, address->city, address->street, address->houseNumber, address->postalCode);
}
