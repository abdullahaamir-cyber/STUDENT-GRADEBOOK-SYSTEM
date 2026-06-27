#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 
#include <cstdlib>

using namespace std;

const int MAX_STUDENTS = 50;
const int NUM_SUBJECTS = 8;
const string DB_FILENAME = "students.txt";
const string REPORT_FILENAME = "report.txt";


const string SUBJECT_NAMES[NUM_SUBJECTS] = {
    "Programming Fundamentals",
    "PF LAB",
    "Applied Physics",
    "Physics LAB",
    "AICT",
    "AICT LAB",
    "Calculus - 1",
    "Discrete Mathematics"
};

struct Student
{
    string id;
    string name;
    float marks[NUM_SUBJECTS]{};
    float totalMarks{ 0.0f };
    float percentage{ 0.0f };
    float gpa{ 0.0f };
    char grade{ 'F' };
};

void loadRecords(Student students[], int& count);
void saveRecords(Student students[], int count);
void calculatePerformance(Student& s);
void addStudent(Student students[], int& count);
void displayAll(Student students[], int count);
int searchStudentIndex(Student students[], int count, string id);
void searchAndDisplay(Student students[], int count);
void updateStudent(Student students[], int count);
void deleteStudent(Student students[], int& count);
void rankStudents(Student students[], int count);
void generateReports(Student students[], int count);
char getGradeFromGPA(float gpa);

int main()
{

    system("color 10F");




    Student students[MAX_STUDENTS];
    int studentCount = 0;
    char choice;

    loadRecords(students, studentCount);

    do
    {
        system("cls");
        cout << "\n=== STUDENT GRADEBOOK SYSTEM ===\n";
        cout << "1. Add New Student\n";
        cout << "2. Display All Records\n";
        cout << "3. Search Student by ID\n";
        cout << "4. Update Student Record\n";
        cout << "5. Delete Student Record\n";
        cout << "6. Rank Students (Highest GPA)\n";
        cout << "7. Generate Analytical Reports (Export to File)\n";
        cout << "8. Save & Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            system("cls");
            addStudent(students, studentCount);
            break;
        case '2':
            system("cls");
            displayAll(students, studentCount);
            saveRecords(students, studentCount);
            break;
        case '3':
            system("cls");
            searchAndDisplay(students, studentCount);
            break;
        case '4':
            system("cls");
            updateStudent(students, studentCount);
            saveRecords(students, studentCount);
            break;
        case '5':
            system("cls");
            deleteStudent(students, studentCount);
            saveRecords(students, studentCount);
            break;
        case '6':
            system("cls");
            rankStudents(students, studentCount);
            cout << "Students ranked by GPA successfully.\n";
            displayAll(students, studentCount);
            break;
        case '7':
            system("cls");
            generateReports(students, studentCount);
            break;
        case '8':
            system("cls");
            saveRecords(students, studentCount);
            cout << "Data saved. Exiting program.\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
            cout << "Press enter to continue...";
            cin.get();
            cin.get();
        }
    } while (choice != '8');

    return 0;
}




void calculatePerformance(Student& s)
{
    s.totalMarks = 0;
    for (int i = 0; i < NUM_SUBJECTS; i++)
    {
        s.totalMarks += s.marks[i];
    }

    s.percentage = (s.totalMarks / (NUM_SUBJECTS * 100.0)) * 100;

    if (s.percentage >= 85) s.gpa = 4.0;
    else if (s.percentage >= 70) s.gpa = 3.0;
    else if (s.percentage >= 60) s.gpa = 2.0;
    else if (s.percentage >= 50) s.gpa = 1.0;
    else s.gpa = 0.0;

    s.grade = getGradeFromGPA(s.gpa);
}

char getGradeFromGPA(float gpa)
{
    if (gpa == 4.0) return 'A';
    if (gpa == 3.0) return 'B';
    if (gpa == 2.0) return 'C';
    if (gpa == 1.0) return 'D';
    return 'F';
}

