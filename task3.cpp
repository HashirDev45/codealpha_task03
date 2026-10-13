#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

class Transaction
{
public:
    string type;
    double amount;
    string description;

    Transaction()
    {
        type = "";
        amount = 0;
        description = "";
    }

    Transaction(string t, double a, string d)
    {
        type = t;
        amount = a;
        description = d;
    }
};

class Customer
{
public:
    int customerId;
    string name;
    string phone;

    Customer()
    {
        customerId = 0;
        name = "";
        phone = "";
    }

    Customer(int id, string n, string p)
    {
        customerId = id;
        name = n;
        phone = p;
    }

    void displayCustomer()
    {
        cout << "Customer ID : " << customerId << endl;
        cout << "Name        : " << name << endl;
        cout << "Phone       : " << phone << endl;
    }
};

class Account
{
public:
    int accountNumber;
    int customerId;
    double balance;

    Transaction transactions[100];
    int transactionCount;

    Account()
    {
        accountNumber = 0;
        customerId = 0;
        balance = 0;
        transactionCount = 0;
    }

    Account(int accNo, int custId)
    {
        accountNumber = accNo;
        customerId = custId;
        balance = 0;
        transactionCount = 0;
    }

    void addTransaction(string type, double amount, string description)
    {
        if(transactionCount < 100)
        {
            transactions[transactionCount] =
                Transaction(type, amount, description);

            transactionCount++;
        }
    }

    void deposit(double amount)
    {
        if(amount <= 0)
        {
            cout << "Invalid deposit amount." << endl;
            return;
        }

        balance = balance + amount;

        addTransaction(
            "Deposit",
            amount,
            "Money deposited into account"
        );

        cout << "Deposit successful." << endl;
        cout << "Current Balance: " << balance << endl;
    }

    void withdraw(double amount)
    {
        if(amount <= 0)
        {
            cout << "Invalid withdrawal amount." << endl;
            return;
        }

        if(amount > balance)
        {
            cout << "Insufficient balance." << endl;
            return;
        }

        balance = balance - amount;

        addTransaction(
            "Withdrawal",
            amount,
            "Money withdrawn from account"
        );

        cout << "Withdrawal successful." << endl;
        cout << "Current Balance: " << balance << endl;
    }

    bool transferTo(Account &receiver, double amount)
    {
        if(amount <= 0)
        {
            cout << "Invalid transfer amount." << endl;
            return false;
        }

        if(amount > balance)
        {
            cout << "Insufficient balance." << endl;
            return false;
        }

        balance = balance - amount;
        receiver.balance = receiver.balance + amount;

        addTransaction(
            "Transfer",
            amount,
            "Money transferred to account " +
            to_string(receiver.accountNumber)
        );

        receiver.addTransaction(
            "Received",
            amount,
            "Money received from account " +
            to_string(accountNumber)
        );

        cout << "Transfer successful." << endl;

        return true;
    }

    void displayAccount()
    {
        cout << "\n==============================" << endl;
        cout << "       ACCOUNT DETAILS" << endl;
        cout << "==============================" << endl;

        cout << "Account Number : " << accountNumber << endl;
        cout << "Customer ID    : " << customerId << endl;
        cout << "Balance        : " << fixed << setprecision(2)
             << balance << endl;
    }

    void showTransactions()
    {
        cout << "\n==============================" << endl;
        cout << "     TRANSACTION HISTORY" << endl;
        cout << "==============================" << endl;

        if(transactionCount == 0)
        {
            cout << "No transactions found." << endl;
            return;
        }

        for(int i = 0; i < transactionCount; i++)
        {
            cout << "\nTransaction " << i + 1 << endl;
            cout << "Type        : " << transactions[i].type << endl;
            cout << "Amount      : " << fixed << setprecision(2)
                 << transactions[i].amount << endl;
            cout << "Description : "
                 << transactions[i].description << endl;
        }
    }
};

int findCustomer(Customer customers[], int customerCount, int customerId)
{
    for(int i = 0; i < customerCount; i++)
    {
        if(customers[i].customerId == customerId)
        {
            return i;
        }
    }

    return -1;
}

int findAccount(Account accounts[], int accountCount, int accountNumber)
{
    for(int i = 0; i < accountCount; i++)
    {
        if(accounts[i].accountNumber == accountNumber)
        {
            return i;
        }
    }

    return -1;
}

