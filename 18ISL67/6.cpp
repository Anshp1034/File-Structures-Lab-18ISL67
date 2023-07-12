#include <fstream>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#define datafile "stud6.txt"
#define indexfile "pri6.txt"
#define sindexfile "sec6.txt"
using namespace std;
fstream dfile, ifile, sifile;
int i, indsize = 0, sindsize;
char buffer[100], skey[20];
int search(char *fusn);
void opener(fstream &file, const char *fn, int mode)
{
    file.open(fn, mode);
    if (!file)
    {
        cout << "unable to open a file";
        _getch();
        exit(1);
    }
}
class student
{
    char dusn[15], name[20], branch[6], sem[5];

public:
    void add();
    void pack();
    friend int search(char *);
    void remove();
    void datadisp();
    void unpack();
    void ssearch();
} s;
class index
{
public:
    char iusn[15], addr[5];
    void initial();
    void write();
} id[50], in;
class sindex
{
public:
    char sname[20], susn[15];
    void sinitial();
    void swrite();
} sind, sid[50];
void index::initial()
{
    ifile.open(indexfile, ios::in);
    if (!ifile)
    {
        indsize = 0;
        return;
    }

    for (indsize = 0;; indsize++)
    {
        ifile.getline(id[indsize].iusn, 15, '|');
        ifile.getline(id[indsize].addr, 5, '\n');
        if (ifile.eof())
            break;
    }
    ifile.close();
}
// function to copy sindex file to array structure 
void sindex::sinitial()
{
    sifile.open(sindexfile, ios::in);
    if (!sifile)
    {
        sindsize = 0;
        return;
    }
    for (sindsize = 0;; sindsize++)
    {
        sifile.getline(sid[sindsize].sname, 20, '|');
        sifile.getline(sid[sindsize].susn, 15, '\n');
        if (sifile.eof())
            break;
    }
    sifile.close();
}
// function to update the index file 
void index::write()
{
    opener(ifile, indexfile, ios::out);

    for (i = 0; i < indsize; i++)
        ifile << id[i].iusn << "|" << id[i].addr << "\n";
}
// function to upadate the secondary file 
void sindex::swrite()
{
    opener(sifile, sindexfile, ios::out);
    for (i = 0; i < sindsize; i++)
        sifile << sid[i].sname << "|" << sid[i].susn << "\n";
}
// function to the student record 
void student::add()
{
    // int search(char* fusn);
    int k, mode = 0;
    cout << "enter the usn number=";
    cin >> dusn;
    if (search(dusn) >= 0)
    {
        cout << "usn is aly present we can't add to index file\n";
        return;
    }
    for (i = indsize; i > 0; i--)
    {
        if (strcmp(dusn, id[i - 1].iusn) < 0)
            id[i] = id[i - 1];
        else
            break;
    }
    if (mode == 0)
        opener(dfile, datafile, ios::app);
    else

    {
        opener(dfile, datafile, ios::out);
        mode = 1;
    }
    // opener(dfile, datafile, ios::app);
    cout << "enter the name=";
    cin >> name;
    cout << "enter the branch=";
    cin >> branch;
    cout << "enter the semester=";
    cin >> sem;
    pack();
    dfile.seekg(0, ios::end);
    k = (int)dfile.tellg();
    dfile << buffer << "\n";
    strcpy_s(id[i].iusn, dusn);
    _itoa_s(k, id[i].addr, 10);
    indsize++;
    for (i = sindsize; i > 0; i--)
    {
        if (strcmp(name, sid[i - 1].sname) < 0)
            sid[i] = sid[i - 1];
        else if ((strcmp(name, sid[i - 1].sname) == 0) && (strcmp(dusn, sid[i - 1].susn) < 0))
            sid[i] = sid[i - 1];
        else
            break;
    }
    strcpy_s(sid[i].sname, name);
    strcpy_s(sid[i].susn, dusn);
    sindsize++;
}
// function to pack 
void student::pack() {

strcpy_s(buffer, dusn);
strcat_s(buffer, "|");
strcat_s(buffer, name);
strcat_s(buffer, "|");
strcat_s(buffer, branch);
strcat_s(buffer, "|");
strcat_s(buffer, sem);
}
// function to search based on usn number 
int search(char* fusn)
{
    int low = 0, high = indsize - 1, mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (strcmp(fusn, id[mid].iusn) == 0)
            return mid;
        if (strcmp(fusn, id[mid].iusn) > 0)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}
