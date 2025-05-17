#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <regex>

using namespace std;

// --- Structures ---
struct User {
    string name;
    string email;
    string password;
};

struct Vehicle {
    string ownerEmail;
    string ownerName;
    string carNumber;
    string plateNumber;
};

struct ParkingSlot {
    int id;
    string vehicleType;
    string size;
    string location;
    string type;
    bool isOccupied;
};

struct Request {
    string ownerEmail;
    string carNumber;
    int slotId;
    bool isApproved;
    bool isPaid;
    string startTime;
    string endTime;
    float amount;
};

struct Log {
    string ownerName;
    string carNumber;
    string plateNumber;
    string entryTime;
    string exitTime;
    float amountPaid;
};

// --- Global Data Storage ---
vector<User> users;
vector<Vehicle> vehicles;
vector<ParkingSlot> parkingSlots;
vector<Request> requests;
vector<Log> logs;

// --- Utility ---
string getCurrentTime() {
    time_t now = time(nullptr);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}

// Validate time string format (YYYY-MM-DD HH:MM:SS)
bool isValidTimeFormat(const string& timeStr) {
    regex timeRegex(R"(\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01]) ([01]\d|2[0-3]):[0-5]\d:[0-5]\d)");
    return regex_match(timeStr, timeRegex);
}

// Parse time string to time_t
time_t parseTime(const string& timeStr, bool& success) {
    success = false;
    if (!isValidTimeFormat(timeStr)) {
        return 0;
    }

    tm tm = {};
    stringstream ss(timeStr);
    ss >> get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (ss.fail()) {
        return 0;
    }

    time_t result = mktime(&tm);
    if (result == -1) {
        return 0;
    }

    success = true;
    return result;
}

// Calculate hours between two times (rounded up)
int calculateHours(const string& start, const string& end) {
    bool startSuccess, endSuccess;
    time_t startTime = parseTime(start, startSuccess);
    time_t endTime = parseTime(end, endSuccess);

    if (!startSuccess || !endSuccess) {
        return -1; // Indicate error
    }

    double seconds = difftime(endTime, startTime);
    if (seconds <= 0) {
        return -1; // Indicate invalid duration
    }

    return ceil(seconds / 3600.0); // Round up to nearest hour
}

// --- User Functions ---
bool registerUser() {
    string name, email, password;
    cout << "Enter full name: ";
    getline(cin, name);
    cout << "Enter email: ";
    getline(cin, email);
    cout << "Enter password: ";
    getline(cin, password);

    for (auto& user : users) {
        if (user.email == email) {
            cout << "User already exists with this email.\n";
            return false;
        }
    }

    users.push_back({name, email, password});
    cout << "?? Registration successful!\n";
    return true;
}

string loginUser() {
    string email, password;
    cout << "Enter email: ";
    getline(cin, email);
    cout << "Enter password: ";
    getline(cin, password);

    if (email == "admin@gmail.com" && password == "Admin@123") {
        return "admin";
    }

    for (auto& user : users) {
        if (user.email == email && user.password == password) {
            return email;
        }
    }

    cout << "Invalid credentials.\n";
    return "";
}

// --- Admin Functions ---
void addParkingSlot() {
    int id = (parkingSlots.empty()) ? 1 : parkingSlots.back().id + 1;
    string vehicleType, size, location, type;

    cout << "Enter vehicle type (e.g., car, bike): ";
    getline(cin, vehicleType);
    cout << "Enter slot size (small, medium, large): ";
    getline(cin, size);
    cout << "Enter slot location: ";
    getline(cin, location);
    cout << "Enter slot type (VIP, Regular): ";
    getline(cin, type);

    parkingSlots.push_back({id, vehicleType, size, location, type, false});
    cout << "??? Parking slot added successfully. ID: " << id << "\n";
}

