#include "Address.h"

#define POSTAL_CODE_LENGTH 6
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
    CHECK_ALLOC_VOID(address->country);
    strcpy(address->country, buffer);
}

void setAddressCity(Address* address) {
    char buffer[BUFFER_SIZE];
    printf("Enter city: ");
    myGets(buffer);
    address->city = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC_VOID(address->city);
    strcpy(address->city, buffer);
}

void setAddressStreet(Address* address) {
    char buffer[BUFFER_SIZE];
    printf("Enter street: ");
    myGets(buffer);
    address->street = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC_VOID(address->street);
    strcpy(address->street, buffer);
}

void setAddressHouseNumber(Address* address) {
    printf("Enter house number: ");
    scanf("%d", &address->houseNumber);
    clearInputBuffer();
}

int setAddressPostalCode(Address* address) {
    char buffer[BUFFER_SIZE];
    printf("Enter postal code (6 characters): ");
    myGets(buffer);
    if (strlen(buffer) == POSTAL_CODE_LENGTH) {
        strncpy(address->postalCode, buffer, POSTAL_CODE_LENGTH);
        address->postalCode[POSTAL_CODE_LENGTH] = '\0';
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

int saveAddressToBinary(const Address* address, FILE* file) {
    int length = (int)strlen(address->country) + 1;
    if (fwrite(&length, sizeof(int), 1, file) != 1)
        return 0;
    if (fwrite(address->country, sizeof(char), length, file) != length)
        return 0;
    length = (int)strlen(address->city) + 1;
    if (fwrite(&length, sizeof(int), 1, file) != 1)
        return 0;
    if (fwrite(address->city, sizeof(char), length, file) != length)
        return 0;
    length = (int)strlen(address->street) + 1;
    if (fwrite(&length, sizeof(int), 1, file) != 1)
        return 0;
    if (fwrite(address->street, sizeof(char), length, file) != length)
        return 0;
    if (fwrite(&address->houseNumber, sizeof(int), 1, file) != 1)
        return 0;
    if (fwrite(address->postalCode, sizeof(char), POSTAL_CODE_LENGTH + 1, file) != POSTAL_CODE_LENGTH + 1)
        return 0;
    return 1;
}

int loadAddressFromBinary(Address* address, FILE* file) {
    int length;
    if (fread(&length, sizeof(int), 1, file) != 1)
        return 0;
    address->country = (char*)malloc(length);
    CHECK_ALLOC_INT(address->country);
    if (fread(address->country, sizeof(char), length, file) != length)
        return 0;
    if (fread(&length, sizeof(int), 1, file) != 1)
        return 0;
    address->city = (char*)malloc(length);
    CHECK_ALLOC_INT(address->city);
    if (fread(address->city, sizeof(char), length, file) != length)
        return 0;
    if (fread(&length, sizeof(int), 1, file) != 1)
        return 0;
    address->street = (char*)malloc(length);
    CHECK_ALLOC_INT(address->street);
    if (fread(address->street, sizeof(char), length, file) != length)
        return 0;
    if (fread(&address->houseNumber, sizeof(int), 1, file) != 1)
        return 0;
    if (fread(address->postalCode, sizeof(char), POSTAL_CODE_LENGTH + 1, file) != POSTAL_CODE_LENGTH + 1)
        return 0;
    return 1;
}

void loadAddress(Address* address, FILE* file){
    address->country = (char*)malloc(BUFFER_SIZE);
    CHECK_ALLOC_VOID(address->country);
    address->city = (char*)malloc(BUFFER_SIZE);
    CHECK_ALLOC_VOID(address->city);
    address->street = (char*)malloc(BUFFER_SIZE);
    CHECK_ALLOC_VOID(address->street);
    fscanf(file, "%s\n", address->country);
    // Read the city included the spaces
    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, file);
    buffer[strlen(buffer) - 1] = '\0';
    strcpy(address->city, buffer);
    // Read the street included the spaces
    fgets(buffer, BUFFER_SIZE, file);
    buffer[strlen(buffer) - 1] = '\0';
    strcpy(address->street, buffer);
    fscanf(file, "%d\n", &address->houseNumber);
    fscanf(file, "%s\n", address->postalCode);
}

void freeAddress(Address* address) {
    free(address->country);
    free(address->city);
    free(address->street);
}