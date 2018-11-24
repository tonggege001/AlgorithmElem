//////
////// Created by Administor on 2018/10/24.
//////
//#include <iostream>
//#include<string>
//
//#ifndef ARITHMETIC1_BIGINTEGER_H
//#define ARITHMETIC1_BIGINTEGER_H
//
//
//using namespace std;
//
//class BigInteger{
//public:
//    string number;//数字,采用小端方式存放数字
//    bool sign;//符号
//    int length;//指明大整数的长度，
//    BigInteger():number(nullptr){
//        this->number = *new string();
//        this->length = 1;
//        this->sign = true;
//    }
//
//    BigInteger(BigInteger b){
//        this->sign = b.sign;
//        this->length = b.length;
//        string temp(b.number);
//        this->number.swap(temp);
//    }
//
//
//    ~BigInteger(){
//        delete &this->number;
//    }
//    BigInteger operator=(BigInteger);//实现赋值运算
//    BigInteger operator+(BigInteger b); //实现加法运算
//    BigInteger operator-(BigInteger b);//实现减法运算
//    BigInteger operator-();//取负运算符
//    BigInteger operator*(BigInteger b); //实现乘法运算
//    BigInteger operator/(BigInteger b);//实现除法运算
//
//    //判断操作数是否绝对值大于等于b
//    bool absBig(BigInteger b);
//
//};
//
//
////#endif //ARITHMETIC1_BIGINTEGER_H
