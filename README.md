Project Title: Rental Vehicle Management System
Objective: To design and implement a console-based application
for managing vehicle rentals.
1. Concepts Used:
• Classes and Objects: Utilized for modeling vehicles, users,
bookings, and the rental system.
• Inheritance: Base class Vehicle inherited by Car and Bike.
• Polymorphism: Virtual functions (display and
calculateRentalCost) are overridden in derived classes.
• Encapsulation: Data members of classes are kept private,
with public member functions providing controlled access.
• Dynamic Memory Allocation: Utilized for storing vehicle
pointers and booking history.
2. Classes:
• Vehicle: Base class with common attributes and virtual
functions.
• Car: Derived from Vehicle, with additional attributes and
overridden functions.
• Bike: Derived from Vehicle, with unique attributes and
overridden functions.
• User: Represents a user with name and age.
• Booking: Represents a booking with associated details.
• RentalSystem: Manages operations related to vehicles and
bookings.
3. Core Functionalities:
• Vehicle Management:
• Add vehicles.
• Display available and all vehicles.
• Book, release, and delete vehicles.
• User Management:
• Add users (implicitly handled during booking).
• Booking System:
• Create bookings with associated users and vehicles.
• Display booking history.
4. User Interfaces:
• Menus: Console-based menus for admin and user
interactions.
• Welcome Message: A stylized welcome message upon
system startup.
• Clear Screen: Option to clear the console for better
readability.
5. Additional Features:
• Error Handling: Basic input validation, ensuring correct data
types are used.
• Memory Management: Proper deallocation of dynamically
allocated memory to prevent memory leaks.
6. Potential Enhancements:
• Data Structures: Consideration for efficient data structures
like maps or hash tables for faster data retrieval as the number
of vehicles grows.
• Extended Features: Options for discounts, vehicle reviews, or
user ratings.
7. Conclusion:
In conclusion, the Rental Vehicle Management System
demonstrates a solid understanding of key C++ concepts, including
classes, inheritance, polymorphism, encapsulation, and dynamic
memory allocation. The project achieves the goal of providing a
functional and user-friendly console-based application for managing
vehicle rentals.
