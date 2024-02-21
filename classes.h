/*
// Assignment 3 - Group 16
// OSU Details : Kunj Kaushikkumar Patel => 934554295 (patekunj@oregonstate.edu)
// OSU Details : Saiyam Maunik Masalia => 934555553 (masalias@oregonstate.edu)
*/

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <bitset>
#include <math.h>
#include <fstream>
#include <stdexcept>
#include <bits/stdc++.h>

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

class LinearHashIndex
{

private:
    const int BLOCK_SIZE = 4096;
    const double MAX = 0.70;

    vector<int> blockDirectory; // Map the least-significant-bits of h(id) to a bucket location in EmployeeIndex (e.g., the jth bucket)
                                // can scan to correct bucket using j*BLOCK_SIZE as offset (using seek function)
                                // can initialize to a size of 256 (assume that we will never have more than 256 regular (i.e., non-overflow) buckets)
    int n = 0;                  // The number of indexes in blockDirectory currently being used
    int i = 0;                  // The number of least-significant-bits of h(id) to check. Will need to increase i once n > 2^i
    int numRecords = 0;         // Records currently in index. Used to test whether to increase n
    int nextFreeBlock;          // Next place to write a bucket. Should increment it by BLOCK_SIZE whenever a bucket is written to EmployeeIndex
    string fName;               // Name of index file
    int sizeOfRecords = 0;

    void insertRecord(Record record)
    {
        string block;
        fstream IndexFile;
        IndexFile.open(fName, ios::in | ios::out | ios_base::binary);

        // Check if any data exists already
        if (numRecords == 0)
        {
            n = 4;
            i = 2;
            blockDirectory.push_back(0);
            blockDirectory.push_back(1);
            blockDirectory.push_back(2);
            blockDirectory.push_back(3);

            nextFreeBlock = 4;
            for (int j = 0; j < 4; ++j)
            {
                IndexFile.seekg(j * BLOCK_SIZE);
                IndexFile << "00" << endl
                          << "$";
            }
            sizeOfRecords = 6;
        }

        int HashKey = hashing(record.id);
        int point = blockDirectory[HashKey];
        int overflow_id, sizeB, sizeR;
        string overLoadStr, dataStr;

        // Read the the index file
        IndexFile.seekg(point * BLOCK_SIZE);
        getline(IndexFile, block, '$');
        stringstream IFStream(block);
        IFStream >> overflow_id;

        while (overflow_id > 0)
        {
            point = overflow_id;
            IndexFile.seekg(point * BLOCK_SIZE);
            getline(IndexFile, block, '$');
            stringstream IFStream(block);
            IFStream >> overflow_id;
        }

        IndexFile.seekp(point * BLOCK_SIZE);
        sizeB = block.length();
        dataStr = to_string(record.id) + "," + record.name + "," + record.bio + "," + to_string(record.manager_id);
        sizeR = dataStr.length();

        if (sizeB + sizeR <= BLOCK_SIZE)
        {
            IndexFile.seekp(point * BLOCK_SIZE);
            IndexFile << block << dataStr << endl
                      << "$";
            sizeOfRecords += sizeR;
            numRecords++;
        }
        else
        {
            IndexFile.seekg(point * BLOCK_SIZE);
            overflow_id = nextFreeBlock++;
            overLoadStr = to_string(overflow_id);
            if (overLoadStr.length() == 1)
            {
                overLoadStr = "0" + overLoadStr;
            }
            point = overflow_id;
            IndexFile << overLoadStr << endl;
            IndexFile.seekp(point * BLOCK_SIZE);
            IndexFile << "00" << endl
                      << dataStr << endl
                      << "$";
            sizeOfRecords += sizeR;
            numRecords++;
        }

        if (sizeOfRecords / n >= (BLOCK_SIZE * MAX))
        {
            int newIndex;
            if (n >= pow(2, i) - 1)
            {
                i++;
            }

            newIndex = n & ~(~0 << i - 1);
            n++;

            blockDirectory.push_back(nextFreeBlock++);
            IndexFile.seekp((nextFreeBlock - 1) * BLOCK_SIZE);

            IndexFile << "00" << endl
                      << "$";
            CreateOverflowBlock(IndexFile, newIndex);
        }

        return;
    }

