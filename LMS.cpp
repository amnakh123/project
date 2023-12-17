#include<iostream>
#include<windows.h>
#include<conio.h>
#include<iomanip>
#include<fstream>

using namespace std;

// Global Data

string fixedSpace = "\t\t\t";
string masterUserName = "LMS";
string masterPassWord = "LMS";


const int arraySize = 10;  // Array Size

bool mainLoop = true; // mainloop condition

// Login and SignIn Data

string userNames[arraySize]={ "admin", "amna" }; // Usernames
string userPassword[arraySize]={ "240", "111" }; // Passwords
string roles[arraySize]={ "Admin", "Student" }; // Roles

// Library Data

int users = 2; 
              //count of users
int books = 5;
              //count of books
int students = 5;
              //count of students
int bookId[arraySize] = {1, 2, 3, 4, 5};
              //Book ids
string Books[arraySize] = {"BookA", "BookB", "BookC", "BookD", "BookE"};
              //Book names
string authors[arraySize] = {"AutherA", "AutherB", "AutherC", "AutherD", "AutherE"};
              //Book authers
string status[arraySize] = {"Available", "Unavailable", "Available", "Unavailable", "Available"};
              //Book status
string category[arraySize] = {"English", "Urdu", "English", "Urdu", "English"};
              //Book categories
string issuedStudentsNames[10] = {"", "Student2", "", "Student4", ""};
              //students who issued the book
string  StudentNo[10] = {"StudentA", "StudentB", "StudentC", "StudentD", "StudentE"};
              //Members of library 
string dueInDates[arraySize] = {"", "23/12/2023", "", "26/12/2023"};
              //Returning dates of books

// Function Prototypes
int validatedInput(int choice);             // validates choice
string setcolor(unsigned short color);      //  change color of specific line
bool isPresent(string username, string password); // check if the user has already signed up
void Header();            //print header on screen
void loginScreen();       // print login options
void clearScreen();       // clear screen and print header again
int roleCheck(string username1, string password1);  //returns the user role 
void printBookByIndex(int index);        //print book fron index
void printBookByNames(string name);   //print book by name,auther,status,category
bool isAlpha(string input);          //return true if input is string
void halt();                         //stops and ask for key to continue

// Admin Function Prototypes
void printAdminMenu();
void addBook();
void deleteBook(int idx);
void viewBooks();
void modifyBook(int choice, int idx);
void searchBook(string name);
void modifyBookSubMenu();
void viewIssuedBooks(); 
void IssueBook(int idx, string studentName, string dueDate);
bool issueanceCheck(int idx);
void returnBook(int idx);
int returnBookIndex(string name1);
void viewStudents();
void addStudent(string student);
void removeStudent(int index);
int returnIndex(string name);
bool checkStudentFromMembers(string studentName);

// Admin Functions Prototypes
void adminMenu();   //Main for Admin
void studentMenu();  //Main for Student

//Student Function Prototypes
void printStuMenu(); 
void searchBookSubMenu();
void checkStatusSubMenu();

// permanently store data
void userData(string userNames[], string userPassword[], string roles[], int users);
void storeData(string userNames[], string userPassword[], string roles[], int &users);
string parseData(string record, int manage);
void stockBook(int bookId[], string Books[], string authors[], string category[], int books, string status[]);
void loadBook(int bookId[], string Books[], string authors[], string category[], int &books, string status[]);
void studentData(int students, string StudentNo[], string issuedStudentsNames[], string dueInDates);
void storeStudentData(int &students, string StudentNo[], string issuedStudentsNames[], string dueInDates);

