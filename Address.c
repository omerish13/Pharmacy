#include "Address.h"

void initAddress(Address* address) {
    setAddressCountry(address);
    setAddressCity(address);
    setAddressStreet(address);
    setAddressHouseNumber(address);
    int res;
    do
    {
        res = setAddressPostalCode(address);
    } while (!res);
}

void setAddressCountry(Address* address) {
    char buffer[BUFFER_SIZE];
    printf("Enter country: ");
    myGets(buffer);
    address->country = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC(address->country);
    strcpy(address->country, buffer);
}

void setAddressCity(Address* address) {
    char buffer[BUFFER_SIZE];
    printf("Enter city: ");
    myGets(buffer);
    address->city = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC(address->city);
    strcpy(address->city, buffer);
}

void setAddressStreet(Address* address) {
    char buffer[BUFFER_SIZE];
    printf("Enter street: ");
    myGets(buffer);
    address->street = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC(address->street);
    strcpy(address->street, buffer);
}

void setAddressHouseNumber(Address* address) {
    char buffer[BUFFER_SIZE];
    printf("Enter house number: ");
    myGets(buffer);
    address->houseNumber = atoi(buffer);
}

int setAddressPostalCode(Address* address) {
    char buffer[BUFFER_SIZE];
    printf("Enter postal code (6 characters): ");
    myGets(buffer);
    if (strlen(buffer) == 6) {
        strncpy(address->postalCode, buffer, 6);
        address->postalCode[6] = '\0';
        return 1;
    }
    printf("Error: Postal code must be exactly 6 characters.\n");
    return 0;
}

void printAddressDetails(const Address* address) {
    printf("Address: %s, %s, %s, %d, %s\n", address->country, address->city, address->street, address->houseNumber, address->postalCode);
}

void saveAddress(const Address* address, FILE* file) {
    fprintf(file, "%s\n%s\n%s\n%d\n%s\n", address->country, address->city, address->street, address->houseNumber, address->postalCode);
}

void loadAddress(Address* address, FILE* file){
    fscanf(file, "%s\n%s\n%s\n%d\n%s\n", address->country, address->city, address->street, &address->houseNumber, address->postalCode);
}

void freeAddress(Address* address) {
    free(address->country);
    free(address->city);
    free(address->street);
}