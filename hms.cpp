// Code for Hostel Mangemant System in cpp.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// define a struct to hold student information
struct Student
{
    string name;
    int id;
    string course;
};

// function to add a new student to the file
void addstudent(){
    Student student;
    cout<<"Enter the student name: ";
    getline(cin, student.name);
    cout<<"Enter student ID: ";
    cin>>student.id;
    cin.ignore();
    cout<<"Enter student course: ";
    getline(cin, student.course);

    ofstream outFile("students.txt", ios::app);
    outFile<<student.name<<','<<student.id<<','<<student.course<<endl;
    outFile.close();

    cout<<"Student added successfully!"<<endl;
}

// function to edit an existing student information
void editstudent(){
    int id;
    cout<<"Enter the ID of student to edit: ";
    cin>>id;
    cin.ignore();

    ifstream inFile("students.txt");
    ofstream outFile("temp.txt");

    bool found=false;
    while (inFile.good())
    {
        string line;
        getline(inFile, line);
        if(line.empty()) continue;
        int pos=line.find(',');
        int currId =  stoi(line.substr(pos+1));
        if(currId==id){
            Student student;
            student.name=line.substr(0,pos);
            student.id=currId;
            student.course=line.substr(pos+3);
            cout<<"Enter new student name (currently "<<student.name<<"): ";
            getline(cin, student.name);
            cout<<"Enter new student course (currently "<<student.course<<"): ";
            getline(cin, student.course);
            outFile<<student.name<<','<<student.id<<','<<student.course<<endl;
            found=true;
            cout<<"Student edited successfully!"<<endl;
        }
        else{
            outFile<<line<<endl;
        }
    }
    inFile.close();
    outFile.close();

    if(!found){
        cout<<"Student not found."<<endl;
        remove("temp.txt");
    }
    else{
        remove("students.txt");
        rename("temp.txt", "students.txt");
    }
}

// function to display a student list
void viewstudents(){
    ifstream inFile("students.txt");
    vector<Student>students;
    while (inFile.good())
    {
        string line;
        getline(inFile, line);
        if(line.empty()) continue;
        int pos=line.find(',');
        int id=stoi(line.substr(pos+1));
        Student student;
        student.name=line.substr(0, pos);
        student.id=id;
        student.course=line.substr(pos+3);
        students.push_back(student);
    }
    inFile.close();

    if(students.empty()){
        cout<<"No students found."<<endl;
    }
    else{
        cout<<endl;
        cout<<"--------------------------------------------------------"<<endl;
        cout<<"Name \t\t\t ID \t\t\t Course"<<endl;
        cout<<"--------------------------------------------------------"<<endl;
        for(const auto& student : students){
            cout<<student.name<<"\t "<<student.id<<"\t\t\t  "<<student.course<<endl;
        }
    }
}

// Function to delete an existing student from the file
void deletestudent() {
    int id;
    cout << "Enter ID of student to delete: ";
    cin >> id;
    cin.ignore();

    ifstream inFile("students.txt");
    ofstream outFile("temp.txt"); 

    bool found = false;
    while (inFile.good()) {
        string line;
        getline(inFile, line);
        if (line.empty()) continue; 
        int pos = line.find(',');
        int currId = stoi(line.substr(pos+1));
        if (currId == id) {
            cout << "Are you sure you want to delete the following student:" << endl;
            cout << line << endl;
            cout << "(y/n): ";
            char confirm;
            cin >> confirm;
            cin.ignore(); 
            if (confirm == 'y' || confirm == 'Y') {
                found = true;
                cout << "Student deleted successfully!" << endl;
            } else {
                outFile << line << endl; 
            }
        } else {
            outFile << line << endl;
        }
    }

    inFile.close();
    outFile.close();

    if (!found) {
        cout << "Student not found." << endl;
        remove("temp.txt"); 
    } else {
        remove("students.txt"); 
        rename("temp.txt", "students.txt"); 
    }
}

// Function to search for a student by ID
void searchStudent() {
    int id;
    cout << "Enter ID of student to search: ";
    cin >> id;
    cin.ignore();

    ifstream inFile("students.txt");

    bool found = false;
    while (inFile.good()) {
        string line;
        getline(inFile, line);
        if (line.empty()) continue;
        int pos = line.find(',');
        int currId = stoi(line.substr(pos+1));
        if (currId == id) {
            cout << "Student found:" << endl;
            cout<<endl;
            cout<<"-------------------------------"<<endl;
            cout<<" Name               ID  Course"<<endl;
            cout<<"-------------------------------"<<endl;
            cout << line << endl;
            found = true;
            break;
        }
    }

    inFile.close();

    if (!found) {
        cout << "Student not found." << endl;
    }
}

// main function
int main(){
    int choice;
    do
    {
        cout<<"--------------------------------------------------------"<<endl;
        cout<<"\t\tHostel Management System"<<endl;
        cout<<"--------------------------------------------------------"<<endl;
        cout<<"1. Add Student"<<endl;
        cout<<"2. Edit Student"<<endl;
        cout<<"3. View Student"<<endl;
        cout<<"4. Delete Student"<<endl;
        cout<<"5. Search Student"<<endl;
        cout<<"6. Exit"<<endl;
        cout<<"Enter your choice: ";

        cin>>choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            addstudent();
            break;
        
        case 2:
            editstudent();
            break;
        
        case 3:
            viewstudents();
            break;

        case 4:
            deletestudent();
            break;

        case 5:
            searchStudent();
            break;

        case 6:
            break;

        default:
            cout<<"Invalid choice. Try again."<<endl;
        }

    cout<<endl;
    cout<<endl;

    }
    while (choice != 6);
     
    return 0;
}

