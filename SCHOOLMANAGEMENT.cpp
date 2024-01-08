#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <climits>
using namespace std;

// Functions defined for Admin.
void AdminLogin();
void AdminPanel();
void AdminToPerformActionOnTeachers();
void AdminToPerformActionOnStudents();

// Functions defined for Teachers.
void TeacherLogin();
void TeacherPanel(int teacherClass);
void RecordMarks(int classIndex);
void DisplayStudentMarks(int teacherClass);
void addTeacher();
void removeTeacher();
void updateTeacher();
void SaveTeacherToFile();
void LoadTeacherFromFile();
void AllTeachers();

// Functions defined for students.
void SaveStudentMarksToFile();
void LoadStudentMarksFromFile();
void Add_Student();
void All_Students();
void Update_Student();
void Remove_Student();
void LoadStudentFromFile();
void SaveStudentToFile();

// Function for text typing animation.
void TextTypingAnimation(const std::string &text, int delay);

const int MAX_Teachers = 10;
int teacher_count = 0;

int teacherID[MAX_Teachers], teacherClass[MAX_Teachers];
string teacherName[MAX_Teachers];
const int MAX_SUBJECTS = 6;
const string subjects[MAX_SUBJECTS] = {"English", "Math", "Pakstudies", "Physics", "Islamiyat", "Computer"};
const int MAX_Students = 100;
const int MAX_Classes = 10;
int student_count[MAX_Classes] = {0};

int attendance[MAX_Classes][MAX_Students] = {0};
int marks[MAX_Classes][MAX_Students][MAX_SUBJECTS] = {0};

string studentClass[MAX_Classes][MAX_Students], Roll_no[MAX_Classes][MAX_Students], name[MAX_Classes][MAX_Students];

int main()
{
    // Load Student and Teacher data from file at the beginning
    LoadStudentFromFile();
    LoadTeacherFromFile();
    LoadStudentMarksFromFile();
    TextTypingAnimation("\t\t\t<============ Welcome to School Management System ! ============> \n", 50);

    while (true)
    {
        TextTypingAnimation("\n 1) Login as admin.\n", 50);
        TextTypingAnimation(" 2) Login as Teacher.\n", 50);
        TextTypingAnimation(" 3) Login as student.\n", 50);

        TextTypingAnimation("\n Enter Your choice from above : ", 50);

        int ch;
        cin >> ch;
        switch (ch)
        {
        case 1:
            system("cls");
            AdminLogin();
            break;
        case 2:
            system("cls");
            TeacherLogin();
            break;
        case 3:
            system("cls");
            cout << "GO to home.";
            SaveStudentToFile();
            exit(0);
            break;
        default:
            cout << "Invalid Option! Enter Only from above options.";
            break;
        }
    }

    return 0;
}

// <---------------- Functions for Admin ---------------->
void AdminLogin()
{
    int attempts = 1;
    const int maxAttempts = 3;
    string AdminPassword = "Admin123!@#";
    string AdminName = "ROYAL";

    while (true)
    {
        cout << "Enter Username: ";
        string AdminInputName;
        cin >> AdminInputName;

        cout << "Enter Password: ";
        string AdminInputPass;
        cin >> AdminInputPass;

        if (AdminInputPass == AdminPassword && AdminInputName == AdminName)
        {
            system("cls");
            TextTypingAnimation(" Please Wait Logging in .....\n", 150);
            TextTypingAnimation(" Getting Things Ready for you ...\n", 150);
            system("cls");
            TextTypingAnimation("\t\t\t<============ Welcome to the Admin Panel ============> \n", 50);
            AdminPanel();
            break;
        }
        else
        {
            system("cls");
            cout << "--------Wrong Credentials!--------\n";
            attempts++;
            if (attempts <= maxAttempts)
            {
                cout << "Attempts left: " << maxAttempts - attempts + 1 << endl;
            }
            else
            {
                system("cls");
                cout << "You have tried too many times. You can't sign in for 24 hours.\n";
                cout << "Exiting School Management System..... \n";
                // this_thread::sleep_for(chrono::seconds(3));
                cout << "Thanks for Using ??????\n";
                exit(0);
            }
        }
    }
}

