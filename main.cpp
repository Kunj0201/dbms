/* This is a skeleton code for External Memory Sorting, you can make modifications as long as you meet 
   all question requirements*/  

#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include "record_class.h"

using namespace std;

//defines how many blocks are available in the Main Memory 
#define buffer_size 22
fstream fileStream;

vector<Records> buffer; //use this class object of size 22 as your main memory

struct less_than_key
{
    inline bool operator() (const Records& struct1, const Records& struct2)
    {
        return (struct1.emp_record.eid < struct2.emp_record.eid);
    }
};


/***You can change return type and arguments as you want.***/


//PASS 1
//Sorting the buffers in main_memory and storing the sorted records into a temporary file (Runs) 
void Sort_Buffer(){
    std::sort(buffer.begin(), buffer.end(), less_than_key());       // sorting the tuples based on eid
    /*for(int i=0; i<buffer.size(); i++){
        buffer[i].print();
    }*/
    string serializedData;     //making the 1 single string out off all the 22 tuples to write it to the disk in 1 sinlge I/O access
    
    for (const auto& obj : buffer) {
        serializedData += obj.serialize() + "\n"; // Separate objects by newline character
    }
    fileStream.write(serializedData.data(), serializedData.size());     // writing 22 tuples at a time
    
    
    //Remember: You can use only [AT MOST] 22 blocks for sorting the records / tuples and create the runs
    return;
}

//PASS 2
//Use main memory to Merge the Runs 
//which are already sorted in 'runs' of the relation Emp.csv 
void Merge_Runs(){

    //and store the Sorted results of your Buffer using PrintSorted() 
    return;
}

void PrintSorted(){

    //Store in EmpSorted.csv
    return;
}

int main() {

    //Open file streams to read and write
    //Opening out the Emp.csv relation that we want to Sort
    fstream empin;
    empin.open("Emp.csv", ios::in);
   
    //Creating the EmpSorted.csv file where we will store our sorted results
    fstream SortOut;
    SortOut.open("EmpSorted.csv", ios::out | ios::app);

    //1. Create runs for Emp which are sorted using Sort_Buffer()
    
    string fileName = "Temp";
     fileStream.open(fileName, ios::in | ios::out | ios::binary | ios::trunc);
        if (!fileStream) {
            throw runtime_error("Cannot open file: " + fileName);
        }
    while(!empin.eof()){
        for(int i=0; i<22; i++){
            if(!empin.eof()){
                Records a = Grab_Emp_Record(empin);
                buffer.push_back(a);
                //buffer[i].print();
            }
            else {
                break;
            }
        }
        Sort_Buffer();  
        buffer.clear();           //clearing out the buffer for the next run
        //cout << "Break" << endl;
        
    }

    //2. Use Merge_Runs() to Sort the runs of Emp relations 


    //Please delete the temporary files (runs) after you've sorted the Emp.csv

    return 0;
}
