/*
	
	Title			: Hotel Management System
	Language		: C++
	Author			: Daljeet Singh Chhabra
	Date Created	: 16-02-2016
	Last Modified	: 01-10-2018

*/
//
//#include<fstream.h>
//#include<iostream.h>
//#include<conio.h>
//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//#include<process.h>
//#include<dos.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

class Hotel {
private:
    int room_no;
    string name;
    string address;
    string phone;
    int days;
    float fare;

public:
    void main_menu();
    void add();
    void display();
    void rooms();
    void edit();
    int check(int);
    void modify(int);
    void delete_rec(int);
};

void clearScreen() {
    // Works on most terminals (use system("cls") on Windows CMD if needed)
    cout << "\033[2J\033[1;1H";
}

void pause() {
    cout << "\nPress enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void Hotel::main_menu() {
    int choice = 0;
    while (choice != 5) {
        clearScreen();
        cout << "\n=== HOTEL MANAGEMENT SYSTEM ===";
        cout << "\n1. Book A Room";
        cout << "\n2. Customer Record";
        cout << "\n3. Rooms Allotted";
        cout << "\n4. Edit Record";
        cout << "\n5. Exit";
        cout << "\nEnter Your Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: add(); break;
            case 2: display(); break;
            case 3: rooms(); break;
            case 4: edit(); break;
            case 5: cout << "\nExiting..."; break;
            default: cout << "\nInvalid choice!"; pause(); break;
        }
    }
}

void Hotel::add() {
    clearScreen();
    cout << "\n=== Book A Room ===\n";
    int r;
    cout << "Enter Room No: ";
    cin >> r;
    cin.ignore();

    if (check(r)) {
        cout << "Sorry, room is already booked!";
    } else {
        room_no = r;
        cout << "Name: ";
        getline(cin, name);
        cout << "Address: ";
        getline(cin, address);
        cout << "Phone: ";
        getline(cin, phone);
        cout << "No. of days: ";
        cin >> days;
        fare = days * 900;

        ofstream fout("Record.txt", ios::app);
        fout << room_no << '\n' << name << '\n' << address << '\n' << phone << '\n' << days << '\n' << fare << '\n';
        fout.close();
        cout << "Room booked successfully!";
    }
    pause();
}

int Hotel::check(int r) {
    ifstream fin("Record.txt");
    int tempRoom;
    string tmp;
    while (fin >> tempRoom) {
        fin.ignore();
        getline(fin, tmp); // name
        getline(fin, tmp); // address
        getline(fin, tmp); // phone
        getline(fin, tmp); // days
        getline(fin, tmp); // fare

        if (tempRoom == r) {
            fin.close();
            return 1;
        }
    }
    fin.close();
    return 0;
}

void Hotel::display() {
    clearScreen();
    cout << "\n=== Customer Record ===\n";
    ifstream fin("Record.txt");
    int r, found = 0;
    cout << "Enter Room No to search: ";
    cin >> r;
    cin.ignore();

    int tempRoom, tempDays;
    float tempFare;
    string tempName, tempAddr, tempPhone;

    while (fin >> tempRoom) {
        fin.ignore();
        getline(fin, tempName);
        getline(fin, tempAddr);
        getline(fin, tempPhone);
        fin >> tempDays;
        fin >> tempFare;
        fin.ignore();

        if (tempRoom == r) {
            cout << "\nRoom No: " << tempRoom;
            cout << "\nName: " << tempName;
            cout << "\nAddress: " << tempAddr;
            cout << "\nPhone: " << tempPhone;
            cout << "\nDays: " << tempDays;
            cout << "\nFare: " << tempFare;
            found = 1;
            break;
        }
    }

    if (!found) cout << "\nRecord not found!";
    fin.close();
    pause();
}

void Hotel::rooms() {
    clearScreen();
    cout << "\n=== List of Allotted Rooms ===\n";
    ifstream fin("Record.txt");

    int tempRoom, tempDays;
    float tempFare;
    string tempName, tempAddr, tempPhone;

    while (fin >> tempRoom) {
        fin.ignore();
        getline(fin, tempName);
        getline(fin, tempAddr);
        getline(fin, tempPhone);
        fin >> tempDays;
        fin >> tempFare;
        fin.ignore();

        cout << "\nRoom No: " << tempRoom;
        cout << "\nName: " << tempName;
        cout << "\nAddress: " << tempAddr;
        cout << "\nPhone: " << tempPhone;
        cout << "\nDays: " << tempDays;
        cout << "\nFare: " << tempFare;
        cout << "\n--------------------------";
    }

    fin.close();
    pause();
}

void Hotel::edit() {
    clearScreen();
    cout << "\n=== Edit Record ===";
    int choice, r;
    cout << "\n1. Modify Record\n2. Delete Record\nEnter choice: ";
    cin >> choice;
    cout << "Enter Room No: ";
    cin >> r;
    cin.ignore();

    switch (choice) {
        case 1: modify(r); break;
        case 2: delete_rec(r); break;
        default: cout << "Invalid choice!"; break;
    }
    pause();
}

void Hotel::modify(int r) {
    ifstream fin("Record.txt");
    ofstream fout("Temp.txt");

    int tempRoom, tempDays;
    float tempFare;
    string tempName, tempAddr, tempPhone;
    bool found = false;

    while (fin >> tempRoom) {
        fin.ignore();
        getline(fin, tempName);
        getline(fin, tempAddr);
        getline(fin, tempPhone);
        fin >> tempDays;
        fin >> tempFare;
        fin.ignore();

        if (tempRoom == r) {
            found = true;
            cout << "\nEnter new details:\n";
            cout << "Name: ";
            getline(cin, tempName);
            cout << "Address: ";
            getline(cin, tempAddr);
            cout << "Phone: ";
            getline(cin, tempPhone);
            cout << "Days: ";
            cin >> tempDays;
            tempFare = tempDays * 900;
            cin.ignore();
        }

        fout << tempRoom << '\n' << tempName << '\n' << tempAddr << '\n' << tempPhone << '\n' << tempDays << '\n' << tempFare << '\n';
    }

    fin.close();
    fout.close();
    remove("Record.txt");
    rename("Temp.txt", "Record.txt");

    if (found)
        cout << "Record modified successfully!";
    else
        cout << "Room not found!";
}

void Hotel::delete_rec(int r) {
    ifstream fin("Record.txt");
    ofstream fout("Temp.txt");

    int tempRoom, tempDays;
    float tempFare;
    string tempName, tempAddr, tempPhone;
    bool found = false;

    while (fin >> tempRoom) {
        fin.ignore();
        getline(fin, tempName);
        getline(fin, tempAddr);
        getline(fin, tempPhone);
        fin >> tempDays;
        fin >> tempFare;
        fin.ignore();

        if (tempRoom == r) {
            found = true;
            continue; // Skip writing
        }

        fout << tempRoom << '\n' << tempName << '\n' << tempAddr << '\n' << tempPhone << '\n' << tempDays << '\n' << tempFare << '\n';
    }

    fin.close();
    fout.close();
    remove("Record.txt");
    rename("Temp.txt", "Record.txt");

    if (found)
        cout << "Record deleted successfully!";
    else
        cout << "Room not found!";
}

int main() {
    Hotel h;
    h.main_menu();
    return 0;
}
