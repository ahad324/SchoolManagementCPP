#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <climits>
using namespace std;
//<----------- Functions To Save And Retrieve All Data From The Files ----------->
// For Students data
void SaveStudentToFile();
void LoadStudentFromFile();
void SaveStudentMarksToFile();
void LoadStudentMarksFromFile();
void SaveStudentAttendanceToFile();
void LoadStudentAttendanceFromFile();
// For Teachers Data
void SaveTeacherToFile();
void LoadTeacherFromFile();
//                   <---------------------->

//<----------- Login Functions For Admin , Teacher , Student ----------->
void AdminLogin();
void TeacherLogin();
void StudentLogin();
//                   <---------------------->

// <----------- Panels For Admin , Teacher , Student ----------->
void AdminPanel();
void TeacherPanel(int teacherClass);
void StudentPanel(int studentClass, int studentIndex);
//                   <---------------------->

//<----------- Actions That Admin Can Perform ----------->
void AdminToPerformActionOnTeachers();
void AdminToPerformActionOnStudents();
// Functions to perform Action on Teachers by Admin
void addTeacher();
void removeTeacher();
void updateTeacher();
void AllTeachers();
// Functions to perform Action on Students by Admin
bool GetStudentDataFromAdmin(string &studentName, char &studentInpGen, int &studentInpAge, int &studentInpFee, int &studentClassInput);
void Add_Student();
void All_Students();
void Update_Student();
void Remove_Student();
//                   <---------------------->

// <----------- Actions That Teacher Can Perform ----------->
void ShowTeacherDetailsToTeacher(int teacherclass);
void ShowStudentsInTeacherClass(int teacherClass);
void TeacherToPerformActionOnStudentMarks(int teacherClass);
void TeacherToPerformActionOnStudentAttendance(int teacherClass);
void ChangeTeacherPassword(int teacherclass);
// Functions To Perform Action on Student Marks by Teacher
void RecordMarks(int classIndex);
void UpdateMarks(int teacherClass);
void DisplayStudentMarks(int teacherClass);
// Functions To Perform Action on Student Attendance by Teacher
void RecordAttendance(int teacherClass);
void UpdateStudentAttendance(int teacherClass);
void ViewStudentAttendance(int teacherClass);
//                   <---------------------->

// <----------- Actions That Student Can Perform ----------->
void ViewStudentDetailsToStudent(int studentClass, int studentIndex);
void ViewStudentMarksToStudent(int studentClass, int studentIndex);
void ViewStudentAttendanceToStudent(int studentClass, int studentIndex);
void ChangeStudentPassword(int studentClass, int studentIndex);
//                   <---------------------->

// <----------- Function For Text Typing Animation ----------->
void PausingOnInvalidInputs()
{
    this_thread::sleep_for(chrono::seconds(1));
}
//                   <---------------------->
// <----------- Function For Error/Succes Message Typing ----------->
// Function to print text with color
// RED=31   GREEN=32    YELLOW=33   BLUE=34   MAGENTA=35    CYAN=36    WHITE=37   RESET=0
void PrintColoredText(const string &text, const string &color)
{
    cout << "\033[" << color << "m" << text << "\033[0m";
}

void HandlingInvalidInputs()
{
    PrintColoredText("Invalid input. Please enter a number.", "31");
    cin.clear();               // clear the error state
    cin.ignore(INT_MAX, '\n'); // ignore the invalid input
    PausingOnInvalidInputs();
    system("cls");
}
// <----------- Function For Text Typing Animation ----------->
void TextTypingAnimation(const string &text, int speed, const string &color)
{
    for (char c : text)
    {
        PrintColoredText(string(1, c), color);
        this_thread::sleep_for(chrono::milliseconds(speed));
    }
}

//                   <---------------------->

void Pattern()
{
    PrintColoredText(
        "\t\t=========== ||     ||   ======  ||\\      || ||   //    ======= \n"
        "\t\t=========== ||     ||  ||====|| || \\     || ||  //    ||======\n"
        "\t\t    ||      ||=====||  ||    || ||  \\    || || //     ||\n"
        "\t\t    ||      ||=====||  ||====|| ||   \\   || ||//      ||======\n"
        "\t\t    ||      ||     ||  ||    || ||    \\  || ||\\             ||\n"
        "\t\t    ||      ||     ||  ||    || ||     \\ || || \\      ======||\n"
        "\t\t    ||      ||     ||  ||    || ||      \\|| ||  \\     =======\n\n",
        "34");

    PrintColoredText("\t\t               ======   =======    =======\n"
                     "\t\t             ||======  ||=====||  ||======||\n"
                     "\t\t             ||        ||     ||  ||      ||\n"
                     "\t\t             ||        ||     ||  ||======||\n"
                     "\t\t             ||======  ||     ||  ||======\n"
                     "\t\t             ||        ||     ||  || \\\n"
                     "\t\t             ||        ||=====||  ||  \\\n"
                     "\t\t             ||         =======   ||   \\\n\n",
                     "35");

    PrintColoredText(" \t\t    ||        ||    =======  ========== ||\\       ||   ==========\n"
                     "\t\t    ||        ||   ||======  ========== || \\      ||  ||========\n"
                     "\t\t    ||        ||   ||            ||     ||  \\     ||  ||\n"
                     "\t\t    ||        ||    ======       ||     ||   \\    ||  ||\n"
                     "\t\t    ||        ||    ======||     ||     ||    \\   ||  ||      =======\n"
                     "\t\t    ||        ||          ||     ||     ||     \\  ||  ||      ||====||\n"
                     "\t\t    ||========||    ======|| ========== ||      \\ ||  ||======||    ||\n"
                     "\t\t     ==========     =======  ========== ||       \\||   ========     ||",
                     "36");
}

const int MAX_Teachers = 10, MAX_Students = 100, MAX_Classes = 10, MAX_SUBJECTS = 6, MAX_DAYS = 30, MAX_MONTHS = 12, MAX_TERMS = 3;

int teacher_count = 0;
int student_count[MAX_Classes] = {0};

int teacherID[MAX_Teachers], teacherClass[MAX_Teachers], teacherSalary[MAX_Teachers], teacherAge[MAX_Teachers];
string teacherName[MAX_Teachers], teacherPassword[MAX_Teachers] = {""}, teacherDefaultPassword = "pass";
const string subjects[MAX_SUBJECTS] = {"English", "Mathematics", "PakStudies", "Physics", "Islamiyat", "Computer"};
char teacherGender[MAX_Teachers];

int attendance[MAX_Classes][MAX_Students][MAX_MONTHS * MAX_DAYS] = {0};
int marks[MAX_Classes][MAX_Students][MAX_SUBJECTS][MAX_TERMS], TotalMarks[MAX_SUBJECTS] = {100, 100, 50, 80, 50, 80}, PassingPerc = 40;
;

string name[MAX_Classes][MAX_Students], studentPassword[MAX_Classes][MAX_Students] = {""}, studentDefaultPassword = "pass";
int Roll_no[MAX_Classes][MAX_Students], studentClass[MAX_Classes][MAX_Students], studentAge[MAX_Classes][MAX_Students], studentFee[MAX_Classes][MAX_Students];
char studentGender[MAX_Classes][MAX_Students];

