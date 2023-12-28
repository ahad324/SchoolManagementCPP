#include <iostream>
#include <fstream>
#include<string>
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
void addTeacher();
void removeTeacher();
void updateTeacher();
void SaveTeacherToFile();
void LoadTeacherFromFile();
void AllTeachers();
// Functions defined for students.
void Add_Student();
void All_Students();
void Update_Student();
void Remove_Student();
// Function for text typing animation.
void TextTypingAnimation(const std::string &text, int delay);

const int MAX_Teachers = 10;
int teacher_count = 0;
string teacherPassword="Password", enteredPassword;
            // Check if teacher ID exists
            bool teacherFound;
string teacherName[MAX_Teachers], teacherID[MAX_Teachers];

const int MAX_Students = 100;
const int MAX_Classes = 10;
int student_count[MAX_Classes] = {0};

string studentClass[MAX_Classes][MAX_Students], Roll_no[MAX_Classes][MAX_Students], name[MAX_Classes][MAX_Students];

void SaveToFile()
{
    ofstream file("student_data.txt");

    if (!file.is_open())
    {
        cout << "Error opening file for writing.\n";
        return;
    }

    for (int i = 0; i < MAX_Classes; ++i)
    {
        for (int j = 0; j < student_count[i]; ++j)
        {
            file << name[i][j] << ' ' << Roll_no[i][j] << ' ' << studentClass[i][j] << '\n';
        }
    }

    file.close();
}
// Function to load student data from a file
void LoadFromFile()
{
    ifstream file("student_data.txt");

    if (!file.is_open())
    {
        cout << "Error opening file for reading.\n";
        return;
    }

    int classIndex; // Initialize classIndex
    while (file >> name[classIndex][student_count[classIndex]] >> Roll_no[classIndex][student_count[classIndex]] >> studentClass[classIndex][student_count[classIndex]])
    {
        student_count[classIndex]++;
    }

    file.close();
}

int main()
{
    // Load student data from file at the beginning
    LoadFromFile();
    LoadTeacherFromFile();
    cout << "Welcome to School Management System ! \n";
    while (true)
    {
        cout << "\n1) Login as admin.\n";
        cout << "2) Login as Teacher.\n";
        cout << "3) Login as student.\n";
        cout << "Enter Your choice from above : ";
        int ch;
        cin >> ch;
        switch (ch)
        {
        case 1:
            AdminLogin();
            break;
        case 2:
            TeacherLogin();
            break;
        case 3:
            cout << "GO to home.";
            SaveToFile();
            exit(0);
            break;
        default:
            cout << "Invalid Option! Enter Only from above options.";
            break;
        }
    }

    return 0;
}
void AdminLogin()
{
    system("cls");
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
            // Showing Text Animation
            TextTypingAnimation("Please Wait Logging in.....", 50);
            cout << endl;
            TextTypingAnimation("Getting Things Ready for you...", 150);
            cout << endl;
            TextTypingAnimation("Welcome to the Admin Panel", 100);
            cout << endl;
            system("cls");
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
                  this_thread::sleep_for(chrono::seconds(3));
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
        cout << "\n<======== MENU ========>\n";
        cout << "1) Panel to perform  action on Teachers \n";
        cout << "2) Panel to perform  action on Students \n";
        cout << "3) Return to Main Menu. \n";
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
        		AdminToPerformActionOnTeachers();
        		break;
        	case 2:
			    AdminToPerformActionOnStudents();
				break;
			case 3:
				SaveToFile();
                SaveTeacherToFile();
                TextTypingAnimation("Loging out.....", 150);
                cout<<endl;
                TextTypingAnimation("Returning to Main Menu.....", 150);
                cout<<endl;
			    return;
			    break;
            default:
                cout << "Invalid Choice !!";
                break;
        }
    }
}
void AdminToPerformActionOnTeachers(){
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

void AdminToPerformActionOnStudents(){
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
void TeacherLogin(){
            LoadTeacherFromFile();
            while(true){
            cout << "Welcome to teachers panel.\n";
            cout << "Enter your ID : ";
            int teacherInpID;
            cin >> teacherInpID;

            teacherFound = false; 

            for (int i = 0; i < teacher_count; ++i)
            {
                if (teacherInpID == stoi(teacherID[i]))
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
                cout << "Login successful.\n";
                // TeacherPanel();
            }
            else
            {
                cout << "Incorrect password.\n";
            }
}
}
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
        SaveToFile(); // Save data to file after adding a student
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
                SaveToFile();
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
                SaveToFile();
                return;
            }
        }
    }

    cout << "Student with Roll No. " << rollToRemove << " not found.\n";
    cout << "<-------------------->\n";
}

void TextTypingAnimation(const std::string &text, int delay)
{
    for (char c : text)
    {
        std::cout << c;
          std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

// Functions for Teachers.
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
            if (teacherInpID == stoi(teacherID[i]))
            {
                cout << "Sorry, Teacher with ID  " << teacherInpID << " already exists with Teacher " << teacherName[j] <<endl;
                cout << "<-------------------->\n";
                return;
            }
        }
    }
    
        teacherID[teacher_count] = to_string(teacherInpID);
        teacherName[teacher_count]=teacherInpName;
        TextTypingAnimation("Teacher added successfully.",50);
        teacher_count++;
        SaveTeacherToFile(); // Assuming you have a function to save teacher data to a file
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
    string idToRemove;
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

// Function to save teacher data to a file
void SaveTeacherToFile()
{
    ofstream teacherFile("teacher_data.txt");

    if (!teacherFile.is_open())
    {
        cout << "Error opening teacher file for writing.\n";
        return;
    }

    for (int i = 0; i < teacher_count; ++i)
    {
        teacherFile << teacherName[i] << ' ' << teacherID[i] << '\n';
    }

    teacherFile.close();
}

// Function to load teacher data from a file
void LoadTeacherFromFile()
{
    ifstream teacherFile("teacher_data.txt");

    if (!teacherFile.is_open())
    {
        cout << "Error opening teacher file for reading.\n";
        return;
    }

    while (teacherFile >> teacherName[teacher_count] >> teacherID[teacher_count])
    {
        teacher_count++;
    }

    teacherFile.close();
}
// Function to update teacher information
void updateTeacher()
{
    cout << "Enter the ID of the teacher to update: ";
    string idToUpdate;
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
            cout << "<-------------------->\n";
        }
    }
}