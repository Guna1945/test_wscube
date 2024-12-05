#include <stdio.h>
#include <string.h>

#define MAX_TABLES 10
#define NAME_LENGTH 100

// Table structure
typedef struct {
    int tableNumber;
    char reservedBy[NAME_LENGTH];
    int isReserved;
} Table;

// Global array of tables
Table tables[MAX_TABLES];

// Function to initialize all tables as available
void initializeTables() {
    for (int i = 0; i < MAX_TABLES; i++) {
        tables[i].tableNumber = i + 1;
        tables[i].isReserved = 0;  // 0 means not reserved
        strcpy(tables[i].reservedBy, "NONE");
    }
}

// Function to display the current status of all tables
void displayTables() {
    printf("\n--- TABLE STATUS ---\n");
    for (int i = 0; i < MAX_TABLES; i++) {
        if (tables[i].isReserved) {
            printf("TABLE %d: RESERVED BY %s\n", tables[i].tableNumber, tables[i].reservedBy);
        } else {
            printf("TABLE %d: AVAILABLE\n", tables[i].tableNumber);
        }
    }
    printf("---------------------\n");
}

// Function to reserve a table
void reserveTable() {
    int tableNumber;
    char name[NAME_LENGTH];

    printf("Enter the table number to reserve (1-%d): ", MAX_TABLES);
    scanf("%d", &tableNumber);
    getchar(); // to consume the newline character left by scanf

    if (tableNumber < 1 || tableNumber > MAX_TABLES) {
        printf("Invalid table number.\n");
        return;
    }

    if (tables[tableNumber - 1].isReserved) {
        printf("Table %d is already reserved.\n", tableNumber);
    } else {
        printf("Enter your name to reserve Table %d: ", tableNumber);
        fgets(name, NAME_LENGTH, stdin);
        name[strcspn(name, "\n")] = '\0'; // Remove the newline character

        tables[tableNumber - 1].isReserved = 1;
        strcpy(tables[tableNumber - 1].reservedBy, name);

        printf("Table %d successfully reserved for %s.\n", tableNumber, name);
    }
}

// Function to cancel a reservation
void cancelReservation() {
    int tableNumber;

    printf("Enter the table number to cancel reservation (1-%d): ", MAX_TABLES);
    scanf("%d", &tableNumber);

    if (tableNumber < 1 || tableNumber > MAX_TABLES) {
        printf("Invalid table number.\n");
        return;
    }

    if (!tables[tableNumber - 1].isReserved) {
        printf("Table %d is not reserved.\n", tableNumber);
    } else {
        printf("Reservation for Table %d canceled. The table is now available.\n", tableNumber);
        tables[tableNumber - 1].isReserved = 0;
        strcpy(tables[tableNumber - 1].reservedBy, "NONE");
    }
}

// Main function to display the menu and handle user interaction
int main() {
    int choice;

    // Initialize the tables
    initializeTables();

    do {
        printf("\n--- RESTAURANT TABLE RESERVATION SYSTEM ---\n");
        printf("1. Display Table Status\n");
        printf("2. Reserve a Table\n");
        printf("3. Cancel Reservation\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayTables();
                break;
            case 2:
                reserveTable();
                break;
            case 3:
                cancelReservation();
                break;
            case 4:
                printf("Exiting system...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

