#ifndef PERSON_H
#define PERSON_H

#include "general.h"  // Include for CHECK_ALLOC and myGets

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
    int id;          /**< Unique person ID, automatically incremented */
    char* name;      /**< Dynamically allocated person name */
    Gender gender;   /**< Gender, represented by an enum */
    char* phoneNumber; /**< Dynamically allocated phone number */
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
 * Frees the dynamically allocated memory for the person's name and phone number.
 * @param person Pointer to the Person structure to free.
 */
void freePerson(Person* person);


#endif // PERSON_H
