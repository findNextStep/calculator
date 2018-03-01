#include <string>
#include "calculator.h"
class computer {
public:
    typedef long double numT;
    computer();
    void input(char a);
    std::string getFormula();
    std::string getResult();
    void clear();
protected:
    void inputNum(char a);
    void inputOper(char a);
    numT static switchToNum(std::string);
    void pushNow(char oper,numT num);
    void pushNow();
    void makeResult();
private:
    bool inInputMode;
    bool hasPoint;
    char lastOperator;
    std::string inputStack;
    std::string lastResult;
    std::string lastFormula;
    calculator cal;
};