#include "calculator.h"
#include "computer.h"
#include <iostream>
#include <conio.h>
using ::std::cin;
using ::std::cout;
using ::std::endl;
int mains() {
    calculator cal;
    char input;
    calculator::numT num;
    cin >> num;
    cal.newInput(' ', num);
    cout << cal.showOut() << " = " << cal.result() << endl;
    while (cin >> input) {
        if (input != 'S') {
            cin >> num;
        }
        cal.newInput(input, num);
        cout << cal.showOut() << " = " << cal.result() << endl;
    }
    return 0;
}
int main() {
    char a;
    computer com;
    while (a = getch()) {
        if (a == 't') {
            break;
        }
        cout << a<<endl;
        com.input(a);
        cout << "result is  : " << com.getResult() <<endl;
        cout << "formula is : " << com.getFormula() << endl;
    }
    return 0;
}