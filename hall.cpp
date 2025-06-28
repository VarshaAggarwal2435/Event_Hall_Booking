#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Base class for Hall
class Hall
{
protected:
    string hallType;
    string hallNumber;
    bool isAvailable;
    double ratePerDay;

public:
    Hall(string hallType, string hallNumber, double ratePerDay)
        : hallType(hallType), hallNumber(hallNumber), ratePerDay(ratePerDay), isAvailable(true) {}

    virtual void display()
    {
        cout << "Hall Type: " << hallType << ", Hall Number : " << hallNumber << ", Rate per day: $" << ratePerDay << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }

    bool isHallAvailable()
    {
        return isAvailable;
    }

    void setAvailability(bool status)
    {
        isAvailable = status;
    }

    double getRate()
    {
        return ratePerDay;
    }

    void updateDetails(string newhallType, string newhallNumber, double newRatePerDay)
    {
        hallType = newhallType;
        hallNumber = newhallNumber;
        ratePerDay = newRatePerDay;
    }

    virtual ~Hall() {}
};

// Derived classes for different Hall types
class Wedding : public Hall
{
public:
    Wedding(string hallType, string hallNumber, double ratePerDay)
        : Hall(hallType, hallNumber, ratePerDay) {}

    void display() override
    {
        cout << "[Wedding] ";
        Hall::display();
    }
};

class Meeting : public Hall
{
public:
    Meeting(string hallType, string hallNumber, double ratePerDay)
        : Hall(hallType, hallNumber, ratePerDay) {}

    void display() override
    {
        cout << "[Meeting] ";
        Hall::display();
    }
};

class Banquet : public Hall
{
public:
    Banquet(string hallType, string hallNumber, double ratePerDay)
        : Hall(hallType, hallNumber, ratePerDay) {}

    void display() override
    {
        cout << "[Banquet] ";
        Hall::display();
    }
};

// Base class for User
class User
{
protected:
    string name;
    string email;
    string contact;
    string password;
    vector<Hall *> bookedHalls; // Store booked Halls

public:
    User() : name(""), email(""), contact(""), password("") {}
    User(string name, string email, string contact, string password)
        : name(name), email(email), contact(contact), password(password) {}

    virtual void displayUserInfo()
    {
        cout << "Name: " << name << ", Email: " << email << ", Contact: " << contact << ", Password" << password << endl;
    }

    string getName() const
    {
        return name;
    }
    string getPassword() const
    {
        return password;
    }
    string getEmail() const
    {
        return email;
    }

    void bookHall(Hall *hall)
    {
        bookedHalls.push_back(hall);
    }

    void returnHall(Hall *hall)
    {
        auto it = find(bookedHalls.begin(), bookedHalls.end(), hall);
        if (it != bookedHalls.end())
        {
            bookedHalls.erase(it);
        }
        else
        {
            cout << "This Hall was not booked by you!" << endl;
        }
    }

    bool hasBookedHall(Hall *hall)
    {
        return find(bookedHalls.begin(), bookedHalls.end(), hall) != bookedHalls.end();
    }

    void displayBookedHalls()
    {
        cout << "\n--- Booked Halls ---" << endl;
        if (bookedHalls.size() == 0)
        {
            cout << "NO halls booked" << endl;
            return;
        }
        for (size_t i = 0; i < bookedHalls.size(); i++)
        {
            cout << "Index: " << i << " ";
            bookedHalls[i]->display();
        }
    }

    virtual ~User() {}
};

// Manager class inherits from User
class Manager : public User
{
private:
    vector<Hall *> halls; // Inventory of Halls

public:
    Manager(string name, string email, string contact, string password)
        : User(name, email, contact, password) {}

    // Manager Authentication
    bool authenticate(string inputEmail, string inputPassword)
    {
        return (inputEmail == email && inputPassword == this->password);
    }

    // Add Hall to inventory
    void addHall(Hall *hall)
    {
        halls.push_back(hall);
        cout << "Hall added successfully!" << endl;
    }

