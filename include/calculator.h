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
     * @brief չʾ��ǰ��ʽ����
     *
     * @return std::string ��ʽ����
     */
    std::string showOut();
    /**
     * @brief ����һ���µ�����
     * �ر�ģ���������������'S'��������Ϊ������������ʱ�������������������
     * ���������������' '��������Ϊ���ò�������ʱ���������������Ϊ��ʼֵʹ��
     * @param operat �����
     * @param num ������
     */
    void newInput(char operat, numT num);
    /**
     * @brief ��ȡ��ǰ��ʽ���
     *
     * @return numT ��ʽ���
     */
    numT result();
private:
    // ��ʽ����
    std::vector<numT> num_array;
    // ��ʽ������
    std::vector<char> operators;
};

class numException : public std::exception
{
public:
    numException(char operat,calculator::numT num_) : oper(operat),num(num_) {};
    ~numException() {}
    /**
     * @brief ��ȡ������������������
     *
     */
    char getoperator() {
        return oper;
    }
    /**
     * @brief ��ȡ���������������
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