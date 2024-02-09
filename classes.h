// Skeleton code for storage and buffer management

// Assignment 2 - Group 15
// OSU Details : Kunj Kaushikkumar Patel => 934554295 (patekunj@oregonstate.edu)
// OSU Details : Saiyam Maunik Masalia => 934555553 (masalias@oregonstate.edu)

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>
using namespace std;

class Record
{
public:
    int id, manager_id;
    string bio, name;

    Record(vector<string> fields)
    {
        id = stoi(fields[0]);
        name = fields[1];
        bio = fields[2];
        manager_id = stoi(fields[3]);
    }

    void print()
    {
        cout << "\tID: " << id << "\n";
        cout << "\tNAME: " << name << "\n";
        cout << "\tBIO: " << bio << "\n";
        cout << "\tMANAGER_ID: " << manager_id << "\n";
    }
};

class StorageBufferManager
{

private:
    const int BLOCK_SIZE = 4096; // initialize the block size allowed in main memory according to the question
    const int MAX_PAGES = 3;

    string fileName;
    fstream fileStream;
    int lenUsedIndex, currentPageNum;
    vector<vector<char>> page;

    // Add record to the block
    void insertRecord(Record record)
    {
        // Convesion to string of the record data
        string tuple = to_string(record.id) + "," + record.name + "," + record.bio + "," + to_string(record.manager_id) + "\n";

        // Size of the Record
        int tupleSize = tuple.size();

        // If adding a new record would exceed the specified block size, save the current page to the file

        if (lenUsedIndex + tupleSize > BLOCK_SIZE)
        {
            fileStream.write(page[currentPageNum].data(), lenUsedIndex);
            lenUsedIndex = 0;
            currentPageNum = (currentPageNum + 1) % MAX_PAGES;
        }

        // Copy the new tuple's data into the current page and update the current memory/storage of a page utilizied
        copy(tuple.begin(), tuple.end(), page[currentPageNum].begin() + lenUsedIndex);
        lenUsedIndex = lenUsedIndex + tupleSize;
    }

public:
    StorageBufferManager(string NewFileName)
    {
        fileName = NewFileName;
        lenUsedIndex = 0;
        currentPageNum = 0;

        page.resize(MAX_PAGES, vector<char>(BLOCK_SIZE));
        fileStream.open(fileName, ifstream::in | ifstream::out | ifstream::binary | ifstream::trunc);
    }

    void createFromFile(string csvFName)
    {
        ifstream csvFile(csvFName);

        string loaded_data;
        while (getline(csvFile, loaded_data))
        {
            vector<string> fields;
            stringstream ss(loaded_data);
            string field;

            // Go through through each line of the CSV, extracting fields separated by commas
            while (getline(ss, field, ','))
            {
                // Extract a field from loaded_data, append it to fields vector
                fields.push_back(field);
            }

            Record record(fields);
            insertRecord(record);
        }

        // Leftover Records
        if (lenUsedIndex > 0)
        {
            fileStream.write(page[currentPageNum].data(), lenUsedIndex);
        }

        csvFile.close();
    }

    // Given an ID, find the relevant record and print it
    Record
    findRecordById(int id)
    {
        // Fstream pointer pointing towards the beginning
        fileStream.seekg(0, ifstream::beg);

        string loaded_data;
        while (getline(fileStream, loaded_data))
        {
            stringstream ss(loaded_data); // Parsing CSV using SS
            vector<string> fields;
            string field;

            // Get all the fields and storing in proper vector
            while (getline(ss, field, ','))
            {
                fields.push_back(field);
            }

            Record record(fields); // Use Vector to make a "Record record"

            // Does the "Record record" contain the ID asked by user
            if (record.id == id)
            {
                return record; // O/p the record for corresponding ID if matched
            }
        }
        return Record(vector<string>()); // O/p nothing if otherwise
    }
};
