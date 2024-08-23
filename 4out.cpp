#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

// Customer Class
class Customer {
public:
    Customer(int id, const string& name, const string& address, const string& phone)
        : customerID(id), name(name), address(address), phone(phone) {}

    void displayCustomerInfo() const {
        cout << "Customer ID: " << customerID << endl;
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Phone: " << phone << endl;
    }

private:
    int customerID;
    string name;
    string address;
    string phone;
};

// Account Class
class Account {
public:
    Account(int accNumber, double initialBalance, int custID)
        : accountNumber(accNumber), balance(initialBalance), customerID(custID) {}

    bool deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            addTransaction("Deposit", amount);
            return true;
        }
        return false;
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            addTransaction("Withdrawal", amount);
            return true;
        }
        return false;
    }

    bool transfer(Account& toAccount, double amount) {
        if (withdraw(amount)) {
            toAccount.deposit(amount);
            addTransaction("Transfer to Account " + to_string(toAccount.accountNumber), amount);
            toAccount.addTransaction("Transfer from Account " + to_string(accountNumber), amount);
            return true;
        }
        return false;
    }

    void displayAccountInfo() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: $" << balance << endl;
    }

    void displayTransactionHistory() const {
        cout << "Transaction History for Account " << accountNumber << ":" << endl;
        for (const auto& txn : transactions) {
            cout << txn << endl;
        }
    }

    int getAccountNumber() const {
        return accountNumber;
    }

private:
    int accountNumber;
    double balance;
    int customerID;
    vector<string> transactions;

    void addTransaction(const string& type, double amount) {
        string txn = getCurrentDateTime() + " - " + type + ": $" + to_string(amount);
        transactions.push_back(txn);
    }

    string getCurrentDateTime() const {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        return to_string(ltm->tm_year + 1900) + '-' +
               to_string(ltm->tm_mon + 1) + '-' +
               to_string(ltm->tm_mday) + ' ' +
               to_string(ltm->tm_hour) + ':' +
               to_string(ltm->tm_min) + ':' +
               to_string(ltm->tm_sec);
    }
};

// BankingServices Class
class BankingServices {
public:
    void createAccount(int accNumber, double initialBalance, int custID) {
        accounts.push_back(Account(accNumber, initialBalance, custID));
    }

    Account* getAccount(int accNumber) {
        for (auto& acc : accounts) {
            if (acc.getAccountNumber() == accNumber) {
                return &acc;
            }
        }
        return nullptr;
    }

    void deposit(int accNumber, double amount) {
        Account* acc = getAccount(accNumber);
        if (acc) {
            if (acc->deposit(amount)) {
                cout << "Deposit successful!" << endl;
            } else {
                cout << "Deposit failed!" << endl;
            }
        } else {
            cout << "Account not found!" << endl;
        }
    }

    void withdraw(int accNumber, double amount) {
        Account* acc = getAccount(accNumber);
        if (acc) {
            if (acc->withdraw(amount)) {
                cout << "Withdrawal successful!" << endl;
            } else {
                cout << "Withdrawal failed!" << endl;
            }
        } else {
            cout << "Account not found!" << endl;
        }
    }

    void transfer(int fromAccNumber, int toAccNumber, double amount) {
        Account* fromAcc = getAccount(fromAccNumber);
        Account* toAcc = getAccount(toAccNumber);
        if (fromAcc && toAcc) {
            if (fromAcc->transfer(*toAcc, amount)) {
                cout << "Transfer successful!" << endl;
            } else {
                cout << "Transfer failed!" << endl;
            }
        } else {
            cout << "One or both accounts not found!" << endl;
        }
    }

    void viewAccountInfo(int accNumber) {
        Account* acc = getAccount(accNumber);
        if (acc) {
            acc->displayAccountInfo();
        } else {
            cout << "Account not found!" << endl;
        }
    }

    void viewTransactionHistory(int accNumber) {
        Account* acc = getAccount(accNumber);
        if (acc) {
            acc->displayTransactionHistory();
        } else {
            cout << "Account not found!" << endl;
        }
    }

private:
    vector<Account> accounts;
};

int main() {
    BankingServices bank;

    // Create customers and accounts
    bank.createAccount(123456, 1000.0, 1);
    bank.createAccount(654321, 500.0, 2);

    // Perform transactions
    bank.deposit(123456, 200.0);
    bank.withdraw(654321, 50.0);
    bank.transfer(123456, 654321, 150.0);

    // View account information and transaction history
    bank.viewAccountInfo(123456);
    bank.viewTransactionHistory(123456);

    bank.viewAccountInfo(654321);
    bank.viewTransactionHistory(654321);

    return 0;
}
