#pragma once
#include<string>
#include<iostream>
#include<math.h>
#include<vector>
using namespace std;

//计算字符串代表的表达式
double CALCULATOR(string s);
//计算含有未知数x的表达式
double CALCULATORX(string s, double x);
//计算函数的积分
double INTEGRAL(string s, double a, double b);
//计算函数在某一点的导数
double DERIVATION(string s, double x);
//方程求根
double ROOT(string s, double a, double b);
//检验正确性
string errorTest();
//double转str
void num2string(double num, string& str);