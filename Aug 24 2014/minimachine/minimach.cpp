#include <iostream>
#include <map>
#include <utility>
#include <string>
#include <vector>
#include <limits>
#include <fstream>

using std::cin; using std::cout; using std::endl;
using std::pair; using std::make_pair;
using std::string; using std::vector;
using std::map; using std::ifstream;

ifstream opinput("minmachine-random-terror-input.txt");
pair<string, int> current_op; // next op to interpret
vector<int> data;             // Holds all integers
int min_val = std::numeric_limits<int>::min(); // Minimum int on stack
int min_index = 0;

void print_vec(vector<int>& v)
/* Prints out all elements in vector, each delimited by a space */
{
    int sz = v.size();
    if (sz == 0) {
        cout << "EMPTYVEC" << endl;
        return;
    }
    for (int i = 0; i != sz; ++i)
    {
        cout << v[i] << " ";
    }
    cout << endl;
    return;
}

void find_min()
/* Set min_val and min_index to min value on stack */
{
    if (data.size() == 0) {
        return;
    }
    int sz = data.size();
    min_val = data[0];
    for (int i = 0; i != sz; ++i) {
        if (data[i] <= min_val) {
            min_index = i;
            min_val = data[i];
        }

    }
}

void insert_op(int n)
{
    // Keeps track of min as adds to stack
    if (n <= min_val || data.size() == 0) {
        min_val = n;
        min_index = data.size();
    }
    data.push_back(n);
    return;
}

void min_op(int n = 0)
/* Print min value on stack */
{
    // Cannot find min of empty stack
    if (data.size() == 0) {
        cout << "error" << endl;
        exit(-1);
    }
    cout << data[min_index] << endl;
    return;
}

void desert_op(int n)
{
    int sz = data.size();
    // Can't desert negative elements or more than are on stack
    if (n < 0 || n > sz) {
        cout << "error" << endl;
        exit(-1);
    }
    vector<int>::iterator b = data.end() - n;
    cout << *b << endl;
    data.erase(b, data.end());
    find_min(); // In case we erased the min
    return;
}

void decr_op(int n)
{
    if (n < 0) { // Can't decrement by negative number
        cout << "error" << endl;
        exit(-1);
    }
    int sz = data.size();
    min_val -= n; // Decr stored minimum
    for (int i = min_index; i != sz; ++i) {
        data[i] -= n;
    }
    return;
}

map<string, decltype(min_op)*> operations; // Maps name of function to f ptrs

bool input_operation()
{
    string opname;  // Opcode
    int number = 0; // Set in case first op is min
    if (!(opinput >> opname)) {
        return false;
    }
    if (opname != "min") {
        if (!(opinput >> number)) {
            return false;
        }
    }
    current_op = make_pair(opname, number);
    return true;
}

void interpret_code()
{
    operations[current_op.first](current_op.second);
    return;
}


int main()
{
    /* map ops to op names */
    operations["insert"] = &insert_op;
    operations["min"] = &min_op;
    operations["desert"] = &desert_op;
    operations["decr"] = &decr_op;
    while (input_operation()) {
        interpret_code();
    }
    return 0;
}