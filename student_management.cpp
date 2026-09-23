#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <limits>

using namespace std;

class Student
{
public:
    int rollNo;
    string name;
    string course;
    int semester;
    float marks;

    void input()
    {
        string input;

        // Roll Number
        while (true)
        {
            cout << "Enter Roll Number: ";
            getline(cin, input);

            try
            {
                rollNo = stoi(input);
                break;
            }
            catch (...)
            {
                cout << "Please enter a valid number!\n";
            }
        }

        // Name
        cout << "Enter Name: ";
        getline(cin, name);

        // Course
        cout << "Enter Course: ";
        getline(cin, course);

        // Semester
        while (true)
        {
            cout << "Enter Semester: ";
            getline(cin, input);

            try
            {
                semester = stoi(input);
                break;
            }
            catch (...)
            {
                cout << "Please enter a valid semester number!\n";
            }
        }

        // Marks
        while (true)
        {
            cout << "Enter Marks: ";
            getline(cin, input);

            try
            {
                marks = stof(input);

                if (marks >= 0 && marks <= 100)
                    break;

                cout << "Marks 0 se 100 ke beech hone chahiye!\n";
            }
            catch (...)
            {
                cout << "Please enter valid marks!\n";
            }
        }
    }

    void display()
    {
        cout << "\n--------------------------------";
        cout << "\nRoll Number : " << rollNo;
        cout << "\nName        : " << name;
        cout << "\nCourse      : " << course;
        cout << "\nSemester    : " << semester;
        cout << "\nMarks       : " << marks << "%";
        cout << "\nGrade       : " << grade();
        cout << "\n--------------------------------\n";
    }

    char grade()
    {
        if (marks >= 90)
            return 'A';
        else if (marks >= 80)
            return 'B';
        else if (marks >= 70)
            return 'C';
        else if (marks >= 60)
            return 'D';
        else if (marks >= 50)
            return 'E';
        else
            return 'F';
    }
};


// ================= ADD STUDENT =================

void addStudent()
{
    Student s;

    cout << "\n========== ADD STUDENT ==========\n";

    s.input();

    ofstream file("students.txt", ios::app);

    if (!file)
    {
        cout << "\nFile open nahi ho rahi!\n";
        return;
    }

    file << s.rollNo << endl;
    file << s.name << endl;
    file << s.course << endl;
    file << s.semester << endl;
    file << s.marks << endl;

    file.close();

    cout << "\nStudent added successfully!\n";
}


// ================= DISPLAY STUDENTS =================

void displayStudents()
{
    Student s;
    ifstream file("students.txt");

    if (!file)
    {
        cout << "\nNo student records found!\n";
        return;
    }

    bool found = false;

    cout << "\n========== ALL STUDENTS ==========\n";

    while (file >> s.rollNo)
    {
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        getline(file, s.name);
        getline(file, s.course);

        file >> s.semester;
        file >> s.marks;

        file.ignore(numeric_limits<streamsize>::max(), '\n');

        s.display();

        found = true;
    }

    file.close();

    if (!found)
        cout << "\nNo student records found!\n";
}


// ================= SEARCH STUDENT =================

void searchStudent()
{
    Student s;
    string input;
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Search: ";
    getline(cin, input);

    try
    {
        roll = stoi(input);
    }
    catch (...)
    {
        cout << "\nInvalid Roll Number!\n";
        return;
    }

    ifstream file("students.txt");

    if (!file)
    {
        cout << "\nNo records found!\n";
        return;
    }

    while (file >> s.rollNo)
    {
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        getline(file, s.name);
        getline(file, s.course);

        file >> s.semester;
        file >> s.marks;

        file.ignore(numeric_limits<streamsize>::max(), '\n');

        if (s.rollNo == roll)
        {
            cout << "\n========== STUDENT FOUND ==========\n";
            s.display();

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nStudent not found!\n";
}


// ================= UPDATE STUDENT =================

void updateStudent()
{
    Student s;
    string input;
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Update: ";
    getline(cin, input);

    try
    {
        roll = stoi(input);
    }
    catch (...)
    {
        cout << "\nInvalid Roll Number!\n";
        return;
    }

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file)
    {
        cout << "\nNo student records found!\n";
        return;
    }

    if (!temp)
    {
        cout << "\nTemporary file create nahi ho rahi!\n";
        file.close();
        return;
    }

    while (file >> s.rollNo)
    {
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        getline(file, s.name);
        getline(file, s.course);

        file >> s.semester;
        file >> s.marks;

        file.ignore(numeric_limits<streamsize>::max(), '\n');

        if (s.rollNo == roll)
        {
            found = true;

            cout << "\n========== UPDATE STUDENT ==========\n";

            // Roll number same rahega
            cout << "Roll Number: " << s.rollNo << "\n";

            cout << "Enter New Name: ";
            getline(cin, s.name);

            cout << "Enter New Course: ";
            getline(cin, s.course);

            while (true)
            {
                cout << "Enter New Semester: ";
                getline(cin, input);

                try
                {
                    s.semester = stoi(input);
                    break;
                }
                catch (...)
                {
                    cout << "Please enter valid semester!\n";
                }
            }

            while (true)
            {
                cout << "Enter New Marks: ";
                getline(cin, input);

                try
                {
                    s.marks = stof(input);

                    if (s.marks >= 0 && s.marks <= 100)
                        break;

                    cout << "Marks 0 se 100 ke beech hone chahiye!\n";
                }
                catch (...)
                {
                    cout << "Please enter valid marks!\n";
                }
            }
        }

        temp << s.rollNo << endl;
        temp << s.name << endl;
        temp << s.course << endl;
        temp << s.semester << endl;
        temp << s.marks << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nStudent updated successfully!\n";
    else
        cout << "\nStudent not found!\n";
}


// ================= DELETE STUDENT =================

void deleteStudent()
{
    Student s;
    string input;
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Delete: ";
    getline(cin, input);

    try
    {
        roll = stoi(input);
    }
    catch (...)
    {
        cout << "\nInvalid Roll Number!\n";
        return;
    }

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file)
    {
        cout << "\nNo student records found!\n";
        return;
    }

    if (!temp)
    {
        cout << "\nTemporary file create nahi ho rahi!\n";
        file.close();
        return;
    }

    while (file >> s.rollNo)
    {
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        getline(file, s.name);
        getline(file, s.course);

        file >> s.semester;
        file >> s.marks;

        file.ignore(numeric_limits<streamsize>::max(), '\n');

        if (s.rollNo == roll)
        {
            found = true;
            continue;
        }

        temp << s.rollNo << endl;
        temp << s.name << endl;
        temp << s.course << endl;
        temp << s.semester << endl;
        temp << s.marks << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nStudent deleted successfully!\n";
    else
        cout << "\nStudent not found!\n";
}


// ================= MAIN =================

int main()
{
    string input;
    int choice;

    while (true)
    {
        cout << "\n\n======================================\n";
        cout << "       STUDENT MANAGEMENT SYSTEM\n";
        cout << "======================================\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "======================================\n";

        cout << "Enter your choice: ";
        getline(cin, input);

        try
        {
            choice = stoi(input);
        }
        catch (...)
        {
            cout << "\nPlease enter 1 to 6 only!\n";
            continue;
        }

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            cout << "\nThank you!\n";
            return 0;

        default:
            cout << "\nInvalid choice! Please enter 1 to 6.\n";
        }
    }

    return 0;
}