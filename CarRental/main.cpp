#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>  // For remove_if
using namespace std;

struct Car {
    string id;
    string name;
    string carNumber;
    string model;
    string rentPrice;
};

struct Rent {
    string id;
    string renterName;
    string renterPhone;
    string renterAddress;
    string carNumber;
    string rentStartDate;
    string rentEndDate;
};

// ========== Helper Functions for CSV IO ==========

vector<Car> getCarRecords() {
    vector<Car> cars;
    ifstream file("cars.csv");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        Car car;
        getline(ss, car.id, ',');
        getline(ss, car.name, ',');
        getline(ss, car.carNumber, ',');
        getline(ss, car.model, ',');
        getline(ss, car.rentPrice, ',');
        if (!car.id.empty())
            cars.push_back(car);
    }

    file.close();
    return cars;
}

void setCarRecords(const vector<Car>& cars) {
    ofstream outFile("cars.csv");
    for (const auto& car : cars) {
        outFile << car.id << "," << car.name << "," << car.carNumber << "," << car.model << "," << car.rentPrice << "\n";
    }
    outFile.close();
}

vector<Rent> getRentRecords() {
    vector<Rent> rents;
    ifstream file("rents.csv");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        Rent rent;
        getline(ss, rent.id, ',');
        getline(ss, rent.renterName, ',');
        getline(ss, rent.renterPhone, ',');
        getline(ss, rent.renterAddress, ',');
        getline(ss, rent.carNumber, ',');
        getline(ss, rent.rentStartDate, ',');
        getline(ss, rent.rentEndDate, ',');
        if (!rent.id.empty())
            rents.push_back(rent);
    }

    file.close();
    return rents;
}

void setRentRecords(const vector<Rent>& rents) {
    ofstream outFile("rents.csv");
    for (const auto& rent : rents) {
        outFile << rent.id << "," << rent.renterName << "," << rent.renterPhone << "," << rent.renterAddress << "," << rent.carNumber << "," << rent.rentStartDate << "," << rent.rentEndDate << "\n";
    }
    outFile.close();
}

// ========== CRUD Operations for Cars ==========

void addCar() {
    vector<Car> cars = getCarRecords();
    Car newCar;

    cout << "Enter Car ID: ";
    getline(cin, newCar.id);
    cout << "Enter Car Name: ";
    getline(cin, newCar.name);
    cout << "Enter Car Number (Plate): ";
    getline(cin, newCar.carNumber);
    cout << "Enter Car Model: ";
    getline(cin, newCar.model);
    cout << "Enter Rent Price per day: ";
    getline(cin, newCar.rentPrice);

    // Check if Car ID or Car Number already exists
    for (const auto& c : cars) {
        if (c.id == newCar.id) {
            cout << "Car with this ID already exists!\n";
            return;
        }
        if (c.carNumber == newCar.carNumber) {
            cout << "Car with this number already exists!\n";
            return;
        }
    }

    cars.push_back(newCar);
    setCarRecords(cars);
    cout << "Car added successfully.\n";
}

void showCars() {
    vector<Car> cars = getCarRecords();
    if (cars.empty()) {
        cout << "No cars found.\n";
        return;
    }
    cout << "---- Car List ----\n";
    for (const auto& car : cars) {
        cout << "ID: " << car.id << ", Name: " << car.name << ", Number: " << car.carNumber
             << ", Model: " << car.model << ", Rent Price: " << car.rentPrice << "\n";
    }
}

void updateCar() {
    vector<Car> cars = getCarRecords();
    string id;
    cout << "Enter Car ID to update: ";
    getline(cin, id);

    bool found = false;
    for (auto& car : cars) {
        if (car.id == id) {
            found = true;
            cout << "Enter new Car Name (old: " << car.name << "): ";
            getline(cin, car.name);
            cout << "Enter new Car Number (old: " << car.carNumber << "): ";
            getline(cin, car.carNumber);
            cout << "Enter new Car Model (old: " << car.model << "): ";
            getline(cin, car.model);
            cout << "Enter new Rent Price (old: " << car.rentPrice << "): ";
            getline(cin, car.rentPrice);
            break;
        }
    }
    if (!found) {
        cout << "Car ID not found.\n";
        return;
    }

    setCarRecords(cars);
    cout << "Car updated successfully.\n";
}

void removeCar() {
    vector<Car> cars = getCarRecords();
    string id;
    cout << "Enter Car ID to remove: ";
    getline(cin, id);

    auto it = remove_if(cars.begin(), cars.end(), [&](const Car& c) { return c.id == id; });
    if (it == cars.end()) {
        cout << "Car ID not found.\n";
        return;
    }
    cars.erase(it, cars.end());
    setCarRecords(cars);
    cout << "Car removed successfully.\n";
}

// ========== CRUD Operations for Rents ==========