void addStudent(Student students[], int& count)
{
    if (count >= MAX_STUDENTS)
    {
        cout << "Error: Database is full!\n";
        return;
    }

    Student newStudent;
    cout << "\n-- Add New Student --\n";
    cout << "Enter ID (No spaces): ";
    cin >> newStudent.id;

    if (searchStudentIndex(students, count, newStudent.id) != -1)
    {
        cout << "Error: Student ID already exists!\n";
        return;
    }

    cout << "Enter Name (Use _ for space, e.g. John_Doe): ";
    cin >> newStudent.name;

    cout << "Enter Marks for " << NUM_SUBJECTS << " subjects (0-100):\n";
    for (int i = 0; i < NUM_SUBJECTS; i++)
    {
        do
        {

            cout << SUBJECT_NAMES[i] << ": ";
            cin >> newStudent.marks[i];

            if (newStudent.marks[i] < 0 || newStudent.marks[i] > 100)
            {
                cout << "Invalid marks! Must be between 0 and 100.\n";
            }
        } while (newStudent.marks[i] < 0 || newStudent.marks[i] > 100);
    }

    calculatePerformance(newStudent);
    students[count] = newStudent;
    count++;
    cout << "Student added successfully!\n";
    cout << "Press enter to continue...";
    cin.get(); cin.get();
}

void displayAll(Student students[], int count)
{
    if (count == 0)
    {
        cout << "No records found.\n";
        cout << "Press enter to continue...";
        cin.get();
        cin.get();
        return;
    }

    cout << "\n-----------------------------------------------------------------------------\n";
    cout << left << setw(10) << "ID" << setw(30) << "Name" << setw(10) << "Total" << setw(10) << "GPA" << setw(5) << "Grade" << endl;
    cout << "-----------------------------------------------------------------------------\n";
    for (int i = 0; i < count; i++)
    {
        cout << left << setw(10) << students[i].id
            << setw(30) << students[i].name
            << setw(10) << students[i].totalMarks
            << setw(10) << setprecision(2) << fixed << students[i].gpa
            << setw(5) << students[i].grade << endl;
    }
    cout << "-----------------------------------------------------------------------------\n";
    cout << "Press enter to continue...";
    cin.get();
    cin.get();
}

