/* This is a skeleton code for Optimized Merge Sort, you can make modifications as long as you meet
   all question requirements*/

#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "record_class.h"

using namespace std;

// defines how many blocks are available in the Main Memory
#define buffer_size 22
fstream fileStreamEmp;
fstream fileStreamDept;
fstream joinout;
Records write;
int buffer = 0;

int locationEmp[19];
int num_records_emp = 0;
int runs_emp = 0;

int location_dept[19];
int num_records_dept = 0;
int run_dept = 0;

struct less_than_key
{
    inline bool operator()(const Records &struct1, const Records &struct2)
    {
        return (struct1.emp_record.eid < struct2.emp_record.eid);
    }
};

struct less_than_key_dept
{
    inline bool operator()(const Records &struct1, const Records &struct2)
    {
        return (struct1.dept_record.managerid < struct2.dept_record.managerid);
    }
};
string s = "$\n";

void Place(int x, fstream &point)
{
    int a = 0;
    point.seekg(0);
    string line;
    while (a < x)
    {
        getline(point, line, '\n');
        if (line == "$")
        {
            a += 1;
        }
    }
}

void Fetch(int x, fstream &point)
{
    for (int i = 0; i < x; i++)
    {
        string line;
        getline(point, line, '\n');
        // cout << line << endl;
    }
}

vector<Records> buffers; // use this class object of size 22 as your main memory
vector<Records> second;

/***You can change return type and arguments as you want.***/

// Sorting the buffers in main_memory and storing the sorted records into a temporary file (runs)
void Sort_Buffer_Emp()
{

    std::sort(buffers.begin(), buffers.end(), less_than_key()); // sorting the tuples based on eid
    /*for(int i=0; i<buffer.size(); i++){
        buffer[i].print();
    }*/
    string serializedData; // making the 1 single string out off all the 22 tuples to write it to the disk in 1 sinlge I/O access

    for (const auto &obj : buffers)
    {
        serializedData += obj.serialize() + "\n"; // Separate objects by newline character
    }
    fileStreamEmp.write(serializedData.data(), serializedData.size()); // writing 22 tuples at a time
    fileStreamEmp.write(s.data(), s.size());

    // Remember: You can use only [AT MOST] 22 blocks for sorting the records / tuples and create the runs
    return;
}

void Sort_Buffer_Dept()
{

    std::sort(buffers.begin(), buffers.end(), less_than_key_dept()); // sorting the tuples based on eid
    /*for(int i=0; i<buffer.size(); i++){
        buffer[i].print();
    }*/
    string Data; // making the 1 single string out off all the 22 tuples to write it to the disk in 1 sinlge I/O access

    for (const auto &ob : buffers)
    {
        Data += ob.serializeDept() + "\n"; // Separate objects by newline character
    }
    fileStreamDept.write(Data.data(), Data.size()); // writing 22 tuples at a time
    // fileStreamDept.write(s.data(), s.size());

    // Remember: You can use only [AT MOST] 22 blocks for sorting the records / tuples and create the runs
    return;
}

// Prints out the attributes from empRecord and deptRecord when a join condition is met
// and puts it in file Join.csv
void PrintJoin()
{

    return;
}

