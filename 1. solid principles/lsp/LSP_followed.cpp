#include <iostream>
#include <vector>
using namespace std;

class DepositOnlyAccount
{
public:
    virtual void deposit(int _amount) = 0;
};

class WithdrawableAccount : public DepositOnlyAccount
{
public:
    virtual void withdraw(int _amount) = 0;
};

class SavingAccount : public WithdrawableAccount
{
private:
    int balance;

public:
    SavingAccount()
    {
        balance = 0;
    }

private:
    void deposit(int amount)
    {
        balance += amount;
        cout << "Deposited: " << amount << " in Saving Account. New Balance: " << balance << endl;
    }

    void withdraw(int amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
            cout << "Withdrawn: " << amount << " from CurrenSaving Account. New Balance: " << balance << endl;
        }
        else
        {
            cout << "Insufficient funds in CurrenSaving Account!\n";
        }
    }
};

class CurrentAccount : public WithdrawableAccount
{
private:
    int balance;

public:
    CurrentAccount()
    {
        balance = 0;
    }

private:
    void deposit(int amount)
    {
        balance += amount;
        cout << "Deposited: " << amount << " in Current Account. New Balance: " << balance << endl;
    }

    void withdraw(int amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
            cout << "Withdrawn: " << amount << " from Current Account. New Balance: " << balance << endl;
        }
        else
        {
            cout << "Insufficient funds in Current Account!\n";
        }
    }
};

class FixedTermAccount : public DepositOnlyAccount
{
private:
    int balance;

public:
    FixedTermAccount()
    {
        balance = 0;
    }

private:
    void deposit(int amount)
    {
        balance += amount;
        cout << "Deposited: " << amount << " in Fixed Term Account. New Balance: " << balance << endl;
    }
};

class BankClient
{
private:
    vector<DepositOnlyAccount *> depositOnlyAccounts;
    vector<WithdrawableAccount *> withdrawableAccounts;

public:
    BankClient(vector<WithdrawableAccount *> _withdrawableAccounts,
               vector<DepositOnlyAccount *> _depositOnlyAccounts)
    {
        this->depositOnlyAccounts = _depositOnlyAccounts;
        this->withdrawableAccounts = _withdrawableAccounts;
    }

    void processTransactions()
    {
        for (auto &account : withdrawableAccounts)
        {
            account->deposit(500);
            account->withdraw(200);
        }

        for (auto &account : depositOnlyAccounts)
        {
            account->deposit(500);
        }
    }
};

int main()
{
    vector<WithdrawableAccount *> withdrawableAccounts;
    withdrawableAccounts.push_back(new SavingAccount());
    withdrawableAccounts.push_back(new CurrentAccount());

    vector<DepositOnlyAccount *> depositOnlyAccounts;
    depositOnlyAccounts.push_back(new FixedTermAccount());

    BankClient *bc = new BankClient(withdrawableAccounts, depositOnlyAccounts);
    bc->processTransactions();

    return 0;
}