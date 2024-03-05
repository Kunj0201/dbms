/* This is a skeleton code for Optimized Merge Sort, you can make modifications as long as you meet 
   all question requirements*/  

#include <bits/stdc++.h>
#include "record_class.h"

using namespace std;

//defines how many blocks are available in the Main Memory 
#define buffer_size 22
fstream fileStreamEmp;
fstream fileStreamDept;
fstream joinout;
Records write;
int buffer = 0;

int locationEmp[19];
int num_records_emp = 0;

int location_dept[19];
int num_records_dept = 0;

struct less_than_key
{
    inline bool operator() (const Records& struct1, const Records& struct2)
    {
        return (struct1.emp_record.eid < struct2.emp_record.eid);
    }
};

struct less_than_key_dept
{
    inline bool operator() (const Records& struct1, const Records& struct2)
    {
        return (struct1.dept_record.managerid < struct2.dept_record.managerid);
    }
};
string s = "$\n";

void Place(int x){
    int a = 0;
    fileStreamEmp.seekg(0);
    string line;
    while(a < x){
        getline(fileStreamEmp, line, '\n');
        if(line == "$"){
            a += 1;
        }
    }
}

void Fetch(int x){
    for(int i=0; i < x; i++){
        string line;
        getline(fileStreamEmp, line, '\n');
        //cout << line << endl;
    }

}

vector<Records> buffers; //use this class object of size 22 as your main memory
vector<Records> second;

/***You can change return type and arguments as you want.***/

//Sorting the buffers in main_memory and storing the sorted records into a temporary file (runs) 
void Sort_Buffer_Emp(){

    std::sort(buffers.begin(), buffers.end(), less_than_key());       // sorting the tuples based on eid
    /*for(int i=0; i<buffer.size(); i++){
        buffer[i].print();
    }*/
    string serializedData;     //making the 1 single string out off all the 22 tuples to write it to the disk in 1 sinlge I/O access
   
    
    for (const auto& obj : buffers) {
        serializedData += obj.serialize() + "\n"; // Separate objects by newline character
    }
    fileStreamEmp.write(serializedData.data(), serializedData.size());     // writing 22 tuples at a time
    fileStreamEmp.write(s.data(), s.size());
    
    //Remember: You can use only [AT MOST] 22 blocks for sorting the records / tuples and create the runs
    return;
}

void Sort_Buffer_Dept(){

    std::sort(buffers.begin(), buffers.end(), less_than_key_dept());       // sorting the tuples based on eid
    /*for(int i=0; i<buffer.size(); i++){
        buffer[i].print();
    }*/
    string Data;     //making the 1 single string out off all the 22 tuples to write it to the disk in 1 sinlge I/O access
   
    
    for (const auto& ob : buffers) {
        Data += ob.serializeDept() + "\n"; // Separate objects by newline character
    }
    fileStreamDept.write(Data.data(), Data.size());     // writing 22 tuples at a time
    //fileStreamDept.write(s.data(), s.size());
    

    //Remember: You can use only [AT MOST] 22 blocks for sorting the records / tuples and create the runs
    return;
}



//Prints out the attributes from empRecord and deptRecord when a join condition is met 
//and puts it in file Join.csv
void PrintJoin() {
    
    return;
}


