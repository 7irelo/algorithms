#include <iostream>

struct student
{
    std::string name;
    double grade;
};

int main(void)
{
    int amount;
    while (true)
    {
        std::cout << std::endl << "How many students do you want to sort by grades: ";
        if (!(std::cin >> amount))
        {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Incorrect entry. Try again" << std::endl;
        }
        else
        {
            break;
        }
    }

    student* students = new student[amount];
    for (int i = 0; i < amount; i++)
    {
        std::cout << "\nStudent " << i + 1 << "'s first name: ";
        std::cin >> students[i].name;
        
        while (true)
        {
            std::cout << students[i].name << "'s grade (Enter num 0 - 100): ";
            if (!(std::cin >> students[i].grade))
            {
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Incorrect entry. Try again" << std::endl;
            }
            else
            {
                break;
            }
        }
    }
    std::cout << "\nGrade Chart\n";
    std::cout << "\n**********************\n";

    for (int i = 0; i < amount - 1; i++)
    {
        for (int j = amount - i; j > 0; j--)
        {
            if (students[j].grade > students[j - 1].grade)
            {
                student temp = students[j];
                students[j] = students[j - 1];
                students[j - 1] = temp;
            }
        }
    }
    for (int i = 0; i < amount; i++)
    {
        std::cout << i + 1 << ". " << students[i].name << ", Grade: " << students[i].grade << '\n';
    }
    std::cout << "\n**********************" << std::endl;
    std::cout << "Press 'Enter' to quit . . .";
    delete[] students;
    std::cin.ignore();
    std::cin.get();
    return 0;
}