int main()
{
    int choice;
    string masterUsername, masterPassword, username, password, role1, username1, password1;
    while(mainLoop)
    {
        clearScreen();
        loginScreen();
        choice = validatedInput(choice);
        if(choice == 1)
        {
            clearScreen();
            
            cout<< "Enter username: ";
            cin >> username;
            cout<< "Enter password: ";
            cin >> password;

            bool usercheck = isPresent(username, password);
            if(usercheck == 0)
            {
                cout << "Enter role: ";
                cin >> role1;
                if(role1 == "Admin" || role1 == "admin" || role1 == "student" || role1 == "Student")
                {
                    if(role1 == "admin" || role1 == "Admin")
                    {
                        cout << "Enter Master UserName: ";
                        cin >> masterUsername;
                        cout << "Enter Master Password: ";
                        cin >> masterPassword;
                        if(masterUsername == masterUserName && masterPassword == masterPassWord)
                        {
                           userNames[users] = username;
                           userPassword[users] = password;
                           roles[users] = role1;
                           cout << "You have Signed up successfully as master!!" << endl;
                           users++;
                        }
                        else
                        {
                            cout << "You don't have access!!" << endl;
                        }
                    }
                    else
                    {
                         userNames[users] = username;
                           userPassword[users] = password;
                           roles[users] = role1;
                           cout<< "You have Signed Up successfully!!" << endl;
                           users++;
                           userData(userNames, userPassword, roles, users);
                    }
                    halt();
                }
                    else
                    {
                        cout << "Enter correct role!!" << endl;
                        halt();
                    }
                }
                else
                {
                    cout << "User already exists!!" << endl;
                    cout << " Login Please!!" << endl;
                    halt();
                }
            }
            else if(choice == 2)
            {
                clearScreen();
                cout << "Enter username: ";
                cin >> username1;
                cout << "Enter password: ";
                cin >> password1;
                int role = roleCheck(username1, password1);
                if(roles[role] == "admin" || roles[role] == "Admin")
                {
                    clearScreen();
                    adminMenu();
                }
                else if(roles[role] == "student" || roles[role] == "Student")
                {
                    clearScreen();
                    studentMenu();
                }
                else if(role == -1)
                {
                    cout << "Incorrect Password!!" <<endl;
                    halt();
                }
                
            }
            else if(choice == 3)
            {
                mainLoop = false;
            }
            else if(choice > 3)
            {
                cout << "Enter Correct Choice!!!"<<endl;
                halt();
            }
        }
        
    
    return 0;
}


