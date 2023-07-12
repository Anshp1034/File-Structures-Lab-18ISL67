#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <stdlib.h>
#define datafile "stu5.txt"
#define indexfile "ind5.txt"
using namespace std;
fstream stdfile, indfile;
int i, indsize, mode = 0;
char buffer[80];
class student
{
    char dusn[15], name[15], branch[10], semester[5];

public:
    void add();
    void pack();
    friend int search(char *);
    void recDisp(int);
    void remove(int);
    void dataDisp();
    void unpack();
};
class index
{
public:
    char iusn[15], addr[5];
    void initial();
    void write();
} in, id[100];
void opener(fstream &sfile, char *fn, int mode)
{
    try

    {
        sfile.open(fn, mode);
    }
    catch (std::ios_base::failure &e)
    {
        cout << e.what() << "\n";
    }
    if (!sfile)
    {
        cout << "Unable to open the file\n";
        exit(1);
    }
}
void index::initial()
{
    indfile.open(indexfile, ios::in);
    if (!indfile)
    {
        indsize = 0;
        return;
    }
    for (indsize = 0;; indsize++)
    {
        indfile.getline(id[indsize].iusn, 15, '|');
        indfile.getline(id[indsize].addr, 5, '\n');
        if (indfile.eof())
            break;
    }
    indfile.close();
}
void index::write()
{
    opener(indfile, (char *)indexfile, ios::out);
    for (i = 0; i < indsize; i++)
        indfile << id[i].iusn << "|" << id[i].addr << "\n";
    indfile.close();
}
int search(char *fusn)
{
    int low = 0, high = indsize - 1;
    int mid;
    while (low <= high)
    {

        mid = (low + high) / 2;
        if (strcmp(fusn, id[mid].iusn) == 0)
            return mid;
        else if (strcmp(fusn, id[mid].iusn) > 0)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}
void student::add()
{
    int k;
    cout << "Enter the USN : ";
    cin >> dusn;
    if (search(dusn) >= 0)
    {
        cout << "Duplicate records cannot be inserted\n";
        return;
    }
    for (i = indsize; i > 0; i--)
    {
        if (strcmp(dusn, id[i - 1].iusn) < 0)
            id[i] = id[i - 1];
        else
            break;
    }
    if (mode)
        opener(stdfile, (char *)datafile, ios::app);
    else
    {
        opener(stdfile, (char *)datafile, ios::out);
        mode = 1;
    }
    cout << "Enter the name : ";
    cin >> name;
    cout << "Enter the branch : ";
    cin >> branch;
    cout << "Enter the semester : ";
    cin >> semester;
    pack();
    stdfile.seekg(0, ios::end);
    k = stdfile.tellg();

    stdfile << buffer << endl;
    strcpy_s(id[i].iusn, dusn);
    _itoa_s(k, id[i].addr, 10);
    indsize++;
    stdfile.close();
}
void student::pack()
{
    strcpy_s(buffer, dusn);
    strcat_s(buffer, "|");
    strcat_s(buffer, name);
    strcat_s(buffer, "|");
    strcat_s(buffer, branch);
    strcat_s(buffer, "|");
    strcat_s(buffer, semester);
}
void student::recDisp(int pos)
{
    opener(stdfile, (char *)datafile, ios::in);
    stdfile.seekg(atoi(id[pos].addr), ios::beg);
    unpack();
    if (dusn[0] == '$')
    {
        cout << "Record is deleted\n";
        return;
    }
    cout << "The searched details are as follows : \n";
    cout << dusn << "\t" << name << "\t" << branch << "\t" << semester << endl;
    stdfile.close();
}
void student::remove(int pos)
{
    opener(stdfile, (char *)datafile, ios::in | ios::out);
    stdfile.seekg(atoi(id[pos].addr), ios::beg);
    stdfile.put('$');
    for (i = pos; i < indsize; i++)
    {
        id[i] = id[i + 1];
        indsize--;
    }
    stdfile.close();
    in.write();
}
void student::unpack()
{
    stdfile.getline(dusn, 15, '|');
    stdfile.getline(name, 15, '|');
    stdfile.getline(branch, 10, '|');
    stdfile.getline(semester, 5, '\n');
}
void student::dataDisp()
{
    cout << "USN\tName\tBranch\tSemester\n";
    while (1)
    {
        unpack();
        if (dusn[0] == '$')
            cout << "This record is deleted\n";
        else
            cout << dusn << "\t" << name << "\t" << branch << "\t" << semester << endl;
        if (stdfile.eof())
        {
            stdfile.close();
            break;
        }
    }
}
void main()
{
    int ch, pos, flag;
    char susn[15];
    student s;
    in.initial();
    for (;;)
    {
        cout << "1. Enter the record \t 2. Data Displaying \n 3. Search with record disp \t 4. Delete ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "Enter the student details : \n";
            s.add();
            in.write();
            break;
        case 2:
            opener(stdfile, (char *)datafile, ios::in);
            cout << "Student details are as follows : \n";
            c

                s.dataDisp();
            cout << "Index file details are as follows : \n";
            for (i = 0; i < indsize; i++)
                cout << id[i].iusn << "|" << id[i].addr << endl;
            break;
        case 3:
            cout << "Enter the USN : ";
            cin >> susn;
            flag = search(susn);
            if (flag == -1)
                cout << "Record is not found\n";
            else
            {
                s.recDisp(flag);
            }
            break;
        case 4:
            cout << "Enter the USN : \n";
            cin >> susn;
            pos = search(susn);
            if (pos == -1)
                cout << "Record not found\n";
            else
                s.remove(pos);
            // in.write();
            break;
        case 5:
            exit(0);
        default:
            cout << "Invalid choice\n";
        }
    }
}