void AdminPanel()
{
    while (true)
    {
        TextTypingAnimation("\n <======== MENU ========>\n", 150);
        cout << " 1) Panel to perform  action on Teachers \n";
        cout << " 2) Panel to perform  action on Students \n";
        cout << " 3) Return to Main Menu \n";
        TextTypingAnimation(" \nEnter Your choice from above : ", 50);

        int choice;
        cin >> choice;

        // Check if input is valid
        if (cin.fail())
        {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();               // clear the error state
            cin.ignore(INT_MAX, '\n'); // ignore the invalid input
            continue;                  // continue the loop
        }
        switch (choice)
        {
        case 1:
            AdminToPerformActionOnTeachers();
            break;
        case 2:
            AdminToPerformActionOnStudents();
            break;
        case 3:
            SaveStudentToFile();
            SaveTeacherToFile();
            TextTypingAnimation("Loging out.....", 150);
            cout << endl;
            TextTypingAnimation("Returning to Main Menu.....", 150);
            cout << endl;
            return;
            break;
        default:
            cout << "Invalid Choice !!";
            break;
        }
    }
}
// <=========== These are the Functions/Actions that Admin can do ===========>
void AdminToPerformActionOnTeachers()
{
    while (true)
    {
        cout << "\n<======== MENU ========>\n";
        cout << "1) Add Teacher . \n";
        cout << "2) Remove Teacher \n";
        cout << "3) Update Teacher \n";
        cout << "4) Show All Teachers \n";
        cout << "5) Return to Admin Menu \n";
        cout << "Enter Your choice from above : ";
        int choice;
        cin >> choice;

        // Check if input is valid
        if (cin.fail())
        {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();               // clear the error state
            cin.ignore(INT_MAX, '\n'); // ignore the invalid input
            continue;                  // continue the loop
        }
        switch (choice)
        {
        case 1:
            addTeacher();
            break;
        case 2:
            removeTeacher();
            break;
        case 3:
            updateTeacher();
            break;
        case 4:
            AllTeachers();
            break;
        case 5:
            return;
            break;
        default:
            cout << "Invalid Choice !!";
            break;
        }
    }
}