// User Menu Functionalities
void adminMenu()
{
    int choice;
    bool admin = true;
    while (admin)
    {
        clearScreen();
        printAdminMenu();
        choice = validatedInput(choice);
        if(choice == 1)
        {
            clearScreen();
            addBook();
        }
        else if(choice == 2)
        {
            clearScreen();
            string name1;
            cout << "Enter Book Name: ";
            cin.ignore();
            getline(cin, name1);
            int x = returnBookIndex(name1);
            if(x != -1)
            {
                deleteBook(x);
                cout << "Book has been deleted successfully!!";
            }
           else
           {
            cout<< "Book not Found!!"<<endl;
           }
           halt();
        }
        else if(choice == 3)
        {
            clearScreen();
            viewBooks();
        }
        else if(choice == 4)
        {
            clearScreen();
            string name2;
            cout << "Enter Book Name: ";
            cin.ignore();
            getline(cin, name2);
            int idx = returnBookIndex(name2);
            if(idx != -1)
            {
                modifyBookSubMenu();
                cin >> choice;
                modifyBook(choice, idx);
            }
            else
            {
                  cout << "Book not Found!!" <<endl;
            }
            halt();
        }
        else if(choice == 5)
        {
            clearScreen();
            string name3;
            cout << "Enter Book Name: ";
            cin.ignore();
            getline(cin, name3);
            int index = returnBookIndex(name3);
            printBookByIndex(index);
        }
        else if(choice == 6)
        {
            clearScreen();
            viewIssuedBooks();
        }
        else if(choice == 7)
        {
            clearScreen();
            string name4, stuName, dueDate;
            cout << "Enter Book Name: ";
            cin.ignore();
            getline(cin, name4);
            int idx = returnBookIndex(name4);
            if(idx != -1)
            {
                bool x = issueanceCheck(idx);
                if(x == true)
                {
                    cout << "Enter Student Name: ";
                    cin.ignore();
                    getline(cin, stuName);
                    bool y = checkStudentFromMembers(stuName);
                    if(y == true)
                    {
                        cout << "Enter Due Date: ";
                        cin >> dueDate;
                        IssueBook(idx, stuName, dueDate);
                        cout << "Book Issued!!" <<endl;
                    }
                    else
                    {
                        cout<< "Student is not in the List." <<endl;
                    }
                }
                else
                {
                    cout << "Book Already Issued!!" << endl;
                }
            }
            else
            {
                cout << "Book is not in the List." <<endl;
            }
            halt();
        }
        else if(choice == 8)
        {
            clearScreen();
            string name;
            cout << "Enter Book Name: ";
            cin.ignore();
            getline(cin, name);
            int idx = returnBookIndex(name);
            if(idx != -1)
            {
                bool i = issueanceCheck(idx);
                if(i == false)
                {
                    returnBook(idx);
                    cout << "Book has been Returned Successfully!!" << endl;
                }
            }
            else
            {
                cout << "Book not found!!" <<endl;
            }
            halt();
        }
        else if(choice == 9)
        {
            clearScreen();
            viewStudents();
        }
        else if(choice == 10)
        {
            clearScreen();
            string stuname;
            cout << "Enter Student Name: ";
            cin.ignore();
            getline(cin, stuname);
            bool z = checkStudentFromMembers(stuname);
            if(z == true)
            {
                addStudent(stuname);
                cout << "Student Added Successfully!!" <<endl;
            }
            else
            {
                cout << "Student Already Exists!!" <<endl;
            }
            halt();
        }
        else if(choice == 11)
        {
            clearScreen();
            string name;
            cout << "Enter Student Name: ";
            cin.ignore();
            getline(cin, name);
            int idx = returnIndex(name);
            if(idx != -1)
            {
                removeStudent(idx);
                cout << "Student has Removed Successfully!!" <<endl;
            }
            else
            {
                cout << "Student has not Found!!" <<endl;
            }
            halt();
        }
        else if(choice == 12)
        {
            admin = false; 
        }
        else if(choice > 12)
        {
            cout << "Enter Correct Choice!!" <<endl;
            halt();
        }
    }
}

void printAdminMenu()
{
    cout << endl 
          << "L M S >= Admin" << endl;
    cout << "1.  Add a new Book" << endl;
    cout << "2.  Delete a Book" << endl;
    cout << "3.  View Books" << endl;
    cout << "4.  Modify Books" << endl;
    cout << "5.  Search Books" << endl;
    cout << "6.  View Issued Books" << endl;
    cout << "7.  Issue Books" << endl;
    cout << "8.  Return Books" << endl;
    cout << "9.  View Students" << endl;
    cout << "10. Add New Students" << endl;
    cout << "11. Remove a Student" << endl;
    cout << "12. Logout" << endl; 
    cout << "Enter your Choice: ";   
}

void printStuMenu()
{
   cout << endl
         << "L M S >= Student" << endl;
   cout << "1.  Search Book" << endl;
   cout << "2.  View Books" << endl;
   cout << "3.  Check status of Book" << endl;
   cout << "4.  Issue Book" << endl;
   cout << "5.  Return Book" << endl;
   cout << "6.  Logout" << endl;
   cout << "Enter your Choice: ";      
}

