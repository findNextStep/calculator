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
    void pushNow(char oper = '\0',numT num = 0.0);
private:

    bool inInputMode;
    bool hasPoint;
    char lastOperator;
    std::string inputStack;
    std::string lastResult;
    calculator cal;
};