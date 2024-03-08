/*
// Assignment 4 - Group 15
// OSU Details : Kunj Kaushikkumar Patel => 934554295 (patekunj@oregonstate.edu)
// OSU Details : Saiyam Maunik Masalia => 934555553 (masalias@oregonstate.edu)
*/

/* This is a skeleton code for External Memory Sorting, you can make modifications as long as you meet
   all question requirements*/
/* This record_class.h contains the class Records, which can be used to store tuples form Emp.csv (stored
in the EmpRecord).
*/
#include <bits/stdc++.h>

using namespace std;

class Records
{
public:
    struct EmpRecord
    {
        int eid;
        string ename;
        int age;
        double salary;
    } emp_record;

    void print()
    {
        cout << emp_record.eid << endl;
    }

    int value()
    {
        return emp_record.eid;
    }

    /*** You can add more variables if you want below ***/

    bool operator<(const EmpRecord &other) const
    {
        return emp_record.eid < other.eid;
    }

    string serialize() const
    {
        stringstream ss;
        ss << emp_record.eid << "," << emp_record.ename << "," << emp_record.age << "," << emp_record.salary;
        return ss.str();
    }

    int no_values = 0;             // You can use this to check if you've don't have any more tuples
    int number_of_emp_records = 0; // Tracks number of emp_records you have on the buffer
};

// Grab a single block from the Emp.csv file and put it inside the EmpRecord structure of the Records Class
Records Grab_Emp_Record(fstream &empin)
{
    string line, word;
    Records emp;
    // grab entire line
    if (getline(empin, line, '\n'))
    {
        // turn line into a stream
        stringstream s(line);
        // gets everything in stream up to comma
        getline(s, word, ',');
        emp.emp_record.eid = stoi(word);
        getline(s, word, ',');
        emp.emp_record.ename = word;
        getline(s, word, ',');
        emp.emp_record.age = stoi(word);
        getline(s, word, ',');
        emp.emp_record.salary = stod(word);

        return emp;
    }
    else
    {
        emp.no_values = -1;
        return emp;
    }
}

Records Grab(string line)
{
    stringstream ss(line);
    string word;
    Records emp;
    getline(ss, word, ',');
    emp.emp_record.eid = stoi(word);
    getline(ss, word, ',');
    emp.emp_record.ename = word;
    getline(ss, word, ',');
    emp.emp_record.age = stoi(word);
    getline(ss, word, ',');
    emp.emp_record.salary = stod(word);

    return emp;
}
