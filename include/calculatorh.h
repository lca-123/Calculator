#pragma once
#include<string>
#include<iostream>
#include<math.h>
#include<vector>
using namespace std;

//�����ַ�������ı��ʽ
double CALCULATOR(string s);
//���㺬��δ֪��x�ı��ʽ
double CALCULATORX(string s, double x);
//���㺯���Ļ���
double INTEGRAL(string s, double a, double b);
//���㺯����ĳһ��ĵ���
double DERIVATION(string s, double x);
//�������
double ROOT(string s, double a, double b);
//������ȷ��
string errorTest();
//doubleתstr
void num2string(double num, string& str);