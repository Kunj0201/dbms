#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>
using namespace std;

class Record {
public:
    int id, manager_id;
    string bio, name;

    Record(vector<string> fields) {
        id = stoi(fields[0]);
        name = fields[1];
        bio = fields[2];
        manager_id = stoi(fields[3]);
    }

    void print() {
        cout << "\tID: " << id << "\n";
        cout << "\tNAME: " << name << "\n";
        cout << "\tBIO: " << bio << "\n";
        cout << "\tMANAGER_ID: " << manager_id << "\n";
    }
};

class StorageBufferManager {

private:
    const int BLOCK_SIZE = 4096; // initialize the block size allowed in main memory according to the question
    const int MAX_BLOCKS_IN_MEMORY = 3;

    string fileName;
    fstream fileStream;
    int currentBlockIndex;
    vector<vector<char>> buffer;
    int currentBufferIndex;

    // Insert new record
    void insertRecord(Record record) {
            // Serialize the record data into a string
        string serialized = to_string(record.id) + "," + record.name + "," + record.bio + "," + to_string(record.manager_id) + "\n";
            
            // Calculate the size of the serialized record

        int recordSize = serialized.size();

            // If inserting this record would exceed the block size, write the current buffer to the file
        if (currentBlockIndex + recordSize > BLOCK_SIZE) {
            fileStream.write(buffer[currentBufferIndex].data(), currentBlockIndex);
            currentBlockIndex = 0;
            currentBufferIndex = (currentBufferIndex + 1) % MAX_BLOCKS_IN_MEMORY;
        }

            // Copy the serialized record data into the current buffer and update the current block index
        copy(serialized.begin(), serialized.end(), buffer[currentBufferIndex].begin() + currentBlockIndex);
        currentBlockIndex += recordSize;
    }

public:
    StorageBufferManager(string NewFileName) {
        fileName = NewFileName;
        currentBlockIndex = 0;
        currentBufferIndex = 0;
        buffer.resize(MAX_BLOCKS_IN_MEMORY, vector<char>(BLOCK_SIZE));

        fileStream.open(fileName, ios::in | ios::out | ios::binary | ios::trunc);
        if (!fileStream) {
            throw runtime_error("Cannot open file: " + fileName);
        }
    }

void createFromFile(string csvFName) {
    ifstream csvFile(csvFName);
    if (!csvFile) {
        throw runtime_error("error in file: " + csvFName);
    }

    string line;
    while (getline(csvFile, line)) {
        size_t pos = 0;
        vector<string> fields;

        while ((pos = line.find(',')) != string::npos) {
            string field = line.substr(0, pos);
            fields.push_back(field);
            line.erase(0, pos + 1);
        }
        fields.push_back(line); // Add the last field

        Record record(fields);
        insertRecord(record);
    }

    // Write the remaining records
    if (currentBlockIndex > 0) {
        fileStream.write(buffer[currentBufferIndex].data(), currentBlockIndex);
    }

    csvFile.close();
}


    // Given an ID, find the relevant record and print it
    Record findRecordById(int id) {
        // Set file stream pointer to the beginning of the file
        fileStream.seekg(0, ios::beg);
        
        string line;
        while (getline(fileStream, line)) {
             // Create a stringstream to parse the comma-separated values in the line
            stringstream ss(line);
            vector<string> fields;
            string field;
            
            // Extract each field from the stringstream and store it in the fields vector
            while (getline(ss, field, ',')) {
                fields.push_back(field);
            }
            
            // Create a Record object from the fields vector
            Record record(fields);

             // Check if the Record object has the desired id
            if (record.id == id) {
                 // Return the Record object if the id matches
                return record;
            }
        }
        // If the id is not found, return an empty Record object
        return Record(vector<string>()); // Not found
    }

};

