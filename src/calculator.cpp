#include "calculator.h"
#include <sstream>
#include <math.h>
using std::stringstream;

calculator::calculator(){
	this->num_array.push_back((numT)0);
}


calculator::~calculator(){}

std::string calculator::showOut()
{
	if (num_array.empty()){
		return "";
	}
	stringstream ss;
	auto num = this->num_array.begin();
	ss << *num;
	++num;
	for (auto oper = this->operators.begin(); oper != operators.end(); ++oper) {
		if (*oper != 'S') {
			ss << " " << *oper << " " << *num;
			++num;
		}
		else {
			std::string now = ss.str();
			ss.str("");
			ss.clear();
			ss << "sqrt( " << now << " )";
		}
	}
	return ss.str();
}

void calculator::newInput(char operat, numT num)
{
	if (operat == ' ') {
		this->num_array.clear();
		this->num_array.resize(0);
		this->operators.clear();
		this->operators.resize(0);
		this->num_array.push_back(num);
	}
	else {
		this->operators.push_back(operat);
		if (operat != 'S') {
			this->num_array.push_back(num);
		}
	}
}

calculator::numT calculator::result()
{
	numT re = *(num_array.begin());
	auto oper = this->operators.begin();
	for (auto num = this->num_array.begin() + 1; this->operators.end() != oper; ++num, ++oper) {
		switch (*oper)
		{
		case '+': {
			re += *num;
		}break;
		case '-': {
			re -= *num;
		}break;
		case '*': {
			re *= *num;
		}break;
		case '/': {
			if (*num == 0.0) {
				throw numException('/', *num);
			}
			re /= *num;
		}break;
		case '%': {
			if (*num == 0.0) {
				throw numException('%', *num);
			}
			re = fmod(re, *num);
		}break;
		case 'S': {
			--num;
			if (re < 0.0) {
				throw numException('S', re);
			
			}
			re = std::sqrt(re);
		}break;
		default:
			break;
		}
	}
	return re;
}