int main()
{
    // Load Student and Teacher data from file at the beginning
    LoadStudentFromFile();
    LoadTeacherFromFile();
    LoadStudentMarksFromFile();
    LoadStudentAttendanceFromFile();

    while (true)
    {
        TextTypingAnimation("\t\t\t\t<============ Welcome to School Management System ! ============> \n", 20, "34");
        TextTypingAnimation("\n [1] Login as admin.\n", 10, "34");
        TextTypingAnimation(" [2] Login as Teacher.\n", 10, "34");
        TextTypingAnimation(" [3] Login as student.\n", 10, "34");

        TextTypingAnimation("\n Enter Your choice from above : ", 10, "35");

        int ch;
        cin >> ch;
        // Check if input is valid
        if (cin.fail())
        {
            HandlingInvalidInputs();
            continue; // continue the loop
        }
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
            StudentLogin();
            break;
        default:
            PrintColoredText("Invalid Choice !!", "31");
            PausingOnInvalidInputs();
            system("cls");
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
            TextTypingAnimation(" Please Wait Logging in .....\n", 50, "32");
            TextTypingAnimation(" Getting Things Ready for you ...\n", 50, "32");
            system("cls");

            AdminPanel();
            break;
        }
        else
        {
            system("cls");
            PrintColoredText("--------Wrong Credentials!--------\n", "31");
            attempts++;
            if (attempts <= maxAttempts)
            {
                cout << "Attempts left: " << maxAttempts - attempts + 1 << endl;
            }
            else
            {
                system("cls");
                PrintColoredText("You have tried too many times. You can't sign in for 24 hours.\n", "31");
                TextTypingAnimation("Exiting School Management System..... \n", 50, "32");
                PausingOnInvalidInputs();
                system("cls");
                Pattern();
                exit(0);
            }
        }
    }
}

