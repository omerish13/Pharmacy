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

int savePersonToBinary(FILE* file, const Person* person) {
    if (((!fwrite(&person->id, sizeof(int), 1, file)) == 1))
        return 0;
    int nameLength = strlen(person->name) + 1;
    if (((!fwrite(&nameLength, sizeof(int), 1, file)) == 1) || ((!fwrite(person->name, sizeof(char), nameLength, file)) == nameLength))
        return 0;
    int gender = (int)person->gender;
    if (((!fwrite(&gender, sizeof(int), 1, file)) == 1))
        return 0;
    int phoneNumberLength = strlen(person->phoneNumber) + 1;
    if (((!fwrite(&phoneNumberLength, sizeof(int), 1, file)) == 1) || ((!fwrite(person->phoneNumber, sizeof(char), phoneNumberLength, file)) == phoneNumberLength))
        return 0;
    return 1;
}

int loadPersonFromBinary(Person* person, FILE* file) {
    if (((!fread(&person->id, sizeof(int), 1, file)) != 1))
        return 0;
    int nameLength;
    if (((!fread(&nameLength, sizeof(int), 1, file)) != 1))
        return 0;
    person->name = (char*)malloc(nameLength);
    CHECK_ALLOC_INT(person->name);
    if (((!fread(person->name, sizeof(char), nameLength, file)) != nameLength))
        return 0;
    if (((!fread(&person->gender, sizeof(Gender), 1, file)) != 1))
        return 0;
    int phoneNumberLength;
    if (((!fread(&phoneNumberLength, sizeof(int), 1, file)) != 1))
        return 0;
    person->phoneNumber = (char*)malloc(phoneNumberLength);
    CHECK_ALLOC_INT(person->phoneNumber);
    if (((!fread(person->phoneNumber, sizeof(char), phoneNumberLength, file)) != phoneNumberLength))
        return 0;
    return 1;
}

void savePerson(FILE* file, const Person* person) {
    fprintf(file, "%d\n", person->id);
    int nameLength = strlen(person->name) + 1;
    fprintf(file, "%d\n", nameLength);
    fprintf(file, "%s\n", person->name);
    fprintf(file, "%d\n", person->gender);
    int phoneNumberLength = strlen(person->phoneNumber) + 1;
    fprintf(file, "%d\n", phoneNumberLength);
    fprintf(file, "%s\n", person->phoneNumber);
}

void loadPerson(Person* person, FILE* file) {
    fscanf(file, "%d\n", &person->id);
    int nameLength;
    fscanf(file, "%d\n", &nameLength);
    person->name = (char*)malloc(nameLength);
    CHECK_ALLOC_VOID(person->name);
    fscanf(file, "%s\n", person->name);
    fscanf(file, "%d\n", &person->gender);
    int phoneNumberLength;
    fscanf(file, "%d\n", &phoneNumberLength);
    person->phoneNumber = (char*)malloc(phoneNumberLength);
    CHECK_ALLOC_VOID(person->phoneNumber);
    fscanf(file, "%s\n", person->phoneNumber);
}

void freePerson(Person* person) {
    free(person->name);
    person->name = NULL;
    free(person->phoneNumber);
    person->phoneNumber = NULL;
}
