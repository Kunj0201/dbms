/*
// Assignment 3 - Group 16
// OSU Details : Kunj Kaushikkumar Patel => 934554295 (patekunj@oregonstate.edu)
// OSU Details : Saiyam Maunik Masalia => 934555553 (masalias@oregonstate.edu)
*/

#include <ios>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cmath>

#include "classes.h"
using namespace std;

int main()
{
    LinearHashIndex employee_index("EmployeeIndex");
    employee_index.createFromFile("Employee.csv");

    while (true)
    {
        cout << "\nEnter an Employee ID to search, or enter '0' to quit: ";
        string input;
        cin >> input;

        if (input == "0")
        {
            cout << "Exiting." << endl;
            break;
        }

        try
        {
            long int id = stol(input);
            Record employee = employee_index.findRecordById(id);
            employee.print();
        }
        catch (const invalid_argument &e)
        {
            cerr << "Invalid Employee ID. Input again." << endl;
        }
        catch (const runtime_error &e)
        {
            cerr << e.what() << endl;
        }
    }

return 0;
}
