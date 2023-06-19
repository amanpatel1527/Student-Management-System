#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

struct Student {
    int id;
    std::string name;
    char grade; 
};

// Function to add a new student
void addStudent(std::vector<Student>& students) {
    Student newStudent;
    std::cout << "Enter student ID: ";
    std::cin >> newStudent.id;
    std::cin.ignore(); // Clear the newline character from the input buffer
    std::cout << "Enter student name: ";
    std::getline(std::cin, newStudent.name);
    std::cout << "Enter student grade (A, B, C, ...): ";
    std::cin >> newStudent.grade;
    students.push_back(newStudent);
    std::cout << "Student added successfully!\n";
}

// Function to display student details
void displayStudent(const Student& student) {
    std::cout << "ID: " << student.id << "\n";
    std::cout << "Name: " << student.name << "\n";
    std::cout << "Grade: " << student.grade << "\n";
}

// Function to search for a student by ID
void searchStudent(const std::vector<Student>& students, int id) {
    auto it = std::find_if(students.begin(), students.end(), [id](const Student& student) {
        return student.id == id;
    });

    if (it != students.end()) {
        displayStudent(*it);
    } else {
        std::cout << "Student not found!\n";
    }
}

// Function to delete a student by ID
void deleteStudent(std::vector<Student>& students, int id) {
    auto it = std::find_if(students.begin(), students.end(), [id](const Student& student) {
        return student.id == id;
    });

    if (it != students.end()) {
        students.erase(it);
        std::cout << "Student deleted successfully!\n";
    } else {
        std::cout << "Student not found!\n";
    }
}

// Function to calculate the average grade of all students
float calculateAverageGrade(const std::vector<Student>& students) {
    float sum = 0.0;
    for (const auto& student : students) {
        sum += student.grade;
    }
    return sum / students.size();
}

// Function to display all students

void displayAllStudents(const std::vector<Student>& students) {
    for (const auto& student : students) {
        displayStudent(student);
        std::cout << "------------------------\n";
    }
}

// Function to save students' data to a file
void saveData(const std::vector<Student>& students) {
    std::ofstream outputFile("students.txt");
    if (outputFile.is_open()) {
        for (const auto& student : students) {
            outputFile << student.id << "," << student.name << "," << student.grade << "\n";
        }
        outputFile.close();
        std::cout << "Data saved to file.\n";
    } else {
        std::cout << "Unable to open file for saving data!\n";
    }
}

// Function to load students' data from a file
void loadData(std::vector<Student>& students) {
    students.clear();
    std::ifstream inputFile("students.txt");
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            Student student;
            std::string token;
            std::getline(iss, token, ',');
            student.id = std::stoi(token);
            std::getline(iss, student.name, ',');
            std::getline(iss, token, ',');
            student.grade = token[0]; // Assign the first character as the grade
            students.push_back(student);
        }
        inputFile.close();
        std::cout << "Data loaded from file.\n";
    } else {
        std::cout << "Unable to open file for loading data!\n";
    }
}

int main() {
    std::vector<Student> students;
    int choice;
    
    while (true) {
        std::cout << "************ Student Management System ************\n";
        std::cout << "1. Add a new student\n";
        std::cout << "2. Search student by ID\n";
        std::cout << "3. Delete student by ID\n";
        std::cout << "4. Calculate average grade\n";
        std::cout << "5. Display all students\n";
        std::cout << "6. Save data to file\n";
        std::cout << "7. Load data from file\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout<<std::endl;
        
        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                int searchId;
                std::cout << "Enter student ID to search: ";
                std::cin >> searchId;
                searchStudent(students, searchId);
                break;
            case 3:
                int deleteId;
                std::cout << "Enter student ID to delete: ";
                std::cin >> deleteId;
                deleteStudent(students, deleteId);
                break;
            case 4:
                std::cout << "Average grade: " << calculateAverageGrade(students) << "\n";
                break;
            case 5:
                std::cout << "List of all students:\n";
                displayAllStudents(students);
                break;
            case 6:
                saveData(students);
                break;
            case 7:
                loadData(students);
                break;
            case 8:
                std::cout << "Exiting the program...\n";
                return 0;
            default:
                std::cout << "Invalid choice! Please try again.\n";
                break;
        }
        
        std::cout << "------------------------------------------\n";
    }
    
    return 0;
}
