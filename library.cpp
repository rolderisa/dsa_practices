#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Book {
    string title;
    string author;
    int year;
    bool available;
};

struct Student {
    string name;
    int roll;
    double balance;
};

Book books[100];
int book_count = 0;

Student students[100];
int student_count = 0;

int find_student(int roll) {
    for (int i = 0; i < student_count; i++) {
        if (students[i].roll == roll) return i;
    }
    return -1;
}

void add_book() {
    if (book_count >= 100) {
        cout << "?? Maximum books reached!\n";
        return;
    }
    Book b;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, b.title);
    cout << "Enter author name: ";
    getline(cin, b.author);
    cout << "Enter year of publication: ";
    cin >> b.year;
    b.available = true;
    books[book_count++] = b;
    cout << "? Book added successfully.\n";
}

void edit_book() {
    cout << "Enter book title to edit: ";
    cin.ignore();
    string title;
    getline(cin, title);
    for (int i = 0; i < book_count; i++) {
        if (books[i].title == title) {
            cout << "Editing book: " << books[i].title << endl;
            cout << "Enter new title: ";
            getline(cin, books[i].title);
            cout << "Enter new author: ";
            getline(cin, books[i].author);
            cout << "Enter new year: ";
            cin >> books[i].year;
            cout << "Book updated successfully.\n";
            return;
        }
    }
    cout << "? Book not found.\n";
}

void view_books() {
    if (book_count == 0) {
        cout << "No books in the library.\n";
        return;
    }
    cout << "\n--- Books List ---\n";
    for (int i = 0; i < book_count; i++) {
        cout << i + 1 << ". Title: " << books[i].title << ", Author: " << books[i].author
             << ", Year: " << books[i].year
             << ", Available: " << (books[i].available ? "Yes" : "No") << endl;
    }
}

void display_all_students() {
    if (student_count == 0) {
        cout << "No students registered.\n";
        return;
    }
    cout << "\n--- Students List ---\n";
    for (int i = 0; i < student_count; i++) {
        cout << i + 1 << ". Name: " << students[i].name << ", Roll: " << students[i].roll
             << ", Balance: $" << students[i].balance << endl;
    }
}

void display_student(int roll) {
    int idx = find_student(roll);
    if (idx == -1) {
        cout << "? Student not found.\n";
        return;
    }
    cout << "\n--- Student Details ---\n";
    cout << "Name: " << students[idx].name << endl;
    cout << "Roll Number: " << students[idx].roll << endl;
    cout << "Balance: $" << students[idx].balance << endl;
}

void create_account() {
    Student s;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, s.name);
    cout << "Enter roll number: ";
    cin >> s.roll;
    s.balance = 0;
    students[student_count++] = s;
    cout << "? Account created successfully.\n";
}

void deposit_amount(int roll, double amount) {
    int idx = find_student(roll);
    if (idx == -1) {
        cout << "? Student not found.\n";
        return;
    }
    students[idx].balance += amount;
    cout << "? Amount deposited. New balance: $" << students[idx].balance << endl;
}

void issue_book(int roll) {
    int idx = find_student(roll);
    if (idx == -1) {
        cout << "? Student not found.\n";
        return;
    }
    cout << "Enter book title to issue: ";
    cin.ignore();
    string title;
    getline(cin, title);

    for (int i = 0; i < book_count; i++) {
        if (books[i].title == title && books[i].available) {
            books[i].available = false;
            cout << "? Book issued successfully to " << students[idx].name << endl;
            return;
        }
    }
    cout << "? Book not available or does not exist.\n";
}

// ? Export students to CSV
void export_students_to_csv() {
    ofstream file("students.csv");
    if (!file) {
        cout << "? Failed to open students.csv for writing.\n";
        return;
    }

    file << "Name,Roll,Balance\n";
    for (int i = 0; i < student_count; i++) {
        file << students[i].name << "," << students[i].roll << "," << students[i].balance << "\n";
    }
    file.close();
    cout << "? Students exported to students.csv successfully.\n";
}