void AdminToPerformActionOnStudents()
{
    while (true)
    {
        cout << "\n<======== MENU ========>\n";
        cout << "1) Add Student \n";
        cout << "2) Remove Student \n";
        cout << "3) Update Student \n";
        cout << "4) Show All Students \n";
        cout << "5) Return to Admin Menu \n";
        cout << "Enter Your choice from above : ";
        int choice;
        cin >> choice;

        // Check if input is valid
        if (cin.fail())
        {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();               // clear the error state
            cin.ignore(INT_MAX, '\n'); // ignore the invalid input
            continue;                  // continue the loop
        }
        switch (choice)
        {
        case 1:
            Add_Student();
            break;
        case 2:
            Remove_Student();
            break;
        case 3:
            Update_Student();
            break;
        case 4:
            All_Students();
            break;
        case 5:
            return;
            break;
        default:
            cout << "Invalid Choice !!";
            break;
        }
    }
}
// <------------------------------------------------------->
// <---------------- Functions for Teacher ---------------->
void TeacherLogin()
{
    LoadTeacherFromFile();
    while (true)
    {
        cout << "Enter your ID : ";
        int teacherInpID;
        cin >> teacherInpID;

        string teacherPassword = "Password", enteredPassword;
        // Check if teacher ID exists
        bool teacherFound = false;

        for (int i = 0; i < teacher_count; ++i)
        {
            if (teacherInpID == teacherID[i])
            {
                teacherFound = true;
                break;
            }
        }

        if (!teacherFound)
        {
            cout << "Teacher with ID " << teacherInpID << " not found.\n";
            break;
        }

        cout << "Enter your password: ";
        cin >> enteredPassword;

        if (enteredPassword == teacherPassword)
        {
            TextTypingAnimation("\t\t\t<============ Welcome to the Teacher Panel ============> \n", 50);
            int teacherIndex;
            for (teacherIndex = 0; teacherIndex < teacher_count; ++teacherIndex)
            {
                if (teacherInpID == teacherID[teacherIndex])
                {
                    break; // Exit the loop when the teacher is found
                }
            }
            // Display the assigned class if the teacher is found
            if (teacherIndex < teacher_count)
            {
                cout << "Assigned Class: " << teacherClass[teacherIndex] << endl;
                TeacherPanel(teacherClass[teacherIndex]);
            }
            else
            {
                cout << "Teacher with ID " << teacherInpID << " not found.\n";
            }

            // Exit the loop after processing
            break;
        }
        else
        {
            cout << "Incorrect password.\n";
        }
    }
}
void addTeacher()
{
    if (teacher_count < MAX_Teachers)
    {
        cout << "Enter Teacher Name: ";
        string teacherInpName;
        cin >> teacherInpName;

        cout << "Enter Teacher ID: ";
        int teacherInpID;
        cin >> teacherInpID;
        for (int i = 0; i < MAX_Teachers; ++i)
        {
            for (int j = 0; j < teacher_count; ++j)
            {
                if (teacherInpID == teacherID[i])
                {
                    cout << "Sorry, Teacher with ID  " << teacherInpID << " already exists with Teacher " << teacherName[j] << endl;
                    cout << "<-------------------->\n";
                    return;
                }
            }
        }

        cout << "Enter the class to assign to the teacher (1-10): ";
        int teacherInpClass;
        cin >> teacherInpClass;

        if (teacherInpClass < 1 || teacherInpClass > 10)
        {
            cout << "Invalid class. Please enter a class between 1 and 10.\n";
            cout << "<-------------------->\n";
            return;
        }
        bool classAlreadyAssigned = false;
        // Verify if the class is already assigned to another teacher
        for (int i = 0; i < teacher_count; ++i)
        {
            if (teacherInpClass == teacherClass[i])
            {
                classAlreadyAssigned = true;
                break;
            }
        }

        if (classAlreadyAssigned)
        {
            cout << "The class " << teacherInpClass << " is already assigned to another teacher.\n";
            cout << "<-------------------->\n";
            return;
        }

        teacherID[teacher_count] = teacherInpID;
        teacherName[teacher_count] = teacherInpName;
        teacherClass[teacher_count] = teacherInpClass;
        TextTypingAnimation("Teacher added successfully.", 50);
        teacher_count++;
        SaveTeacherToFile();
    }
    else
    {
        cout << "Sorry, can't add more teachers. The limit is " << MAX_Teachers << ".\n";
        cout << "<-------------------->\n";
    }
}
void removeTeacher()
{
    cout << "Enter the ID of the teacher to remove: ";
    int idToRemove;
    cin >> idToRemove;

    for (int i = 0; i < teacher_count; ++i)
    {
        if (idToRemove == teacherID[i])
        {
            // Remove the teacher by shifting the remaining elements
            for (int j = i; j < teacher_count - 1; ++j)
            {
                teacherName[j] = teacherName[j + 1];
                teacherID[j] = teacherID[j + 1];
                teacherClass[j] = teacherClass[j + 1];
            }
            // Decrement the teacher count
            teacher_count--;
            cout << "Teacher with ID " << idToRemove << " removed successfully.\n";
            cout << "<-------------------->\n";
            SaveTeacherToFile(); // Assuming you have a function to save teacher data to a file
            return;
        }
    }

    cout << "Teacher with ID " << idToRemove << " not found.\n";
    cout << "<-------------------->\n";
}

