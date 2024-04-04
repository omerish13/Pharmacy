#ifndef ADDRESS_H
#define ADDRESS_H

#include "general.h"  // Include for CHECK_ALLOC and myGets

/**
 * Structure for storing address details with dynamically allocated strings
 * for country, city, and street, and a fixed-size array for the postal code.
 */
typedef struct {
    char* country;      /**< Dynamically allocated country string */
    char* city;         /**< Dynamically allocated city string */
    char* street;       /**< Dynamically allocated street string */
    int houseNumber;    /**< House number */
    char postalCode[7]; /**< Fixed-size array for postal code (6 characters + null terminator) */
} Address;

/**
 * Sets the country for an address after dynamically allocating memory for it.
 * @param address Pointer to the Address structure whose country is being set.
 */
void setAddressCountry(Address* address);

/**
 * Sets the city for an address after dynamically allocating memory for it.
 * @param address Pointer to the Address structure whose city is being set.
 */
void setAddressCity(Address* address);

/**
 * Sets the street for an address after dynamically allocating memory for it.
 * @param address Pointer to the Address structure whose street is being set.
 */
void setAddressStreet(Address* address);

/**
 * Sets the house number for an address based on the user's input.
 * @param address Pointer to the Address structure whose house number is being set.
 */
void setAddressHouseNumber(Address* address);

/**
 * Sets the postal code for an address after validating it's exactly 6 characters.
 * @param address Pointer to the Address structure whose postal code is being set.
 */
int setAddressPostalCode(Address* address);

/**
 * Prints the details of an address in a formatted manner.
 * @param address Pointer to the Address structure whose details are being printed.
 */
void printAddressDetails(const Address* address);

/**
 * Initializes an address by setting its country, city, street, house number, and postal code.
 * @param address Pointer to the Address structure to be initialized.
 */
void initAddress(Address* address);

/**
 * Saves address details to a file.
 * @param address Pointer to the Address structure containing the details to save.
 * @param file Pointer to the file to save the address details to.
 */
void saveAddress(const Address* address, FILE* file);
/**
 * Loads address details from a file, assuming the file is formatted correctly.
 * @param address Pointer to the Address structure to load the details into.
 * @param file Pointer to the file to read the address details from.
 */
void loadAddress(Address* address, FILE* file);
/**
 * Frees the dynamically allocated memory for the strings in an Address structure.
 * @param address Pointer to the Address structure to be freed.
 */
void freeAddress(Address* address);

#endif // ADDRESS_H