void listParkingSlots() {
    if (parkingSlots.empty()) {
        cout << "No parking slots available.\n";
        return;
    }
    for (const auto& slot : parkingSlots) {
        cout << "Slot ID: " << slot.id
             << ", Vehicle Type: " << slot.vehicleType
             << ", Size: " << slot.size
             << ", Location: " << slot.location
             << ", Type: " << slot.type
             << ", Status: " << (slot.isOccupied ? "Occupied" : "Free") << endl;
    }
}

void showRequests() {
    bool anyPending = false;
    cout << "\n--- Pending Slot Requests ---\n";
    for (size_t i = 0; i < requests.size(); ++i) {
        const auto& req = requests[i];
        if (!req.isApproved) {
            anyPending = true;
            cout << i+1 << ". Request by: " << req.ownerEmail
                 << ", Car: " << req.carNumber
                 << ", Slot ID: " << req.slotId << endl;
        }
    }
    if (!anyPending) {
        cout << "No pending requests.\n";
    }
}

void approveRequests() {
    showRequests();
    if (requests.empty()) return;

    cout << "Enter the number of the request you want to approve (0 to cancel): ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 0) {
        cout << "Approval canceled.\n";
        return;
    }

    if (choice < 1 || choice > (int)requests.size()) {
        cout << "Invalid choice.\n";
        return;
    }

    Request& req = requests[choice - 1];
    if (req.isApproved) {
        cout << "Request already approved.\n";
        return;
    }

    auto slotIt = find_if(parkingSlots.begin(), parkingSlots.end(),
                          [&](const ParkingSlot& slot) { return slot.id == req.slotId; });
    if (slotIt == parkingSlots.end()) {
        cout << "Slot not found.\n";
        return;
    }
    if (slotIt->isOccupied) {
        cout << "Slot already occupied. Cannot approve this request.\n";
        return;
    }

    req.isApproved = true;
    cout << "? Request approved for car " << req.carNumber << " on slot " << req.slotId << endl;
}

void showLogs() {
    if (logs.empty()) {
        cout << "No parking logs available.\n";
        return;
    }
    for (const auto& log : logs) {
        cout << "Car: " << log.carNumber
             << ", Plate: " << log.plateNumber
             << ", Owner: " << log.ownerName
             << ", Entry: " << log.entryTime
             << ", Exit: " << (log.exitTime.empty() ? "Still parked" : log.exitTime)
             << ", Amount Paid: $" << log.amountPaid << endl;
    }
}

void showUsers() {
    if (users.empty()) {
        cout << "No users registered.\n";
        return;
    }
    cout << "\n?? Registered Users:\n";
    for (const auto& user : users) {
        cout << "- Name: " << user.name << ", Email: " << user.email << endl;
    }
}

void exportAdminLogsToCSV() {
    ofstream file("logs_admin.csv");
    file << "OwnerName,CarNumber,PlateNumber,EntryTime,ExitTime,AmountPaid\n";
    for (const auto& log : logs) {
        file << "\"" << log.ownerName << "\","
             << log.carNumber << ","
             << log.plateNumber << ","
             << log.entryTime << ","
             << (log.exitTime.empty() ? "Still parked" : log.exitTime) << ","
             << log.amountPaid << "\n";
    }
    file.close();
    cout << "?? Admin logs exported to logs_admin.csv\n";
}

// --- User Actions ---
void registerVehicle(const string& email) {
    string ownerName, carNumber, plateNumber;
    cout << "Enter owner name: ";
    getline(cin, ownerName);
    cout << "Enter car number: ";
    getline(cin, carNumber);
    cout << "Enter plate number: ";
    getline(cin, plateNumber);
    vehicles.push_back({email, ownerName, carNumber, plateNumber});
    cout << "?? Vehicle registered.\n";
}