    // Delete Hall from inventory
    void deleteHall(int index)
    {
        if (index >= 0 && index < halls.size())
        {
            delete halls[index]; // Free memory
            halls.erase(halls.begin() + index);
            cout << "Hall deleted successfully!" << endl;
        }
        else
        {
            cout << "Invalid Hall index!" << endl;
        }
    }

    // Update Hall details
    void updateHallDetails(int index, string newhallType, string newhallNumber, double newRatePerDay)
    {
        if (index >= 0 && index < halls.size())
        {
            halls[index]->updateDetails(newhallType, newhallNumber, newRatePerDay);
            cout << "Hall details updated successfully!" << endl;
        }
        else
        {
            cout << "Invalid Hall index!" << endl;
        }
    }

    // Display all Halls in the inventory
    bool displayInventory()
    {
        cout << "\n--- Hall Inventory ---" << endl;
        if (halls.size() == 0)
        {
            cout << "No Halls added yet" << endl;
            return false;
        }
        for (size_t i = 0; i < halls.size(); i++)
        {
            cout << "Index: " << i << " ";
            halls[i]->display();
        }
        return true;
    }

    Hall *getHall(int index)
    {
        return halls[index];
    }

    int getInventorySize()
    {
        return halls.size();
    }
};

// Booking class for managing bookings
class Booking
{
private:
    Manager &manager;

public:
    Booking(Manager &manager) : manager(manager) {}

    void displayInventory()
    {
        manager.displayInventory();
    }
    void bookHall(int HallIndex, int days, User &user)
    {
        if (HallIndex >= 0 && HallIndex < manager.getInventorySize())
        {
            Hall *hall = manager.getHall(HallIndex);
            if (hall->isHallAvailable())
            {
                double cost = hall->getRate() * days;
                cout << "Booking confirmed for " << user.getName() << " for " << days << " days. Total cost: $" << cost << endl;
                hall->setAvailability(false);
                user.bookHall(hall);
            }
            else
            {
                cout << "Sorry, this Hall is not available!" << endl;
            }
        }
        else
        {
            cout << "Invalid Hall index!" << endl;
        }
    }

    void returnHall(int hallIndex, User &user)
    {
        if (hallIndex >= 0 && hallIndex < manager.getInventorySize())
        {
            Hall *hall = manager.getHall(hallIndex);
            if (user.hasBookedHall(hall))
            {
                hall->setAvailability(true);
                user.returnHall(hall);
                cout << "Hall returned successfully!" << endl;
            }
            else
            {
                cout << "This Hall was not booked by you!" << endl;
            }
        }
        else
        {
            cout << "Invalid Hall index!" << endl;
        }
    }
};

// Function to show Manager menu
void managerMenu(Manager &manager)
{
    while (true)
    {
        cout << "\n--- Manager Menu ---" << endl;
        cout << "1. Add Hall" << endl;
        cout << "2. Delete Hall" << endl;
        cout << "3. Update Hall Details" << endl;
        cout << "4. Display Inventory" << endl;
        cout << "5. Return to Main Menu" << endl;
        cout << "Choose an option: ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter Hall type (Wedding/Meeting/Banquet): ";
            string type;
            cin >> type;
            cout << "Enter hallType: ";
            string hallType;
            cin >> hallType;
            cout << "Enter hall number: ";
            string hallNumber;
            cin >> hallNumber;
            cout << "Enter rate per day: ";
            double ratePerDay;
            cin >> ratePerDay;

            if (type == "Wedding")
            {
                manager.addHall(new Wedding(hallType, hallNumber, ratePerDay));
            }
            else if (type == "Meeting")
            {
                manager.addHall(new Meeting(hallType, hallNumber, ratePerDay));
            }
            else if (type == "Banquet")
            {
                manager.addHall(new Banquet(hallType, hallNumber, ratePerDay));
            }
            else
            {
                cout << "Invalid Hall type!" << endl;
            }
        }
        else if (choice == 2)
        {
            if (manager.displayInventory() == true)
            {
                manager.displayInventory();
                cout << "Enter Hall index to delete: ";
                int index;
                cin >> index;
                manager.deleteHall(index);
            }
        }
        else if (choice == 3)
        {
            if (manager.displayInventory() == true)
            {
                manager.displayInventory();
                cout << "Enter Hall index to update: ";
                int index;
                cin >> index;

                cout << "Enter new hallType: ";
                string newhallType;
                cin >> newhallType;
                cout << "Enter new hall number: ";
                string newhallNumber;
                cin >> newhallNumber;
                cout << "Enter new rate per day: ";
                double newRatePerDay;
                cin >> newRatePerDay;

                manager.updateHallDetails(index, newhallType, newhallNumber, newRatePerDay);
            }
        }
        else if (choice == 4)
        {
            manager.displayInventory();
        }
        else if (choice == 5)
        {
            break;
        }
        else
        {
            cout << "Invalid option! Please try again." << endl;
        }
    }
}

