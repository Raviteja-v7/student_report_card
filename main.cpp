#include <iostream>
#include <mysql.h>
#include <sstream>
#include <string>
using namespace std;

const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "your password";
const char* DB = "mydb";

class Student {
private:
    string Name, RollNo, Grade;
    float Avg;
    
public:
    Student(string name, string rollNo, float avg = 0.0, string grade = "NULL") : Name(name), RollNo(rollNo), Avg(avg), Grade(grade) {}
    
    string getName() { return Name; }
    string getRollNo() { return RollNo; }
    float getAvg() { return Avg; }
    string getGrade() { return Grade; }

    void calculateGrade(int sub1, int sub2, int sub3) {
        Avg = (sub1 + sub2 + sub3) / 3.0;
        if (Avg >= 90) Grade = "A+";
        else if (Avg >= 80) Grade = "A";
        else if (Avg >= 70) Grade = "B+";
        else if (Avg >= 60) Grade = "B";
        else if (Avg >= 50) Grade = "C";
        else if (Avg >= 40) Grade = "D";
        else Grade = "F";
    }
};

class Database {
private:
    MYSQL* conn;

public:
    Database() {
        conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0)) {
            cout << "Database connection failed: " << mysql_error(conn) << endl;
        } else {
            cout << "Database connection successful." << endl;
        }
    }

    ~Database() {
        mysql_close(conn);
    }

    void insertStudent(Student& student) {
        stringstream ss;
        ss << "INSERT INTO Student (RollNo, Name, Avg, Grade) VALUES ('" 
           << student.getRollNo() << "', '" << student.getName() << "', '" 
           << student.getAvg() << "', '" << student.getGrade() << "')";
        
        if (mysql_query(conn, ss.str().c_str())) {
            cout << "Insert Error: " << mysql_error(conn) << endl;
        } else {
            cout << "Student " << student.getName() << " added successfully." << endl;
        }
    }

    void updateStudent(Student& student) {
        stringstream ss;
        ss << "UPDATE Student SET Avg = '" << student.getAvg() 
           << "', Grade = '" << student.getGrade() 
           << "' WHERE RollNo = '" << student.getRollNo() << "'";
        
        if (mysql_query(conn, ss.str().c_str())) {
            cout << "Update Error: " << mysql_error(conn) << endl;
        } else {
            cout << "Student " << student.getName() << " updated successfully." << endl;
        }
    }

    void displayStudent(string rollNo) {
        string query = "SELECT * FROM Student WHERE RollNo = '" + rollNo + "'";
        
        if (mysql_query(conn, query.c_str())) {
            cout << "Display Error: " << mysql_error(conn) << endl;
        } else {
            MYSQL_RES* res = mysql_store_result(conn);
            if (res) {
                MYSQL_ROW row;
                cout << "\t|  RollNo  |  Name  |  Avg  |  Grade  |" << endl;
                while ((row = mysql_fetch_row(res))) {
                    for (int i = 0; i < mysql_num_fields(res); ++i) {
                        cout << "\t" << row[i];
                    }
                    cout << endl;
                }
            }
        }
    }
};

void reportCard(Database& db) {
    string rollNo;
    int sub1, sub2, sub3;
    cout << "Enter RollNo: "; cin >> rollNo;
    cout << "Enter Subject 1 Marks: "; cin >> sub1;
    cout << "Enter Subject 2 Marks: "; cin >> sub2;
    cout << "Enter Subject 3 Marks: "; cin >> sub3;

    // Fetch and update student
    Student student("", rollNo);
    student.calculateGrade(sub1, sub2, sub3);
    db.updateStudent(student);
    db.displayStudent(rollNo);
}

int main() {
    Database db;
    Student s1("Ali", "ab123"), s2("Ahmad", "bc234"), s3("Kabeer", "cd345"); //Examples 

    db.insertStudent(s1);
    db.insertStudent(s2);
    db.insertStudent(s3);

    bool exit = false;
    while (!exit) {
        cout << "1. Report Card\n2. Exit\nChoose: ";
        int choice; cin >> choice;
        if (choice == 1) {
            reportCard(db);
        } else if (choice == 2) {
            exit = true;
        } else {
            cout << "Invalid choice." << endl;
        }
    }
    return 0;
}