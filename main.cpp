#include <iostream>
#include <algorithm> 
#include <string>


void displayAdminMenu();
void displayUserMenu();

using namespace std;
//the base class Vehicle
class Vehicle
{
protected:
    string vehicleID;
    string brand;
    string model;
    bool isBooked;

public:
    // Constructor to initialize common attributes of all vehicles
    Vehicle(const string &id, const string &b, const string &m)
        : vehicleID(id), brand(b), model(m), isBooked(false) {}

    // Pure virtual function for displaying vehicle information
    virtual void display() const = 0;

    // Pure virtual function for calculating rental cost
    virtual double calculateRentalCost() const = 0;

    // Getter function to retrieve the vehicle ID
    const string &getVehicleID() const
    {
        return vehicleID;
    }

    // Getter function to check if the vehicle is booked
    bool getIsBooked() const
    {
        return isBooked;
    }

    // Function to mark the vehicle as booked
    void book()
    {
        isBooked = true;
    }

    // Function to release the booked vehicle
    void release()
    {
        isBooked = false;
    }
};

// Derived class for Car, inheriting from the base class Vehicle
class Car : public Vehicle
{
    int numSeats;

public:
    // Constructor to initialize Car-specific attributes
    Car(const string &id, const string &b, const string &m, int seats)
        : Vehicle(id, b, m), numSeats(seats) {}

    // Implementation of the virtual display function for Car
    void display() const override
    {
        cout << "Car ID: " << vehicleID << ", Brand: " << brand
             << ", Model: " << model << ", Seats: " << numSeats << endl;
    }

    // Implementation of the virtual calculateRentalCost function for Car
    double calculateRentalCost() const override
    {
        // Add logic for calculating rental cost for a car
        return 50.0; 
    }
       // Copy constructor to create a new Car by copying an existing Car
    Car(const Car &other)
        : Vehicle(other.vehicleID, other.brand, other.model), numSeats(other.numSeats) {}

    // Overloaded assignment operator to assign the values of one Car to another
    Car &operator=(const Car &other)
    {
        // Check for self-assignment
        if (this != &other)
        {
            // Copy values from the other Car to this Car
            vehicleID = other.vehicleID;
            brand = other.brand;
            model = other.model;
            numSeats = other.numSeats;
        }
        return *this;
    }
   
    
};

// Derived class for Bike, inheriting from the base class Vehicle
class Bike : public Vehicle
{
    string bikeType;

public:
    // Constructor to initialize Bike-specific attributes
    Bike(const string &id, const string &b, const string &m, const string &type)
        : Vehicle(id, b, m), bikeType(type) {}

    // Implementation of the virtual display function for Bike
    void display() const override
    {
        cout << "Bike ID: " << vehicleID << ", Brand: " << brand
             << ", Model: " << model << ", Type: " << bikeType << endl;
    }

    // Implementation of the virtual calculateRentalCost function for Bike
    double calculateRentalCost() const override
    {
        // Add logic for calculating rental cost for a bike
        return 20.0; // Dummy value
    }
};

// Class representing user information
class User
{
    string name;
    int age;

public:
    User(const string &n, int a) : name(n), age(a) {}

    const string &getName() const
    {
        return name;
    }

    int getAge() const
    {
        return age;
    }
};

// Class representing a booking
class Booking
{
    const Vehicle *vehicle;
    const User *user;
    int duration; // in hours
    double charges;

public:
    Booking(const Vehicle *v, const User *u, int d, double c)
        : vehicle(v), user(u), duration(d), charges(c) {}
    Booking (){};    

    void display() const
    {
        cout << "Booking Details:" << endl;
        cout << "Vehicle ID: " << vehicle->getVehicleID() << endl;
        cout << "User Name: " << user->getName() << endl;
        cout << "User Age: " << user->getAge() << endl;
        cout << "Booking Duration: " << duration << " hours" << endl;
        cout << "Total Charges: $" << charges << endl;
        cout << endl;
    }
};

// Class representing the rental system
class RentalSystem
{
    static const int MAX_VEHICLES = 100; // Maximum number of vehicles in the system
    Vehicle *vehicles[MAX_VEHICLES];     // Array to store pointers to vehicles
    int numVehicles;              //  used Current number of vehicles in the system
    Booking *bookingHistory[MAX_VEHICLES];       // Array to store booking history
    int numBookings;                            // Current number of bookings

public:
    // Constructor to initialize the rental system
    RentalSystem() : numVehicles(0), numBookings(0) {};

