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
void setAddressPostalCode(Address* address);

/**
 * Prints the details of an address in a formatted manner.
 * @param address Pointer to the Address structure whose details are being printed.
 */
void printAddressDetails(const Address* address);

#endif // ADDRESS_H