// function to search based on secondary key 
int sec_search()
{
    int pos, j, flag = -1;
    cout << "\nenter the name to search(sec key):";
    cin >> skey;
    cout << "the searched record details are :" << endl;
    cout << "usn"
         << "\t\tname" << endl;
    opener(dfile, datafile, ios::in | ios::out);
    for (j = 0; j < sindsize; j++)

        if (strcmp(skey, sid[j].sname) == 0)
        {
            cout << sid[j].susn << "\t\t" << sid[j].sname << endl;
            flag = j;
        }
    return flag;
}
// function to remove the record
void student::remove()
{
    char rusn[10];
    int pos, spos;
    cout << "enter the usn number above listed to delete:";
    cin >> rusn;
    for (i = 0; i < sindsize; i++)
    {
        if (strcmp(sid[i].susn, rusn) == 0)
        {
            spos = i; /* spos is the index to sid array where the rusn is present*/
            break;
        }
    }
    if (strcmp(sid[spos].sname, skey) == 0)
    {
        pos = search(rusn);
        dfile.seekp(atoi(id[pos].addr), ios::beg);
        dfile.put('$');
        for (i = pos; i < indsize; i++)
            id[i] = id[i + 1];
        indsize--;

        for (i = spos; i < sindsize; i++)
            sid[i] = sid[i + 1];
        sindsize--;
    }
    else
        cout << "usn number and name doesnot match";
}
void student::ssearch()
{
    int pos, flag = -1;
    cout << "\nenter the name to search(sec key):";
    cin >> skey;
    opener(dfile, datafile, ios::in | ios::out);
    for (int j = 0; j < sindsize; j++)
        if (strcmp(skey, sid[j].sname) == 0)
            for (int i = 0; i < indsize; i++)
                if (strcmp(sid[j].susn, id[i].iusn) == 0)
                {
                    pos = i;
                    flag = i;
                }
    if (flag == -1)
    {
        cout << "no data record ";
        _getch();
        return;
    }
    dfile.seekg(atoi(id[pos].addr), ios::beg);
    unpack();
    if (dusn[0] == '$')
    {

        cout << "The record is already deleted!!\n";
        return;
    }
    cout << "Details: \n";
    cout << "USN\tName\tBranch\tSemester" << endl;
    cout << dusn << "\t" << name << "\t" << branch << "\t" << sem << endl;
    dfile.close();
}
// function to display the datafile
void student::datadisp()
{
    cout << endl
         << "the index file details are " << endl;
    cout << "\n"
         << "usn"
         << "\t"
         << "address";
    for (i = 0; i < indsize; i++)
        cout << endl
             << "\n"
             << id[i].iusn << "\t" << id[i].addr;
    cout << endl
         << "\n the secondary file details are " << endl;
    cout << "\n"
         << "name"
         << "\t"
         << "primary reference";
    for (i = 0; i < sindsize; i++)
        cout << endl
             << "\n"
             << sid[i].sname << "\t" << sid[i].susn;
    cout << "\n"
         << "usn"
         << "\t"
         << "name"
         << "\t";
    cout << "branch"
         << "\t"
         << "sem\n";
    while (dfile)
    {
        unpack();
        if (dusn[0] != '$')
        {
            cout << "\n"
                 << dusn << "\t" << name << "\t";
            cout << branch << "\t" << sem;
        }
        else
        {
            cout << "\nDeleted record\n";
        }
    }
}
// function to unpack the data file 
void student::unpack()
{
    dfile.getline(dusn, 15, '|');
    dfile.getline(name, 20, '|');
    dfile.getline(branch, 6, '|');
    dfile.getline(sem, 5, '\n');
}
// main program 
void main()
{
    int ch, flag;
    in.initial();
    sind.sinitial();
    for (;;)
    {
        cout << endl
             << "1-Add,2-display,3-search,4-delete,5-exit\n";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << endl
                 << "enter student details : " << endl;
            s.add();
            in.write();
            sind.swrite();
            break;
        case 2:
            opener(dfile, datafile, ios::in);

            cout << "\nthe indexfile, secondary file and data file" << endl;
            s.datadisp();
            break;
        case 3:
            cout << "To search based on sec key ";
            s.ssearch();
            break;
        case 4:
            flag = sec_search();
            if (flag == -1)
                cout << "no data record found";
            else
            {
                s.remove();
                in.write();
                sind.swrite();
            }
            break;
        default:
            exit(0);
        }
        dfile.close();
        ifile.close();
        sifile.close();
    }
}
