#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define ENTRY_SIZE 45
// Function to create a telephone book file with reserved space for entries
void reserveSpaceForTelephoneBook(const char *filename, size_t numEntries) {
    int fileDescriptor;
    if((fileDescriptor = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {//open the file
        perror("Error: Unable to create telephone book file");
        exit(EXIT_FAILURE);
    }
    if(lseek(fileDescriptor, numEntries * ENTRY_SIZE - 1, SEEK_SET) == -1) { // Seeking to the end to allocate space for entries
        perror("Error: Unable to allocate space in telephone book file");
        close(fileDescriptor);
        exit(EXIT_FAILURE);
    }
    if(write(fileDescriptor, "", 1) == -1) {// Writing a dummy byte to ensure space allocation
        perror("Error: Unable to write to telephone book file");
        close(fileDescriptor);
        exit(EXIT_FAILURE);
    }
    close(fileDescriptor);
}
// Function to read and display an entry from the telephone book
void readTelephoneBookEntry(const char *filename, size_t index) {
    int fileDescriptor;
    char entry[ENTRY_SIZE];
    if((fileDescriptor = open(filename, O_RDONLY)) == -1) {
        perror("Error: Unable to open telephone book file");
        exit(EXIT_FAILURE);
    }
    if(lseek(fileDescriptor, index * ENTRY_SIZE, SEEK_SET) == -1) {// Seeking to the specified entry
        perror("Error: Unable to locate entry in telephone book file");
        close(fileDescriptor);
        exit(EXIT_FAILURE);
    }
    if(read(fileDescriptor, entry, ENTRY_SIZE) == -1) {// reading the entry
        perror("Error: Unable to read from telephone book file");
        close(fileDescriptor);
        exit(EXIT_FAILURE);
    }
    printf("Entry at index %zu: %s\n", index, entry);//Displaying the entry

    close(fileDescriptor);
}
// Function to write an entry to the telephone book
void writeTelephoneBookEntry(const char *filename, size_t index, const char *name, const char *telephone) {
    int fileDescriptor;
    char entry[ENTRY_SIZE];
    if((fileDescriptor = open(filename, O_RDWR)) == -1) {//opening file to read and write
        perror("Error: Unable to open telephone book file");
        exit(EXIT_FAILURE);
    }
    if(lseek(fileDescriptor, index * ENTRY_SIZE, SEEK_SET) == -1) {  // Seeking to the entry specified
        perror("Error: Unable to locate entry in telephone book file");
        close(fileDescriptor);
        exit(EXIT_FAILURE);
    }
    snprintf(entry, sizeof(entry), "%-20s%-20s", name, telephone);//constructing the entry string
    if(write(fileDescriptor, entry, ENTRY_SIZE) == -1) { //writing the entry
        perror("Error: Unable to write to telephone book file");
        close(fileDescriptor);
        exit(EXIT_FAILURE);
    }
    close(fileDescriptor);
}
// Function to display the current contents of the telephone book
void displayTelephoneBook(const char *filename, size_t numEntries) {
    int fileDescriptor;
    char entry[ENTRY_SIZE];
    if((fileDescriptor = open(filename, O_RDONLY)) == -1) {//Open the file to read
        perror("Error: Unable to open telephone book file");
        exit(EXIT_FAILURE);
    }
    // Display all entries
    for(size_t i = 0; i < numEntries; ++i) {
        if (lseek(fileDescriptor, i * ENTRY_SIZE, SEEK_SET) == -1) {//seeking of the specified entry
            perror("Error: Unable to locate entry in telephone book file");
            close(fileDescriptor);
            exit(EXIT_FAILURE);
        }
        if(read(fileDescriptor, entry, ENTRY_SIZE) == -1) {//reading the entry
            perror("Error: Unable to read from telephone book file");
            close(fileDescriptor);
            exit(EXIT_FAILURE);
        }
        printf("Entry at index %zu: %s\n", i, entry);//displaying the entry
    }
    close(fileDescriptor);
}
int displayTelephoneBookMenu() {
    int userChoice;//to get choice from the user
    //below are to display the menu
    printf("\nTelephone Book Options:\n");
    printf("\n1. Reserve Space for Telephone Book (only if you want to delete the previous file and create a new file..\ncumpulsory if you dont have any file and want ot write..)\n");
    printf("\n2. Read an Entry\n");
    printf("\n3. Write an Entry\n");
    printf("\n4. Display Telephone Book Entries\n");  
    printf("\n5. Exit\n");
    printf("\nPlease enter your choice: ");
    scanf("%d", &userChoice);
    return userChoice;
}
int main(){
    const char *telephoneBookFilename = "telephone_book.txt";
    size_t numberOfEntries = 20;  // Set the number of entries
    int userChoice;
    do {
        userChoice = displayTelephoneBookMenu();
        if(userChoice==1){
            reserveSpaceForTelephoneBook(telephoneBookFilename,numberOfEntries);
            printf("\nReserved space successfully for telephone book entries.\n");
        }else if(userChoice==2){
            size_t indexToRead;
            printf("\nEnter the index to read: ");
            scanf("%zu",&indexToRead);
            readTelephoneBookEntry(telephoneBookFilename,indexToRead);
        }else if(userChoice==3){
            size_t indexToWrite;
            char personName[21],personTelephone[21];
            printf("\nEnter the index to write\n(only between 0 to 19..anything outside this range will not be written, read, and displayed): ");
            scanf("%zu", &indexToWrite);
            printf("\nEnter name: ");
            scanf("%20s", personName);
            printf("\nEnter telephone: ");
            scanf("%20s", personTelephone);
            writeTelephoneBookEntry(telephoneBookFilename, indexToWrite, personName, personTelephone);
            printf("\nEntry written successfully.\n");
        }else if(userChoice==4) {
            displayTelephoneBook(telephoneBookFilename, numberOfEntries);
        }else if(userChoice==5) {
            printf("\nExiting the telephone book application.\n");
        }else{
            printf("\nInvalid choice. Please enter a valid option.\n");
        }
    }while(userChoice != 5);
    return 0;
}
