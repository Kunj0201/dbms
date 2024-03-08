/*
// Assignment 4 - Group 15
// OSU Details : Kunj Kaushikkumar Patel => 934554295 (patekunj@oregonstate.edu)
// OSU Details : Saiyam Maunik Masalia => 934555553 (masalias@oregonstate.edu)
*/

/* This is a skeleton code for External Memory Sorting, you can make modifications as long as you meet
   all question requirements*/

#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include "record_class.h"

using namespace std;

// defines how many blocks are available in the Main Memory
#define buffer_size 22
fstream fileStream;

fstream SortOut;

vector<Records> buffer; // use this class object of size 22 as your main memory
vector<int> arr;
int location[19];
int num_records = 0;
int u = 0;
Records write;

struct less_than_key
{
    inline bool operator()(const Records &struct1, const Records &struct2)
    {
        return (struct1.emp_record.eid < struct2.emp_record.eid);
    }
};
string s = "$\n";

/***You can change return type and arguments as you want.***/

// PASS 1
// Sorting the buffers in main_memory and storing the sorted records into a temporary file (Runs)
void Sort_Buffer()
{
    std::sort(buffer.begin(), buffer.end(), less_than_key()); // sorting the tuples based on eid
    /*for(int i=0; i<buffer.size(); i++){
        buffer[i].print();
    }*/
    string serializedData; // making the 1 single string out off all the 22 tuples to write it to the disk in 1 sinlge I/O access

    for (const auto &obj : buffer)
    {
        serializedData += obj.serialize() + "\n"; // Separate objects by newline character
    }
    fileStream.write(serializedData.data(), serializedData.size()); // writing 22 tuples at a time
    fileStream.write(s.data(), s.size());

    // Remember: You can use only [AT MOST] 22 blocks for sorting the records / tuples and create the runs
    return;
}

// PASS 2
// Use main memory to Merge the Runs
// which are already sorted in 'runs' of the relation Emp.csv
void Place(int x)
{
    int a = 0;
    fileStream.seekg(0);
    string line;
    while (a < x)
    {
        getline(fileStream, line, '\n');
        if (line == "$")
        {
            a += 1;
        }
    }
}

void Fetch(int x)
{
    for (int i = 0; i < x; i++)
    {
        string line;
        getline(fileStream, line, '\n');
        // cout << line << endl;
    }
}

void Merge_Runs()
{

    std::sort(buffer.begin(), buffer.end(), less_than_key()); // sorting the buffer
    // buffer[0].print();

    write = buffer[0];

    SortOut << write.serialize() + "\n"; // wriitng the first object to the csv file which is the minimum

    int index;
    int record_number;
    string fileData;
    Records r;

    int target = buffer[0].value(); // to find which tuple was written to the csv file

    auto it = find(arr.begin(), arr.end(), target);
    index = distance(arr.begin(), it); // to jump to the bucket from which the tuple was written to the csv
    Place(index);
    // cout << "Index: " << index << endl;
    location[index] = location[index] + 1; // to track how many tuples have been written from a specific bucket
    // cout << "location[index]: " << location[index] << endl;
    if (index == 18)
    {
        record_number = location[index] % 3; // to jump to a record in a bucket
    }
    else
    {
        record_number = location[index] % 22; // to jump to a record in a bucket
    }
    // cout << "record number: " << record_number << endl;
    Fetch(record_number);

    if (fileStream.eof() || record_number == 0)
    {
        buffer.erase(buffer.begin());
    }
    else
    {
        getline(fileStream, fileData, '\n'); // fetching a new tuple
        // cout << fileData << endl;
        u += 1;

        r = Grab(fileData);
        buffer[0] = r;                 // adding the new tuple to the existing buffer
        arr[index] = r.emp_record.eid; // adding it to the vector which has only eids of the tuple in the buffer
    }

    // buffer[0].print();

    // cout << distance(arr.begin(), it);
    // and store the Sorted results of your Buffer using PrintSorted()
    return;
}

void PrintSorted()
{

    // Store in EmpSorted.csv
    return;
}

int main()
{

    // Open file streams to read and write
    // Opening out the Emp.csv relation that we want to Sort
    fstream empin;
    empin.open("Emp.csv", ios::in);

    // Creating the EmpSorted.csv file where we will store our sorted results
    SortOut.open("EmpSorted.csv", ios::out | ios::app);

    // 1. Create runs for Emp which are sorted using Sort_Buffer()

    string fileName = "Temp";
    fileStream.open(fileName, ios::in | ios::out | ios::binary | ios::trunc);
    if (!fileStream)
    {
        throw runtime_error("Cannot open file: " + fileName);
    }
    int l = 0;
    while (!empin.eof())
    {

        int y = 0;
        for (int i = 0; i < 22; i++)
        {
            if (!empin.eof())
            {
                Records a = Grab_Emp_Record(empin);
                buffer.push_back(a);
                num_records += 1;
                y += 1;
                // buffer[i].print();
            }
            else
            {
                break;
            }
        }
        Sort_Buffer();
        // cout << y << endl;
        location[l] = y;
        l += 1;
        buffer.clear(); // clearing out the buffer for the next run
        // cout << "Break" << endl;
    }

    if (!fileStream.is_open())
    {
        cerr << "Error: Unable to open the file." << endl;
        return 1;
    }
    buffer.clear();

    // 2. Use Merge_Runs() to Sort the runs of Emp relations
    for (int i = 0; i < 19; i++)
    {
        Place(i);
        string fileData, word;
        Records r;
        if (getline(fileStream, fileData, '\n'))
        {
            r = Grab(fileData);
            // r.print();
        }
        buffer.push_back(r);
        arr.push_back(r.emp_record.eid);
    }

    while (u < num_records - 19)
    {
        Merge_Runs();
    }

    std::sort(buffer.begin(), buffer.end(), less_than_key());
    string serializedData; // making the 1 single string out off all the 22 tuples to write it to the disk in 1 sinlge I/O access

    for (const auto &obj : buffer)
    {
        serializedData += obj.serialize() + "\n"; // Separate objects by newline character
    }
    SortOut.write(serializedData.data(), serializedData.size()); // writing 22 tuples at a time

    // cout << u << endl;
    // cout << location[18];
    SortOut.close();
    // cout << location[18];
    // buffer[1].print();

    // Please delete the temporary files (runs) after you've sorted the Emp.csv
    const char *tempFileNameToDelete = "Temp";
    if (remove(tempFileNameToDelete) != 0)
    {
        cerr << "Error: Unable to delete the temporary file. Reason: " << strerror(errno) << endl;
        return 1;
    }
    else
    {
        cout << "Temporary file deleted successfully." << endl;
    }

    return 0;
}