void SaveTeacherToFile()
{
    ofstream teacherFile("teacher_data.txt");

    if (!teacherFile.is_open())
    {
        cout << "Error opening Teacher file for writing.\n";
        return;
    }

    for (int i = 0; i < teacher_count; ++i)
    {
        teacherFile << teacherName[i] << ' ' << teacherID[i] << ' ' << teacherClass[i] << '\n';
    }

    teacherFile.close();
}

void LoadTeacherFromFile()
{
    ifstream teacherFile("teacher_data.txt");

    if (!teacherFile.is_open())
    {
        cout << "Error opening Teacher file for reading.\n";
        return;
    }
    // Reset teacher_count before loading data
    teacher_count = 0;

    while (teacherFile >> teacherName[teacher_count] >> teacherID[teacher_count] >> teacherClass[teacher_count])
    {
        teacher_count++;
        // Check if the teacher_count exceeds the MAX_Teachers limit
        if (teacher_count >= MAX_Teachers)
        {
            cout << "Warning: Maximum number of teachers reached.\n";
            break;
        }
    }

    teacherFile.close();
}
void updateTeacher()
{
    cout << "Enter the ID of the teacher to update: ";
    int idToUpdate;
    cin >> idToUpdate;

    for (int i = 0; i < teacher_count; ++i)
    {
        if (idToUpdate == teacherID[i])
        {
            // Update the teacher's information
            cout << "Enter the new Name: ";
            cin >> teacherName[i];

            cout << "Teacher with ID " << idToUpdate << " updated successfully.\n";
            cout << "<-------------------->\n";
            SaveTeacherToFile(); // Save data to file after updating a teacher
            return;
        }
    }

    cout << "Teacher with ID " << idToUpdate << " not found.\n";
    cout << "<-------------------->\n";
}
void AllTeachers()
{

    cout << "\n<======== List of Teachers ========>\n";
    if (teacher_count == 0)
    {
        cout << "No teachers in the system.\n";
        cout << "<---------------------------------------------->\n";
    }
    else
    {
        for (int i = 0; i < teacher_count; i++)
        {
            cout << "Teacher Name: " << teacherName[i] << endl;
            cout << "Teacher ID: " << teacherID[i] << endl;
            cout << "Teacher Class: " << teacherClass[i] << endl;
            cout << "<-------------------->\n";
        }
    }
}
// <-------------------------------------------------------->

// <---------------- Functions for Students ---------------->
void Add_Student()
{
    cout << "Enter your Name: ";
    string studentName;
    cin >> studentName;

    cout << "Enter your Roll No.: ";
    string studentRoll;
    cin >> studentRoll;

    for (int i = 0; i < MAX_Classes; ++i)
    {
        for (int j = 0; j < student_count[i]; ++j)
        {
            if (studentRoll == Roll_no[i][j])
            {
                cout << "Sorry, Roll No. " << studentRoll << " already exists with student " << name[i][j] << " in Class " << (i + 1) << endl;
                cout << "<-------------------->\n";
                return;
            }
        }
    }

    cout << "Enter your class (1-10): ";
    int studentClassInput;
    cin >> studentClassInput;

    if (studentClassInput < 1 || studentClassInput > 10)
    {
        cout << "Invalid class. Please enter a class between 1 and 10.\n";
        cout << "<-------------------->\n";
        return;
    }

    int classIndex = studentClassInput - 1;

    if (student_count[classIndex] < MAX_Students)
    {
        name[classIndex][student_count[classIndex]] = studentName;
        Roll_no[classIndex][student_count[classIndex]] = studentRoll;
        studentClass[classIndex][student_count[classIndex]] = to_string(studentClassInput);
        cout << "Student added successfully to Class " << studentClassInput << ".\n";
        student_count[classIndex]++;
        SaveStudentToFile(); // Save data to file after adding a student
    }
    else
    {
        cout << "Sorry, can't add more students to Class " << studentClassInput << ". The limit is " << MAX_Students << " and there are already " << student_count[classIndex] << " students.";
        cout << "<-------------------->\n";
    }
}

