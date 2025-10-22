#include "AVL.h"
#include <sstream>
using namespace std;

// Parsing Inputs:
// Given # of lines (useful for looping) + commands (will need to break into separate sections)
// Sample input given on project page (insert “Brandon” 45679999)

// Main function
//  Should hold an instance of your AVLTree class to access
//  Use the parsed input to determine which function should be called ex.  tree.search(00000001);
bool validateNextWord(const string &word)
{
    for (char c : word)
    {
        if (!isdigit(c) && !isalpha(c))
        {
            // cout << "Character not valid: " << c << endl;
            return false;
        }
    }
    // cout << "Next word validated: " << word << endl;
    return true;
}

bool validateufid(const string &ufid)
{
    if (ufid.length() != 8)
    {
        //  cout << "UFID length invalid: " << ufid.length() << endl;
        return false;
    }
    for (char c : ufid)
    {
        if (!isdigit(c))
        {
            // cout << "UFID contains non-digit character: " << c << endl;
            return false;
        }
    }
    // cout << "UFID validated: " << ufid << endl;
    return true;
}

bool validatename(const string &name)
{
    for (char c : name)
    {
        if (!isalpha(c) && !isspace(c))
        {
            // cout << "Name contains invalid character: " << c << endl;
            return false;
        }
    }
    // cout << "Name validated: " << name << endl;
    return true;
}

bool validatefunction(const string &function)
{
    if (function != "insert" && function != "remove" && function != "search" && function != "printInorder" && function != "printPreorder" && function != "printPostorder" && function != "printLevelCount" && function != "removeInorder")
    {
        // cout << "Function not valid: " << function << endl;
        return false;
    }
    // cout << "Function validated: " << function << endl;
    return true;
}

int main()
{
    AVLTree tree;

    // 1st step: read number of commands
    string numCommands;
    getline(cin, numCommands);

    int numCommandsInt = stoi(numCommands);

    // loop to read each command line
    for (int i = 0; i < numCommandsInt; i++)
    {
        string line;
        getline(cin, line);
        istringstream inStream(line);
        string name;
        string number;

        // read the 1st word up to space
        string function;
        getline(inStream, function, ' ');
        // Any invalid or misspelled commands must be ignored with an "unsuccessful" message followed by executing the next command.
        if (!validatefunction(function))
        {
            cout << "unsuccessful" << endl;
            continue;
        }

        // space to next quotation mark: (white space in insert, search name, print ones)
        // number in remove, search id, removeInorder.
        string first;
        getline(inStream, first, '"');

        // read name up to ending quotation mark for insert or search name
        string second;
        getline(inStream, second, '"');

        // in insert is ufid in all others whitespace or empty string
        string third;
        getline(inStream, third, ' ');

        // read number up to end of line
        string fourth;
        getline(inStream, fourth);

        // cout << "line: " << line << endl;
        // cout << "function: " << function << endl;
        // cout << "first: " << first << endl;
        // cout << "second: " << second << endl;
        // cout << "third: " << third << endl;
        // cout << "fourth: " << fourth << endl;

        // commands
        if (function == "insert")
        {
            const string &name = second;
            const string &ufid = fourth;
            if (validatename(name) && validateufid(ufid))
            {
                tree.insert(name, ufid);
            }
            else
            {
                cout << "unsuccessful" << endl;
            }
        }

        else if ((function == "remove"))
        {
            const string &ufid = first;
            if (validateufid(ufid))
            {
                tree.remove(ufid);
            }
            else
            {
                cout << "unsuccessful" << endl;
            }
        }

        else if ((function == "search"))
        {
            if (validateufid(first))
            {
                tree.search_id(first);
            }
            else if (validatename(second))
            {
                tree.search_name(second);
            }
            else
            {
                cout << "unsuccessful - neither ufid or name validated" << endl;
            }
        }

        else if (function == "printInorder")
        {
            tree.printinorder();
        }

        else if (function == "printPreorder")
        {
            tree.printpreorder();
        }

        else if (function == "printPostorder")
        {
            tree.printpostorder();
        }

        else if (function == "printLevelCount")
        {
            tree.printLevelCount();
        }

        else if (function == "removeInorder")
        {
            if (validateNextWord(first))
            {
                int n = stoi(first);
                tree.removeInorder(n);
            }
            else
            {
                cout << "unsuccessful - n not validated" << endl;
            }
        }
    }

    return 0;
}

// int main()
// {
//     AVLTree tree;

//     tree.insert("Brandon", "45679999");
//     tree.insert("Brian", "35459999");
//     tree.insert("Briana", "87879999");
//     tree.insert("Bella", "95469999");
//     tree.printinorder();
//     tree.search_name("Brian");
//     tree.search_id("35459999");
//     tree.search_id("00000000");
//     tree.remove("35459999");
//     tree.printinorder();
//     return 0;
// }

// string line;
// getline(cin, line);

// istringstream inStream(line);

// // read the 1st word up to space
// string function;
// getline(inStream, function, ' ');

// // space to next quotation mark (we don't want that)
// string next;
// getline(inStream, next, '"');

// // read name up to ending quotation mark
// string name;
// getline(inStream, name, '"');

// // quotation mark to space
// string next2;
// getline(inStream, next2, ' ');

// // read number up to end of line
// string number;
// getline(inStream, number);

// cout << line << endl;

// cout << "function: " << function << endl;
// cout << "next: " << next << endl;
// cout << "name: " << name << endl;
// cout << "next2: " << next2 << endl;
// cout << "number: " << number << endl;

// primeiro
// TA CODE AND EXPLANATIONS:
// TA: read one line of input from cin
// string line;
// getline(cin, line);

// // TA: create an input stream from that line
// // READ IN EVERYTHING IN THIS LINE USING THE IN.
// istringstream in(line);

// // TA: read the first word from the input stream
// string command;
// in >> command;

// // TA: read up to the next quotation mark
// string next;
// getline(in, next, '"');

// //// oie
// AVLTree tree;
// // The first line will always be a number which will indicate the number of commands after that.
// string numCommands;
// // After receiving first number, we're going to read in the lines one by one.
// // parsing 21:00; Regex may be helpful but not necessary
// // recommends using a for loop to take in the correct amount of inputs

// tree.insert("Brandon", "45679999");
// tree.insert("Brian", "35459999");
// tree.insert("Briana", "87879999");
// tree.insert("Bella", "95469999");
// // tree.printinorder();
// //  tree.debugprint();
// //  tree.search_name("Brian");
// //  tree.search_id("35459999");
// //  tree.search_id("00000000");
// tree.remove_id("35459999");
// tree.printinorder();

// TA CODE:
// string fullstringline;
// getline(cin, fullstringline);

// // test
// cout << fullstringline << endl;

// istringstream newCin(fullstringline);

// string city;
// newCin >> city;
// string street;
// newCin >> street;
// string num;
// newCin >> num;

// cout << city << endl
//      << street << endl
//      << num << endl;

// cout << "----- another case -----" << endl;