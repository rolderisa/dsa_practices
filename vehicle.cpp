#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#define FILE_NAME "vehicles.csv"

using namespace std;

struct Vehicle {
    int vehicle_id;
    string vehicle_make;
    string vehicle_model;
    int year;
    string registration_date;
};

bool compareByMakeModel(const Vehicle &a, const Vehicle &b) {
    if (a.vehicle_make == b.vehicle_make) {
        return a.vehicle_model < b.vehicle_model;
    }
    return a.vehicle_make < b.vehicle_make;
}

vector<Vehicle> loadVehicles() {
    vector<Vehicle> vehicles;
    ifstream file(FILE_NAME);
    string line;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << FILE_NAME << endl;
        return vehicles;
    }

    while (getline(file, line)) {
        istringstream ss(line);
        string vehicle_id_str, vehicle_make, vehicle_model, year_str, registration_date;

        if (ss >> vehicle_id_str >> vehicle_make >> vehicle_model >> year_str >> registration_date) {
            Vehicle v = {
                stoi(vehicle_id_str),
                vehicle_make,
                vehicle_model,
                stoi(year_str),
                registration_date
            };
            vehicles.push_back(v);
        } else {
            cerr << "Invalid record: " << line << endl;
        }
    }
    file.close();
    return vehicles;
}

void saveVehicles(const vector<Vehicle> &vehicles) {
    ofstream file(FILE_NAME, ios::trunc);
    if (!file.is_open()) {
        cerr << "Failed to open file for writing: " << FILE_NAME << endl;
        return;
    }

    for (const auto &v : vehicles) {
        file << v.vehicle_id << " " << v.vehicle_make << " " << v.vehicle_model << " " << v.year << " " << v.registration_date << endl;
    }
    file.close();
}

void showVehicles() {
    vector<Vehicle> vehicles = loadVehicles();
    if (vehicles.empty()) {
        cout << "No vehicles found in " << FILE_NAME << endl;
        return;
    }

    sort(vehicles.begin(), vehicles.end(), compareByMakeModel);

    for (const auto &v : vehicles) {
        cout << "ID: " << v.vehicle_id << "\tMake: " << v.vehicle_make << "\tModel: " << v.vehicle_model 
             << "\tYear: " << v.year << "\tReg Date: " << v.registration_date << endl;
    }
}

void addVehicle(const Vehicle &v) {
    vector<Vehicle> vehicles = loadVehicles();

    // Check if vehicle_id already exists
    for (const auto &veh : vehicles) {
        if (veh.vehicle_id == v.vehicle_id) {
            cerr << "Vehicle with ID " << v.vehicle_id << " already exists!" << endl;
            return;
        }
    }

    vehicles.push_back(v);
    saveVehicles(vehicles);
    cout << "Vehicle added successfully!" << endl;
}

void editVehicle(int vehicle_id) {
    vector<Vehicle> vehicles = loadVehicles();
    bool found = false;

    for (auto &v : vehicles) {
        if (v.vehicle_id == vehicle_id) {
            found = true;
            cout << "Editing Vehicle ID " << vehicle_id << endl;
            cout << "Current Make: " << v.vehicle_make << ", Enter new Make (or '-' to keep): ";
            string input;
            getline(cin, input);
            if (input != "-") v.vehicle_make = input;

            cout << "Current Model: " << v.vehicle_model << ", Enter new Model (or '-' to keep): ";
            getline(cin, input);
            if (input != "-") v.vehicle_model = input;

            cout << "Current Year: " << v.year << ", Enter new Year (or 0 to keep): ";
            getline(cin, input);
            if (!input.empty() && stoi(input) != 0) v.year = stoi(input);

            cout << "Current Reg Date: " << v.registration_date << ", Enter new Reg Date (or '-' to keep): ";
            getline(cin, input);
            if (input != "-") v.registration_date = input;

            saveVehicles(vehicles);
            cout << "Vehicle updated successfully!" << endl;
            break;
        }
    }

    if (!found) {
        cerr << "Vehicle with ID " << vehicle_id << " not found!" << endl;
    }
}

void deleteVehicle(int vehicle_id) {
    vector<Vehicle> vehicles = loadVehicles();
    auto it = remove_if(vehicles.begin(), vehicles.end(), [vehicle_id](const Vehicle &v) {
        return v.vehicle_id == vehicle_id;
    });

    if (it == vehicles.end()) {
        cerr << "Vehicle with ID " << vehicle_id << " not found!" << endl;
        return;
    }

    vehicles.erase(it, vehicles.end());
    saveVehicles(vehicles);
    cout << "Vehicle deleted successfully!" << endl;
}

string toLowercase(const string &str) {
    string result;
    for (char c : str) {
        result.push_back(tolower(c));
    }
    return result;
}

int main() {
    string user_input, command;

    while (true) {
        cout << "\nEnter command (vehicleadd, vehicleedit, vehicledelete, vehicleshow, help, exit):" << endl;
        getline(cin, user_input);
        istringstream ss(user_input);
        ss >> command;
        command = toLowercase(command);

        if (command == "vehicleadd") {
            string id_str, make, model, year_str, reg_date;
            if (ss >> id_str >> make >> model >> year_str >> reg_date) {
                Vehicle v = {stoi(id_str), make, model, stoi(year_str), reg_date};
                addVehicle(v);
            } else {
                cerr << "Invalid input. Usage: vehicleadd <id> <make> <model> <year> <registration_date>" << endl;
            }
        } else if (command == "vehicleedit") {
            string id_str;
            if (ss >> id_str) {
                editVehicle(stoi(id_str));
            } else {
                cerr << "Invalid input. Usage: vehicleedit <id>" << endl;
            }
        } else if (command == "vehicledelete") {
            string id_str;
            if (ss >> id_str) {
                deleteVehicle(stoi(id_str));
            } else {
                cerr << "Invalid input. Usage: vehicledelete <id>" << endl;
            }
        } else if (command == "vehicleshow") {
            showVehicles();
        } else if (command == "help") {
            cout << "Commands:" << endl;
            cout << "  vehicleadd <id> <make> <model> <year> <registration_date>" << endl;
            cout << "  vehicleedit <id>" << endl;
            cout << "  vehicledelete <id>" << endl;
            cout << "  vehicleshow" << endl;
            cout << "  help" << endl;
            cout << "  exit" << endl;
        } else if (command == "exit") {
            cout << "Exiting program..." << endl;
            break;
        } else {
            cerr << "Invalid command! Type 'help' for list of commands." << endl;
        }
    }
}
