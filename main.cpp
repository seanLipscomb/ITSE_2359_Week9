#include <iostream>
#include <exception>
#include <string>
 
using namespace std;
 
// Custom exception classes
class InsufficientFunds : public exception {
public:
    const char* what() const noexcept override {
        return "Error: Insufficient funds for this withdrawal.";
    }
};
 
class NegativeDeposit : public exception {
public:
    const char* what() const noexcept override {
        return "Error: Deposit amount cannot be negative.";
    }
};
 
class BankAccount {
    double balance;
    string accountNumber;
 
public:
    BankAccount(string accNo, double initialBalance)
        : accountNumber(accNo), balance(initialBalance) {}
 
    void withdraw(double amount) {
        if (amount > balance) {
            throw InsufficientFunds();
        }
        balance -= amount;
        cout << "Successfully withdrew: $" << amount << endl;
    }
 
    void deposit(double amount) {
        if (amount < 0) {
            throw NegativeDeposit();
        }
        balance += amount;
        cout << "Successfully deposited: $" << amount << endl;
    }
 
    double getBalance() const {
        return balance;
    }
};
 
void processWithdrawal(BankAccount& account, double amount) {
    account.withdraw(amount);  // Exception may propagate from here
}
 
int main() {
    try {
        BankAccount myAccount("12345", 100.0);
 
        cout << "Initial balance: $" << myAccount.getBalance() << endl;
 
        myAccount.deposit(50);
        processWithdrawal(myAccount, 200);  // Will throw InsufficientFunds
 
    } catch (const InsufficientFunds& e) {
        cout << e.what() << endl;
    } catch (const NegativeDeposit& e) {
        cout << e.what() << endl;
    } catch (...) {
        cout << "An unexpected error occurred." << endl;
    }
 
    cout << "Program completed." << endl;
    return 0;
}