void showUserVehicles(const string& email) {
    bool found = false;
    cout << "\n--- Your Vehicles ---\n";
    for (size_t i = 0; i < vehicles.size(); ++i) {
        if (vehicles[i].ownerEmail == email) {
            found = true;
            cout << i+1 << ". Car Number: " << vehicles[i].carNumber
                 << ", Plate Number: " << vehicles[i].plateNumber
                 << ", Owner: " << vehicles[i].ownerName << endl;
        }
    }
    if (!found) {
        cout << "No vehicles registered.\n";
    }
}

void editVehicle(const string& email) {
    showUserVehicles(email);
    if (vehicles.empty()) return;

    cout << "Enter the number of the vehicle to edit (0 to cancel): ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 0) {
        cout << "Edit canceled.\n";
        return;
    }

    int index = -1;
    for (size_t i = 0; i < vehicles.size(); ++i) {
        if (vehicles[i].ownerEmail == email) {
            if (--choice == 0) {
                index = i;
                break;
            }
        }
    }

    if (index == -1) {
        cout << "Invalid choice.\n";
        return;
    }

    string carNumber, plateNumber;
    cout << "Enter new car number (leave blank to keep " << vehicles[index].carNumber << "): ";
    getline(cin, carNumber);
    cout << "Enter new plate number (leave blank to keep " << vehicles[index].plateNumber << "): ";
    getline(cin, plateNumber);

    if (!carNumber.empty()) vehicles[index].carNumber = carNumber;
    if (!plateNumber.empty()) vehicles[index].plateNumber = plateNumber;
    cout << "?? Vehicle updated successfully.\n";
}

void deleteVehicle(const string& email) {
    showUserVehicles(email);
    if (vehicles.empty()) return;

    cout << "Enter the number of the vehicle to delete (0 to cancel): ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 0) {
        cout << "Deletion canceled.\n";
        return;
    }

    int index = -1;
    for (size_t i = 0; i < vehicles.size(); ++i) {
        if (vehicles[i].ownerEmail == email) {
            if (--choice == 0) {
                index = i;
                break;
            }
        }
    }

    if (index == -1) {
        cout << "Invalid choice.\n";
        return;
    }

    vehicles.erase(vehicles.begin() + index);
    cout << "??? Vehicle deleted successfully.\n";
}

void requestParkingSlot(const string& email) {
    vector<ParkingSlot> availableSlots;
    for (const auto& slot : parkingSlots) {
        if (!slot.isOccupied) {
            availableSlots.push_back(slot);
        }
    }

    if (availableSlots.empty()) {
        cout << "? No free slots available.\n";
        return;
    }

    cout << "\nAvailable Slots:\n";
    for (const auto& slot : availableSlots) {
        cout << "ID: " << slot.id
             << ", Vehicle Type: " << slot.vehicleType
             << ", Size: " << slot.size
             << ", Location: " << slot.location
             << ", Type: " << slot.type << endl;
    }

    cout << "Enter the Slot ID you want to request: ";
    int chosenSlotId;
    cin >> chosenSlotId;
    cin.ignore();

    auto it = find_if(availableSlots.begin(), availableSlots.end(),
                      [&](const ParkingSlot& slot) { return slot.id == chosenSlotId; });
    if (it == availableSlots.end()) {
        cout << "Invalid slot selected or slot is occupied.\n";
        return;
    }

    cout << "\nYour Vehicles:\n";
    vector<size_t> userVehicles;
    for (size_t i = 0; i < vehicles.size(); ++i) {
        if (vehicles[i].ownerEmail == email) {
            userVehicles.push_back(i);
            cout << i+1 << ". Car Number: " << vehicles[i].carNumber
                 << ", Plate Number: " << vehicles[i].plateNumber << endl;
        }
    }

    if (userVehicles.empty()) {
        cout << "No vehicles registered. Please register a vehicle first.\n";
        return;
    }

    cout << "Select vehicle number for parking request: ";
    int vehicleChoice;
    cin >> vehicleChoice;
    cin.ignore();

    if (vehicleChoice < 1 || vehicleChoice > (int)userVehicles.size()) {
        cout << "Invalid vehicle selection.\n";
        return;
    }

    string carNumber = vehicles[userVehicles[vehicleChoice-1]].carNumber;
    requests.push_back({email, carNumber, chosenSlotId, false, false, "", "", 0.0f});
    cout << "Requested slot ID: " << chosenSlotId << " for car " << carNumber << endl;
}

