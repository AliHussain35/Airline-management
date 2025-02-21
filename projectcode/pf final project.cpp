#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct for Flights
struct Flight {
    char flightname[30];
    char pickup[30];
    char destination[30];
    int businessclass;
    int economy;
    int availableseats;
    char timing[10];
};

// Struct for Passengers
struct Passenger {
    char name[50];
    char passengerseat[50];
    char flightname[30];
    char bookingRef[15];
};

// Global Variables
struct Flight *flights = NULL;
struct Passenger *passengers = NULL;
int flightCount = 0, passengerCount = 0;
int flightCapacity = 10, passengerCapacity = 10;
const char *VERIFICATION_CODE = "1234";

// Function Prototypes
void initialize();
void addFlight();
void removeFlight();
void modifyFlight();
void displayFlights();
void bookFlight();
void cancelBooking();
void searchFlights();
void viewBookingDetails();
void saveDataToFile();
void loadDataFromFile();
int verifyUser();
void generateBookingRef(char *ref);

// Utility Functions
int validateTimeFormat(const char *time);
void resizeFlights();
void resizePassengers();

int main() {
    initialize();

    int option;
    printf("***** Welcome to ABC International Airlines *****\n");
    do {
        printf("\nMenu:\n");
        printf("1. View Flights\n");
        printf("2. Book Flight\n");
        printf("3. Cancel Booking\n");
        printf("4. Search Flights\n");
        printf("5. View Booking Details\n");
        printf("6. Add Flight (Authorized Only)\n");
        printf("7. Remove Flight (Authorized Only)\n");
        printf("8. Modify Flight (Authorized Only)\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 1: displayFlights(); break;
            case 2: bookFlight(); break;
            case 3: cancelBooking(); break;
            case 4: searchFlights(); break;
            case 5: viewBookingDetails(); break;
            case 6: addFlight(); break;
            case 7: removeFlight(); break;
            case 8: modifyFlight(); break;
            case 0: 
                saveDataToFile();
                printf("Exiting... Thank you for using ABC Airlines!\n");
                break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (option != 0);

    // Free allocated memory
    free(flights);
    free(passengers);

    return 0;
}

// Initialize program, allocate memory, and load data from files
void initialize() {
	flights = (struct Flight*)malloc(300 * sizeof(struct Flight)); // Corrected
    passengers = (struct Passenger*)malloc(300 * sizeof(struct Passenger)); // Corrected
    loadDataFromFile();
}

// Add a new flight
void addFlight() {
    if (!verifyUser()) return;

    if (flightCount == flightCapacity) resizeFlights();

    struct Flight newFlight;
    printf("Enter Flight Name: ");
    scanf("%s", newFlight.flightname);
    printf("Enter Pickup Location: ");
    scanf("%s", newFlight.pickup);
    printf("Enter Destination: ");
    scanf("%s", newFlight.destination);
    printf("Enter Business Class Seats: ");
    scanf("%d", &newFlight.businessclass);
    printf("Enter Economy Seats: ");
    scanf("%d", &newFlight.economy);
    printf("Enter Timing (HH:MM): ");
    scanf("%s", newFlight.timing);

    if (!validateTimeFormat(newFlight.timing)) {
        printf("Invalid time format. Flight not added.\n");
        return;
    }

    newFlight.availableseats = newFlight.businessclass + newFlight.economy;
    flights[flightCount++] = newFlight;
    printf("Flight successfully added!\n");
}

// Remove a flight
void removeFlight() {
    if (!verifyUser()) return;

    displayFlights();
    int flightNum;
    printf("Enter the flight number to remove: ");
    scanf("%d", &flightNum);

    if (flightNum < 1 || flightNum > flightCount) {
        printf("Invalid flight number.\n");
        return;
    }

    for (int i = flightNum - 1; i < flightCount - 1; i++) {
        flights[i] = flights[i + 1];
    }
    flightCount--;
    printf("Flight successfully removed!\n");
}
#include <stdio.h>
#include <windows.h>  // Include windows.h for Beep function

// Function to play a beep sound
void playSound(int frequency, int duration) {
    Beep(frequency, duration);  // Play a sound with the given frequency and duration
}

// Function to generate and display the booking receipt
void generateReceipt(struct Passenger *passenger, struct Flight *flight) {
    printf("\n------------------------------------------------------------\n");
    printf("                    ABC International Airlines               \n");
    printf("------------------------------------------------------------\n");
    printf("                      BOOKING RECEIPT                       \n");
    printf("------------------------------------------------------------\n");

    // Play a sound effect as soon as the receipt starts printing
    playSound(500, 500); // Low-pitched sound for 500ms

    // Display passenger details
    printf("Passenger Name: %-30s\n", passenger->name);
    printf("Flight Name: %-32s\n", flight->flightname);
    printf("Pickup Location: %-26s\n", flight->pickup);
    printf("Destination: %-30s\n", flight->destination);
    printf("Seat Type: %-30s\n", passenger->passengerseat);
    printf("Booking Reference: %-17s\n", passenger->bookingRef);
    
    // Play another sound effect after displaying passenger info
    playSound(600, 300); // Medium-pitched sound for 300ms

    // Display available seats and pricing
    printf("Business Class Seats Left: %-5d  |  Economy Seats Left: %-5d\n", flight->businessclass, flight->economy);

    // Add pricing (you can modify the pricing based on your logic)
    int price = (strcmp(passenger->passengerseat, "Business") == 0) ? 1000 : 500;
    printf("Price: $%-33d\n", price);
    
    // Play a final sound effect before the receipt ends
    playSound(700, 400); // Higher-pitched sound for 400ms

    // Display footer
    printf("------------------------------------------------------------\n");
    printf("Thank you for choosing ABC International Airlines!\n");
    printf("------------------------------------------------------------\n");
}


// Modify flight details
void modifyFlight() {
    if (!verifyUser()) return;

    displayFlights();
    int flightNum;
    printf("Enter the flight number to modify: ");
    scanf("%d", &flightNum);

    if (flightNum < 1 || flightNum > flightCount) {
        printf("Invalid flight number.\n");
        return;
    }

    struct Flight *flight = &flights[flightNum - 1];
    printf("Modify Flight Name (current: %s): ", flight->flightname);
    scanf("%s", flight->flightname);
    printf("Modify Pickup Location (current: %s): ", flight->pickup);
    scanf("%s", flight->pickup);
    printf("Modify Destination (current: %s): ", flight->destination);
    scanf("%s", flight->destination);
    printf("Modify Business Class Seats (current: %d): ", flight->businessclass);
    scanf("%d", &flight->businessclass);
    printf("Modify Economy Seats (current: %d): ", flight->economy);
    scanf("%d", &flight->economy);
    printf("Modify Timing (current: %s): ", flight->timing);
    scanf("%s", flight->timing);

    if (!validateTimeFormat(flight->timing)) {
        printf("Invalid time format. Changes not saved.\n");
        return;
    }

    flight->availableseats = flight->businessclass + flight->economy;
    printf("Flight successfully modified!\n");
}

// View all flights
void displayFlights() {
    if (flightCount == 0) {
        printf("No flights available.\n");
        return;
    }

    for (int i = 0; i < flightCount; i++) {
        printf("Flight %d: %s | From: %s | To: %s | Business: %d | Economy: %d | Timing: %s\n",
               i + 1, flights[i].flightname, flights[i].pickup, flights[i].destination,
               flights[i].businessclass, flights[i].economy, flights[i].timing);
    }
}

// Search flights by destination
void searchFlights() {
    char destination[30];
    printf("Enter destination to search flights: ");
    scanf("%s", destination);

    printf("Flights to %s:\n", destination);
    int found = 0;
    for (int i = 0; i < flightCount; i++) {
        if (strcmp(flights[i].destination, destination) == 0) {
            printf("Flight %d: %s | Timing: %s\n", i + 1, flights[i].flightname, flights[i].timing);
            found = 1;
        }
    }

    if (!found) printf("No flights found for the destination.\n");
}

// Book a flight
// Book a flight
void bookFlight() {
    displayFlights();
    int choice;
    printf("Enter the number of the flight to book: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > flightCount) {
        printf("Invalid flight number.\n");
        return;
    }

    struct Flight *flight = &flights[choice - 1];
    if (flight->availableseats == 0) {
        printf("No seats available on this flight.\n");
        return;
    }

    int numTickets;
    printf("Enter the number of tickets you want to book: ");
    scanf("%d", &numTickets);

    // Ensure enough seats are available for the requested number of tickets
    if (numTickets > flight->availableseats) {
        printf("Not enough seats available. Only %d seats remaining.\n", flight->availableseats);
        return;
    }

    if (passengerCount + numTickets > passengerCapacity) resizePassengers();

    for (int i = 0; i < numTickets; i++) {
        struct Passenger newPassenger;
        printf("Enter Passenger %d Name: ", i + 1);
        scanf("%s", newPassenger.name);

        // Show seat type options
        int seatChoice;
        printf("Select Seat Type:\n");
        printf("1. Business\n");
        printf("2. Economy\n");
        printf("Enter your choice: ");
        scanf("%d", &seatChoice);

        if (seatChoice == 1 && flight->businessclass > 0) {
            flight->businessclass--;
            strcpy(newPassenger.passengerseat, "Business");
        } else if (seatChoice == 2 && flight->economy > 0) {
            flight->economy--;
            strcpy(newPassenger.passengerseat, "Economy");
        } else {
            printf("No available seats in the selected class.\n");
            i--; // Let the user re-enter this passenger's details
            continue;
        }

        flight->availableseats--;
        strcpy(newPassenger.flightname, flight->flightname);
        generateBookingRef(newPassenger.bookingRef);
        passengers[passengerCount++] = newPassenger;

        printf("Booking successful for %s! Booking Reference: %s\n", newPassenger.name, newPassenger.bookingRef);

        // Generate and print the booking receipt for this passenger
        generateReceipt(&newPassenger, flight);
    }
}

// View booking details
void viewBookingDetails() {
    if (passengerCount == 0) {
        printf("No bookings found.\n");
        return;
    }

    for (int i = 0; i < passengerCount; i++) {
        printf("Booking %d: %s | Flight: %s | Seat: %s | Ref: %s\n",
               i + 1, passengers[i].name, passengers[i].flightname, passengers[i].passengerseat, passengers[i].bookingRef);
    }
}

// Cancel a booking
void cancelBooking() {
    char ref[15];
    printf("Enter booking reference to cancel: ");
    scanf("%s", ref);

    for (int i = 0; i < passengerCount; i++) {
        if (strcmp(passengers[i].bookingRef, ref) == 0) {
            struct Passenger *p = &passengers[i];
            for (int j = 0; j < flightCount; j++) {
                if (strcmp(flights[j].flightname, p->flightname) == 0) {
                    if (strcmp(p->passengerseat, "Business") == 0) {
                        flights[j].businessclass++;
                    } else if (strcmp(p->passengerseat, "Economy") == 0) {
                        flights[j].economy++;
                    }
                    flights[j].availableseats++;
                }
            }

            for (int k = i; k < passengerCount - 1; k++) {
                passengers[k] = passengers[k + 1];
            }
            passengerCount--;
            printf("Booking successfully cancelled.\n");
            return;
        }
    }

    printf("No booking found with the provided reference.\n");
}

// Utility Functions

// Resize flights array
void resizeFlights() {
    flightCapacity *= 2;
    flights = (struct Flight*)realloc(flights, flightCapacity * sizeof(struct Flight)); // Explicit cast
    if (flights == NULL) { // Check for memory allocation failure
        printf("Memory allocation failed while resizing flights array.\n");
        exit(1); // Exit the program if realloc fails
    }
}


// Resize passengers array
void resizePassengers() {
    passengerCapacity *= 2;
    passengers = (struct Passenger*)realloc(passengers, passengerCapacity * sizeof(struct Passenger)); // Explicit cast
    if (passengers == NULL) { // Check for memory allocation failure
        printf("Memory allocation failed while resizing passengers array.\n");
        exit(1); // Exit the program if realloc fails
    }
}

// Validate time format (HH:MM)
int validateTimeFormat(const char *time) {
    if (strlen(time) != 5 || time[2] != ':') return 0;
    int hour = (time[0] - '0') * 10 + (time[1] - '0');
    int minute = (time[3] - '0') * 10 + (time[4] - '0');
    return hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59;
}

// Verify user with a passcode
int verifyUser() {
    char code[10];
    printf("Enter verification code: ");
    scanf("%s", code);
    if (strcmp(code, VERIFICATION_CODE) == 0) return 1;

    printf("Invalid code.\n");
    return 0;
}

// Generate booking reference
void generateBookingRef(char *ref) {
    srand(time(NULL));
    sprintf(ref, "%d%d%d", rand() % 1000, rand() % 1000, rand() % 1000);
}

// Save data to file
void saveDataToFile() {
    FILE *flightFile = fopen("flights.dat", "wb");
    fwrite(&flightCount, sizeof(int), 1, flightFile);
    fwrite(flights, sizeof(struct Flight), flightCount, flightFile);
    fclose(flightFile);

    FILE *passengerFile = fopen("passengers.dat", "wb");
    fwrite(&passengerCount, sizeof(int), 1, passengerFile);
    fwrite(passengers, sizeof(struct Passenger), passengerCount, passengerFile);
    fclose(passengerFile);
}

// Load data from file
// Load flight data from file
void loadDataFromFile() {
    FILE *flightFile = fopen("flights.dat", "rb");
    
    // Check if the file exists
    if (!flightFile) {
        // If the file does not exist, create it (for first-time use)
        printf("Flight data file not found. Creating a new file...\n");
        flightFile = fopen("flights.dat", "wb");  // Create file in write mode
        if (!flightFile) {
            perror("Error creating flight file");
            exit(1);  // Exit if the file can't be created
        }
        fclose(flightFile);
        return;  // No data to load, return from the function
    }

    // If the file exists, proceed to read data
    fread(&flightCount, sizeof(int), 1, flightFile);

    // Resize the flights array to hold all flights
    

    // Read the flight data
    fread(flights, sizeof(struct Flight), flightCount, flightFile);
    fclose(flightFile);

    printf("Successfully loaded %d flights.\n", flightCount);
}

// Load passenger data from file
void loadPassengerDataFromFile() {
    FILE *passengerFile = fopen("passengers.dat", "rb");
    
    // Check if the file exists
    if (!passengerFile) {
        // If the file does not exist, create it (for first-time use)
        printf("Passenger data file not found. Creating a new file...\n");
        passengerFile = fopen("passengers.dat", "wb");  // Create file in write mode
        if (!passengerFile) {
            perror("Error creating passengers file");
            exit(1);  // Exit if the file can't be created
        }
        fclose(passengerFile);
        return;  // No data to load, return from the function
    }

    // If the file exists, proceed to read data
    fread(&passengerCount, sizeof(int), 1, passengerFile);

    // Resize the passengers array to hold all passengers
    passengers = (struct Passenger*)realloc(passengers, passengerCount * sizeof(struct Passenger));
    if (passengers == NULL) {
        perror("Memory allocation failed while loading passenger data");
        fclose(passengerFile);
        exit(1);  // Exit if memory allocation fails
    }

    // Read the passenger data
    fread(passengers, sizeof(struct Passenger), passengerCount, passengerFile);
    fclose(passengerFile);

    printf("Successfully loaded %d passengers.\n", passengerCount);
}