void All_Students()
{
    for (int i = 0; i < MAX_Classes; ++i)
    {
        cout << "\t\tList of Students in Class " << (i + 1) << ":\n";
        if (student_count[i] == 0)
        {
            cout << "\t\tNo students in this class.\n";
            cout << "<---------------------------------------------->\n";
        }
        else
        {
            for (int j = 0; j < student_count[i]; j++)
            {
                cout << "Name: " << name[i][j] << endl;
                cout << "Roll Number: " << Roll_no[i][j] << endl;
                cout << "Class: " << studentClass[i][j] << endl;
                cout << "<-------------------->\n";
            }
        }
    }
}

void Update_Student()
{
    cout << "Enter the Roll No. of the student to update: ";
    string rollToUpdate;
    cin >> rollToUpdate;

    for (int i = 0; i < MAX_Classes; ++i)
    {
        for (int j = 0; j < student_count[i]; ++j)
        {
            if (rollToUpdate == Roll_no[i][j])
            {
                // Update the student's information
                cout << "Enter the new Name: ";
                cin >> name[i][j];
                cout << "Enter the new Roll No.: ";
                cin >> Roll_no[i][j];

                cout << "Student with Roll No. " << rollToUpdate << " updated successfully.\n";
                cout << "<-------------------->\n";
                SaveStudentToFile();
                return;
            }
        }
    }

    cout << "Student with Roll No. " << rollToUpdate << " not found.\n";
    cout << "<-------------------->\n";
}

void Remove_Student()
{
    cout << "Enter the Roll No. of the student to remove: ";
    string rollToRemove;
    cin >> rollToRemove;

    for (int i = 0; i < MAX_Classes; ++i)
    {
        for (int j = 0; j < student_count[i]; ++j)
        {
            if (rollToRemove == Roll_no[i][j])
            {
                // Remove the student by shifting the remaining elements
                for (int k = j; k < student_count[i] - 1; ++k)
                {
                    name[i][k] = name[i][k + 1];
                    Roll_no[i][k] = Roll_no[i][k + 1];
                }
                // Decrement the student count in the class
                student_count[i]--;
                cout << "Student with Roll No. " << rollToRemove << " removed successfully.\n";
                cout << "<-------------------->\n";
                SaveStudentToFile();
                return;
            }
        }
    }

    cout << "Student with Roll No. " << rollToRemove << " not found.\n";
    cout << "<-------------------->\n";
}
void SaveStudentToFile()
{
    ofstream file("student_data.txt");

    if (!file.is_open())
    {
        cout << "Error opening Student file for reading.\n";
        return;
    }

    for (int i = 0; i < MAX_Classes; ++i)
    {
        for (int j = 0; j < student_count[i]; ++j)
        {
            file << i << ' ' << name[i][j] << ' ' << Roll_no[i][j] << ' ' << studentClass[i][j] << '\n';
        }
    }

    file.close();
}
void LoadStudentFromFile()
{
    ifstream file("student_data.txt");

    if (!file.is_open())
    {
        cout << "Error opening Student file for reading.\n";
        return;
    }

    int classIndex = 0;
    while (file >> classIndex >> name[classIndex][student_count[classIndex]] >> Roll_no[classIndex][student_count[classIndex]] >> studentClass[classIndex][student_count[classIndex]])
    {
        student_count[classIndex]++;
    }

    file.close();
}
// <-------------------------------------------------------->

// <======================================= End For Admin Functions/Actions =======================================>

// Functions Defined For Panels of Teachers and Students .

