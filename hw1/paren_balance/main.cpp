#include <iostream>
#include <string>

using namespace std;
int numOfOPare = 0;
int numOfOBrac = 0;
int numOfCPare = 0;
int numOfCBrac = 0;
int arb = 0;
int arb1 = 0;
char posParen[100];
char queue[100];
// Implement below
bool are_paren_balanced(const string& expression, size_t len);
bool check(const string& express, int leng);

// We have suggested a helper method, but feel free to write whatever you see fit
//bool are_paren_balanced(const string& expression, size_t& i, char expected_closing);

// Do not change this method
int main(int argc, char* argv[]) {
    cout << "." << endl;
    // Check if an expression has been passed to the program
    if (argc != 2) {
        cerr << "error: expected expression to check!" << endl;
        return -1;
    }
    cout << "." << endl;

    // The second argument is the expression string in the format specified and
    // promised in the assignment page. You do not need to do any error checking
    // except for checking the parentheses.
    string expression(argv[1]);
    cout << "." << endl;

    if (are_paren_balanced(expression, expression.length()) == true) {
        cout << "correct" << endl;
    } else {
        cout << "incorrect" << endl;
    }

    return 0;
}

// Some notes:
// - This method must be implemented recursively.
// - When debugging, make sure to output to cerr rather than cout. This will
//   prevent any leftover debug statements from confusing the automated
//   grading and will make sure output is guaranteed to be written to the
//   terminal in case your program crashes.

bool are_paren_balanced(const string& expression, size_t len) {
    cout << "." << endl;
    if (expression.length() == 0 || expression.length() == 1)
        return true;
    if (expression[arb] == '(')
    {
        numOfOPare++;
        posParen[arb1] = '(';
        arb1++;
    }
    else if (expression[arb] == ')')
    {
        numOfCPare++;
        posParen[arb1] = ')';
        arb1++;
    }
    else if (expression[arb] == '[')
    {
        numOfOBrac++;
        posParen[arb1] = '[';
        arb1++;
    }
    else if (expression[arb] == ']')
    {
        numOfCBrac++;
        posParen[arb1] = ']';
        arb1++;
    }
    if (arb == (len - 1))
    {
        if (check(posParen, arb1))
            return true;
        else
            return false;
    }
    arb++;
    if (are_paren_balanced(expression, expression.length()))
        return true;
    else
        return false;

}
bool check(const string&  express, int leng)
{
    cout << numOfOBrac << numOfCBrac << numOfOPare << numOfCPare << endl;
    cout << express[0] << endl;
    if (express[0] == ']' || express[0] == ')' || numOfCBrac != numOfOBrac || numOfOPare != numOfCPare)
    {
        cout << "test" << endl;
        return false;
    }
    else
    {
        int k = 0;
        for (int i = 0; i < leng; i++)
        {

            if (express[i] == '(')
            {
                if (express[i + 1] == ']')
                {
                    return false;
                }
                else if (express[i + 1] == ')')
                {
                    numOfOPare--;
                    queue[k] = '(';
                    k++;
                }
                else
                {
                    queue[k] = '(';
                    k++;
                }
            }
            else if (express[i] == '[')
            {
                if (express[i + 1] == ')')
                    return false;
                else if (express[i + 1] == ']')
                {
                    numOfOBrac--;
                    queue[k] = '[';
                    k++;
                }
                else
                {
                    queue[k] = '[';
                    k++;
                }
            }
            else if (express[i] == ')')
            {
                if (queue[k-1] == '(')
                {
                    numOfCPare--;
                    k--;
                }
                else
                {
                    cout << "test" << endl;
                    return false;
                }
            }
            else if (express[i] == ']')
            {
                if (queue[k - 1] == '[')
                {
                    numOfCBrac--;
                    k--;
                }
                else
                {
                    return false;
                }
            }
        }
        return true;
    }
   
}
// Add any additional function implementations here.
//
// If you want to use the suggested helper method, you'll have to write its
// definition here.