    // Function to add a vehicle to the system
    void addVehicle(Vehicle *vehicle)
    {
        if (numVehicles < MAX_VEHICLES)
        {
            vehicles[numVehicles++] = vehicle;
            cout << "Vehicle added successfully." << endl;
        }
        else
        {
            cout << "Cannot add more vehicles. Maximum limit reached." << endl;
        }
    }

    // Function to display available vehicles
    void displayAvailableVehicles() 
    {

        cout << "Available Vehicles:" << endl;
        for (int i = 0; i < numVehicles; ++i)
        {
            if (!vehicles[i]->getIsBooked())
            {
                vehicles[i]->display();
            }
        }
        cout << endl;
    }

    // Function to display all vehicles
    void displayAllVehicles() 
    {

        cout << "All Vehicles:" << endl;
        for (int i = 0; i < numVehicles; ++i)
        {
            vehicles[i]->display();
        }
        cout << endl;
    }

    // Function to book a vehicle by its ID
    void bookVehicle(const string &vehicleID, const User &user, int duration)
    {
        for (int i = 0; i < numVehicles; ++i)
        {
            if (vehicles[i]->getVehicleID() == vehicleID && !vehicles[i]->getIsBooked())
            {
                vehicles[i]->book();
                double charges = vehicles[i]->calculateRentalCost() * duration;
                bookingHistory[numBookings++] = new  Booking(vehicles[i], &user, duration, charges);
                cout << "Vehicle with ID " << vehicleID << " booked successfully." << endl;
                cout << "Total Charges: @" << charges << endl;
                return;
            }
        }
        cout << "Vehicle with ID " << vehicleID << " not found or already booked." << endl;
    }

    // Function to release a booked vehicle by its ID
    void releaseVehicle(const string &vehicleID)
    {
        for (int i = 0; i < numVehicles; ++i)
        {
            if (vehicles[i]->getVehicleID() == vehicleID && vehicles[i]->getIsBooked())
            {
                vehicles[i]->release();
                cout << "Vehicle with ID " << vehicleID << " released successfully." << endl;
                return;
            }
        }
        cout << "Vehicle with ID " << vehicleID << " not found or not booked." << endl;
    }

    // Function to delete a vehicle by its ID
    void deleteVehicle(const string &vehicleID)
    {
        for (int i = 0; i < numVehicles; ++i)
        {
            if (vehicles[i]->getVehicleID() == vehicleID)
            {
                // Shift the remaining elements to fill the gap
                for (int j = i; j < numVehicles - 1; ++j)
                {
                    vehicles[j] = vehicles[j + 1];
                }
                --numVehicles;
                cout << "Vehicle with ID " << vehicleID << " deleted successfully." << endl;
                return;
            }
        }
        cout << "Vehicle with ID " << vehicleID << " not found." << endl;
    }

      // Function to display booking history
    void displayBookingHistory() const {
        cout << "Booking History:" << endl;
        for (int i = 0; i < numBookings; ++i) {
            bookingHistory[i]->display();
        }
    }
     
     ~RentalSystem()
    {
        for (int i = 0; i < numVehicles; ++i)
        {
            delete vehicles[i];
        }
        for (int i = 0; i < numBookings; ++i)
        {
            delete bookingHistory[i];
        }
    }

};


// Function to display the admin menu