void studentMenu()
{
    bool student1 = true;
    int choice, choice1, choice2;

    while(student1)
    {
        clearScreen();
        printStuMenu();
        choice = validatedInput(choice);
        if(choice == 1)
        {
            clearScreen();
            searchBookSubMenu();
            choice1 = validatedInput(choice1);
            if(choice1 == 1)
            {
                clearScreen();
                string dname;
                cout<< "Enter Student Name: ";
                cin.ignore();
                getline(cin, dname);
                printBookByNames(dname);

            }
            else if(choice1 == 2)
            {
                clearScreen();
                string auther;
                cout << "Enter Auther Book: ";
                cin.ignore();
                getline(cin, auther);
                printBookByNames(auther);
            }
            else if(choice1 == 3)
            {
                clearScreen();
                string category;
                cout << "Enter the Category of Book: ";
                cin.ignore();
                getline(cin, category);
                printBookByNames(category);
            }
        }
        else if(choice == 2)
        {
            clearScreen();
            viewBooks();
        }
        else if(choice == 3)
        {
            clearScreen();
            checkStatusSubMenu();
            choice2 = validatedInput(choice2);
            if(choice2 == 1)
            {
                string fname;
                cout << "Enter the Book Name: ";
                cin.ignore();
                getline(cin, fname);
                int idx = returnBookIndex(fname);
                if(status[idx] == "Available")
                {
                    cout << "Book Status: "<< status[idx] << endl;
                }
                else 
                {
                    cout << "Book Status: "<< status[idx] << endl;
                }
                halt();
            }
            else if(choice2 == 2)
            {
                clearScreen();
                string bookStatus = "Available";
                cout << "Available Books List" << endl;
                printBookByNames(bookStatus);
            }
            else if(choice2 == 3)
            {
                clearScreen();
                string bookStatus = "Unavailable";
                cout << "Unavailable Books List" <<endl;
                printBookByNames(bookStatus);
            }
        }
        else if(choice == 4)
        {
            clearScreen();
            string bname, stunaMe, dueDate;
            cout << "Enter Book Name: ";
            cin.ignore();
            getline(cin, bname);
            int idx = returnBookIndex(bname);
            if(idx != -1)
            {
                bool x = issueanceCheck(idx);
                if(x == true)
                {
                    cout << "Enter Student Name: ";
                    cin.ignore();
                    getline(cin, stunaMe);
                    bool y = checkStudentFromMembers(stunaMe);
                    if(y == true)
                    {
                        cout<< "Enter Due Date: ";
                        cin>> dueDate;
                        IssueBook(idx, stunaMe, dueDate);
                        cout << "Book has been Issued!!" <<endl;
                    }
                    else
                    {
                         cout << "Student Not Found." <<endl;
                    }
                }
                else
                {
                    cout << "Book Already issued!!" << endl;
                }
            }
            else
            {
                cout << "Book Not Found!!" << endl;
            }
            halt();
        }
        else if(choice == 5)
        {
            clearScreen();
            string fname;
            cout<< "Enter Student Name: ";
            cin.ignore();
            getline(cin, fname);
            int idx = returnBookIndex(fname);
            if(idx != -1)
            {
                bool z = issueanceCheck(idx);
                if(z == false)
                {
                    returnBook(idx);
                    cout << "Book Returned Successfully!!" << endl;
                }
            }
            else
            {
                  cout << "Book not Found!!" << endl;
            }
            halt();
        }
        else if(choice == 6)
        {
            student1 = false;           
        }
        else if(choice > 6)
        {
            cout << "Enter Correct Choice!!" << endl;
            halt();
        }
    }
}

// Function Definitions

void halt()
{
    cout << "Press any key to continue... ";
    getch();
}

void clearScreen()
{
    system("cls");
    Header();
    cout<< endl
        << endl;
}

void loginScreen()
{
    cout << endl
          << "L M S >= Login Screen" << endl
          <<endl;
    cout << "1. Sign Up" <<endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << "Emter your choice: ";    
}

bool isPresent(string username, string password)
{
    for(int i = 0; i < users; i++)
    {
        if(username == userNames[i] && password == userPassword[i])
        {
            return true;
        }
    }
    return false;
}

int roleCheck(string username1, string password1)
{
    int role = -1;
    for(int x = 0; x < users; x++)
    {
        if(username1 == userNames[x])
        {
            if(password1 == userPassword[x])
            {
                role = x;
            }
        }
    }
    return role;
}

void addBook()
{
    cout << "Enter Book ID: ";
    cin>> bookId[books];
      cin.ignore();
    cout << "Enter Book Name: ";
    getline(cin, Books[books]);
    cout << "Enter Author Name: ";
     getline(cin, authors[books]);
     cout << "Enter Book Category: ";
     getline(cin, category[books]);
     status[books] = "Available";
     issuedStudentsNames[books] = "";
     books++;
     cout<< "Book has been added!!" <<endl;
     halt();
}