int main()
{
    Customer customers[100];
    Account accounts[100];

    int customerCount = 0;
    int accountCount = 0;

    int choice;

    do
    {
        cout << "\n====================================" << endl;
        cout << "          BANKING SYSTEM" << endl;
        cout << "====================================" << endl;

        cout << "1. Create Customer" << endl;
        cout << "2. Create Account" << endl;
        cout << "3. Deposit Money" << endl;
        cout << "4. Withdraw Money" << endl;
        cout << "5. Transfer Money" << endl;
        cout << "6. Display Account Information" << endl;
        cout << "7. Show Transaction History" << endl;
        cout << "8. Exit" << endl;

        cout << "\nEnter your choice: ";
        cin >> choice;

        if(choice == 1)
        {
            if(customerCount >= 100)
            {
                cout << "Customer limit reached." << endl;
                continue;
            }

            int id;
            string name;
            string phone;

            cout << "\nEnter Customer ID: ";
            cin >> id;

            if(findCustomer(customers, customerCount, id) != -1)
            {
                cout << "Customer ID already exists." << endl;
                continue;
            }

            cin.ignore();

            cout << "Enter Customer Name: ";
            getline(cin, name);

            cout << "Enter Phone Number: ";
            getline(cin, phone);

            customers[customerCount] =
                Customer(id, name, phone);

            customerCount++;

            cout << "Customer created successfully." << endl;
        }

        else if(choice == 2)
        {
            if(accountCount >= 100)
            {
                cout << "Account limit reached." << endl;
                continue;
            }

            int accountNumber;
            int customerId;

            cout << "\nEnter Account Number: ";
            cin >> accountNumber;

            if(findAccount(accounts, accountCount, accountNumber) != -1)
            {
                cout << "Account number already exists." << endl;
                continue;
            }

            cout << "Enter Customer ID: ";
            cin >> customerId;

            int customerIndex =
                findCustomer(customers, customerCount, customerId);

            if(customerIndex == -1)
            {
                cout << "Customer not found." << endl;
                continue;
            }

            accounts[accountCount] =
                Account(accountNumber, customerId);

            accountCount++;

            cout << "Account created successfully." << endl;
        }

        else if(choice == 3)
        {
            int accountNumber;
            double amount;

            cout << "\nEnter Account Number: ";
            cin >> accountNumber;

            int index =
                findAccount(accounts, accountCount, accountNumber);

            if(index == -1)
            {
                cout << "Account not found." << endl;
                continue;
            }

            cout << "Enter Deposit Amount: ";
            cin >> amount;

            accounts[index].deposit(amount);
        }

        else if(choice == 4)
        {
            int accountNumber;
            double amount;

            cout << "\nEnter Account Number: ";
            cin >> accountNumber;

            int index =
                findAccount(accounts, accountCount, accountNumber);

            if(index == -1)
            {
                cout << "Account not found." << endl;
                continue;
            }

            cout << "Enter Withdrawal Amount: ";
            cin >> amount;

            accounts[index].withdraw(amount);
        }

        else if(choice == 5)
        {
            int senderAccount;
            int receiverAccount;
            double amount;

            cout << "\nEnter Sender Account Number: ";
            cin >> senderAccount;

            cout << "Enter Receiver Account Number: ";
            cin >> receiverAccount;

            if(senderAccount == receiverAccount)
            {
                cout << "Sender and receiver cannot be same."
                     << endl;
                continue;
            }

            int senderIndex =
                findAccount(accounts, accountCount, senderAccount);

            int receiverIndex =
                findAccount(accounts, accountCount, receiverAccount);

            if(senderIndex == -1)
            {
                cout << "Sender account not found." << endl;
                continue;
            }

            if(receiverIndex == -1)
            {
                cout << "Receiver account not found." << endl;
                continue;
            }

            cout << "Enter Transfer Amount: ";
            cin >> amount;

            accounts[senderIndex].transferTo(
                accounts[receiverIndex],
                amount
            );
        }

        else if(choice == 6)
        {
            int accountNumber;

            cout << "\nEnter Account Number: ";
            cin >> accountNumber;

            int accountIndex =
                findAccount(accounts, accountCount, accountNumber);

            if(accountIndex == -1)
            {
                cout << "Account not found." << endl;
                continue;
            }

            int customerId =
                accounts[accountIndex].customerId;

            int customerIndex =
                findCustomer(customers, customerCount, customerId);

            customers[customerIndex].displayCustomer();

            accounts[accountIndex].displayAccount();
        }

        else if(choice == 7)
        {
            int accountNumber;

            cout << "\nEnter Account Number: ";
            cin >> accountNumber;

            int index =
                findAccount(accounts, accountCount, accountNumber);

            if(index == -1)
            {
                cout << "Account not found." << endl;
                continue;
            }

            accounts[index].showTransactions();
        }

        else if(choice == 8)
        {
            cout << "\nThank you for using Banking System." << endl;
        }

        else
        {
            cout << "Invalid choice." << endl;
        }
    }
    while(choice != 8);
    return 0;
}