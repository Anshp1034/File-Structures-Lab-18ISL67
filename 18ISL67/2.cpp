// This program creates a student database and allows the user to
// write, search, modify, and display the records.

#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;

class student {
public:
  char name[25], usn[15], branch[15], buffer[100];
};

// This function packs the student record into a buffer.
void pack() {
  fstream app;
  if (mode == 0)
    app.open("st1.txt", ios::app);
  else
    app.open("st1.txt", ios::out);
  if (!app) {
    cout << "cant open the file in output mode";
    _getch();
    exit(0);
  }
  strcpy_s(s.buffer, s.name);
  strcat_s(s.buffer, "|");
  strcat_s(s.buffer, s.usn);
  strcat_s(s.buffer, "|");
  strcat_s(s.buffer, s.branch);
  int count = strlen(s.buffer);
  for (int k = 0; k < 45 - count; k++)
    strcat_s(s.buffer, "|");
  strcat_s(s.buffer, "\n");
  app << s.buffer;
  app.close();
}

// This function unpacks the student records from the file.
void unpack() {
  fstream in;
  in.open("st1.txt", ios::in);
  i = 0, no = 0;
  if (!in) {
    cout << "cant open the file in input mode";
    _getch();
    exit(0);
  }
  while (!in.eof()) {
    in.getline(s1[i].name, 15, '|');
    in.getline(s1[i].usn, 15, '|');
    in.getline(s1[i].branch, 15, '|');
    in.getline(extra, 45, '\n');
    no++;
    i++;
  }
  in.close();
}

// This function writes a student record to the file.
void write() {
  cout << "\n enter the student name\n";
  cin >> s.name;
  cout << "enter the student usn\n";
  cin >> s.usn;
  cout << "enter the student branch\n";
  cin >> s.branch;
  pack();
  mode = 0;
}

// This function searches for a student record in the file.
void search() {
  char usn[15], extra[45];
  cout << "enter the usn to search=";
  cin >> usn;
  unpack();
  for (i = 0; i < no; i++) {
    if (strcmp(s1[i].usn, usn) == 0) {
      cout << "\nrecord found";
      cout << "\n"
           << s1[i].name << "\t" << s1[i].usn << "\t" << s1[i].branch;
      _getch();
      return;
    }
  }
  cout << "record not found";
  _getch();
  return;
}

// This function displays all the student records in the file.
void display() {
  cout << "name\t\t usn\t\t branch\n\n";
  unpack();
  for (int i = 0; i < no; i++)
    cout << "\n\n"
         << s1[i].name << "\t\t" << s1[i].usn << "\t\t" << s1[i].branch;
  _getch();
}

// This function modifies a student record in the file.
void modify() {
  char usn[15];
  int j;
  cout << "enter the usn to search\n";
  cin >> usn;
  unpack();
  no--;
  for (j = 0; j < no; j++) {
    if (strcmp(usn, s1[j].usn) == 0) {
      cout << "the old values of the record are with usn" << usn << "are";
      cout << "\nname=" << s1[j].name;
      cout << "\nusn=" << s1[j].usn;
      cout << "\nbranch=" << s1[j].branch;
      cout << "enter the new values\n";
      cout << "\nname=";
      cin >> s1[j].name;
      cout << "\nusn=";
      cin >> s1[j].usn;
      cout << "\nbranch=";
      cin >> s1[j].branch;
      break;
    }
  }
  if (j == no) {
    cout << "the record with usn is not present";
    _getch();
    return;
  }
  mode = 1;
  for (j = 0; j < no; j++) {
    strcpy_s(s.name, s1[j].name);
    strcpy_s(s.usn, s1[j].usn);
    strcpy_s(s.branch, s1[j].branch);
    pack();
    mode = 0;
  }
  cout << "record modified\n";
}

// This is the main function of the program.
void main() {
  int choice;
  for (;;) {
    cout << "\n0:exit";
    cout << "\n1:write";
    cout << "\n2:display";
    cout << "\n3:modify";
    cout << "\n4:search";
    cout << "enter u choice\n";
    cin >> choice;
    switch (choice) {
    case 1:
      write();
      break;
    case 2:
      display();
      break;
    case 3:
      modify();
      break;
    case 4:
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