void deleteBook(int idx)
{
    for(int y = idx; y <= books - 1; y++)
    {
        Books[y] = Books[y + 1];
        authors[y] = authors[y + 1];
        status[y] = status[y + 1];
        bookId[y] = bookId[y + 1];
        category[y] = category[y + 1];
        dueInDates[y] = dueInDates[y + 1];
    }
    books--;
}

void modifyBookSubMenu()
{
     clearScreen();
     cout << endl;
     cout << "1.  Change the Book Status: "<<endl;
     cout << "2.  Change Book's due date: "<<endl;
     cout << "Enter your Choice: ";
}

void modifyBook(int choice, int idx)
{
           if(choice  == 1)
           {
            clearScreen();
            cout<< "Enter Book Status: ";
            cin >> status[idx];
            cout << endl
                 <<"Book status has been changed successfully!!"<<endl;
           }
           else if(choice == 2)
           {
            clearScreen();
            cout << "Enter the due date of Book: ";
            cin >> dueInDates[idx];
            cout << endl
                  << "Book due date has been changed successfully!!"<<endl;
           }
}

void viewBooks()
{
    cout << left << setw(20) << "Book ID" << setw(20) << "Category" << setw(20) << "Book Name" << setw(20) << "Author" << setw(20) << "Status" << setw(20) << "Student Name" << setw(20) << "DueInDate" <<endl
    <<endl;
    for(int i = 0; i < books; i++)
    {
        cout << left << setw(20) << bookId[i] << setw(20) << category[i] << setw(20) << Books[i] << setw(20) << authors[i];
        if(status[i] == "Unavailable")
        {
            setcolor(12);
            cout << setw(20) << status[i];
            setcolor(15);
            cout<< setw(20) << issuedStudentsNames[i] << setw(20) << dueInDates[i] << endl;
        }
        else
        {
           cout << setw(20) << status[i] << setw(20) << issuedStudentsNames[i] << setw(20) << dueInDates[i] << endl;
        }
        cout << endl;
    }
    cout << endl;
    halt();
}

void viewIssuedBooks()
{
    cout << left << setw(20) << "Book ID" << setw(20) << "Category" << setw(20) << "Book Name" << setw(20) << "Author" << setw(20) << "Status" << setw(20) << "Student Name" << setw(20) << "DueInDate" <<endl
    << endl;
    for(int i = 0; i < arraySize; i++)
    {
        if(status[i] == "Unavailable")
        {
              cout << left << setw(20) << bookId[i] << setw(20) << category[i] << setw(20) << Books[i] << setw(20) << authors[i] << setw(20) << status[i] << setw(20) << issuedStudentsNames[i] << setw(20) << dueInDates[i] << endl;
        }
    }
    halt();
}

void IssueBook(int idx, string studentName, string dueDate)
{
    issuedStudentsNames[idx] = studentName;
    dueInDates[idx] = dueDate;
    status[idx] = "Unavailable";
}

bool issueanceCheck(int idx)
{
    if(status[idx] == "Available")
    {
        return true;
    }
    return false;
}

void returnBook(int idx)
{
    issuedStudentsNames[idx] = "";
    dueInDates[idx] = "";
    status[idx] = "Available";
}

void viewStudents()
{
    cout << "List of Members of Library: "<<endl;
    for(int i = 0; i < students; i++)
    {
        cout << StudentNo[i] << endl;
    }
    halt();
}

void addStudent(string student)
{
    StudentNo[students] = student;
    students++;
}

void removeStudent(int index)
{
    for(int z = index; z <= students; z++)
    {
        StudentNo[z] = StudentNo[z + 1];
    }
    students--;
}

int returnIndex(string name)
{
    int index = -1;
    for(int y = 0; y < students; y++)
    {
        if(name == Books[y] || name == authors[y] || name == category[y] || name == StudentNo[y])
        {
            index = y;
            break;
        }
    }
    return index;
}