void payForSlot(const string& email) {
    bool found = false;
    cout << "\n--- Approved Requests ---\n";
    for (size_t i = 0; i < requests.size(); ++i) {
        const auto& req = requests[i];
        if (req.ownerEmail == email && req.isApproved && !req.isPaid) {
            found = true;
            cout << i+1 << ". Car: " << req.carNumber << ", Slot ID: " << req.slotId << endl;
        }
    }

    if (!found) {
        cout << "No approved requests found.\n";
        return;
    }

    cout << "Select request number to pay for (0 to cancel): ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 0) {
        cout << "Payment canceled.\n";
        return;
    }

    int index = -1;
    for (size_t i = 0; i < requests.size(); ++i) {
        if (requests[i].ownerEmail == email && requests[i].isApproved && !requests[i].isPaid) {
            if (--choice == 0) {
                index = i;
                break;
            }
        }
    }

    if (index == -1) {
        cout << "Invalid choice.\n";
        return;
    }

    Request& req = requests[index];
    bool validInput = false;
    while (!validInput) {
        cout << "Enter start time (YYYY-MM-DD HH:MM:SS, e.g., 2025-05-01 10:00:00): ";
        getline(cin, req.startTime);
        cout << "Enter end time (YYYY-MM-DD HH:MM:SS, e.g., 2025-05-01 12:00:00): ";
        getline(cin, req.endTime);

        bool startSuccess, endSuccess;
        time_t startT = parseTime(req.startTime, startSuccess);
        time_t endT = parseTime(req.endTime, endSuccess);

        if (!startSuccess || !endSuccess) {
            cout << "Invalid time format. Please use YYYY-MM-DD HH:MM:SS with zero-padded values.\n";
            continue;
        }

        if (endT <= startT) {
            cout << "End time must be after start time.\n";
            continue;
        }

        int hours = calculateHours(req.startTime, req.endTime);
        if (hours <= 0) {
            cout << "Error calculating duration. Please try again.\n";
            continue;
        }

        req.amount = hours * 200.0f; // 200 per hour
        cout << "Parking duration: " << hours << " hours\n";
        cout << "Total amount: $" << req.amount << endl;
        validInput = true;
    }

    req.isPaid = true;
    for (auto& slot : parkingSlots) {
        if (slot.id == req.slotId) {
            slot.isOccupied = true;
            for (auto& v : vehicles) {
                if (v.ownerEmail == email && v.carNumber == req.carNumber) {
                    logs.push_back({v.ownerName, v.carNumber, v.plateNumber, req.startTime, "", req.amount});
                    cout << "?? Payment successful for slot ID: " << req.slotId << endl;
                    return;
                }
            }
        }
    }
    cout << "Error: Slot or vehicle not found.\n";
}

void carExit(const string& email) {
    for (auto& slot : parkingSlots) {
        for (auto& req : requests) {
            if (req.ownerEmail == email && req.isApproved && req.isPaid && req.slotId == slot.id) {
                for (auto& log : logs) {
                    if (log.carNumber == req.carNumber && log.exitTime.empty()) {
                        log.exitTime = req.endTime; // Use user-specified end time
                        slot.isOccupied = false;
                        cout << "?? Exit recorded for car: " << log.carNumber << endl;
                        return;
                    }
                }
            }
        }
    }
    cout << "No parked car found for exit.\n";
}