// Use main memory to Merge and Join tuples
// which are already sorted in 'runs' of the relations Dept and Emp
void Merge_Join_Runs()
{

    bool z = true;
    bool v = true;
    int p = 0;
    int count = 1;
    int x = 0;
    int y = 0;
    int index;

    vector<int> arrEmp;
    // vector<int> arrDept;

    // From the Dept file
    Place(0, fileStreamDept);
    Fetch(0, fileStreamDept);
    string n, m;
    Records q;
    if (getline(fileStreamDept, n, '\n'))
    {
        if (n != "$")
        {
            q = Grab_Dept(n);
            // arrDept.push_back(q.dept_record.managerid);
        }
    }
    buffers.push_back(q);

    // From the Bucket

    Place(0, fileStreamEmp);
    Fetch(0, fileStreamEmp);
    string fileData, word;
    Records r;
    if (getline(fileStreamEmp, fileData, '\n') && v)
    {
        if (fileData != "$")
        {
            r = Grab_Emp(fileData);
            y += 1;
            arrEmp.push_back(r.emp_record.eid);
            // r.printEmp();
        }
        else
        {
            v = false;
        }
    }
    second.push_back(r);

    // From the second bucket
    string filevalue, letter;
    Records k;
    Place(1, fileStreamEmp);
    Fetch(0, fileStreamEmp);
    if (getline(fileStreamEmp, filevalue, '\n') && z)
    {
        if (filevalue != "$")
        {
            k = Grab_Emp(filevalue);
            x += 1;
            arrEmp.push_back(k.emp_record.eid);
        }
        else
        {
            z = false;
        }
    }
    second.push_back(k);

    

    for (int j = 0; j < 28; j++)
    {
        

        for (int d = 0; d < 42; d++)
        {
            std::sort(second.begin(), second.end(), less_than_key());

            //cout << count << endl;

            int h = second[0].valueEmp();
            int s = buffers[0].valueDept();
            //cout <<"Dept: " << s << endl << "Emp: " << h << endl;
            //cout << "This is the count:" << count << endl;
            if (s == h)
            {
                string a = second[0].serialEmp();
                string b = buffers[0].serialDep();

                b = b + a;

                //cout << b << endl << a << endl;

                joinout << b << "\n";
                //cout << "first_1" << endl;

                Place(0, fileStreamDept);
                Fetch(count, fileStreamDept);
                count += 1;
                string n, m;
                Records q;
                if (getline(fileStreamDept, n, '\n'))
                {
                    if (n != "$")
                    {
                        q = Grab_Dept(n);
                        buffers[0] = q;
                        // arrDept.push_back(q.dept_record.managerid);
                    }
                }
                
                
            }else if (h < s)
            {
                int target = h; // to find which tuple was written to the csv file
                //cout << "Hey";
                auto it = find(arrEmp.begin(), arrEmp.end(), target);
                index = distance(arrEmp.begin(), it); // to jump to the bucket from which the tuple was written to the csv

                
                //cout << s << "\t" << h << "\t" << index << endl;
                locationEmp[index] = locationEmp[index] + 1;
                int record_number_emp;
               // cout << "Index:" << index << endl;
                if (index == 1 && locationEmp[index] < 16)
                {
                    Place(index, fileStreamEmp);
                    record_number_emp = locationEmp[index] % 8;
                    //cout << "Olaaa" << endl;
                }
                else{
                    if(index == 1){
                        Place(index-1, fileStreamEmp);
                        record_number_emp = locationEmp[index-1] % 22;
                        second.erase(second.begin());
                        //cout << "Heyoooooo" << endl;
                    }
                    else{
                        Place(index, fileStreamEmp);
                        record_number_emp = locationEmp[index] % 22;
                    }
                }
                Fetch(record_number_emp, fileStreamEmp);

                string fil, le;
                Records k;

                getline(fileStreamEmp, fil, '\n');
                if(fil != "$"){
                    k = Grab_Emp(fil);
                    x += 1;
                    arrEmp[index] = k.valueEmp();
                    second[0] = k;
                    cout << "DBMS";
                }
                
            }else if(h > s){
                Place(0, fileStreamDept);
                Fetch(count, fileStreamDept);
                count += 1;
                string n, m;
                Records q;
                if (getline(fileStreamDept, n, '\n'))
                {
                    if (n != "$")
                    {
                        q = Grab_Dept(n);
                        buffers[0] = q;
                        // arrDept.push_back(q.dept_record.managerid);
                    }
                }
                cout << "ECC";
                
            }
        }

        // Continue from here
        // and store the Joined new tuples using PrintJoin()
        return;
    }
}

int main()
{

    // Open file streams to read and write
    // Opening out two relations Emp.csv and Dept.csv which we want to join
    fstream empin;
    fstream deptin;
    empin.open("Emp.csv", ios::in);
    deptin.open("Dept.csv", ios::in);

    string fileName = "Temp";
    fileStreamEmp.open(fileName, ios::in | ios::out | ios::binary | ios::trunc);
    if (!fileStreamEmp)
    {
        throw runtime_error("Cannot open file: " + fileName);
    }

    string fileNameDept = "TempDept";
    fileStreamDept.open(fileNameDept, ios::in | ios::out | ios::binary | ios::trunc);
    if (!fileStreamDept)
    {
        throw runtime_error("Cannot open file: " + fileNameDept);
    }
    // 1. Create runs for Dept and Emp which are sorted using Sort_Buffer()
    int l = 0;
    while (!empin.eof())
    {

        int y = 0;
        for (int i = 0; i < 22; i++)
        {
            if (num_records_emp <= 29)
            {
                Records a = Grab_Emp_Record(empin);
                buffers.push_back(a);
                num_records_emp += 1;
                y += 1;
                // buffers[i].printEmp();
            }
            else
            {
                break;
            }
        }
        runs_emp += 1;
        Sort_Buffer_Emp();
        // cout << y << endl;
        locationEmp[l] = y;
        l += 1;
        buffers.clear(); // clearing out the buffer for the next run
        // cout << empin.eof() << endl;
    }

    int z = 0;

    int y = 0;
    for (int j = 0; j < 22; j++)
    {
        if (!deptin.eof())
        {
            Records a = Grab_Dept_Record(deptin);
            buffers.push_back(a);
            num_records_dept += 1;
            y += 1;
            // buffers[j].printDept();
        }
        else
        {
            break;
        }
    }
    run_dept += 1;
    Sort_Buffer_Dept();
    // cout << y << endl;
    location_dept[z] = y;
    z += 1;
    buffers.clear(); // clearing out the buffer for the next run
    // cout << "Break" << endl;

    // Creating the Join.csv file where we will store our joined results

    joinout.open("Join.csv", ios::out | ios::app);
    buffers.clear();
    fileStreamDept.seekg(0);
    fileStreamEmp.seekg(0);

    Merge_Join_Runs();

    // 2. Use Merge_Join_Runs() to Join the runs of Dept and Emp relations

    // Please delete the temporary files (runs) after you've joined both Emp.csv and Dept.csv

    return 0;
}
