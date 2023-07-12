#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;
class student
{
public:
    char name[25], usn[15], branch[15], buffer[45];
};
student s, s1[100];
int i, no = 0, mode = 0;
void pack()
{
    fstream app;
    if (mode == 0)
        app.open("st3.txt", ios::app);
    else
        app.open("st3.txt", ios::out);
    if (!app)
    {
        cout << "cant open the file in output mode";
        _getch();
        exit(0);
    }
    strcpy_s(s.buffer, s.name);
    strcat_s(s.buffer, "|");
    strcat_s(s.buffer, s.usn);
    strcat_s(s.buffer, "|");
    strcat_s(s.buffer, s.branch);
    strcat_s(s.buffer, "\n");
    app << s.buffer;
    app.close();
}
void unpack()
{
    fstream in;
    in.open("st3.txt", ios::in);
    i = 0, no = 0;
    if (!in)
    {
        cout << "cant open the file in input mode";
        _getch();
        exit(0);
    }

    while (!in.eof())
    {
        in.getline(s1[i].name, 15, '|');
        in.getline(s1[i].usn, 15, '|');
        in.getline(s1[i].branch, 15, '\n');
        no++;
        i++;
    }
    in.close();
}
void write()
{
    cout << "\n enter the student name\n";
    cin >> s.name;
    cout << "enter the student usn\n";
    cin >> s.usn;
    cout << "enter the student branch\n";
    cin >> s.branch;
    pack();
    mode = 0;
}
void search()
{
    char usn[15], extra[45];
    int rrn;
    cout << "enter the rrn to search=";
    cin >> rrn;
    unpack();
    no--;
    for (int i = 0; i < no; i++)
    {
        if (rrn == i)
        {
            cout << "\nrecord found";
            cout << "\n"<< s1[i].name << "\t" << s1[i].usn << "\t" << s1[i].branch;
            _getch();
            return;
        }
    }
    cout << "record not found";
    _getch();
    return;
}
void main()
{
    int choice;
    for (;;)
    {
        cout << "\n0:exit";
        cout << "\n1:write";

        cout << "\n2:search";
        cout << "enter u choice\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            write();
            break;
        case 2:
            search();
            break;
        case 0:
            exit(0);
        default:
            cout << "\ninvalid input";
            break;
        }
    }
}