// ? Export books to CSV
void export_books_to_csv() {
    ofstream file("books.csv");
    if (!file) {
        cout << "? Failed to open books.csv for writing.\n";
        return;
    }

    file << "Title,Author,Year,Available\n";
    for (int i = 0; i < book_count; i++) {
        file << books[i].title << "," << books[i].author << "," << books[i].year << "," << (books[i].available ? "Yes" : "No") << "\n";
    }
    file.close();
    cout << "? Books exported to books.csv successfully.\n";
}

int main() {
    // Initial demo data
    books[0] = {"C++ Programming", "Bjarne Stroustrup", 1985, true};
    books[1] = {"Data Structures", "Mark Allen Weiss", 1992, true};
    book_count = 2;

    students[0] = {"Alice", 101, 50.0};
    students[1] = {"Bob", 102, 20.0};
    student_count = 2;

    while (true) {
        cout << "\n====== Library Management System ======\n";
        cout << "1. Admin Login\n";
        cout << "2. Student Login\n";
        cout << "0. Exit\n";
        cout << "Choose option: ";
        int option;
        cin >> option;

        if (option == 0) {
            cout << "? Exiting Library System. Goodbye!\n";
            break;
        }

        if (option == 1) {
            // Admin Login
            cout << "Enter admin username: ";
            string username;
            cin >> username;

            cout << "Enter admin password: ";
            string password;
            cin >> password;

            if (username != "admin" || password != "admin123") {
                cout << "? Incorrect admin credentials!\n";
                continue;
            }

            // Admin menu loop
            while (true) {
                cout << "\n--- Admin Menu ---\n";
                cout << "1. Add Book\n";
                cout << "2. Edit Book\n";
                cout << "3. View Books\n";
                cout << "4. View All Students\n";
                cout << "5. View Student Details\n";
                cout << "6. Export Students to CSV\n";
                cout << "7. Export Books to CSV\n";
                cout << "0. Logout\n";
                cout << "Choose option: ";
                int admin_option;
                cin >> admin_option;

                if (admin_option == 0) {
                    cout << "Admin logged out.\n";
                    break;
                }

                switch (admin_option) {
                    case 1:
                        add_book();
                        break;
                    case 2:
                        edit_book();
                        break;
                    case 3:
                        view_books();
                        break;
                    case 4:
                        display_all_students();
                        break;
                    case 5: {
                        cout << "Enter student roll number: ";
                        int roll;
                        cin >> roll;
                        display_student(roll);
                        break;
                    }
                    case 6:
                        export_students_to_csv();
                        break;
                    case 7:
                        export_books_to_csv();
                        break;
                    default:
                        cout << "Invalid admin menu option!\n";
                }
            }
        } 
        else if (option == 2) {
            // Student login or register
            cout << "Enter student roll number: ";
            int roll;
            cin >> roll;

            int idx = find_student(roll);
            if (idx == -1) {
                cout << "Account not found. Create new account? (1=Yes, 0=No): ";
                int create;
                cin >> create;
                if (create == 1) {
                    create_account();
                }
            } else {
                cout << "\n--- Student Menu ---\n";
                cout << "1. View Details\n";
                cout << "2. Deposit Amount\n";
                cout << "3. Issue Book\n";
                cout << "Choose option: ";
                int stu_option;
                cin >> stu_option;

                switch (stu_option) {
                    case 1:
                        display_student(roll);
                        break;
                    case 2: {
                        cout << "Enter amount to deposit: $";
                        double amount;
                        cin >> amount;
                        deposit_amount(roll, amount);
                        break;
                    }
                    case 3:
                        issue_book(roll);
                        break;
                    default:
                        cout << "Invalid student menu option!\n";
                }
            }
        }
        else {
            cout << "Invalid main menu option!\n";
        }
    }

    return 0;
}