// <---------------- Function for Text Typing Animation ---------------->
void TextTypingAnimation(const string &text, int delay)
{
    for (char c : text)
    {
        cout << c;
        //   this_thread::sleep_for(chrono::milliseconds(delay));
    }
}
// RecordMarks function
void TeacherPanel(int teacherClass)
{
    while (true)
    {
        cout << "\n<======== Teacher Panel ========>\n";
        cout << "1) Record Attendance\n";
        cout << "2) Record Marks\n";
        cout << "3) Display Marks For Student.\n";
        cout << "4) Return to Main Menu\n";
        cout << "Enter Your choice from above : ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Record Attendence.";
            break;
        case 2:
            RecordMarks(teacherClass);
            break;
        case 3:
            DisplayStudentMarks(teacherClass);
            break;
        case 4:
            return;
            break;
        default:
            cout << "Invalid Choice !!";
            break;
        }
    }
}
void RecordMarks(int teacherClass)
{
    cout << "\n<======== Record Marks ========>\n";

    if (student_count[teacherClass - 1] == 0)
    {
        cout << "No Students in the Class.\n";
    }
    else
    {
        // Iterate over each student in the specified class
        for (int i = 0; i < student_count[teacherClass - 1]; ++i)
        {
            cout << "Recording marks for " << name[teacherClass - 1][i] << " (Roll No. " << Roll_no[teacherClass - 1][i] << ")\n";

            // Iterate over each subject
            for (int j = 0; j < MAX_SUBJECTS; ++j)
            {
                cout << "Enter marks for " << subjects[j] << ": ";
                cin >> marks[teacherClass - 1][i][j];
            }
        }

        cout << "Marks recorded successfully for class " << teacherClass << ".\n";
        SaveStudentMarksToFile();
    }
}
void DisplayStudentMarks(int teacherClass)
{
    string rollToDisplay;
    cout << "Enter Roll No.: ";
    cin >> rollToDisplay;

    // Find the student with the specified roll number
    for (int i = 0; i < MAX_Classes; ++i)
    {
        for (int j = 0; j < student_count[i]; ++j)
        {
            if (rollToDisplay == Roll_no[i][j])
            {
                // Check if the student's class matches the class assigned to the teacher
                if (i + 1 == teacherClass)
                {
                    cout << "Marks for " << name[i][j] << " (Roll No. " << Roll_no[i][j] << "):\n";

                    // Display marks for each subject
                    for (int k = 0; k < MAX_SUBJECTS; ++k)
                    {
                        cout << subjects[k] << ": " << marks[i][j][k] << endl;
                    }
                }
                else
                {
                    cout << "Student with Roll No. " << rollToDisplay << " is not in your assigned class.\n";
                }
                return; // Exit the function after displaying marks
            }
        }
    }

    cout << "Student with Roll No. " << rollToDisplay << " not found.\n";
}
// Function to save student marks to a file
void SaveStudentMarksToFile()
{
    ofstream file("student_marks.txt");

    if (!file.is_open())
    {
        cout << "Error opening Student Marks file for writing.\n";
        return;
    }

    for (int i = 0; i < MAX_Classes; ++i)
    {
        for (int j = 0; j < student_count[i]; ++j)
        {

            file << i << ' ' << Roll_no[i][j] << ' ';

            for (int k = 0; k < MAX_SUBJECTS; ++k)
            {
                file << marks[i][j][k] << ' ';
            }

            file << '\n';
        }
    }

    file.close();
}
// Function to load student marks from a file
void LoadStudentMarksFromFile()
{
    ifstream file("student_marks.txt");

    if (!file.is_open())
    {
        cout << "Error opening Student Marks file for reading.\n";
        return;
    }

    int classIndex, subjectMarks;
    string roll;

    while (file >> classIndex >> roll)
    {
        // Find the student with the specified roll number and update the marks
        for (int i = 0; i < student_count[classIndex]; ++i)
        {
            if (roll == Roll_no[classIndex][i])
            {
                for (int j = 0; j < MAX_SUBJECTS; ++j)
                {
                    file >> subjectMarks;
                    marks[classIndex][i][j] = subjectMarks;
                }
                break; // Marks found for the student, break the loop
            }
        }
    }

    file.close();
}
