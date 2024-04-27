#ifndef PERSON_H
#define PERSON_H

#include "general.h"  // Include for CHECK_ALLOC and myGets
#include <ctype.h>    // Include for isdigit

#define ID_LENGTH 9
#define PHONE_NUMBER_LENGTH 11

typedef unsigned char BYTE;

/**
 * Enum for Gender.
 */
typedef enum {
    MALE,   /**< Male gender */
    FEMALE, /**< Female gender */
    OTHER   /**< Other/Unspecified gender */
} Gender;

/**
 * Structure representing a person's basic information, including a phone number.
 */
typedef struct {
    char* name;      /**< Dynamically allocated person name */
    Gender gender;   /**< Gender, represented by an enum */
    char PersonId[ID_LENGTH+1]; /**< Person ID, a 9-digit string */
    char phoneNumber[PHONE_NUMBER_LENGTH+1]; /**< Dynamically allocated phone number */
} Person;

/**
 * Initializes a Person structure with a unique ID and other provided details.
 * @param person Pointer to the Person structure to initialize.
 */
void initPerson(Person* person);

/**
 * Sets the name of a person after dynamically allocating memory for it.
 * @param person Pointer to the Person structure whose name is being set.
 */
void setPersonName(Person* person);

/**
 * Sets the gender of a person based on the user's input.
 * @param person Pointer to the Person structure whose gender is being set.
 */
void setPersonGender(Person* person);

/**
 * @brief Sets the ID of a person.
 * @param person A pointer to the person object.
 */
void setPersonId(Person* person);

/**
 * Validates the ID of a person.
 * @param personId The ID of the person.
 */
int validatePersonId(const char* personId);

/**
 * Sets the phone number of a person after dynamically allocating memory for it.
 * @param person Pointer to the Person structure whose phone number is being set.
 */
void setPersonPhoneNumber(Person* person);

/**
 * Validate the phone number.
 * @param phonNumber String of a phone number.
 */
int validatePhoneNumber(const char* phoneNumber);

/**
 * Prints the details of a person in a formatted manner.
 * @param person Pointer to the Person structure whose details are being printed.
 */
void printPersonDetails(const Person* person);

/**
 * Save person details to a binary file.
 * @param file Pointer to the binary file.
 * @param person Pointer to the Person structure to save.
 */
int savePersonToBinary(FILE* file, const Person* person);

/**
 * Load person details from a binary file.
 * @param file Pointer to the binary file.
 * @param person Pointer to the Person structure to load.
 */
int loadPersonFromBinary(Person* person, FILE* file);

/**
 * Save person details to a binary file with compression.
 * @param file Pointer to the binary file.
 * @param person Pointer to the Person structure to save.
 */
int savePersonToBinaryFileCompressed(FILE* file, const Person* person);

/**
 * Load person details from a binary file with compression.
 * @param file Pointer to the binary file.
 * @param person Pointer to the Person structure to load.
 */
int loadPersonFromBinaryFileCompressed(Person* person, FILE* file);

/**
 * Save person details from the user, including name and phone number.
 * @param person Pointer to the Person structure to store the details.
 */
void savePerson(FILE* file, const Person* person);

/**
 * Reads person details from a file, including name and phone number.
 * @param person Pointer to the Person structure to store the details.
 */
void loadPerson(Person* person, FILE* file);

/**
 * Frees the dynamically allocated memory for the person's name and phone number.
 * @param person Pointer to the Person structure to free.
 */
void freePerson(Person* person);


#endif // PERSON_H