// Function to show user menu
void userMenu(Booking &booking, User &user)
{
    while (true)
    {
        cout << "\n--- User Menu ---" << endl;
        cout << "1. Book Hall" << endl;
        cout << "2. Return Hall" << endl;
        cout << "3. Display Booked Halls" << endl;
        cout << "4. Return to Main Menu" << endl;
        cout << "Choose an option: ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            booking.displayInventory(); // Show inventory before booking
            cout << "Enter Hall index to book: ";
            int index, days;
            cin >> index;
            cout << "Enter number of days to book: ";
            cin >> days;

            booking.bookHall(index, days, user);
        }
        else if (choice == 2)
        {
            user.displayBookedHalls();
            cout << "Enter Hall index to return: ";
            int index;
            cin >> index;

            booking.returnHall(index, user);
        }
        else if (choice == 3)
        {
            user.displayBookedHalls();
        }
        else if (choice == 4)
        {
            break;
        }
        else
        {
            cout << "Invalid option! Please try again." << endl;
        }
    }
}

// Main function for testing
int main()
{
    // Create Manager
    Manager manager("John Doe", "john@gmail.com", "9089972067", "1234");

    // Create booking system
    Booking booking(manager);

    unordered_map<string, User> registeredUsers;

    while (true)
    {
        cout << "Login as  (1)Manager or  (2)User: ";
        int loginChoice;
        cin >> loginChoice;

        if (loginChoice == 1)
        {
            // Manager Authentication
            cout << "Manager Login\nEnter Email: ";
            string email;
            cin >> email;
            cout << "Enter Password: ";
            string password;
            cin >> password;

            // Authenticate Manager
            if (!manager.authenticate(email, password))
            {
                cout << "Invalid Manager credentials!" << endl;
                continue;
            }

            cout << "Manager authenticated successfully!" << endl;

            // Manager menu
            managerMenu(manager);
        }
        else if (loginChoice == 2)
        {
            cout << "Are you a registered user? (yes/no): ";
            string isRegistered;
            cin >> isRegistered;

            if (isRegistered == "yes")
            {
                cout << "Enter Email: ";
                string userEmail;
                cin >> userEmail;
                cout << "Enter Password: ";
                string password;
                cin >> password;

                if (registeredUsers.find(userEmail) != registeredUsers.end())
                {
                    if (registeredUsers[userEmail].getPassword() != password)
                    {
                        cout << "User not found or incorrect credentials!" << endl;
                        return 0;
                    }
                    User &user = registeredUsers[userEmail];
                    cout << "User logged in successfully!" << endl;
                    userMenu(booking, user);
                }
                else
                {
                    cout << "User not found or incorrect credentials!" << endl;
                }
            }
            else
            {
                // User registration
                cout << "\nUser Registration\nEnter Name: ";
                string name;
                cin >> name;
                cout << "Enter Email: ";
                string userEmail;
                cin >> userEmail;
                cout << "Enter Contact No: ";
                string contact;
                cin >> contact;
                cout << "Enter Password:";
                string password;
                cin >> password;
                User user(name, userEmail, contact, password);
                registeredUsers[userEmail] = user;

                cout << "User registered successfully!" << endl;
                userMenu(booking, user);
            }
        }
        else
        {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}