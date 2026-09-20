// DIGITAL WALLET MANAGEMENT SYSTEM

#include <iostream>
using namespace std;
class Wallet {
protected:
    string name;
    double balance;
public:
    Wallet(string a, double b)
    {
        name = a;
        balance = b;
    }
    virtual ~Wallet() {}
    string inputName()
    {
        return name;
    }
    double inputBalance()
    {
        return balance;
    }
    virtual string getType()
    {
        return "Wallet";
    }
    void showBalance()
    {
        cout << name << "  Balance = " << balance << endl;
    }
    void deposit(double amount)
    {
        balance += amount;
        cout << "Deposited = " << amount << endl;
    }
    void withdraw(double amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
            cout << "Withdrawn = " << amount << endl;
        }
        else
        {
            cout << "Insufficient Balance!!!\n";
        }
    }
    virtual void cashback(double amount)
    {
        cout << "No cashback for this user.\n";
    }
    Wallet operator+(double amount)
    {
        Wallet temp(name, balance + amount);
        cout << "Added = " << amount << endl;
        return temp;
    }
    Wallet operator-(double amount)
    {
        if (balance >= amount)
        {
            Wallet temp(name, balance - amount);
            cout << "Sent = " << amount << endl;
            return temp;
        }
        else
        {
            cout << "Insufficient Balance!!!!\n";
            return *this;
        }
    }
   
};
class RegularUser : public Wallet {
public:
    RegularUser(string n, double b) : Wallet(n, b) {}
    string getType() override
    {
        return "Regular";
    }
    void cashback(double amount)  
    {
        double cb = amount * 0.02;
        balance += cb;
        cout << "Regular Cashback = " << cb << endl;
    }
};
class PremiumUser : public Wallet
{
public:
    PremiumUser(string n, double b) : Wallet(n, b) {}
    string getType() override
    {
        return "Premium";
    }
    void cashback(double amount)
    {
        double cb = amount * 0.05;
        balance += cb;
        cout << "Premium Cashback = " << cb << endl;
    }
};
int main() {
    Wallet* users[50];
    int totalUsers = 0;
    int n;
    cout << "How many users = ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        string name;
        double bal;
        int type;

        cout << "\nEnter name: ";
        cin >> name;
        cout << "Initial balance: ";
        cin >> bal;
        cout << "1. Regular  2. Premium: ";
        cin >> type;
        if (type == 1)
            users[i] = new RegularUser(name, bal);
        else
            users[i] = new PremiumUser(name, bal);
        totalUsers++;
    }
    int choice;
    do {
        cout << "\n\t Digital Wallet Menu \n";
        cout << "1. Add Money\n";
        cout << "2. Send Money\n";
        cout << "3. Show Balance\n";
        cout << "4. Cashback\n";
        cout << "5. Transfer Between Users\n";
        cout << "6. Show All Users\n";
        cout << "7. Search User\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        int userIndex;
        double amt;
        if (choice >= 1 && choice <= 4) {
            cout << "Select user from 0 to " << totalUsers - 1 << ": ";
            cin >> userIndex;
            if (userIndex < 0 || userIndex >= totalUsers)
            {
                cout << "Invalid user!!!!\n";
                continue;
            }
        }
        switch (choice) {
        case 1:
            cout << "Enter amount= ";
            cin >> amt;
            users[userIndex]->deposit(amt);
            break;
        case 2:
            cout << "Enter amount= ";
            cin >> amt;
            users[userIndex]->withdraw(amt);
            break;

        case 3:
            users[userIndex]->showBalance();
            break;

        case 4:
            cout << "Enter transaction amount= ";
            cin >> amt;
            users[userIndex]->cashback(amt);
            break;

        case 5: {
            int from, to;
            cout << "From user index= ";
            cin >> from;
            cout << "To user index= ";
            cin >> to;
            cout << "Amount= ";
            cin >> amt;

            if (from >= 0 && from < totalUsers && to >= 0 && to < totalUsers) {
                if (users[from]->inputBalance() >= amt) {
                    users[from]->withdraw(amt);
                    users[to]->deposit(amt);
                    cout << "Transfer successful!!!!\n";
                } else {
                    cout << "Insufficient balance!!!!\n";
                }
            } else {
                cout << "Invalid\n";
            }
            break;
        }

        case 6:
            cout << "\nAll users\n";
            for (int i = 0; i < totalUsers; i++) {
                cout << i << ". "
                     << users[i]->inputName()
                     << " (" << users[i]->getType() << ")"
                     << " - Balance: " << users[i]->inputBalance()
                     << endl;
            }
            break;
        case 7: {
            string searchName;
            cout << "Enter name for searching= ";
            cin >> searchName;

            bool found = false;
            for (int i = 0; i < totalUsers; i++) {
                if (users[i]->inputName() == searchName) {
                    cout << "Found: ";
                    users[i]->showBalance();
                    found = true;
                }
            }

            if (!found)
                cout << "User not found!\n";

            break;
        }
        case 8:
            cout << "bye bye\n";
            break;
        default:
            cout << "incorrect choce!!!!\n";
        }
    }
    while (choice != 8);
    for (int i = 0; i < totalUsers; i++) {
        delete users[i];
    }
    return 0;
}