//Use main memory to Merge and Join tuples 
//which are already sorted in 'runs' of the relations Dept and Emp 
void Merge_Join_Runs(){

    for(int j=0; j<15; j++){
        
        bool z = true;
        bool v = true;
        int x = 0;
        //int y =0;
        for(int f=0; f<22; f++){

            // From the 1st Bucket
            Place(0);
            Fetch(f);
            string fileData, word;
            Records r;
            if(getline(fileStreamEmp, fileData, '\n') && v){
                if(fileData != "$"){
                    r = Grab_Emp(fileData);
                    //y += 1;
                    //r.printEmp();
                }   
                else{
                    v = false;
                }
            }
            second.push_back(r);
            

            //From the second bucket
            string filevalue, letter;
            Records k;
            Place(1);
            Fetch(x);
            if(getline(fileStreamEmp, filevalue, '\n') && z){
                if(filevalue != "$"){
                    k = Grab_Emp(filevalue);
                    x += 1;
                }
                else{
                    z = false;
                }
            }
            else{

            }
            second.push_back(k);

            //buffers[j].printDept();           //Error at this position 
            //second[0].printEmp();

            int s = buffers[j].valueDept();
            int h = second[0].valueEmp();
            int g = second[1].valueEmp();

           // cout << s <<endl << h << endl;

            //cout << (buffers[j].valueDept() == second[0].valueEmp());

            if(s == h){
                string a = second[0].serialEmp();
                string b = buffers[j].serialDep();

                b = b + a;

                cout << b << endl << a << endl;

                joinout << b << "\n";
                cout << "First" << endl;

            }

            if(s == g){
                string a = second[1].serialEmp();
                string b = buffers[j].serialDep();

                b = b + a;

                cout << b << endl << a << endl;

                joinout << b << "\n";
                cout << "Second" << endl;

            }
            second.clear();
        }
        

    }

   

    //and store the Joined new tuples using PrintJoin() 
    return;
}

int main() {

    //Open file streams to read and write
    //Opening out two relations Emp.csv and Dept.csv which we want to join
    fstream empin;
    fstream deptin;
    empin.open("Emp.csv", ios::in);
    deptin.open("Dept.csv", ios::in);

    string fileName = "Temp";
     fileStreamEmp.open(fileName, ios::in | ios::out | ios::binary | ios::trunc);
        if (!fileStreamEmp) {
            throw runtime_error("Cannot open file: " + fileName);
        }

    string fileNameDept = "TempDept";
     fileStreamDept.open(fileNameDept, ios::in | ios::out | ios::binary | ios::trunc);
        if (!fileStreamDept) {
            throw runtime_error("Cannot open file: " + fileNameDept);
        }
//1. Create runs for Dept and Emp which are sorted using Sort_Buffer()
    int l = 0;
    while(!empin.eof()){
        
        int y = 0;
        for(int i=0; i<22; i++){
            if(num_records_emp <= 29){
                Records a = Grab_Emp_Record(empin);
                buffers.push_back(a);
                num_records_emp += 1;
                y += 1;
                //buffers[i].printEmp();
            }
            else{
                break;
            }
            
           
        }
        Sort_Buffer_Emp();  
        //cout << y << endl;
        locationEmp[l] = y;
        l += 1;
        buffers.clear();           //clearing out the buffer for the next run
        //cout << empin.eof() << endl;
        
    }
    

    int z = 0;
   
        
        int y = 0;
        for(int j=0; j<15; j++){
            Records a = Grab_Dept_Record(deptin);
            buffers.push_back(a);
            num_records_dept += 1;
            y += 1;
            //buffers[j].printDept();
        
            
        }
        Sort_Buffer_Dept();  
        //cout << y << endl;
        location_dept[z] = y;
        z += 1;
        buffers.clear();           //clearing out the buffer for the next run
        //cout << "Break" << endl;
        
    
   
    //Creating the Join.csv file where we will store our joined results
    
    joinout.open("Join.csv", ios::out | ios::app);
    buffers.clear();
    fileStreamDept.seekg(0);
    fileStreamEmp.seekg(0);

    for(int i=0; i<16; i++){
        string fileData, word;
        Records r;
        if(getline(fileStreamDept, fileData, '\n')){
            r = Grab_Dept(fileData);
            //r.print();
        }
        buffers.push_back(r);
    }

   



    Merge_Join_Runs();
    

    


    //2. Use Merge_Join_Runs() to Join the runs of Dept and Emp relations 


    //Please delete the temporary files (runs) after you've joined both Emp.csv and Dept.csv

    return 0;
}
