// Skeleton code for storage and buffer management

// Assignment 2 - Group 15
// OSU Details : Kunj Kaushikkumar Patel => 934554295 (patekunj@oregonstate.edu)
// OSU Details : Saiyam Maunik Masalia => 934555553 (masalias@oregonstate.edu)

#include <string>
#include <ios>
#include <fstream>
#include <vector>
#include <string.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "classes.h"
using namespace std;

// If ID entered has no record
void id_not_found()
{
    cout << "The ID you entered has no corresponding record. Exiting." << endl;
}

int main(int argc, char *const argv[])
{
    // Create the EmployeeRelation file from Employee.csv
    StorageBufferManager manager("EmployeeRelation");
    manager.createFromFile("Employee.csv");

    // Loop to lookup IDs until user is ready to quit
    int id;
    while (true)
    {
        cout << "Enter an Employee ID you are looking for OR to quit, press 0: ";
        cin >> id;
        if (id == 0)
        {
            cout << "\nOops, It's a ZERO. Exiting." << endl;
            break;
        }

        Record record = manager.findRecordById(id);
        record.id != 0 ? record.print() : id_not_found();
    }

    return 0;
}
