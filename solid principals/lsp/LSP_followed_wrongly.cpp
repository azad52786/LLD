#include <iostream>
#include <vector>
#include <typeinfo>
using namespace std;

// Abstract Class
class Account
{
public:
    virtual void deposit(int amount) = 0;
    virtual void withdraw(int amount) = 0;
};

// Saving Account
class SavingAccount : public Account
{
public:
    int balance;

public:
    SavingAccount()
    {
        this->balance = 0;
    }

    void deposit(int _amount) override
    {
        this->balance += _amount;
        cout << "Deposited: " << _amount << " in Savings Account. New Balance: " << balance << endl;
    }

    void withdraw(int _amount) override
    {
        if (balance >= _amount)
        {
            balance -= _amount;
            cout << "Withdrawn: " << _amount << " from Savings Account. New Balance: " << balance << endl;
        }
        else
        {
            cout << "Insufficient funds in Savings Account!\n";
        }
    }
};

// Current Account
class CurrentAccount : public Account
{
public:
    int balance;

public:
    CurrentAccount()
    {
        this->balance = 0;
    }

    void deposit(int _amount) override
    {
        this->balance += _amount;
        cout << "Deposited: " << _amount << " in Current Account. New Balance: " << balance << endl;
    }

    void withdraw(int _amount) override
    {
        if (balance >= _amount)
        {
            balance -= _amount;
            cout << "Withdrawn: " << _amount << " from Current Account. New Balance: " << balance << endl;
        }
        else
        {
            cout << "Insufficient funds in Current Account!\n";
        }
    }
};

// Current Account
class FixedDepositeAccount : public Account
{
public:
    int balance;

public:
    FixedDepositeAccount()
    {
        this->balance = 0;
    }

    void deposit(int _amount) override
    {
        this->balance += _amount;
        cout << "Deposited: " << _amount << " in Current Account. New Balance: " << balance << endl;
    }

    void withdraw(int _amount) override
    {
        throw logic_error("Withdrawal not allowed in Fixed Term Account!");
    }
};

// Bank Client
class BankClient
{
private:
    vector<Account *> accounts;

public:
    BankClient(vector<Account *> _accounts)
    {
        this->accounts = _accounts;
    }

    void processTransaction()
    {
        for (auto &account : accounts)
        {
            account->deposit(500);


            // Here it violates the Open-Close Principal that's why we should not do this type of approach
            if (typeid(*account) == typeid(FixedDepositeAccount))
            {
                cout << "Skipping the withdraw functionality for the Fixed Term Accounts!" << endl;
            }
            else
            {
                account->withdraw(200);
            }
        }
    }
};

int main()
{
    vector<Account *> accounts;
    accounts.push_back(new SavingAccount());
    accounts.push_back(new CurrentAccount());
    accounts.push_back(new FixedDepositeAccount());

    BankClient *bc = new BankClient(accounts);

    bc->processTransaction();
    return 0;
}