void searchBookSubMenu()
{
    cout << "1.  Search Book by Name" << endl;
    cout << "2.  Search Book by Author" << endl;
    cout << "3.  Search Book by Category" << endl;
    cout << "Enter your choice: ";
}

void checkStatusSubMenu()
{
    cout << "1.  Check Status by Book Name" << endl;
    cout << "2.  View Available Books" << endl;
    cout << "3.  View Unavailable Books" << endl;
    cout << "Enter your choice: "<<endl;
}

void printBookByIndex(int index)
{
    if(index != -1)
    {
           cout << left << setw(20) << "Book ID" << setw(20) << "Category" << setw(20) << "Book Name" << setw(20) << "Author" << setw(20) << "Status" << setw(20) << "Student Name" << setw(20) << "DueInDate" <<endl
          << endl;
          cout << left << setw(20) << bookId[index] << setw(20) << category[index] << setw(20) << Books[index] << setw(20) << authors[index];
          if(status[index] == "Unavailable")
          {
            setcolor(12);
            cout << setw(20) << status[index];
            setcolor(15);
          }
          else
          {
               cout << setw(20) << status[index];
          }
          
           cout << setw(20) << issuedStudentsNames[index] << setw(20) << dueInDates[index] << endl;
    }
    else
    {
        cout << "Book Not Found!!" << endl;
    }
    cout << endl;
    halt();
}

void printBookByNames(string name)
{
      cout << left << setw(20) << "Book ID" << setw(20) << "Category" << setw(20) << "Book Name" << setw(20) << "Author" << setw(20) << "Status" << setw(20) << "Student Name" << setw(20) << "DueInDate" <<endl
          << endl;
          for(int i = 0; i < books; i++)
          {
            if(name == category[i] || name == Books[i] || name == authors[i] || name == status[i])
            {
                 cout << left << setw(20) << bookId[i] << setw(20) << category[i] << setw(20) << Books[i] << setw(20) << authors[i];
                 if(status[i] == "Unavailable")
                 {
                    setcolor(12);
                    cout << setw(20) << status[i];
                    setcolor(15);
                 }
                 else
                 {
                       cout << setw(20) << status[i];
                 }
            }
             cout<< setw(20) << issuedStudentsNames[i] << setw(20) << dueInDates[i] << endl
             <<endl;
          }
          cout << endl;
          halt();
}

int returnBookIndex(string name1)
{
    int indexNo = -1;
    for(int i = 0; i < books; i++)
    {
        if(name1 == Books[i] || name1 == authors[i] || name1 == category[i])
        {
            indexNo = i;
            break;
        }
    }
    return indexNo;
}

bool checkStudentFromMembers(string studentName)
{
     bool x;
     for(int i=0; i < students; i++)
     {
        if(studentName == StudentNo[i])
        {
            x = true;
        }
     }
     return x;
}

string setcolor(unsigned short color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
    return "";
}

bool isAlpha(string input)
{
    bool y;
    int check;
    
    for(int i = 0; i<input.length(); i++)
    {
        if(input[i] != ' ')
        {
            check = int(input[i]);
            if(check >= 65 && check <= 91 || check >= 97 && check <= 122)
            {
                y = true;
            }
            else
             {
                  return false;
            }
        }
    }
    return y;
}

int validatedInput(int choice)
{
    cin >> choice;
    while (true)
    {
        if(cin.fail())
        {
        cin.clear();
        cin.ignore();
        cout<< "Enter wrong Input!!" << endl;
        cout << "Enter Correct Input: ";
        cin >> choice;

        }
        if(!cin.fail())
        {
            break;
        }
    }
    return choice;
}