int searchStudentIndex(Student students[], int count, string id)
{
    for (int i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

void searchAndDisplay(Student students[], int count)
{
    string id;
    cout << "Enter Student ID to Search: ";
    cin >> id;

    int index = searchStudentIndex(students, count, id);
    if (index != -1)
    {
        cout << "\nStudent Found:\n";
        cout << "Name: " << students[index].name << "\n";
        cout << "GPA: " << students[index].gpa << "\n";
        cout << "Marks:\n";
        for (int j = 0; j < NUM_SUBJECTS; j++)
        {
            cout << "  " << SUBJECT_NAMES[j] << ": " << students[index].marks[j] << "\n";
        }
    }
    else
    {
        cout << "Student not found.\n";
    }
    cout << "Press enter to continue...";
    cin.get();
    cin.get();
}

void updateStudent(Student students[], int count)
{
    string id;
    cout << "Enter Student ID to Update: ";
    cin >> id;

    int index = searchStudentIndex(students, count, id);
    if (index == -1)
    {
        cout << "Student not found.\n";
        cout << "Press enter to continue...";
        cin.get(); cin.get();
        return;
    }

    cout << "Updating records for " << students[index].name << ".\n";
    cout << "Enter new marks:\n";
    for (int i = 0; i < NUM_SUBJECTS; i++)
    {
        while (true)
        {
            cout << SUBJECT_NAMES[i] << ": ";
            cin >> students[index].marks[i];
            if (students[index].marks[i] < 0 || students[index].marks[i] > 100)
            {
                cout << "Invalid marks! 0-100 only. Re-enter:\n";
            }
            else
            {
                break;
            }
        }
    }

    calculatePerformance(students[index]);
    cout << "Record updated successfully.\n";
    cout << "Press enter to continue...";
    cin.get(); cin.get();
}


void deleteStudent(Student students[], int& count)
{
    string id;
    cout << "Enter Student ID to Delete: ";
    cin >> id;

    int index = searchStudentIndex(students, count, id);
    if (index == -1)
    {
        cout << "Student not found.\n";
    }
    else
    {
        char confirm;
        cout << "Are you sure you want to delete " << students[index].name << "? (y/n): ";
        cin >> confirm;

        if (confirm == 'y' || confirm == 'Y')
        {

            for (int i = index; i < count - 1; i++)
            {
                students[i] = students[i + 1];
            }
            count--;
            cout << "Student deleted successfully.\n";
        }
        else
        {
            cout << "Delete cancelled.\n";
        }
    }
    cout << "Press enter to continue...";
    cin.get(); cin.get();
}

void rankStudents(Student students[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (students[j].gpa < students[j + 1].gpa)
            {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

void generateReports(Student students[], int count)
{
    if (count == 0)
    {
        cout << "No data to analyze.\n";
        cout << "Press enter to continue...";
        cin.get(); cin.get();
        return;
    }

    int topperIndex = 0;
    for (int i = 1; i < count; i++)
    {
        if (students[i].gpa > students[topperIndex].gpa)
            topperIndex = i;
    }

    float subjAvg[NUM_SUBJECTS] = { 0 };
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < NUM_SUBJECTS; j++)
        {
            subjAvg[j] += students[i].marks[j];
        }
    }
    for (int j = 0; j < NUM_SUBJECTS; j++) subjAvg[j] /= count;

    int passCount = 0;
    for (int i = 0; i < count; i++)
    {
        if (students[i].gpa >= 1.0) passCount++;
    }

    cout << "\n--- ANALYTICAL REPORT ---\n";
    cout << "Topper: " << students[topperIndex].name << " (GPA: " << students[topperIndex].gpa << ")\n";
    cout << "Pass Ratio: " << passCount << "/" << count << " students passed.\n";
    cout << "Subject Averages calculated. Exporting details...\n";

    ofstream outFile(REPORT_FILENAME);
    if (outFile.is_open())
    {
        outFile << "Student Result Analysis Report\n";
        outFile << "------------------------------\n";
        outFile << "Topper: " << students[topperIndex].name << " (GPA: " << students[topperIndex].gpa << ")\n";
        outFile << "Total Students: " << count << "\n";
        outFile << "Passed: " << passCount << "\n";
        outFile << "Failed: " << (count - passCount) << "\n";
        outFile << "Subject Averages:\n";


        for (int j = 0; j < NUM_SUBJECTS; j++)
        {
            outFile << left << setw(30) << SUBJECT_NAMES[j] << ": " << subjAvg[j] << "\n";
        }
        outFile.close();
        cout << "Report exported to '" << REPORT_FILENAME << "' successfully.\n";
    }
    else
    {
        cout << "Error creating report file.\n";
    }

    cout << "Press enter to continue...";
    cin.get();
    cin.get();
}

void loadRecords(Student students[], int& count)
{
    ifstream inFile(DB_FILENAME);
    if (!inFile)
    {

        return;
    }

    while (inFile >> students[count].id >> students[count].name)
    {
        for (int i = 0; i < NUM_SUBJECTS; i++)
        {
            inFile >> students[count].marks[i];
        }

        calculatePerformance(students[count]);
        count++;
        if (count >= MAX_STUDENTS) break;
    }
    inFile.close();
    if (count > 0)
        cout << count << " records loaded.\n";
}

void saveRecords(Student students[], int count)
{
    ofstream outFile(DB_FILENAME);
    if (!outFile)
    {
        cout << "Error saving to file!\n";
        return;
    }

    for (int i = 0; i < count; i++)
    {
        outFile << students[i].id << " " << students[i].name << " ";
        for (int j = 0; j < NUM_SUBJECTS; j++)
        {
            outFile << students[i].marks[j] << " ";
        }
        outFile << "\n";
    

    outFile.close();
}
	
        
        
