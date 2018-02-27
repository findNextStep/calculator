#include "calculator.h"
#include <iostream>
using ::std::cin;
using ::std::cout;
using ::std::endl;
int main(){
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