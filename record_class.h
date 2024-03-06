/* This is a skeleton code for Optimized Merge Sort, you can make modifications as long as you meet 
   all question requirements*/  
/* This record_class.h contains the class Records, which can be used to store tuples form Emp.csv (stored
in the EmpRecords) and Dept.csv (Stored in DeptRecords) files.
*/
#include <bits/stdc++.h>

using namespace std;

class Records{
    public:
    
    struct EmpRecord {
        int eid;
        string ename;
        int age;
        double salary;
    }emp_record;

    struct DeptRecord {
        int did;
        string dname;
        double budget;
        int managerid;
    }dept_record;

    
    void printEmp(){
        cout << emp_record.eid << endl;
    }

    int valueEmp(){
        return emp_record.eid;
    }

    void printDept(){
        cout << dept_record.managerid << endl;
    }

    int valueDept(){
        return dept_record.managerid;
    }


    string serialize() const {
        stringstream ss;
        ss << emp_record.eid << "," << emp_record.ename << "," << emp_record.age << "," << emp_record.salary << "," << dept_record.did << "," << dept_record.dname << "," << dept_record.budget << "," << dept_record.managerid;
        return ss.str();
    }

    

    string serializeDept() const {
        stringstream ss;
        ss << dept_record.did << "," << dept_record.dname << "," << dept_record.budget << "," << dept_record.managerid << "," << emp_record.eid << "," << emp_record.ename << "," << emp_record.age << "," << emp_record.salary;
        return ss.str();
    }

    string serialDep() const {
        stringstream ss;
        ss << dept_record.did << "," << dept_record.dname << "," << dept_record.budget << "," << dept_record.managerid << ",";
        return ss.str();
    }

    string serialEmp() const {
        stringstream ss;
        ss << emp_record.eid << "," << emp_record.ename << "," << emp_record.age << "," << emp_record.salary;
        return ss.str();
    }

    

    /*** You can add more variables if you want below ***/

    int no_values = 0; //You can use this to check if you've don't have any more tuples
    int number_of_emp_records = 0; // Tracks number of emp_records you have on the buffer
    int number_of_dept_records = 0; //Track number of dept_records you have on the buffer
};

// Grab a single block from the Emp.csv file and put it inside the EmpRecord structure of the Records Class
Records Grab_Emp_Record(fstream &empin) {
    string line, word;
    Records emp;
    // grab entire line
    if (getline(empin, line, '\n')) {
        // turn line into a stream
        stringstream s(line);
        // gets everything in stream up to comma
        getline(s, word,',');
        emp.emp_record.eid = stoi(word);
        getline(s, word, ',');
        emp.emp_record.ename = word;
        getline(s, word, ',');
        emp.emp_record.age = stoi(word);
        getline(s, word, ',');
        emp.emp_record.salary = stod(word);

        //Ensuring that you cannot use both structure (EmpEecord, DeptRecord) at the same memory block / time 
        emp.dept_record.did = 0;
        emp.dept_record.dname = "";
        emp.dept_record.budget = 0;
        emp.dept_record.managerid = 0;

        return emp;
    } else {
        emp.no_values = -1;
        return emp;
    }
}

// Grab a single block from the Dept.csv file and put it inside the DeptRecord structure of the Records Class
Records Grab_Dept_Record(fstream &deptin) {
    string line, word;
    //DeptRecord dept;
    Records dept;
    if (getline(deptin, line, '\n')) {
        stringstream s(line);
        getline(s, word,',');
        dept.dept_record.did = stoi(word);
        getline(s, word, ',');
        dept.dept_record.dname = word;
        getline(s, word, ',');
        dept.dept_record.budget = stod(word);
        getline(s, word, ',');
        dept.dept_record.managerid = stoi(word);

        //Ensuring that you cannot use both structure (EmpEecord, DeptRecord) at the same memory block / time 
        dept.emp_record.eid = 0;
        dept.emp_record.ename = "";
        dept.emp_record.age = 0;
        dept.emp_record.salary = 0;

        return dept;
    } else {
        dept.no_values = -1;
        return dept;
    }
}

Records Grab_Emp(string line){
    string word;
    Records emp;
    // turn line into a stream
    stringstream s(line);
    // gets everything in stream up to comma
    getline(s, word,',');
    emp.emp_record.eid = stoi(word);
    getline(s, word, ',');
    emp.emp_record.ename = word;
    getline(s, word, ',');
    emp.emp_record.age = stoi(word);
    getline(s, word, ',');
    emp.emp_record.salary = stod(word);

    //Ensuring that you cannot use both structure (EmpEecord, DeptRecord) at the same memory block / time 
    emp.dept_record.did = 0;
    emp.dept_record.dname = "";
    emp.dept_record.budget = 0;
    emp.dept_record.managerid = 0;
    
    return emp;   
}

Records Grab_Dept(string line){
    string word;
    Records dept;
    stringstream s(line);
    getline(s, word,',');
    dept.dept_record.did = stoi(word);
    getline(s, word, ',');
    dept.dept_record.dname = word;
    getline(s, word, ',');
    dept.dept_record.budget = stod(word);
    getline(s, word, ',');
    dept.dept_record.managerid = stoi(word);

    //Ensuring that you cannot use both structure (EmpEecord, DeptRecord) at the same memory block / time 
    dept.emp_record.eid = 0;
    dept.emp_record.ename = "";
    dept.emp_record.age = 0;
    dept.emp_record.salary = 0;

    return dept;   
}

