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
    // ����һ�������Ϊ������ʱ
    if (lastOperator == ' ') {
        bool lastHasPoint = hasPoint;
        // �����һ�εĽ�������¿�ʼ
        this->clear();
        // �ָ����״��
        hasPoint = lastHasPoint;
    }
    // ��������С��������
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
    if (!inputStack.empty()) {// ���ǵ�ǰ����������ֵ����
        // ����һ�����������������
        pushNow();
    } else { // ���������û��������������
        if (cal.showOut().empty()) {
            // ���������ڲ�û������ʱ
            cal.newInput(' ',0.0);
            pushNow(' ',0.0);
        }
    }
    // ���⿼�ǿ����ŵ����
    if ('S' == a) {
        // �����������裬����û��������µĲ�����
        // �������µ�����
        lastOperator = ' ';
        // �������п�������
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
            lastResult = "��������Ϊ��";
        } else if(e.getoperator() == '%') {
            lastResult = "���δ����";
        } else if (e.getoperator() == 'S') {
            lastResult = "���������������ڸ���";
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