void Header()
{
    cout << fixedSpace << "                                        ##       ######    ######   ######      ###     ######    ##    ##                                                              "<< endl;
    cout << fixedSpace << "                                        ##         ##      ##   #   ##   #     ## ##    ##   #     ##  ##                                                               "<< endl;
    cout << fixedSpace << "                                        ##         ##      ######   #####     ## # ##   #####        ##                                                                 "<< endl;
    cout << fixedSpace << "                                        ##   ##    ##      ##   #   ##  #     ##   ##   ##  #        ##                                                                 "<< endl;
    cout << fixedSpace << "                                        #######  ######    ######   ##   ##   ##   ##   ##   ##      ##                                                                 "<< endl;
    cout << endl;
    cout  << " ##     ##     ###    ##    ##     ###     ######   ######   ##     ##   ######   ##    ##   ######            ######   ##    ##   ######   ######   ######   ##     ## " << endl;
    cout  << " ## # # ##    ## ##   ## #  ##    ## ##    ##       ##       ## # # ##   ##       ## #  ##     ##              ##        ##  ##    ##         ##     ##       ## # # ## " << endl;
    cout  << " ##  #  ##   ## # ##  ##  # ##   ## # ##   ##       ######   ##  #  ##   ######   ##  # ##     ##              ######      ##      ######     ##     ######   ##  #  ## " << endl;
    cout  << " ##     ##   ##   ##  ##   ###   ##   ##   ##  ##   ##       ##     ##   ##       ##   ###     ##                  ##      ##          ##     ##     ##       ##     ## " << endl;
    cout  << " ##     ##   ##   ##  ##    ##   ##   ##   ######   ######   ##     ##   ######   ##    ##     ##              ######      ##      ######     ##     ######   ##     ## " << endl;
}

string parseData(string record, int manage)
{
    int count = 1;
    string item;
    for(int x=0; x < record.length(); x++)
    {
        if(record[x] == ',')
        {
            count = count + 1;
        }
        else if(count == manage)
        {
            item = item + record[x];
        }
    }
    return item;
}

void userData(string userNames[], string userPassword[], string roles[], int users)
{
    fstream file;
    file.open("userDetails.txt", ios::out);
    for(int i = 0; i < users; i++)
    {
        file<<userNames[i]<<","<<userPassword[i]<<","<<roles[i]<<endl;
    }
    file.close();
}

void storeData(string userNames[], string userPassword[], string roles[], int &users)
{
    string record;
    fstream file;
    file.open("userDetials.txt", ios::in);
    while(!(file.eof()))
    {
        getline(file, record);
        userNames[users]=parseData(record, 1);
        userPassword[users]=parseData(record, 2);
        roles[users]=parseData(record, 3);
        users++;
    }
    file.close();
}

void stockBook(int bookId[], string Books[], string authors[], string category[], int books, string status[])
{
    fstream file;
    file.open("viewStock.txt", ios::out);
    for(int i=0; i<books; i++)
    {
        file<<Books[i]<<","<<authors[i]<<","<<category[i]<<","<<status[i]<<","<<bookId[i]<<endl;
    }
    file.close();
}

void loadBook(int bookId[], string Books[], string authors[], string category[], int &books, string status[])
{
         string storeBook;
         fstream file;
         file.open("viewStock.txt", ios::in);
         while(!(file.eof()))
         {
            getline(file, storeBook);
            Books[books]=parseData(storeBook, 1);
            authors[books]=parseData(storeBook, 2);
            category[books]= parseData(storeBook, 3);
            status[books]=parseData(storeBook, 4);
            bookId[books]=stof(parseData(storeBook, 5));
            books++;
         }
         file.close();
}

void studentData(int students, string StudentNo[], string issuedStudentsNames[], string dueInDates)
{
    fstream file;
    file.open("StudentData.txt", ios::out);
    for(int i=0; i<students; i++)
    {
        file<<StudentNo[i]<<","<<issuedStudentsNames[i]<<","<<dueInDates[i]<<endl;
    }
    file.close();
}

void storeStudentData(int &students, string StudentNo[], string issuedStudentsNames[], string dueInDates)
{
     string storeStudent;
     fstream file;
     file.open("StudentData.txt", ios::in);
     while(!(file.eof()))
     {
        getline(file, storeStudent);
        StudentNo[students]=parseData(storeStudent, 1);
        issuedStudentsNames[students]=parseData(storeStudent, 2);
        dueInDates[students]=stof(parseData(storeStudent, 3));
        students++;
     }
     file.close();
}