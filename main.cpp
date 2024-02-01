/*
Skeleton code for storage and buffer management
*/
//  This assignment is perfomed by Sri Sahith Reddy Kuncharam and Swar GirishBhai Patel.
// OSU ID : 934498290  sahith
// OSU ID : 934408982  swar patel
// ONID ID :  kunchars@oregonstate.edu and pateswar@oregonstate.edu 

#include <string>
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

// This function is used to print the error message when the record is not found
void error_message()
{
    printf("Record not found\n");
}

int main(int argc, char* const argv[]) {
    // Create the EmployeeRelation file from Employee.csv
    StorageBufferManager manager("EmployeeRelation");
    manager.createFromFile("Employee.csv");
    
    // Loop to lookup IDs until user is ready to quit
    int id;
    while (true) {
        cout << "Enter an Employee ID to search for (or -1 to quit): ";
        cin >> id;
        if (id == -1) break;
        
        Record record = manager.findRecordById(id);
        // if (record.id != -1) {
        //     record.print();
        // } else {
        //     cout << "Record not found." << endl;
        // }
        record.id != -1 ? record.print() : error_message();
    }
    
    return 0;
}



// int main(int argc, char* const argv[]) {

//     // Create the EmployeeRelation file from Employee.csv
//     StorageBufferManager manager("EmployeeRelation");
//     manager.createFromFile("Employee.csv");
    
//     // Loop to lookup IDs until user is ready to quit
    
//     int idd;

//     while (true)
//     {
//         cout << "Please Provide the Employee ID to fetch the record / to quit enter -1: ";
// cin >> idd;
// cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any remaining characters in the buffer


//         Record rr = manager.findRecordById(idd);

//         rr.id != -1 ? rr.print() : error_message();

//         if(idd == -1)
//             break;
            

//     }
    

//     return 0;
// }
