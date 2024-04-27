#include "Person.h"


void initPerson(Person* person) {
    setPersonName(person);
    setPersonGender(person);
    setPersonId(person);  // Set the ID for the person
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

void setPersonId(Person* person) {
    char buffer[BUFFER_SIZE];
    int valid = 0;

    while (!valid) {
        printf("Enter person ID: ");
        myGets(buffer);

        // Validation check
        valid = validatePersonId(buffer);

        if (valid) {
            strcpy(person->PersonId, buffer);
        } else {
            printf("Invalid person ID format. Please try again.\n");
        }
    }
}

int validatePersonId(const char* personId) {
    // Check for correct format: XXXXXX (9 digits)
    if (strlen(personId) != 9) {
        return 0;
    }

    // Check for digits in all positions
    for (int i = 0; i < 9; i++) {
        if (!isdigit(personId[i])) {
            return 0;
        }
    }

    // If all checks pass, the format is valid
    return 1;
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

int savePersonToBinaryFileCompressed(FILE* file, const Person* person) {
    // Compress the information into two bytes
    BYTE data[2] = { 0 };
    int nameLength = (int)strlen(person->name);
    int personGender = (int)person->gender;
    // Allocate 8 bits for name length
    data[0] = (BYTE)nameLength;
    // Allocate 2 bits for gender
    data[1] = (BYTE)(personGender << 2);
    if (fwrite(data, sizeof(BYTE), 2, file) != 2)
        return 0;
    if (fwrite(person->name, sizeof(char), nameLength, file) != nameLength)
        return 0;
    if (fwrite(person->PersonId, sizeof(char), ID_LENGTH, file) != ID_LENGTH)
        return 0;
    if (fwrite(person->phoneNumber, sizeof(char), PHONE_NUMBER_LENGTH, file) != PHONE_NUMBER_LENGTH)
        return 0;
    return 1;
}

int loadPersonFromBinaryFileCompressed(Person* person, FILE* file) {
    BYTE data[2];
    if (fread(data, sizeof(BYTE), 2, file) != 2)
        return 0;
    int nameLength = (int)data[0];
    int gender = (int)(data[1] >> 2);
    printf("Name length: %d\n", nameLength);

    person->name = (char*)malloc(nameLength);
    CHECK_ALLOC_INT(person->name);

    if (fread(person->name, sizeof(char), nameLength, file) != nameLength)
        return 0;
    printf("Name");

    if (fread(person->PersonId, sizeof(char), ID_LENGTH, file) != ID_LENGTH)
        return 0;
    printf("ID");

    if (fread(person->phoneNumber, sizeof(char), PHONE_NUMBER_LENGTH, file) != PHONE_NUMBER_LENGTH)
        return 0;

    printf("Phone number");
    person->name[nameLength] = '\0';
    person->PersonId[ID_LENGTH] = '\0';
    person->phoneNumber[PHONE_NUMBER_LENGTH] = '\0';
    
    person->gender = (Gender)gender;

    return 1;
}
 
void printPersonDetails(const Person* person) {
    printf("Name: %s, ", person->name);
    printf("Gender: %s, ", person->gender == MALE ? "Male" : person->gender == FEMALE ? "Female" : "Other");
    printf("Person ID: %s, ", person->PersonId);
    printf("Phone Number: %s, ", person->phoneNumber);
}

int savePersonToBinary(FILE* file, const Person* person) {
    int nameLength = (int)(strlen(person->name))+1;
    if ((fwrite(&nameLength, sizeof(int), 1, file)) != 1)
        return 0;
    if ((fwrite(person->name, sizeof(char), nameLength, file)) != nameLength)
        return 0;
    int gender = (int)person->gender;
    if (fwrite(&gender, sizeof(int), 1, file) != 1)
        return 0;
    if ((fwrite(person->PersonId, sizeof(char), ID_LENGTH, file) != ID_LENGTH))
        return 0;
    if ((fwrite(person->phoneNumber, sizeof(char), PHONE_NUMBER_LENGTH, file) != PHONE_NUMBER_LENGTH))
        return 0;
    return 1;
}

int loadPersonFromBinary(Person* person, FILE* file) {
    int nameLength;
    if (fread(&nameLength, sizeof(int), 1, file) != 1)
    {
        printf("Error reading name length\n");
        return 0;
    }
    person->name = (char*)malloc(nameLength);
    CHECK_ALLOC_INT(person->name);
    if (fread(person->name, sizeof(char), nameLength, file) != nameLength)
        return 0;
    int gender;
    if (fread(&gender, sizeof(int), 1, file) != 1)
        return 0;
    person->gender = (Gender)gender;
    if (fread(person->PersonId, sizeof(char), ID_LENGTH, file) != ID_LENGTH)
        return 0;
    if (fread(person->phoneNumber, sizeof(char), PHONE_NUMBER_LENGTH, file) != PHONE_NUMBER_LENGTH)
        return 0;
    return 1;
}

void savePerson(FILE* file, const Person* person) {
    int nameLength = strlen(person->name) + 1;
    fprintf(file, "%d\n", nameLength);
    fprintf(file, "%s\n", person->name);
    fprintf(file, "%d\n", person->gender);
    fprintf(file, "%s\n", person->PersonId);
    fprintf(file, "%s\n", person->phoneNumber);
}

void loadPerson(Person* person, FILE* file) {
    int nameLength;
    fscanf(file, "%d\n", &nameLength);
    person->name = (char*)malloc(nameLength);
    CHECK_ALLOC_VOID(person->name);
    fscanf(file, "%s\n", person->name);
    fscanf(file, "%d\n", &person->gender);
    fscanf(file, "%s\n", person->PersonId);
    fscanf(file, "%s\n", person->phoneNumber);
}

void freePerson(Person* person) {
    free(person->name);
    person->name = NULL;
}
