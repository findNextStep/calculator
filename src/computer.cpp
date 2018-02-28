#include "computer.h"
#include <sstream>
using std::stringstream;
using std::string;
computer::computer():lastOperator(' '),
    inInputMode(true),hasPoint(false),inputStack("") {}

string computer::getFormula() {
    return cal.showOut();
}
void computer::clear() {
    lastOperator = ' ';
    inInputMode = true;
    hasPoint = false;
    inputStack = "";
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
    default:
        break;
    }
}

void computer::inputNum(char a) {
    // ����һ�������Ϊ������ʱ
    if (lastOperator == 'S') {
        // �����һ�εĽ�������¿�ʼ
        this->clear();
        inputStack += a;
    } else {
        // ��������С��������
        if (a == '.' && !hasPoint) {
            hasPoint = true;
            if (inputStack.empty()) {
                inputStack += '0';
            }
            inputStack += a;
        } else if (a >= '0' && a <= '9') {
            if (a == '0' && inputStack.empty()) {
                return;
            }
            inputStack += a;
        }
    }
    lastResult = "";
}

void computer::inputOper(char a) {
    if (!inputStack.empty()) {// ���ǵ�ǰ����������ֵ����
        // ����һ�����������������
        pushNow();
        // ���⿼�ǿ����ŵ����
        if ('S' == a) {
            // �����������裬����û��������µĲ�����
            // �������µ�����
            lastOperator = ' ';
            // �������п�������
            cal.newInput(a,0.0);
        }
    } else { // ���������û��������������
        if (cal.showOut().empty()) {
            // ���������ڲ�û������ʱ
            cal.newInput(' ',0.0);
            pushNow(' ',0.0);
        }
        lastOperator = a;
    }
}

void computer::pushNow(char oper, numT num) {
    if ('\0' == oper) {
        oper = lastOperator;
        num = switchToNum(inputStack);
    }
    cal.newInput(oper,num);
    stringstream ss;
    ss << cal.result();
    lastResult = ss.str();
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