    void CreateOverflowBlock(fstream &employeeIndexFile, int point)
    {
        string currentDataB, newB, recordTuple, cell;
        vector<string> field;
        int overload = 1;
        int indexP = blockDirectory[point];

        while (overload > 0)
        {
            newB = "";
            field.clear();

            employeeIndexFile.seekg(indexP * BLOCK_SIZE);

            getline(employeeIndexFile, currentDataB, '$');

            stringstream ss(currentDataB);
            ss >> overload;

            currentDataB = currentDataB.substr(3, currentDataB.length());

            string overLoadStr = to_string(overload);

            if (overLoadStr.length() == 1)
            {
                overLoadStr = "0" + overLoadStr;
            }
            newB += overLoadStr + "\n";
            stringstream line(currentDataB);
            while (getline(line, recordTuple))
            {
                stringstream lineSS(recordTuple);

                getline(lineSS, cell, ',');
                field.push_back(cell);
                getline(lineSS, cell, ',');
                field.push_back(cell);
                getline(lineSS, cell, ',');
                field.push_back(cell);
                getline(lineSS, cell, ',');
                field.push_back(cell);

                Record employee(field);
                if (employee.id != 0)
                {
                    if (point != hashing(employee.id))
                    {
                        numRecords--;
                        insertRecord(employee);
                    }
                    else
                    {
                        newB += recordTuple + "\n";
                    }
                }
                field.clear();
            }
            newB += "$";
            employeeIndexFile.seekp(indexP * BLOCK_SIZE);
            employeeIndexFile << newB;

            int usedLen = currentDataB.length() - newB.length();
            if (usedLen < 0)
            {
                usedLen = ~usedLen;
            }
            string op(usedLen, '\0');
            employeeIndexFile << op;
            indexP = overload;
        }
    }

    int hashing(int id)
    {
        int num_bits = 16;
        int num_buckets = 1 << num_bits;
        int HashKey = id % num_buckets;

        HashKey &= (1 << i) - 1;
        if (HashKey >= n)
        {
            HashKey &= (1 << (i - 1)) - 1;
        }

        return HashKey;
    }

public:
    LinearHashIndex(string indexFileName)
    {
        n = 4;
        i = 2;
        numRecords = 0;
        nextFreeBlock = 0;
        sizeOfRecords = 0;
        fName = indexFileName;
    }

    void createFromFile(const string &csvFName)
    {
        fstream fs, newFile;
        fs.open(csvFName, ios::in);
        if (!fs.is_open())
        {
            throw runtime_error("Failed to open file: " + csvFName);
        }

        newFile.open(fName, ios::out | ios::trunc | ios::binary);
        if (!newFile.is_open())
        {
            throw runtime_error("Failed to open file: " + fName);
        }
        newFile.close();

        while (true)
        {
            try
            {
                Record employee = searchingR(fs);

                if (employee.id == -1)
                {
                    cout << "Encountered record with id -1, exiting loop." << endl;
                    break;
                }
                insertRecord(employee);
            }
            catch (const runtime_error &e)
            {
                if (string(e.what()) == "End of file reached")
                {
                    break;
                }
            }
        }
        fs.close();
    }

    Record searchingR(fstream &fs)
    {
        string dataTuple;
        vector<string> fields;

        if (!getline(fs, dataTuple))
        {
            throw runtime_error(fs.eof() ? "End of file reached" : "Failed to read the line.");
        }

        istringstream lineSS(dataTuple);
        string empCell;
        for (int i = 0; i < 4; ++i)
        {
            if (!getline(lineSS, empCell, ','))
            {
                throw runtime_error("Failed to read field from the file");
            }
            fields.push_back(empCell);
        }

        return Record(fields);
    }

    // Read csv file and add records to the index
    Record findRecordById(int id)
    {
        bool recordFlag = false;
        vector<string> fields;
        string idTuple, recordB, cellVal;
        int hash = hashing(id);
        int hashedB = blockDirectory[hash];
        int ind = 1;

        fstream fs;
        fs.open(fName, ios::in | ios::binary);
        if (!fs.is_open())
        {
            throw runtime_error("Cannot open specified file");
        }
        while (ind > 0 && id != -1)
        {
            fields.clear();
            fs.seekg(hashedB * BLOCK_SIZE);
            getline(fs, recordB, '$');

            stringstream SSB(recordB);
            SSB >> ind;
            stringstream SSL(recordB);

            while (getline(SSL, idTuple))
            {
                stringstream SSR(idTuple);
                for (int i = 0; i < 4; i++)
                {
                    getline(SSR, cellVal, ',');
                    fields.push_back(cellVal);
                }
                Record employee(fields);

                if (employee.id == id)
                {
                    return employee;
                }
                fields.clear();
                hashedB = ind;
            }
        }
        if (!recordFlag)
        {
            fs.close();
            throw runtime_error("\nThe ID " + to_string(id) + " you entered has no corresponding record.");
        }
    }
};