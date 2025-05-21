#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Account {
private:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    Account() : accountNumber(0), accountHolderName(""), balance(0.0) {}
    
    Account(int accNum, string name, double bal) 
        : accountNumber(accNum), accountHolderName(name), balance(bal) {}

    int getAccountNumber() const { return accountNumber; }
    string getAccountHolderName() const { return accountHolderName; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Successfully deposited $" << amount << endl;
        } else {
            cout << "Invalid deposit amount" << endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Successfully withdrawn $" << amount << endl;
            return true;
        } else {
            cout << "Invalid withdrawal amount or insufficient balance" << endl;
            return false;
        }
    }

    void display() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    void saveToFile(ofstream& outFile) const {
        outFile << accountNumber << endl;
        outFile << accountHolderName << endl;
        outFile << balance << endl;
    }

    void loadFromFile(ifstream& inFile) {
        inFile >> accountNumber;
        inFile.ignore();
        getline(inFile, accountHolderName);
        inFile >> balance;
    }
};

class Bank {
private:
    vector<Account> accounts;
    string dataFile;

    int generateAccountNumber() {
        return accounts.empty() ? 1001 : accounts.back().getAccountNumber() + 1;
    }

public:
    Bank(string filename = "accounts.txt") : dataFile(filename) {
        loadAccounts();
    }

    void loadAccounts() {
        ifstream inFile(dataFile);
        if (inFile.is_open()) {
            while (!inFile.eof()) {
                Account acc;
                acc.loadFromFile(inFile);
                if (inFile.good()) {
                    accounts.push_back(acc);
                }
            }
            inFile.close();
        }
    }

    void saveAccounts() {
        ofstream outFile(dataFile);
        if (outFile.is_open()) {
            for (const auto& acc : accounts) {
                acc.saveToFile(outFile);
            }
            outFile.close();
        } else {
            cout << "Error saving accounts to file" << endl;
        }
    }

    void createAccount(string name, double initialDeposit) {
        if (initialDeposit >= 0) {
            Account newAccount(generateAccountNumber(), name, initialDeposit);
            accounts.push_back(newAccount);
            saveAccounts();
            cout << "Account created successfully!" << endl;
            newAccount.display();
        } else {
            cout << "Invalid initial deposit amount" << endl;
        }
    }

    Account* findAccount(int accNum) {
        for (auto& acc : accounts) {
            if (acc.getAccountNumber() == accNum) {
                return &acc;
            }
        }
        return nullptr;
    }

    void deposit(int accNum, double amount) {
        Account* acc = findAccount(accNum);
        if (acc) {
            acc->deposit(amount);
            saveAccounts();
        } else {
            cout << "Account not found" << endl;
        }
    }

    void withdraw(int accNum, double amount) {
        Account* acc = findAccount(accNum);
        if (acc) {
            if (acc->withdraw(amount)) {
                saveAccounts();
            }
        } else {
            cout << "Account not found" << endl;
        }
    }

    void checkBalance(int accNum) {
        Account* acc = findAccount(accNum);
        if (acc) {
            acc->display();
        } else {
            cout << "Account not found" << endl;
        }
    }

    void displayAllAccounts() {
        if (accounts.empty()) {
            cout << "No accounts found" << endl;
            return;
        }
        for (const auto& acc : accounts) {
            acc.display();
            cout << "------------------------" << endl;
        }
    }
};

void displayMenu() {
    cout << "\n=== Bank Management System ===" << endl;
    cout << "1. Create Account" << endl;
    cout << "2. Deposit" << endl;
    cout << "3. Withdraw" << endl;
    cout << "4. Check Balance" << endl;
    cout << "5. Display All Accounts" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Bank bank;
    int choice;
    string name;
    int accNum;
    double amount;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter account holder name: ";
                getline(cin, name);
                cout << "Enter initial deposit: $";
                cin >> amount;
                bank.createAccount(name, amount);
                break;

            case 2:
                cout << "Enter account number: ";
                cin >> accNum;
                cout << "Enter deposit amount: $";
                cin >> amount;
                bank.deposit(accNum, amount);
                break;

            case 3:
                cout << "Enter account number: ";
                cin >> accNum;
                cout << "Enter withdrawal amount: $";
                cin >> amount;
                bank.withdraw(accNum, amount);
                break;

            case 4:
                cout << "Enter account number: ";
                cin >> accNum;
                bank.checkBalance(accNum);
                break;

            case 5:
                bank.displayAllAccounts();
                break;

            case 6:
                cout << "Exiting system. Goodbye!" << endl;
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}