void AdminPanel()
{
    while (true)
    {
        TextTypingAnimation("\t\t\t\t<============ Welcome to the Admin Panel ============> \n", 20, "33");
        TextTypingAnimation("\n <======== MENU ========>\n", 10, "33");
        cout << " [1] Panel to perform  action on Teachers \n";
        cout << " [2] Panel to perform  action on Students \n";
        cout << " [3] Return to Main Menu \n";
        TextTypingAnimation(" \n Enter Your choice from above : ", 10, "33");

        int choice;
        cin >> choice;

        // Check if input is valid
        if (cin.fail())
        {
            HandlingInvalidInputs();
            continue; // continue the loop
        }
        switch (choice)
        {
        case 1:
            system("cls");
            AdminToPerformActionOnTeachers();
            break;
        case 2:
            system("cls");
            AdminToPerformActionOnStudents();
            break;
        case 3:
            SaveStudentToFile();
            SaveTeacherToFile();
            system("cls");
            TextTypingAnimation("Loging out.....\n", 150, "31");
            TextTypingAnimation("Returning to Main Menu.....\n", 150, "32");
            system("cls");
            return;
            break;
        default:
            cout << "Invalid Choice !!";
            PausingOnInvalidInputs();
            system("cls");
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
        cout << "[1] Add Teacher  \n";
        cout << "[2] Remove Teacher \n";
        cout << "[3] Update Teacher \n";
        cout << "[4] Show All Teachers \n";
        cout << "[5] Return to Admin Menu \n";
        cout << "\n Enter Your choice from above : ";
        int choice;
        cin >> choice;

        // Check if input is valid
        if (cin.fail())
        {
            HandlingInvalidInputs();
            continue; // continue the loop
        }
        switch (choice)
        {
        case 1:
            system("cls");
            addTeacher();
            break;
        case 2:
            system("cls");
            removeTeacher();
            break;
        case 3:
            system("cls");
            updateTeacher();
            break;
        case 4:
            system("cls");
            AllTeachers();
            break;
        case 5:
            system("cls");
            return;
            break;
        default:
            cout << "Invalid Choice !!";
            PausingOnInvalidInputs();
            system("cls");
            break;
        }
    }
}

void AdminToPerformActionOnStudents()
{
    while (true)
    {
        cout << "\n<======== MENU ========>\n";
        cout << "[1] Add Student \n";
        cout << "[2] Remove Student \n";
        cout << "[3] Update Student \n";
        cout << "[4] Show All Students \n";
        cout << "[5] Return to Admin Menu \n";
        cout << "\n Enter Your choice from above : ";
        int choice;
        cin >> choice;

        // Check if input is valid
        if (cin.fail())
        {
            HandlingInvalidInputs();
            continue; // continue the loop
        }
        switch (choice)
        {
        case 1:
            system("cls");
            Add_Student();
            break;
        case 2:
            system("cls");
            Remove_Student();
            break;
        case 3:
            system("cls");
            Update_Student();
            break;
        case 4:
            system("cls");
            All_Students();
            break;
        case 5:
            system("cls");
            return;
            break;
        default:
            cout << "Invalid Choice !!";
            PausingOnInvalidInputs();
            system("cls");
            break;
        }
    }
}
// <------------------------------------------------------->
// <---------------- Functions for Teacher ---------------->
void TeacherLogin()
{
    int attempts = 1;
    const int maxAttempts = 3;
    string enteredPassword;

    while (true)
    {
        cout << "Enter your ID : ";
        int teacherInpID;
        cin >> teacherInpID;
        // Check if input is valid
        if (cin.fail())
        {
            HandlingInvalidInputs();
            continue; // continue the loop
        }

        // Check if teacher ID exists
        bool teacherFound = false;
        int teacherIndex;
        //        Verify if Teacher Exists
        for (teacherIndex = 0; teacherIndex < teacher_count; ++teacherIndex)
        {
            if (teacherInpID == teacherID[teacherIndex])
            {
                teacherFound = true;
                break;
            }
        }

        if (!teacherFound)
        {
            cout << "Teacher with ID " << teacherInpID << " not found.\n";
            PausingOnInvalidInputs();
            system("cls");
            break;
        }

        // Check if a password is available for the teacher
        string storedPassword;
        if (teacherIndex < teacher_count)
        {
            storedPassword = teacherPassword[teacherIndex];
        }

        cout << "Enter your password: ";
        cin >> enteredPassword;

        if (enteredPassword == storedPassword)
        {
            system("cls");
            TextTypingAnimation(" Please Wait Logging in .....\n", 150, "32");
            TextTypingAnimation(" Getting Things Ready for you ...\n", 150, "32");
            system("cls");

            if (teacherIndex < teacher_count)
            {
                TeacherPanel(teacherClass[teacherIndex]);
            }

            // Exit the loop after processing
            break;
        }
        else
        {
            system("cls");
            PrintColoredText("--------Wrong Credentials!--------\n", "31");
            attempts++;
            if (attempts <= maxAttempts)
            {
                cout << "Attempts left: " << maxAttempts - attempts + 1 << endl;
            }
            else
            {
                system("cls");
                PrintColoredText("You have tried too many times. You can't sign in for 24 hours.\n", "31");
                TextTypingAnimation("Exiting School Management System..... \n", 50, "32");
                PausingOnInvalidInputs();
                system("cls");
                Pattern();
                exit(0);
            }
        }
    }
}
void addTeacher()
{
    if (teacher_count < MAX_Teachers)
    {
        TextTypingAnimation("\nEnter data carefully beacuse giving wrong data once can result in entering the whole data again\n", 5, "31");
        cout << "Enter Teacher ID: ";
        int teacherInpID;
        cin >> teacherInpID;
        // Check if input is valid
        if (cin.fail())
        {
            HandlingInvalidInputs();
            return;
        }
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
        cout << "Enter Teacher Name: ";
        string teacherInpName;
        cin >> teacherInpName;

        cout << "Enter Teacher Gender (M for Male, F for Female): ";
        char teacherInpGen;
        cin >> teacherInpGen;
        teacherInpGen = toupper(teacherInpGen);

        if (teacherInpGen != 'M' && teacherInpGen != 'F')
        {
            cout << "Invalid Gender!!";
            return;
        }

        cout << "Enter Teacher Age: ";
        int teacherInpAge;
        cin >> teacherInpAge;
        // Check if input is valid
        if (cin.fail())
        {
            HandlingInvalidInputs();
            return;
        }

        cout << "Enter Teacher Salary: ";
        int teacherInpSalary;
        cin >> teacherInpSalary;
        // Check if input is valid
        if (cin.fail())
        {
            HandlingInvalidInputs();
            return;
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
        teacherGender[teacher_count] = teacherInpGen;
        teacherAge[teacher_count] = teacherInpAge;
        teacherSalary[teacher_count] = teacherInpSalary;
        teacherClass[teacher_count] = teacherInpClass;

        TextTypingAnimation("Teacher added successfully.", 50, "32");
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
    // Check if input is valid
    if (cin.fail())
    {
        HandlingInvalidInputs();
        return;
    }

    if (teacher_count == 0)
    {
        cout << "No Teachers in the system!";
        return;
    }
    for (int i = 0; i < teacher_count; ++i)
    {
        if (idToRemove == teacherID[i])
        {
            // Display information about the teacher to be removed
            cout << "Are you sure you want to remove the following Student?\n";
            cout << "ID: " << teacherID[i] << "\nName: " << teacherName[i] << "\nClass: " << teacherClass[i] << "\nGender: " << teacherGender[i] << "\nAge: " << teacherAge[i] << "\nSalary: " << teacherSalary[i] << "\n";

            cout << "Enter 'Y' to confirm or any other key to cancel: ";
            char confirm;
            cin >> confirm;

            if (confirm == 'Y' || confirm == 'y')
            {

                // Remove the teacher by shifting the remaining elements
                teacherName[i] = teacherName[teacher_count - 1];
                teacherID[i] = teacherID[teacher_count - 1];
                teacherClass[i] = teacherClass[teacher_count - 1];
                teacherGender[i] = teacherGender[teacher_count - 1];
                teacherAge[i] = teacherAge[teacher_count - 1];
                teacherSalary[i] = teacherSalary[teacher_count - 1];

                // Decrement the teacher count
                teacher_count--;
                cout << "Teacher with ID " << idToRemove << " removed successfully.\n";
                cout << "<-------------------->\n";
                SaveTeacherToFile(); // Assuming you have a function to save teacher data to a file
                return;
            }
            else
            {
                cout << "Removal cancelled.\n";
                cout << "<-------------------->\n";
                return;
            }
        }
    }

    cout << "Teacher with ID " << idToRemove << " not found.\n";
    cout << "<-------------------->\n";
}
void updateTeacher()
{
    cout << "Enter the ID of the teacher to update: ";
    int idToUpdate;
    cin >> idToUpdate;
    // Check if input is valid
    if (cin.fail())
    {
        HandlingInvalidInputs();
        return;
    }

    for (int i = 0; i < teacher_count; ++i)
    {
        if (idToUpdate == teacherID[i])
        {
            // Update the teacher's information
            cout << "Enter the new Name: ";
            cin >> teacherName[i];
            cout << "Enter Teacher Gender (M for Male, F for Female): ";
            char teacherInpGen;
            cin >> teacherInpGen;
            teacherInpGen = toupper(teacherInpGen);

            if (teacherInpGen != 'M' && teacherInpGen != 'F')
            {
                cout << "Invalid Gender!!";
                return;
            }
            teacherGender[i] = teacherInpGen;

            cout << "Enter Teacher Age: ";
            cin >> teacherAge[i];
            // Check if input is valid
            if (cin.fail())
            {
                HandlingInvalidInputs();
                return; // continue the loop
            }

            cout << "Enter Teacher Salary: ";
            cin >> teacherSalary[i];
            if (cin.fail())
            {
                HandlingInvalidInputs();
                continue; // continue the loop
            }
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
            cout << "Teacher ID: " << teacherID[i] << endl;
            cout << "Teacher Name: " << teacherName[i] << endl;
            cout << "Teacher Class: " << teacherClass[i] << endl;
            cout << "Teacher Gender: " << (teacherGender[i] == 'M' ? "Male" : "Female") << endl;
            cout << "Teacher Age: " << teacherAge[i] << endl;
            cout << "Teacher Salary: " << teacherSalary[i] << endl;
            cout << "<-------------------->\n";
        }
        cout << "Press Enter to go back ...\n";
	    cin.ignore(); // Ignore any leftover newline characters
	    cin.get();    // Wait for Enter key press
	    system("cls");
    }
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
        if (teacherPassword[i] == "")
        {
            teacherPassword[i] = teacherDefaultPassword;
        }
        teacherFile << teacherID[i] << ' ' << teacherName[i] << ' ' << teacherClass[i] << ' ' << teacherGender[i] << ' ' << teacherAge[i] << ' ' << teacherSalary[i] << ' ' << teacherPassword[i] << '\n';
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

    while (teacherFile >> teacherID[teacher_count] >> teacherName[teacher_count] >> teacherClass[teacher_count] >> teacherGender[teacher_count] >> teacherAge[teacher_count] >> teacherSalary[teacher_count] >> teacherPassword[teacher_count])
    {
        teacher_count++;
    }

    teacherFile.close();
}
// <-------------------------------------------------------->

// <---------------- Functions for Students ---------------->
bool GetStudentDataFromAdmin(string &studentName, char &studentInpGen, int &studentInpAge, int &studentInpFee)
{
    cout << "Enter Student Name: ";
    cin >> studentName;

    cout << "Enter Student Gender (M for Male, F for Female): ";
    cin >> studentInpGen;
    studentInpGen = toupper(studentInpGen);

    if (studentInpGen != 'M' && studentInpGen != 'F')
    {
        cout << "Invalid Gender!!";
        return false;
    }

    cout << "Enter Student Age: ";
    cin >> studentInpAge;
    // Check if input is valid
    if (cin.fail())
    {
        HandlingInvalidInputs();
        return false;
    }

    cout << "Enter Student Fee: ";
    cin >> studentInpFee;
    // Check if input is valid
    if (cin.fail())
    {
        HandlingInvalidInputs();
        return false;
    }
    return true;
}
void Add_Student()
{
    string studentName;
    char studentInpGen;
    int studentRoll, studentInpAge, studentInpFee, studentClassInput;

    TextTypingAnimation("\nEnter data carefully beacuse giving wrong data once can result in entering the whole data again\n", 5, "31");
    cout << "Enter Student Roll No.: ";
    cin >> studentRoll;
    // Check if input is valid
    if (cin.fail())
    {
        HandlingInvalidInputs();
        return;
    }
    for (int i = 0; i < MAX_Classes; ++i)
    {
        for (int j = 0; j < student_count[i]; ++j)
        {
            if (studentRoll == Roll_no[i][j])
            {
                cout << "Sorry, Roll No. " << studentRoll << " already exists with Student " << name[i][j] << " in Class " << (i + 1) << endl;
                cout << "<-------------------->\n";
                return;
            }
        }
    }

    if (!GetStudentDataFromAdmin(studentName, studentInpGen, studentInpAge, studentInpFee))
    {
        // Invalid input, don't proceed further
        return;
    }
    cout << "Enter student class (1-10): ";
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
        studentClass[classIndex][student_count[classIndex]] = studentClassInput;
        studentGender[classIndex][student_count[classIndex]] = studentInpGen;
        studentAge[classIndex][student_count[classIndex]] = studentInpAge;
        studentFee[classIndex][student_count[classIndex]] = studentInpFee;
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
                cout << "Gender: " << studentGender[i][j] << endl;
                cout << "Age: " << studentAge[i][j] << endl;
                cout << "Fee: " << studentFee[i][j] << endl;
                TextTypingAnimation("<-------------------->\n", 1, "32");
            }
        }
    }
    cout << "Press Enter to go back ...\n";
    cin.ignore(); // Ignore any leftover newline characters
    cin.get();    // Wait for Enter key press
    system("cls");
    return;
}

