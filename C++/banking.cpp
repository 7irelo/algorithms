#include <iostream>
#include <iomanip>

void show_balance(double balance);
double deposit(void);
double withdraw(double balance);


int main(void)
{
    double balance = 0;
    int choice = 0;

    do
    {
        std::cout << "****STANDARD BANK****\n";
        std::cout << "**Enter Your Choice**\n";
        std::cout << "*********************\n";
        std::cout << "1. Show Balance\n";
        std::cout << "2. Deposit Money\n";
        std::cout << "3. Withdraw Money\n";
        std::cout << "4. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        std::cin.clear();
        fflush(stdin);

        switch(choice)
        {
            case 1: show_balance(balance);
                    break;
            case 2: balance += deposit();
                    show_balance(balance);
                    break;
            case 3: balance = withdraw(balance);
                    show_balance(balance);
                    break;
            case 4: std::cout << "***THANK YOU***\n";
                    break;
            default: std::cout << "Invalid Choice\n";
        }
        std::cout << '\n';
    }
    while (choice != 4);
    return 0;
}
void show_balance(double balance)
{
    std::cout << "Your balance is: R" << std::setprecision(2) << std::fixed << balance << '\n';
}
double deposit(void)
{
    double deposit;
    do
    {   std::cout << "Deposit Amount: ";
        std::cin >> deposit;
    }
    while (deposit < 1);
    return deposit;
}
double withdraw(double balance)
{
    double withdraw;
    do
    {   std::cout << "Withdraw Amount: ";
        std::cin >> withdraw;
    }
    while (withdraw > balance);
    balance -= withdraw;
    return balance;
}