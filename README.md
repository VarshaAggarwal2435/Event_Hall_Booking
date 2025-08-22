# Event_Hall_Booking

## Overview

This is a C++ console-based application for managing event hall bookings, built with Object-Oriented Programming (OOP) principles. The system supports user registration and login, admin login, hall management with CRUD operations, booking functionality with price display and time slot allocation, and availability checks.

The project demonstrates OOP concepts like classes, inheritance, polymorphism, encapsulation, and abstraction.

## Features

- **User Authentication**:
  - Register users with username, password, and basic details.
  - User login to access booking features.
  - Admin login with predefined credentials for management tasks.

- **Hall Management (Admin Only)**:
  - **CRUD Operations**: Create, Read, Update, Delete halls.
  - Add halls with details like name, capacity, price per hour, and amenities.
  - View, update, or delete halls.

- **Booking System (Users)**:
  - View available halls with prices and details.
  - Check availability for specific dates and time slots.
  - Book a hall for a specified period (date and hours).
  - Automatic allotment if available; suggests alternatives if not.
  - Simulated payment confirmation.

- **Additional Features**:
  - User booking history.
  - Admin dashboard to view all bookings, cancel bookings, or generate reports (e.g., total revenue).
  - Input validation (e.g., date formats, time overlaps).
  - Error handling for file operations and invalid credentials.
  - Logout functionality for users and admins.

## Technologies Used

- **C++**: Standard Library (`<iostream>`, `<fstream>`, `<vector>`, `<string>`, etc.).
- **OOP Principles**: Classes, inheritance, polymorphism, encapsulation, abstraction.

## Usage

### Main Menu
- Options: **User Login**, **User Register**, **Admin Login**

### User Flow
1. Register or login  
2. View halls and prices  
3. Select a hall, check availability, and book for a date/time  
4. Confirm booking (simulated payment)  
5. View booking history  
6. Logout  

### Admin Flow
1. Login with admin credentials (default: username: `admin`, password: `admin123`)
2. Manage halls: **Add, View, Update, Delete**  
3. View all bookings, cancel bookings, or generate reports  
4. Logout  
