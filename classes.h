#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <bitset>
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;

class Record
{
public:
    int id, manager_id;
    std::string bio, name;

    Record(vector<std::string> row)
    {
        id = stoi(row[0]);
        name = row[1];
        bio = row[2];
        manager_id = stoi(row[3]);
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
    const int BLOCK_SIZE = 4096; // initialize the  block size allowed in main memory according to the question

    // You may declare variables based on your need
    int numRecords = 0;
    ofstream ofs;
    vector<std::string> *st = new vector<std::string>(4096);
    vector<std::string> *end = st + 4096;
    int memory = 0;
    
    

    // Insert new record
    void insertRecord(Record record)
    {
        // Making sure
        
        int offset = 0;
        string delimiter = "$";

        stringstream ss;
        ss << record.id;
        string a = ss.str();

        st->push_back(a);
        offset += sizeof(a);

        st->push_back(delimiter);
        offset += sizeof(delimiter);

        st->push_back(record.name);
        offset += sizeof(record.name);

        st->push_back(delimiter);
        offset += sizeof(delimiter);

        st->push_back(record.bio);
        offset += sizeof(record.bio);

        st->push_back(delimiter);
        offset += sizeof(delimiter); 

        
        ss << record.manager_id;
        string b = ss.str();

        st->push_back(b);
        offset += sizeof(b);

        st->push_back(delimiter);
        offset += sizeof(delimiter);

        
        
        ss << offset;
        string c = ss.str();
        end->push_back(c);
        end = end - sizeof(c);
        
        memory = memory + offset + sizeof(c);


        // No records written yet
        /*if (numRecords == 0) {
            // Initialize first block

        }*/
        // Add record to the block

        // Take neccessary steps if capacity is reached (you've utilized all the blocks in main memory)
    }

public:
    string fileName;
    StorageBufferManager(string newfileName)
    {
        fileName = newfileName; //+ ".csv";
            numRecords = 0;
        ofs.open(fileName, ios::out);
    }

    ~StorageBufferManager()
    {
        ofs.close();
    }

    /* {

        //initialize your variables

        // Create your EmployeeRelation file


    }
    */
    // Read csv file (Employee.csv) and add records to the (EmployeeRelation)
    void createFromFile(string csvFName)
    {

        ifstream ifs(csvFName);
        string str;

        while (getline(ifs, str))
        {
            vector<string> row;
            stringstream strstream(str);
            string cell;

            while (getline(strstream, cell, ','))
            {
                row.push_back(cell);
            }

            Record record(row);
            if(4096 - memory > sizeof(record) + 32){
                insertRecord(record);
                numRecords++;
            }
            else {
                vector<std::string> *st = new vector<std::string>(4096);
                vector<std::string> *end = st + 4096;
                memory = 0;
                insertRecord(record);

            }
            
            

            /*
            if (numRecords < 15){
                insertRecord(record);
                numRecords++;
            }
            else {
                cout<<"Page limit Reached";
            }*/
        }
        ifs.close();
    }

    // Given an ID, find the relevant record and print it
   /* Record findRecordById(int id)
    {
    }*/
};
