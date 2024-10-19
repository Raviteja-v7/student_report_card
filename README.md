# Student Report Card System

This project is a **Student Report Card System** implemented in C++ using Object-Oriented Programming (OOP) principles. It interacts with a MySQL database to store, update, and retrieve student data such as name, roll number, average marks, and grade.

## Features

- Add new students to the database.
- Calculate average marks from three subjects and assign a grade based on the calculated average.
- Update the student information with average marks and grade.
- Display the updated student report card.
- Object-Oriented structure for managing student data and database operations.

## OOP Concepts Implemented

- **Encapsulation**: 
  - Student details such as name, roll number, marks, and grade are encapsulated in the `Student` class.
  
- **Abstraction**: 
  - Interaction with the MySQL database is abstracted into the main function, simplifying the logic of student operations.
  
- **Single Responsibility Principle (SRP)**: 
  - The `Student` class is responsible only for handling student data and calculating grades.
  
- **Modularity**: 
  - Each class is designed to perform a single function, improving code readability and maintainability.

## Prerequisites

1. Install MySQL server on your machine and ensure it is running.
2. Install the MySQL C++ connector.
3. Create a MySQL database named `mydb` and a table `Student` with the following structure:
    ```sql
    CREATE DATABASE mydb;
    USE mydb;
    
    CREATE TABLE Student (
      RollNo VARCHAR(10) PRIMARY KEY,
      Name VARCHAR(50),
      Avg FLOAT,
      Grade VARCHAR(2)
    );
    ```

## Configuration

You need to update the following database credentials in the source code:
```cpp
const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "your_password";
const char* DB = "mydb";
