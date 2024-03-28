#include "Person.h"

static int lastPersonID = 0;  // Static variable to keep track of the last used person ID

void initPerson(Person* person) {
    person->id = ++lastPersonID;  // Auto-increment the person ID for each new person
    setPersonName(person);
    setPersonGender(person);
    setPersonPhoneNumber(person);  // Set the phone number for the person
}

void setPersonName(Person* person) {
    char buffer[BUFFER_SIZE];
    printf("Enter person name: ");
    myGets(buffer, BUFFER_SIZE);
    person->name = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC(person->name);
    strcpy(person->name, buffer);
}

void setPersonGender(Person* person) {
    char buffer[BUFFER_SIZE];
    printf("Enter person gender (Male, Female, Other): ");
    myGets(buffer, BUFFER_SIZE);
    if (strcmp(buffer, "Male") == 0) {
        person->gender = MALE;
    } else if (strcmp(buffer, "Female") == 0) {
        person->gender = FEMALE;
    } else {
        person->gender = OTHER;
    }
}

void setPersonPhoneNumber(Person* person) {
    char buffer[BUFFER_SIZE];
    int valid = 0;
    
    while (!valid) {
        printf("Enter person phone number (format 000-0000000): ");
        myGets(buffer, BUFFER_SIZE);

        // Validation check
        valid = validatePhoneNumber(buffer);
        
        if (valid) {
            person->phoneNumber = (char*)malloc(strlen(buffer) + 1);
            CHECK_ALLOC(person->phoneNumber);
            strcpy(person->phoneNumber, buffer);
        } else {
            printf("Invalid phone number format. Please try again.\n");
        }
    }
}

int validatePhoneNumber(const char* phoneNumber) {
    // Check for correct format: 000-0000000 (11 characters including hyphen)
    if (strlen(phoneNumber) != 11) {
        return 0;
    }

    // Check for digits in the correct positions
    for (int i = 0; i < 11; i++) {
        if (i == 3) {
            // The fourth character should be a hyphen
            if (phoneNumber[i] != '-') {
                return 0;
            }
        } else {
            // All other characters should be digits
            if (!isdigit(phoneNumber[i])) {
                return 0;
            }
        }
    }

    // If all checks pass, the format is valid
    return 1;
}


void printPersonDetails(const Person* person) {
    printf("Person ID: %d\n", person->id);
    printf("Name: %s\n", person->name);
    printf("Gender: %s\n", person->gender == MALE ? "Male" : person->gender == FEMALE ? "Female" : "Other");
    printf("Phone Number: %s\n", person->phoneNumber);
}