void displayAdminMenu(RentalSystem &rentalSystem)
{
    int adminChoice;
    do
    {
        displayAdminMenu();
        cin >> adminChoice;

        switch (adminChoice)
        {
        case 3:
            rentalSystem.displayAllVehicles();
            break;
        case 2:
            rentalSystem.displayAvailableVehicles();
            break;
        case 4:
        {
            string vehicleID;
            cout << "Enter the Vehicle ID to release: ";
            cin >> vehicleID;
            rentalSystem.releaseVehicle(vehicleID);
            break;
        }
        case 5:
        {
            string vehicleID;
            cout << "Enter the Vehicle ID to delete: ";
            cin >> vehicleID;
            rentalSystem.deleteVehicle(vehicleID);
            break;
        }
        case 6:
            rentalSystem.displayBookingHistory();
            break;
        case 1:
        {
            // Add a new vehicle
            string vehicleID, brand, model;
            int numSeats;
            cout << "Enter Vehicle ID: ";
            cin >> vehicleID;
            cout << "Enter Brand: ";
            cin >> brand;
            cout << "Enter Model: ";
            cin >> model;
            cout << "Enter Number of Seats: ";
            cin >> numSeats;
            Car *newCar = new Car(vehicleID, brand, model, numSeats);
            rentalSystem.addVehicle(newCar);
            break;
        }
        case 8:
            cout << "Exiting Admin Menu." << endl;
            break;
        case 7:
            system("clear");
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (adminChoice != 8);
}

// Function to display the user menu
void displayUserMenu(RentalSystem &rentalSystem)
{
    int userChoice;
    do
    {
        displayUserMenu();
        cin >> userChoice;

        switch (userChoice)
        {
        case 1:
            rentalSystem.displayAvailableVehicles();
            break;
        case 2:
        {
            string vehicleID;
            cout << "Enter the Vehicle ID to book: ";
            cin >> vehicleID;
            string userName;
            int userAge;
            cout << "Enter your name: ";
            cin >> userName;
            cout << "Enter your age: ";
            cin >> userAge;
            int duration;
            cout << "Enter the booking duration (in hours): ";
            cin >> duration;
            User user(userName, userAge);
            rentalSystem.bookVehicle(vehicleID, user, duration);
            break;
        }
        case 3:
            cout << "Exiting User Menu." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (userChoice != 3);
}

// Function to display  design for the Welcome message
void displayWelcomeMessage()
{
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║        Welcome to Prince Rentals!        ║" << endl;
    cout << "║                                          ║" << endl;
    cout << "║    Discover the Thrill of Your Next Ride ║" << endl;
    cout << "║            with Our Stylish Fleet        ║" << endl;
    cout << "║                                          ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << "        vroom vroom... Choose Your Ride!     " << endl;
    cout << "--------------------------------------------" << endl;
}

// Function to display  design for the main menu
void displayMainMenu()
{
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║              Main Menu                   ║" << endl;
    cout << "║  1. Admin                                ║" << endl;
    cout << "║  2. User                                 ║" << endl;
    cout << "║  3. Exit                                 ║" << endl;
    cout << "║  Enter your choice:                      ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
}

// Function to display  design for the Admin Menu
void displayAdminMenu()
{
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║              Admin Menu                  ║" << endl;
    cout << "║                                          ║" << endl;
    cout << "║  1. Add New Vehicle                      ║" << endl;
    cout << "║  2. Display All Vehicles                 ║" << endl;
    cout << "║  3. Display Available Vehicles           ║" << endl;
    cout << "║  4. Release a Vehicle                    ║" << endl;
    cout << "║  5. Delete a Vehicle                     ║" << endl;
    cout << "║  6. Display Booking History              ║" << endl;
    cout << "║  7. Clear screen                         ║" << endl;
    cout << "║  8. Exit Admin Menu                      ║" << endl;
    cout << "║                                          ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << "Enter your choice: ";
}

// Function to display  design for the User Menu
void displayUserMenu()
{
    cout << "╔══════════════════════════════════════════╗" << endl;
    cout << "║              User Menu                   ║" << endl;
    cout << "║                                          ║" << endl;
    cout << "║  1. Display Available Vehicles           ║" << endl;
    cout << "║  2. Book a Vehicle                       ║" << endl;
    cout << "║  3. Exit User Menu                       ║" << endl;
    cout << "║                                          ║" << endl;
    cout << "╚══════════════════════════════════════════╝" << endl;
    cout << "Enter your choice: ";
}

int main()
{

    RentalSystem rentalSystem;

    Car car1("C001", "Toyota", "Camry", 5);
    Car car2("C002", "Honda", "Accord", 4);
    Bike bike1("B001", "Harley", "Davidson", "Cruiser");
    Bike bike2("B002", "Ducati", "Monster", "Sport");

    rentalSystem.addVehicle(&car1);
    rentalSystem.addVehicle(&car2);
    rentalSystem.addVehicle(&bike1);
    rentalSystem.addVehicle(&bike2);

    system("clear");

    displayWelcomeMessage();

    // Main Menu
    int mainChoice;
    do
    {
        displayMainMenu();

        cin >> mainChoice;

        switch (mainChoice)
        {
        case 1: // Admin
            displayAdminMenu(rentalSystem);
            break;
        case 2: // User
            displayUserMenu(rentalSystem);
            break;
        case 3:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (mainChoice != 3);

    return 0;
}
