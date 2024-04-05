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
    myGets(buffer);
    person->name = (char*)malloc(strlen(buffer) + 1);
    CHECK_ALLOC_VOID(person->name);
    strcpy(person->name, buffer);
}

void setPersonGender(Person* person) {
    char buffer[BUFFER_SIZE];
    printf("Enter person gender (Male, Female, Other): ");
    myGets(buffer);
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
        myGets(buffer);

        // Validation check
        valid = validatePhoneNumber(buffer);
        
        if (valid) {
            person->phoneNumber = (char*)malloc(strlen(buffer) + 1);
            CHECK_ALLOC_VOID(person->phoneNumber);
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
    printf("Person ID: %d ", person->id);
    printf("Name: %s ", person->name);
    printf("Gender: %s ", person->gender == MALE ? "Male" : person->gender == FEMALE ? "Female" : "Other");
    printf("Phone Number: %s ", person->phoneNumber);
}

void savePerson(FILE* file, const Person* person) {
    fwrite(&person->id, sizeof(int), 1, file);
    int nameLength = strlen(person->name) + 1;
    fwrite(&nameLength, sizeof(int), 1, file);
    fwrite(person->name, sizeof(char), nameLength, file);
    fwrite(&person->gender, sizeof(Gender), 1, file);
    int phoneNumberLength = strlen(person->phoneNumber) + 1;
    fwrite(&phoneNumberLength, sizeof(int), 1, file);
    fwrite(person->phoneNumber, sizeof(char), phoneNumberLength, file);
}

void loadPerson(Person* person, FILE* file) {
    fread(&person->id, sizeof(int), 1, file);
    int nameLength;
    fread(&nameLength, sizeof(int), 1, file);
    person->name = (char*)malloc(nameLength);
    fread(person->name, sizeof(char), nameLength, file);
    fread(&person->gender, sizeof(Gender), 1, file);
    int phoneNumberLength;
    fread(&phoneNumberLength, sizeof(int), 1, file);
    person->phoneNumber = (char*)malloc(phoneNumberLength);
    fread(person->phoneNumber, sizeof(char), phoneNumberLength, file);
}

void freePerson(Person* person) {
    free(person->name);
    person->name = NULL;
    free(person->phoneNumber);
    person->phoneNumber = NULL;
}
