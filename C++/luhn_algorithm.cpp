#include <iostream>
#include <istream>

int get_digit(const int number);
int sum_odd_digits(const std::string cardNumber);
int sum_even_digits(const std::string cardNumber);

int main(void)
{
    int result = 0;
    std::string cardNumber;
    std::cout << "\nThis is an algorithm to confirm Credit Card Numbers\n";
    std::cout << "Enter card Number: ";
    std:getline(std::cin, cardNumber);

    result = sum_odd_digits(cardNumber) + sum_even_digits(cardNumber);

    switch (result % 10)
    {
    case 0: std::cout << "Valid!\n";
        break;
    
    default: std::cout << "Invalid!\n";
        break;
    }
    return 0;
}
int get_digit(const int number)
{
    return number % 10 + (number / 10 % 10);
}
int sum_odd_digits(const std::string cardNumber)
{
    int sum = 0;
    for (int i = cardNumber.size() - 1; i >= 0; i -=2)
    {
        sum += cardNumber[i] - '0';
    }
    return sum;
}
int sum_even_digits(const std::string cardNumber)
{
    int sum = 0;
    for (int i = cardNumber.size() - 2; i >= 0; i -=2)
    {
        sum += get_digit((cardNumber[i] - '0') * 2);
    }
    return sum;
}