void Update_Student()
{
    string studentName;
    char studentInpGen;
    int studentRoll, studentInpAge, studentInpFee;

    cout << "Enter the Roll No. of the student to update: ";
    int rollToUpdate;
    cin >> rollToUpdate;
    // Check if input is valid
    if (cin.fail())
    {
        HandlingInvalidInputs();
        return;
    }
    for (int i = 0; i < MAX_Classes; ++i)
    {
        for (int j = 0; j < student_count[i]; ++j)
        {
            if (rollToUpdate == Roll_no[i][j])
            {
                // Update the student's information
                cout << "Enter the new Roll No.: ";
                cin >> studentRoll;
                // Check if input is valid
                if (cin.fail())
                {
                    HandlingInvalidInputs();
                    return;
                }
                // Check if the new Roll No. is unique
                bool isRollUnique = true;
                for (int k = 0; k < MAX_Classes; ++k)
                {
                    for (int l = 0; l < student_count[k]; ++l)
                    {
                        if (studentRoll == Roll_no[k][l] && !(i == k && j == l))
                        {
                            isRollUnique = false;
                            break;
                        }
                    }
                    if (!isRollUnique)
                        break;
                }
                if (!isRollUnique)
                {
                    cout << "Error: The new Roll No. is already assigned to another student. Please choose a unique Roll No.\n";
                    return;
                }

                if (!GetStudentDataFromAdmin(studentName, studentInpGen, studentInpAge, studentInpFee))
                {
                    // Invalid input, don't proceed further
                    return;
                }

                name[i][j] = studentName;
                Roll_no[i][j] = studentRoll;
                studentGender[i][j] = studentInpGen;
                studentAge[i][j] = studentInpAge;
                studentFee[i][j] = studentInpFee;
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
    int rollToRemove;
    cin >> rollToRemove;
    // Check if input is valid
    if (cin.fail())
    {
        HandlingInvalidInputs();
        return;
    }
    for (int i = 0; i < MAX_Classes; ++i)
    {
        for (int j = 0; j < student_count[i]; ++j)
        {
            if (rollToRemove == Roll_no[i][j])
            {
                // Display information about the teacher to be removed
                cout << "Are you sure you want to remove the following teacher?\n";
                cout << "ROll No.: " << Roll_no[i][j] << "\nName: " << name[i][j] << "\nClass: " << studentClass[i][j] << "\nGender: " << studentGender[i][j] << "\nAge: " << studentAge[i][j] << "\nFee: " << studentFee[i][j] << "\n";

                cout << "Enter 'Y' to confirm or any other key to cancel: ";
                char confirm;
                cin >> confirm;

                if (confirm == 'Y' || confirm == 'y')
                {
                    // Remove the student by shifting the remaining elements
                    for (int k = j; k < student_count[i] - 1; ++k)
                    {
                        name[i][k] = name[i][k + 1];
                        Roll_no[i][k] = Roll_no[i][k + 1];
                        studentClass[i][k] = studentClass[i][k + 1];
                        studentGender[i][k] = studentGender[i][k + 1];
                        studentAge[i][k] = studentAge[i][k + 1];
                        studentFee[i][k] = studentFee[i][k + 1];
                    }
                    // Decrement the student count in the class
                    student_count[i]--;
                    cout << "Student with Roll No. " << rollToRemove << " removed successfully.\n";
                    cout << "<-------------------->\n";
                    SaveStudentToFile();
                    return;
                }
                else
                {
                    cout << "Removal cancelled.\n";
                    cout << "<-------------------->\n";
                    return;
                }
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
            if (studentPassword[i][j].empty())
            {
                studentPassword[i][j] = studentDefaultPassword;
            }
            file << i << ' ' << name[i][j] << ' ' << Roll_no[i][j] << ' ' << studentClass[i][j] << ' ' << studentGender[i][j] << ' ' << studentAge[i][j] << ' ' << studentFee[i][j] << ' ' << studentPassword[i][j] << '\n';
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
    while (file >> classIndex >> name[classIndex][student_count[classIndex]] >> Roll_no[classIndex][student_count[classIndex]] >> studentClass[classIndex][student_count[classIndex]] >> studentGender[classIndex][student_count[classIndex]] >> studentAge[classIndex][student_count[classIndex]] >> studentFee[classIndex][student_count[classIndex]] >> studentPassword[classIndex][student_count[classIndex]])
    {
        student_count[classIndex]++;
    }

    file.close();
}
// <-------------------------------------------------------->

// <======================================= End For Admin Functions/Actions =======================================>

// Functions Defined For Panels of Teachers and Students .

// Teacher Menu
void TeacherPanel(int teacherClass)
{
    while (true)
    {
        TextTypingAnimation("\t\t\t\t<============ Welcome to the Teacher Panel ============> \n", 3, "33");

        TextTypingAnimation("\n<======== Menu ========>\n", 1, "33");
        cout << "[1] Show My Details \n";
        cout << "[2] Show all Students \n";
        cout << "[3] Perform action on student marks \n";
        cout << "[4] Perform action on student Attendence \n";
        cout << "[5] Change Password \n";
        cout << "[6] Return to Main Menu\n";

        TextTypingAnimation("\n Enter Your choice from above : ", 1, "33");

        int choice;
        cin >> choice;
        // Check if input is valid
        if (cin.fail())
        {
            HandlingInvalidInputs();
            continue; // continue the loop
        }

        switch (choice)
        {
        case 1:
            system("cls");
            ShowTeacherDetailsToTeacher(teacherClass);
            break;
        case 2:
            system("cls");
            ShowStudentsInTeacherClass(teacherClass);
            break;
        case 3:
            system("cls");
            TeacherToPerformActionOnStudentMarks(teacherClass);
            break;
        case 4:
            system("cls");
            TeacherToPerformActionOnStudentAttendance(teacherClass);
            break;
        case 5:
            system("cls");
            ChangeTeacherPassword(teacherClass);
            break;
        case 6:
            system("cls");
            TextTypingAnimation("Loging out.....", 150, "31");
            cout << endl;
            TextTypingAnimation("Returning to Main Menu.....", 150, "32");
            cout << endl;
            system("cls");
            return;
            break;
        default:
            TextTypingAnimation("Invalid Choice !!", 1, "31");
            PausingOnInvalidInputs();
            system("cls");
            break;
        }
    }
}
void ShowTeacherDetailsToTeacher(int teacherclass)
{
    cout << "\n<======== Teacher Details ========>\n";

    TextTypingAnimation("Assigned Class: ", 1, "35");
    cout << teacherclass << endl;
    TextTypingAnimation("Class Strength : ", 1, "35");
    cout << student_count[teacherclass - 1] << endl;
    for (int i = 0; i < MAX_Teachers; i++)
    {
        if (teacherclass == teacherClass[i])
        {

            TextTypingAnimation("Teacher Name: ", 1, "35");
            cout << teacherName[i] << endl;
            TextTypingAnimation("Teacher ID: ", 1, "35");
            cout << teacherID[i] << endl;
            TextTypingAnimation("Teacher Gender: ", 1, "35");
            cout << (teacherGender[i] == 'M' ? "Male" : "Female") << endl;
            TextTypingAnimation("Teacher Age: ", 1, "35");
            cout << teacherAge[i] << endl;
            TextTypingAnimation("Teacher Salary: ", 1, "35");
            cout << teacherSalary[i] << endl;
            TextTypingAnimation("Password: ", 1, "35");
            cout << teacherPassword[i] << endl;

            cout << "<-------------------->\n";
            cout << "Press Enter to go back ...\n";
            cin.ignore(); // Ignore any leftover newline characters
            cin.get();    // Wait for Enter key press
            system("cls");
            break;
        }
    }

    PausingOnInvalidInputs();
}

void ShowStudentsInTeacherClass(int teacherClass)
{
    cout << "\n\t\t<======== Viewing All Students ========>\n";
    if (student_count[teacherClass - 1] == 0)
    {
        TextTypingAnimation("No Students in the Class.\n", 1, "31");
        PausingOnInvalidInputs();
        system("cls");
    }
    else
    {
        TextTypingAnimation("\n\t\t  ROLL NO.\t\t  NAME\n", 1, "32");
        PausingOnInvalidInputs();
        cout << "\t\t----------------------------------\n";
        for (int i = 0; i < student_count[teacherClass - 1]; ++i)
        {
            cout << "\t\t    " << Roll_no[teacherClass - 1][i] << "\t\t\t  " << name[teacherClass - 1][i] << endl;
        }
        TextTypingAnimation("\t\t<----------------------------------->\n", 1, "32");
        cout << "Press Enter to go back ...\n";
        cin.ignore(); // Ignore any leftover newline characters
        cin.get();    // Wait for Enter key press
        system("cls");
        return;
    }
}

void TeacherToPerformActionOnStudentMarks(int teacherClass)
{
    while (true)
    {
        cout << "\n<======== Menu ========>\n";
        cout << "[1] Record Marks\n";
        cout << "[2] Update Marks\n";
        cout << "[3] Display Marks For Student\n";
        cout << "[4] Return to Teacher Menu\n";

        cout << "\n Enter Your choice from above : ";

        int choice;
        cin >> choice;
        // Check if input is valid
        if (cin.fail())
        {
            HandlingInvalidInputs();
            continue; // continue the loop
        }

        switch (choice)
        {
        case 1:
            system("cls");
            RecordMarks(teacherClass);
            break;
        case 2:
            system("cls");
            UpdateMarks(teacherClass);
            break;
        case 3:
            system("cls");
            DisplayStudentMarks(teacherClass);
            break;
        case 4:
            system("cls");
            return;
            break;
        default:
            cout << "Invalid Choice !!";
            PausingOnInvalidInputs();
            system("cls");
            break;
        }
    }
}

void RecordMarks(int teacherClass)
{
    cout << "\n<======== Record Marks ========>\n";

    if (student_count[teacherClass - 1] == 0)
    {
        TextTypingAnimation("No Students in the Class.\n", 1, "31");
        PausingOnInvalidInputs();
        system("cls");
    }
    else
    {
        int term;
        cout << "Enter Term (1,2,3) : ";
        cin >> term;
        if (term >= 1 && term <= 3)
        {
            // Iterate over each student in the specified class
            for (int i = 0; i < student_count[teacherClass - 1]; ++i)
            {

                cout << "Recording marks for " << name[teacherClass - 1][i] << " (Roll No. " << Roll_no[teacherClass - 1][i] << ")\n";

                // Iterate over each subject
                for (int j = 0; j < MAX_SUBJECTS; ++j)
                {
                    while (true)
                    {
                        cout << "Enter marks for " << subjects[j] << ": ";
                        int inpmarks;
                        cin >> inpmarks;
                        if (cin.fail() || inpmarks < 0 || !(inpmarks <= TotalMarks[j]))
                        {
                            if (cin.fail())
                            {
                                HandlingInvalidInputs();
                            }
                            else
                            {
                                cout << "Invalid input! Please enter marks between 0 and " << TotalMarks[j] << ".\n";
                            }
                            continue;
                        }
                        else
                        {
                            marks[teacherClass - 1][i][j][term] = inpmarks;
                            break; // Break out of the loop if input is valid
                        }
                    }
                }
            }
        }
        else
        {
            cout << "Invalid Term\n";
            return;
        }

        cout << "Marks recorded successfully for class " << teacherClass << ", Term " << term << ".\n";
        SaveStudentMarksToFile();
    }
}
void UpdateMarks(int teacherClass)
{
    cout << "\n<======== Update Marks ========>\n";

    int rollToUpdate, term;
    cout << "Enter Term (1,2,3): ";
    cin >> term;
    if (term >= 1 && term <= 3)
    {

        cout << "Enter Roll No.: ";
        cin >> rollToUpdate;
        // Check if input is valid
        if (cin.fail())
        {
            HandlingInvalidInputs();
            return;
        }
        // Find the student with the specified roll number
        for (int i = 0; i < MAX_Classes; ++i)
        {
            for (int j = 0; j < student_count[i]; ++j)
            {
                if (rollToUpdate == Roll_no[i][j])
                {
                    // Check if the student's class matches the class assigned to the teacher
                    if (i + 1 == teacherClass)
                    {
                        cout << "Updating marks for " << name[i][j] << " (Roll No. " << Roll_no[i][j] << "):\n";

                        // Update marks for each subject
                        for (int k = 0; k < MAX_SUBJECTS; ++k)
                        {
                        	while (true)
                            {
	                            cout << "Enter new marks for " << subjects[k] << ": ";
	                            int inpmarks;
		                        cin >> inpmarks;
		                        if (cin.fail() || inpmarks < 0 || !(inpmarks <= TotalMarks[k]))
		                        {
		                            if (cin.fail())
		                            {
		                                HandlingInvalidInputs();
		                            }
		                            else
		                            {
		                                cout << "Invalid input! Please enter marks between 0 and " << TotalMarks[k] << ".\n";
		                            }
		                                continue;
		                        }
		                        else
		                        {
		                            marks[i][j][k][term] = inpmarks;
		                            break; // Break out of the loop if input is valid
		                        }
    
                            }
						}

                        cout << "Marks updated successfully for student " << name[i][j] << ", Term " << term << ".\n";
                        SaveStudentMarksToFile();
                    }
                    else
                    {
                        cout << "Student with Roll No. " << rollToUpdate << " is not in your assigned class.\n";
                    }
                    return; // Exit the function after updating marks
                }
            }
        }
        cout << "Student with Roll No. " << rollToUpdate << " not found.\n";
    }
    else
    {
        cout << "Invalid Term!\n";
        return;
    }
}
void DisplayStudentMarks(int teacherClass)
{
    int rollToDisplay, term, Obperc;
    cout << "Enter Term (1,2,3): ";
    cin >> term;
    if (term >= 1 && term <= 3)
    {
        cout << "Show All Students Marks ? (Y for yes, N for no) : ";
        char showmarks;
        cin >> showmarks;

        if (showmarks == 'Y' || showmarks == 'y')
        {
            for (int i = 0; i < student_count[teacherClass - 1]; ++i)
            {
                cout << "\n\t\tStudent: " << name[teacherClass - 1][i] << " (Roll No. " << Roll_no[teacherClass - 1][i] << ")\n";
                cout << "\t\t--------------------------------\n";

                cout << "\t\tSubjects\t"
                     << "\tMarks\n";
                cout << "\t\t-----------------------------\n";
                for (int j = 0; j < MAX_SUBJECTS; ++j)
                {
                    cout << "\t\t " << subjects[j] << "\t\t";
                    // Showing Marks less than 40% with red color
                    int ObMarks = marks[teacherClass - 1][i][j][term];
                    Obperc = (ObMarks * 100) / TotalMarks[j];
                    if (Obperc < PassingPerc)
                    {
                        cout << "\033[31m" << marks[teacherClass - 1][i][j][term] << "\033[0m" << endl;
                    }
                    else
                    {
                        cout << marks[teacherClass - 1][i][j][term] << endl;
                    }
                }

                cout << "\n\t\t<-------------------------->\n";
            }
            cout << "Press Enter to go back ...\n";
		    cin.ignore(); // Ignore any leftover newline characters
		    cin.get();    // Wait for Enter key press
		    system("cls");
            return;
        }
        else if (showmarks == 'N' || showmarks == 'n')
        {

            cout << "Enter Roll No.: ";
            cin >> rollToDisplay;
            // Check if input is valid
            if (cin.fail())
            {
                HandlingInvalidInputs();
                return;
            }
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
                            cout << "\n\t\tStudent: " << name[i][j] << " (Roll No. " << Roll_no[i][j] << ")\n";
                            cout << "\t\t--------------------------------\n";

                            cout << "\t\tSubjects\t"
                                 << "\tMarks\n";
                            cout << "\t\t-----------------------------\n";
                            // Display marks for each subject
                            for (int k = 0; k < MAX_SUBJECTS; ++k)
                            {
                                cout << "\t\t " << subjects[k] << "\t\t";
                                // Showing Marks less than 40% with red color
                                int ObMarks = marks[i][j][k][term];
                                Obperc = (ObMarks * 100) / TotalMarks[k];
                                if (Obperc < PassingPerc)
                                {
                                    cout << "\033[31m" << ObMarks << "\033[0m" << endl;
                                }
                                else
                                {
                                    cout << ObMarks << endl;
                                }
                            }
                            cout << "\n\t\t<-------------------------->\n";
                            cout << "Press Enter to go back ...\n";
						    cin.ignore(); // Ignore any leftover newline characters
						    cin.get();    // Wait for Enter key press
						    system("cls");
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
        else
        {

            cout << "Invalid Choice!\n";
            return;
        }
    }
    else
    {
        cout << "Invalid Term!\n";
        return;
    }
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

            for (int term = 0; term < MAX_TERMS; ++term)
            {
                for (int k = 0; k < MAX_SUBJECTS; ++k)
                {
                    file << marks[i][j][k][term] << ' ';
                }
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

    int roll, classIndex, subjectMarks;

    while (file >> classIndex >> roll)
    {
        // Find the student with the specified roll number and update the marks
        for (int i = 0; i < student_count[classIndex]; ++i)
        {
            if (roll == Roll_no[classIndex][i])
            {
                for (int term = 0; term < MAX_TERMS; ++term)
                {
                    for (int j = 0; j < MAX_SUBJECTS; ++j)
                    {
                        file >> subjectMarks;
                        marks[classIndex][i][j][term] = subjectMarks;
                    }
                }
                break; // Marks found for the student, break the loop
            }
        }
    }

    file.close();
}

void TeacherToPerformActionOnStudentAttendance(int teacherClass)
{
    while (true)
    {
        cout << "\n<======== Menu ========>\n";
        cout << "[1] Record Attendance\n";
        cout << "[2] Update Attendance\n";
        cout << "[3] Display Attendance\n";
        cout << "[4] Return to Teacher Menu\n";

        cout << "\n Enter Your choice from above : ";

        int choice;
        cin >> choice;
        // Check if input is valid
        if (cin.fail())
        {
            HandlingInvalidInputs();
            continue;
        }
        switch (choice)
        {
        case 1:
            system("cls");
            RecordAttendance(teacherClass);
            break;
        case 2:
            system("cls");
            UpdateStudentAttendance(teacherClass);
            break;
        case 3:
            system("cls");
            ViewStudentAttendance(teacherClass);
            break;
        case 4:
            system("cls");
            return;
            break;
        default:
            cout << "Invalid Choice !!";
            PausingOnInvalidInputs();
            system("cls");
            break;
        }
    }
}
void RecordAttendance(int teacherClass)
{
    cout << "\n<======== Mark Attendance ========>\n";

    // Get the current date and time
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int currentDayIndex = ltm->tm_mday - 1;
    // Print the current date
    cout << "Date: " << 1900 + ltm->tm_year << '-' << 1 + ltm->tm_mon << '-' << ltm->tm_mday << "\n";

    if (student_count[teacherClass - 1] == 0)
    {
        cout << "No Students in the Class.\n";
    }
    else
    {
        for (int i = 0; i < student_count[teacherClass - 1]; ++i)
        {
        	if (ltm->tm_wday >= 1 && ltm->tm_wday <= 5)
           {
	            cout << "Marking attendance for " << name[teacherClass - 1][i] << " (Roll No. " << Roll_no[teacherClass - 1][i] << ")\n";
	
	            while (true)
	            {
	                // Mark attendance for the student
	
	                cout << "Is the student present? (1 for Present, 0 for Absent): ";
	                int status;
	                cin >> status;
	
	                if (status == 0 || status == 1)
	                {
	                    // Save attendance for the current day
	                    attendance[teacherClass - 1][i][currentDayIndex] = status;
	                    break; // Break out of the loop if input is valid
	                }
	                else
	                {
	                    cout << "Invalid Status! Please enter 1 for Present or 0 for Absent.\n\n";
	                    cin.clear();               // Clear the error state
	                    cin.ignore(INT_MAX, '\n'); // Ignore the invalid input
	                }
	            }
	            
	            
	            
           	    PausingOnInvalidInputs();
           	    system("cls");
           	    return;
		   }else{
			   	TextTypingAnimation(" Today is Holiday!\n", 150, "32");
			   	return;
		   }
        }
    }

    cout << "Attendance marked successfully for class " << teacherClass << ".\n";
    // Save attendance to file after marking
    SaveStudentAttendanceToFile();
}

void UpdateStudentAttendance(int teacherClass)
{
    cout << "\n<======== Update Attendence ========>\n";

    int rollToUpdate;
    cout << "Enter Roll No.: ";
    cin >> rollToUpdate;

    // Get the current date and time
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int currentDayIndex = ltm->tm_mday - 1;

    for (int i = 0; i < MAX_Classes; ++i)
    {
        for (int j = 0; j < student_count[i]; ++j)
        {
            if (rollToUpdate == Roll_no[i][j])
            {
                // Check if the student's class matches the class assigned to the teacher
                if (i + 1 == teacherClass)
                {
                    cout << "Updating attendance for " << name[teacherClass - 1][j] << " (Roll No. " << Roll_no[teacherClass - 1][j] << ")\n";

                    // Mark attendance for the student
                    cout << "Is the student present? (1 for Present, 0 for Absent): ";
                    int status;
                    cin >> status;

                    if (status == 0 || status == 1)
                    {
                        // Save attendance for the current day
                        attendance[teacherClass - 1][j][currentDayIndex] = status;
                        cout << "Student Attendance Updated Successfully \n";
	                    SaveStudentAttendanceToFile();
	                    return;
                    }
                    else
                    {
                        cout << "Invalid Status! Please enter 1 for Present or 0 for Absent.\n\n";
                        cin.clear();               // Clear the error state
                        cin.ignore(INT_MAX, '\n'); // Ignore the invalid input
                    }
                    
                }
                else
                {
                    cout << "Student is not in your assigned class \n";
                    return;
                }
            }
        }
    }
    cout << "Student with Roll No. " << rollToUpdate << " not found.\n";
}
void ViewStudentAttendance(int teacherClass)
{
    cout << "\n\t\t<======== View Attendance ========>\n";

    if (student_count[teacherClass - 1] == 0)
    {
        cout << "No Students in the Class.\n";
    }
    else
    {
        // Iterate over each student in the specified class
        for (int i = 0; i < student_count[teacherClass - 1]; ++i)
        {
            cout << "\n\t\tStudent: " << name[teacherClass - 1][i] << " (Roll No. " << Roll_no[teacherClass - 1][i] << ")\n";
            cout << "\t\t--------------------------------\n";

            // Get the current date and time
            time_t now = time(0);
            tm *ltm = localtime(&now);
            int currentDay = ltm->tm_mday;

            // Display attendance for each day
            cout << "\t\tDay\t"
                 << "\tAttendance\n";
            cout << "\t\t-----------------------------\n";
            for (int j = 0; j < currentDay; ++j)
            {
	                cout << "\t\t " << (j + 1) << "\t\t";
	                if (attendance[teacherClass - 1][i][j])
	                {
	                    PrintColoredText("Present", "32");
	                }
	                else
	                {
	                    PrintColoredText("Absent", "31");
	                }
	                cout << endl;
            }

            cout << "\n\t\t<-------------------------->\n";
        }
        cout << "Press Enter to go back ...\n";
	    cin.ignore(); // Ignore any leftover newline characters
	    cin.get();    // Wait for Enter key press
	    system("cls");
    }
}
void ChangeTeacherPassword(int teacherclass)
{

    string currentPassword, newPassword;

    // Prompt for the current password
    cout << "Enter your current password: ";
    cin >> currentPassword;
    for (int i = 0; i < MAX_Teachers; i++)
    {
        if (teacherclass == teacherClass[i])
        {
            // Verify the current password
            if (currentPassword == teacherPassword[i])
            {
                // Prompt for a new password
                cout << "Enter your new password: ";
                cin >> newPassword;

                // Update the password in the array
                teacherPassword[i] = newPassword;

                // Save the updated password to the file
                SaveTeacherToFile();

                cout << "Password updated successfully!\n";
            }
            else
            {
                cout << "Incorrect current password. Password not updated.\n";
            }
        }
    }
}
// Function to save student attendance to a file
void SaveStudentAttendanceToFile()
{
    ofstream file("student_attendance.txt");

    if (!file.is_open())
    {
        cout << "Error opening Student Attendance file for writing.\n";
        return;
    }

    // Get the current date and time
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int currentMonth = 1 + ltm->tm_mon; // Current month (1-12)
    int currentDay = ltm->tm_mday;
    
    for (int i = 0; i < MAX_Classes; ++i)
    {
        for (int j = 0; j < student_count[i]; ++j)
        {
            file << i << ' ' << Roll_no[i][j] << ' ';

             // Save attendance for each school day up to the current day and month
            for (int day = 0; day < currentDay; ++day)
            {
                // Check if it's a school day (Monday to Friday) and not a holiday
                if (ltm->tm_wday >= 1 && ltm->tm_wday <= 5 )
                {
                    file << attendance[i][j][day] << ' ';
                }
            }

            file << '\n';
        }
    }

    file.close();
}
void LoadStudentAttendanceFromFile()
{
    ifstream file("student_attendance.txt");
    if (!file.is_open())
    {
        cout << "Error opening Student Attendance file for Reading.\n";
        return;
    }

    time_t now = time(0);
    tm *ltm = localtime(&now);
    int currentDay = ltm->tm_mday;
    int classIndex, status;
    int roll;

    while (file >> classIndex >> roll)
    {
        // Find the student with the specified roll number and update the attendance up to the current day
        for (int i = 0; i < MAX_Students; ++i)
        {
            if (roll == Roll_no[classIndex][i])
            {
                for (int j = 0; j < currentDay; ++j)
                {
                    file >> status;
                    // Update attendance only if it's a school day (Monday to Friday)
                    if (ltm->tm_wday >= 1 && ltm->tm_wday <= 5)
                    {
                        attendance[classIndex][i][j] = status;
                    }
                }
                break; // Attendance found for the student, break the loop
            }
        }
    }

    file.close();
}

// <---------------- Function/Actions that Student can Perform ---------------->
void StudentLogin()
{
    int attempts = 1;
    const int maxAttempts = 3;
    string storedPassword, enteredPassword;
    while (true)
    {

        cout << "Enter your Roll No.: ";
        int studentRoll;
        cin >> studentRoll;
        // Check if input is valid
        if (cin.fail())
        {
            HandlingInvalidInputs();
            continue;
        }
        // Check if student Roll No. exists
        bool studentFound = false;
        int studentIndex, studentClass;

        for (int i = 0; i < MAX_Classes; ++i)
        {
            for (int j = 0; j < student_count[i]; ++j)
            {
                if (studentRoll == Roll_no[i][j])
                {
                    studentFound = true;
                    studentClass = i;
                    studentIndex = j;
                    storedPassword = studentPassword[i][j];
                    break;
                }
            }
        }

        if (!studentFound)
        {
            cout << "Student with Roll No. " << studentRoll << " not found.\n";
            PausingOnInvalidInputs();
            system("cls");
            break;
        }

        cout << "Enter your password: ";
        cin >> enteredPassword;

        if (enteredPassword == storedPassword)
        {
            system("cls");
            TextTypingAnimation(" Please Wait Logging in .....\n", 150, "32");
            TextTypingAnimation(" Getting Things Ready for you ...\n", 150, "32");
            system("cls");
            StudentPanel(studentClass, studentIndex);
            break;
        }
        else
        {
            system("cls");
            PrintColoredText("--------Wrong Credentials!--------\n", "31");
            attempts++;
            if (attempts <= maxAttempts)
            {
                cout << "Attempts left: " << maxAttempts - attempts + 1 << endl;
            }
            else
            {
                system("cls");
                PrintColoredText("You have tried too many times. You can't sign in for 24 hours.\n", "31");
                TextTypingAnimation("Exiting School Management System..... \n", 50, "32");
                PausingOnInvalidInputs();
                system("cls");
                Pattern();
                exit(0);
            }
        }
    }
}
void StudentPanel(int studentClass, int studentIndex)
{
    while (true)
    {
        TextTypingAnimation("\t\t\t\t<============ Welcome to the Student Panel ============> \n", 20, "33");
        TextTypingAnimation("\n <======== MENU ========>\n", 10, "33");
        cout << "[1] View My Details\n";
        cout << "[2] View My Marks\n";
        cout << "[3] View My Attendance\n";
        cout << "[4] Change password\n";
        cout << "[5] Return to Main Menu\n";
        TextTypingAnimation(" \n Enter Your choice from above : ", 10, "33");

        int choice;
        cin >> choice;

        // Check if input is valid
        if (cin.fail())
        {
            HandlingInvalidInputs();
            continue;
        }
        switch (choice)
        {
        case 1:
            system("cls");
            ViewStudentDetailsToStudent(studentClass, studentIndex);
            break;
        case 2:
            system("cls");
            ViewStudentMarksToStudent(studentClass, studentIndex);
            break;
        case 3:
            system("cls");
            ViewStudentAttendanceToStudent(studentClass, studentIndex);
            break;
        case 4:
            system("cls");
            ChangeStudentPassword(studentClass, studentIndex);
            break;
        case 5:
            system("cls");
            TextTypingAnimation("Loging out.....\n", 150, "31");
            TextTypingAnimation("Returning to Main Menu.....\n", 150, "32");
            system("cls");
            return;
            break;
        default:
            cout << "Invalid Choice !!";
            PausingOnInvalidInputs();
            system("cls");
            break;
        }
    }
}
void ViewStudentDetailsToStudent(int studentclass, int studentIndex)
{
    cout << "\n<======== Student Details ========>\n";

    bool teacherFound = false;
    TextTypingAnimation("Class Teacher: ", 1, "35");
    for (int i = 0; i < MAX_Teachers; i++)
    {
        if (teacherClass[i] == (studentclass + 1))
        {
            teacherFound = true;
            cout << teacherName[i] << endl;
        }
    }
    if (!teacherFound)
    {
        TextTypingAnimation("Teacher not assigned\n", 1, "31");
    }

    TextTypingAnimation("Roll No.: ", 1, "35");
    cout << Roll_no[studentclass][studentIndex] << endl;

    TextTypingAnimation("Name: ", 1, "35");
    cout << name[studentclass][studentIndex] << endl;

    TextTypingAnimation("Class: ", 1, "35");
    cout << studentClass[studentclass][studentIndex] << endl;

    TextTypingAnimation("Gender: ", 1, "35");
    cout << (studentGender[studentclass][studentIndex] == 'M' ? "Male" : "Female") << endl;

    TextTypingAnimation("Age: ", 1, "35");
    cout << studentAge[studentclass][studentIndex] << endl;

    TextTypingAnimation("StudentFee: ", 1, "35");
    cout << studentFee[studentclass][studentIndex] << endl;

    TextTypingAnimation("Total Subjects: ", 1, "35");
    cout << MAX_SUBJECTS << endl;

    TextTypingAnimation("Password: ", 1, "35");
    cout << studentPassword[studentclass][studentIndex] << endl;

    cout << "<-------------------->\n";
    cout << "Press Enter to go back ...\n";
    cin.ignore(); // Ignore any leftover newline characters
    cin.get();    // Wait for Enter key press
    system("cls");
    return;
}

void ViewStudentMarksToStudent(int studentClass, int studentIndex)
{
    cout << "\n<======== Viewing Marks ========>\n";
    int term, ObMarks, Obperc, AllSujectsTotalMarks = 0, AllSujectsObMarks = 0;
    cout << "Enter Term (1,2,3): ";
    cin >> term;
    if (term >= 1 && term <= 3)
    {

        cout << "\n\t\t  SUBJECT\t\tMARKS\n";
        cout << "\t\t----------------------------------\n";
        for (int i = 0; i < MAX_SUBJECTS; ++i)
        {
            cout << "\t\t|  " << subjects[i] << "\t\t  ";
            // Showing Marks less than 40% with red color
            ObMarks = marks[studentClass][studentIndex][i][term];
            Obperc = (ObMarks * 100) / TotalMarks[i];

            if (Obperc < PassingPerc)
            {
                cout << "\033[31m" << ObMarks << "\033[0m" << "     |"<< endl;
            }
            else
            {
                cout << ObMarks << "     |"<< endl;
            }
            AllSujectsObMarks += ObMarks;
            AllSujectsTotalMarks += TotalMarks[i];
        }
        cout << "\t\t----------------------------------\n";
        cout << "\t\t     Total Marks : " << AllSujectsTotalMarks << endl;
        cout << "\t\t     Obtained Marks : " << AllSujectsObMarks << endl;
        cout << "\t\t     Obtained Percentage : " << (AllSujectsTotalMarks != 0 ? (AllSujectsObMarks * 100) / AllSujectsTotalMarks : 0) << "%" << endl;
        cout << "\t\t<----------------------------------->\n";
        cout << "Press Enter to go back ...\n";
	    cin.ignore(); // Ignore any leftover newline characters
	    cin.get();    // Wait for Enter key press
	    system("cls");
    }
    else
    {
        cout << "Invalid Term !\n";
        return;
    }
}
void ViewStudentAttendanceToStudent(int studentClass, int studentIndex)
{
    cout << "\n\t\t<======== Viewing Attendance ========>\n";

    // Get the current date and time
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int currentDay = ltm->tm_mday;

    cout << "\t\tDay\t"
         << "\tAttendance\n";
    cout << "\t\t-----------------------------\n";
    // Display attendance for each day
    for (int i = 0; i < currentDay; ++i)
    {
	        cout << "\t\t " << (i + 1) << "\t\t";
	        if (attendance[studentClass][studentIndex][i])
	        {
	            PrintColoredText("Present", "32");
	        }
	        else
	        {
	            PrintColoredText("Absent", "31");
	        }
	        cout << endl;
    }
    cout << "\t\t<----------------------------------->\n";
    cout << "Press Enter to go back ...\n";
    cin.ignore(); // Ignore any leftover newline characters
    cin.get();    // Wait for Enter key press
    system("cls");
}
void ChangeStudentPassword(int studentClass, int studentIndex)
{
    string currentPassword, newPassword;

    // Prompt for the current password
    cout << "Enter your current password: ";
    cin >> currentPassword;

    // Verify the current password
    if (currentPassword == studentPassword[studentClass][studentIndex])
    {
        // Prompt for a new password
        cout << "Enter your new password: ";
        cin >> newPassword;

        // Update the password in the array
        studentPassword[studentClass][studentIndex] = newPassword;

        // Save the updated password to the file
        SaveStudentToFile();

        cout << "Password updated successfully!\n";
    }
    else
    {
        cout << "Incorrect current password. Password not updated.\n";
    }
}