void showUserLogs(const string& email) {
    bool found = false;
    cout << "\n--- Your Parking Logs ---\n";
    for (const auto& log : logs) {
        if (find_if(vehicles.begin(), vehicles.end(),
                    [&](const Vehicle& v) { return v.carNumber == log.carNumber && v.ownerEmail == email; })
            != vehicles.end()) {
            found = true;
            cout << "Car: " << log.carNumber
                 << ", Plate: " << log.plateNumber
                 << ", Entry: " << log.entryTime
                 << ", Exit: " << (log.exitTime.empty() ? "Still parked" : log.exitTime)
                 << ", Amount Paid: $" << log.amountPaid << endl;
        }
    }
    if (!found) {
        cout << "No parking logs available.\n";
    }
}

void exportUserLogsToCSV(const string& email) {
    string filename = "logs_user_" + email + ".csv";
    ofstream file(filename);
    file << "OwnerName,CarNumber,PlateNumber,EntryTime,ExitTime,AmountPaid\n";
    for (const auto& log : logs) {
        if (find_if(vehicles.begin(), vehicles.end(),
                    [&](const Vehicle& v) { return v.carNumber == log.carNumber && v.ownerEmail == email; })
            != vehicles.end()) {
            file << "\"" << log.ownerName << "\","
                 << log.carNumber << ","
                 << log.plateNumber << ","
                 << log.entryTime << ","
                 << (log.exitTime.empty() ? "Still parked" : log.exitTime) << ","
                 << log.amountPaid << "\n";
        }
    }
    file.close(); // Fixed typo: was file/close()
    cout << "?? Your logs exported to " << filename << "\n";
}

// --- Menus ---
void adminMenu() {
    while (true) {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Parking Slot\n";
        cout << "2. List Parking Slots\n";
        cout << "3. View Requests and Approve\n";
        cout << "4. View Logs\n";
        cout << "5. View Users\n";
        cout << "6. Export Logs to CSV\n";
        cout << "7. Logout\n";
        cout << "Choose option: ";
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addParkingSlot(); break;
            case 2: listParkingSlots(); break;
            case 3: approveRequests(); break;
            case 4: showLogs(); break;
            case 5: showUsers(); break;
            case 6: exportAdminLogsToCSV(); break;
            case 7: return;
            default: cout << "Invalid option.\n";
        }
    }
}

void userMenu(const string& email) {
    while (true) {
        cout << "\n--- User Menu ---\n";
        cout << "1. Register Vehicle\n";
        cout << "2. View My Vehicles\n";
        cout << "3. Edit Vehicle\n";
        cout << "4. Delete Vehicle\n";
        cout << "5. Request Parking Slot\n";
        cout << "6. Pay for Approved Slot\n";
        cout << "7. Exit Parking\n";
        cout << "8. View My Logs\n";
        cout << "9. Export Logs to CSV\n";
        cout << "10. Logout\n";
        cout << "Choose option: ";
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: registerVehicle(email); break;
            case 2: showUserVehicles(email); break;
            case 3: editVehicle(email); break;
            case 4: deleteVehicle(email); break;
            case 5: requestParkingSlot(email); break;
            case 6: payForSlot(email); break;
            case 7: carExit(email); break;
            case 8: showUserLogs(email); break;
            case 9: exportUserLogsToCSV(email); break;
            case 10: return;
            default: cout << "Invalid option.\n";
        }
    }
}

int main() {
    cout << "Welcome to the Parking Management System\n";

    while (true) {
        cout << "\n1. Register\n2. Login\n3. Exit\nChoose option: ";
        int option;
        cin >> option;
        cin.ignore();

        if (option == 1) {
            registerUser();
        } else if (option == 2) {
            string role = loginUser();
            if (role == "admin") {
                cout << "Welcome, Admin!\n";
                adminMenu();
            } else if (!role.empty()) {
                cout << "Welcome, " << role << "!\n";
                userMenu(role);
            }
        } else if (option == 3) {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid option.\n";
        }
    }

    return 0;
}