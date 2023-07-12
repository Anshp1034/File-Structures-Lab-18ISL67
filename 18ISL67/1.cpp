// This program reads names from the user, reverses them, and writes them to a file.
// The reversed names are then read from the file and reversed again, and the
// reversed names are written to another file.

#include <iostream>
#include <conio.h>
#include <process.h>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

// This class represents a name.
class names {
public:
  char name[50]; // The name.
};

// This function is the main function of the program.
void main() {
  // Declare an array of names.
  names n[10];

  // Open a file to write the names to.
  ofstream out("file.txt");

  // Get the number of names from the user.
  int m;
  cout << "enter the no. of names to be entered\n";
  cin >> m;

  // For each name, read it from the user, reverse it, and write it to the file.
  for (int i = 0; i < m; i++) {
    cout << "enter name\n";
    cin >> n[i].name;
    cout << "the name in reverse order\n";
    strrev(n[i].name);
    cout << n[i].name << "\n";
    out << n[i].name;
    out << "\n";
  }

  // Close the file.
  out.close();

  // Open the file to read the names from.
  ifstream in("file.txt");

  // Declare a character array to store the names from the file.
  char ch[10];

  // For each name in the file, reverse it and write it to a new file.
  cout << "names from files\n";
  while (in) {
    in >> ch;
    if (in)
      strrev(ch);
    cout << ch << "\n";
    outf << ch;
    outf << "\n";
  }

  // Close the files.
  in.close();
  outf.close();
  getch();
}