void addRent() {
    vector<Rent> rents = getRentRecords();
    vector<Car> cars = getCarRecords();

    Rent newRent;

    cout << "Enter Rent ID: ";
    getline(cin, newRent.id);

    // Check if Rent ID exists
    for (const auto& r : rents) {
        if (r.id == newRent.id) {
            cout << "Rent with this ID already exists!\n";
            return;
        }
    }

    cout << "Enter Renter Name: ";
    getline(cin, newRent.renterName);
    cout << "Enter Renter Phone: ";
    getline(cin, newRent.renterPhone);
    cout << "Enter Renter Address: ";
    getline(cin, newRent.renterAddress);
    cout << "Enter Car Number (Plate) to rent: ";
    getline(cin, newRent.carNumber);

    // Check if Car Number exists
    bool carExists = false;
    for (const auto& car : cars) {
        if (car.carNumber == newRent.carNumber) {
            carExists = true;
            break;
        }
    }
    if (!carExists) {
        cout << "Car Number not found.\n";
        return;
    }

    cout << "Enter Rent Start Date (YYYY-MM-DD): ";
    getline(cin, newRent.rentStartDate);
    cout << "Enter Rent End Date (YYYY-MM-DD): ";
    getline(cin, newRent.rentEndDate);

    rents.push_back(newRent);
    setRentRecords(rents);
    cout << "Rent record added successfully.\n";
}

void showRents() {
    vector<Rent> rents = getRentRecords();
    if (rents.empty()) {
        cout << "No rent records found.\n";
        return;
    }
    cout << "---- Rent List ----\n";
    for (const auto& rent : rents) {
        cout << "ID: " << rent.id << ", Renter: " << rent.renterName << ", Phone: " << rent.renterPhone
             << ", Address: " << rent.renterAddress << ", Car Number: " << rent.carNumber
             << ", Start: " << rent.rentStartDate << ", End: " << rent.rentEndDate << "\n";
    }
}

void updateRent() {
    vector<Rent> rents = getRentRecords();
    string id;
    cout << "Enter Rent ID to update: ";
    getline(cin, id);

    bool found = false;
    for (auto& rent : rents) {
        if (rent.id == id) {
            found = true;
            cout << "Enter new Renter Name (old: " << rent.renterName << "): ";
            getline(cin, rent.renterName);
            cout << "Enter new Renter Phone (old: " << rent.renterPhone << "): ";
            getline(cin, rent.renterPhone);
            cout << "Enter new Renter Address (old: " << rent.renterAddress << "): ";
            getline(cin, rent.renterAddress);
            cout << "Enter new Car Number (old: " << rent.carNumber << "): ";
            getline(cin, rent.carNumber);
            cout << "Enter new Rent Start Date (old: " << rent.rentStartDate << "): ";
            getline(cin, rent.rentStartDate);
            cout << "Enter new Rent End Date (old: " << rent.rentEndDate << "): ";
            getline(cin, rent.rentEndDate);
            break;
        }
    }
    if (!found) {
        cout << "Rent ID not found.\n";
        return;
    }

    setRentRecords(rents);
    cout << "Rent record updated successfully.\n";
}

void removeRent() {
    vector<Rent> rents = getRentRecords();
    string id;
    cout << "Enter Rent ID to remove: ";
    getline(cin, id);

    auto it = remove_if(rents.begin(), rents.end(), [&](const Rent& r) { return r.id == id; });
    if (it == rents.end()) {
        cout << "Rent ID not found.\n";
        return;
    }
    rents.erase(it, rents.end());
    setRentRecords(rents);
    cout << "Rent record removed successfully.\n";
}

// ========== Menu ==========

void carMenu() {
    while (true) {
        cout << "\n--- Car Management Menu ---\n";
        cout << "1. Add Car\n";
        cout << "2. Show All Cars\n";
        cout << "3. Update Car\n";
        cout << "4. Remove Car\n";
        cout << "5. Back to Main Menu\n";
        cout << "Choose an option: ";

        string choice;
        getline(cin, choice);

        if (choice == "1") addCar();
        else if (choice == "2") showCars();
        else if (choice == "3") updateCar();
        else if (choice == "4") removeCar();
        else if (choice == "5") break;
        else cout << "Invalid option. Try again.\n";
    }
}

void rentMenu() {
    while (true) {
        cout << "\n--- Rent Management Menu ---\n";
        cout << "1. Add Rent\n";
        cout << "2. Show All Rents\n";
        cout << "3. Update Rent\n";
        cout << "4. Remove Rent\n";
        cout << "5. Back to Main Menu\n";
        cout << "Choose an option: ";

        string choice;
        getline(cin, choice);

        if (choice == "1") addRent();
        else if (choice == "2") showRents();
        else if (choice == "3") updateRent();
        else if (choice == "4") removeRent();
        else if (choice == "5") break;
        else cout << "Invalid option. Try again.\n";
    }
}

int main() {
    while (true) {
        cout << "\n=== Car Rental Management System ===\n";
        cout << "1. Manage Cars\n";
        cout << "2. Manage Rents\n";
        cout << "3. Exit\n";
        cout << "Select option: ";

        string choice;
        getline(cin, choice);

        if (choice == "1") carMenu();
        else if (choice == "2") rentMenu();
        else if (choice == "3") {
            cout << "Exiting system. Goodbye!\n";
            break;
        }
        else cout << "Invalid choice, please try again.\n";
    }

    return 0;
}
