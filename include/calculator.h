#pragma once
#include <string>
#include <vector>
class calculator
{
public:
    typedef long double numT;
    calculator();
    virtual ~calculator();
    /**
     * @brief 展示当前算式内容
     *
     * @return std::string 算式内容
     */
    std::string showOut();
    /**
     * @brief 增加一个新的运算
     * 特别的，如果输入运算符是'S'。将定义为开方操作，此时输入的运算数不做处理
     * 如果输入的运算符是' '。将定义为重置操作，此时输入的运算数将作为初始值使用
     * @param operat 运算符
     * @param num 运算数
     */
    void newInput(char operat, numT num);
    /**
     * @brief 获取当前算式结果
     *
     * @return numT 算式结果
     */
    numT result();
private:
    // 算式数据
    std::vector<numT> num_array;
    // 算式操作符
    std::vector<char> operators;
};

class numException : public std::exception
{
public:
    numException(char operat,calculator::numT num_) : oper(operat),num(num_) {};
    ~numException() {}
    /**
     * @brief 获取发生错误的运算符种类
     *
     */
    char getoperator() {
        return oper;
    }
    /**
     * @brief 获取发生错误的运算数
     *
     * @return calculator::numT
     */
    calculator::numT getErrorNum() {
        return num;
    }
private:
    char oper;
    calculator::numT num;
};