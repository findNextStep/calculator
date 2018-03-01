#include "computer.h"
#include <iostream>
#include <sstream>
using std::stringstream;
using std::string;
computer::computer():lastOperator(' '),
    inInputMode(true),hasPoint(false),inputStack("") {}

string computer::getFormula() {
    return lastFormula;
}
void computer::clear() {
    lastOperator = ' ';
    inInputMode = true;
    hasPoint = false;
    cal.newInput(' ',0);
}

string computer::getResult() {
    if (lastResult.empty()) {
        return inputStack;
    }
    else {
        return lastResult;
    }
}

void computer::input(char a) {
    switch(a) {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0':
    case '.':
        this->inputNum(a);
        break;
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case 'S':
        this->inputOper(a);
        break;
    case 'C':
        this->clear();
        lastResult = "";
        inputStack = "";
        lastFormula = cal.showOut();
        break;
    case '=':
        if (this->inputStack.size()){
            this->pushNow();
        }
        this->makeResult();
        this->clear();
        break;
    default:
        break;
    }
}

void computer::inputNum(char a) {
    // 当上一个运算符为开根号时
    if (lastOperator == ' ') {
        bool lastHasPoint = hasPoint;
        // 清空上一次的结果，重新开始
        this->clear();
        // 恢复点的状况
        hasPoint = lastHasPoint;
    }
    // 考虑输入小数点的情况
    if (a == '.' && !hasPoint) {
        hasPoint = true;
        if (inputStack.empty()) {
            inputStack += '0';
        }
        inputStack += a;
    } else if (a >= '0' && a <= '9') {
        if (a == '0' && (inputStack.empty() || inputStack == "0")) {
            if (inputStack.empty()) {
                inputStack = "0";
            }
        } else {
            inputStack += a;
        }
    }
    lastResult = "";
}

void computer::inputOper(char a) {
    if (!inputStack.empty()) {// 考虑当前输入框有数字的情况
        // 将上一个操作与操作数输入
        pushNow();
    } else { // 考虑输入框没有数字输入的情况
        if (cal.showOut().empty()) {
            // 当运算器内部没有数据时
            cal.newInput(' ',0.0);
            pushNow(' ',0.0);
        }
    }
    // 特殊考虑开根号的情况
    if ('S' == a) {
        // 将操作符重设，如果用户不输入新的操作符
        // 则启用新的运算
        lastOperator = ' ';
        // 立即进行开方运算
        pushNow(a,0.0);
    } else {
        lastOperator = a;
    }
}

void computer::pushNow() {
    return pushNow(lastOperator,switchToNum(inputStack));
}

void computer::pushNow(char oper, numT num) {
    cal.newInput(oper,num);
    makeResult();
}

void computer::makeResult() {
    stringstream ss;
    lastFormula = cal.showOut();
    try {
        ss << cal.result();
        lastResult = ss.str();
    } catch(numException e) {
        std::cout << "error" << std::endl;
        if (e.getoperator() == '/') {
            lastResult = "除数不可为零";
        } else if(e.getoperator() == '%') {
            lastResult = "结果未定义";
        } else if (e.getoperator() == 'S') {
            lastResult = "开方操作不可用于负数";
        }
        lastOperator = ' ';
    }
    inputStack = "";
}

computer::numT computer::switchToNum(string inputString) {
    if (inputString.empty()) {
        return 0.0;
    }
    else {
        stringstream ss;
        ss << inputString;
        computer::numT result;
        ss >> result;
        return result;
    }
}
