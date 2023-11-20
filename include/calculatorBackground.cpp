#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<vector>
#include<math.h>
#include<conio.h>
#include<regex>
#include<sstream>
#include<stack>
using namespace std;

const int N = 3000;
const double stepi = 0.0005;
const double stepd = 0.01;
const double E = 2.71828182845904523536;
const double PI = 3.14159265358979323846;
const double esp = 1e-6;
int errorType = -1;

string Sstr = "-[0-9]+(.[0-9]+)?|[0-9]+(.[0-9]+)?";
regex re(Sstr);

/*
//��������
//1. ����Ϊ0
//2.ȡģ��������������������
//3.�׳˲���������
//4.����Ϊ����
//6.ȡ��������Ϊ����
//5.�����Ǻ���������
//7.����������
*/
string errorTest() {
	if (errorType == 1) {
		return "Zero divisor��";
	}
	if (errorType == 2) {
		return "Modulus must be positive integers";
	}
	if (errorType == 3) {
		return "Factorial should be positive integer";
	}
	if (errorType == 4) {
		return "Root should be positive";
	}
	if (errorType == 6) {
		return "Logarithm should be positive";
	}
	if (errorType == 5) {
		return "Domain of the inverse trigonometric should between 0 and 1";
	}
	if (errorType == 7) {
		return "Operator Error";
	}
	return "RIGHT";
	
}

//�׳�
double FAC(double num) {
	if (num < 0) {
		printf("�������ܽ׳�");
		exit(0);
	}
	if (fabs(num - (int)num) <= 1e-8) {
		double res = 1;
		for (double i = 0; i < num; i+=1) {
			res *= i + 1.0;
		}
		return res;
	}
	else {
		printf("С�����ܽ׳�");
		exit(0);
	}
	return 0;
}

//������
double SQRT(double num) {
	if (num < 0) {
		printf("�������ܿ���");
		exit(0);
	}
	else {
		return sqrt(num);
	}
	return 0;
}

//�ַ���תdouble
void string2num(string str, double& num) {
	if (str.compare("pi") == 0) {
		num = PI;
	}
	else if (str.compare("e") == 0) {
		num = E;
	}
	else {
		stringstream ss;
		ss << str;
		ss >> num;
	}
}

//doubleת�ַ���
void num2string(double num, string& str) {
	stringstream ss;
	ss << num;
	str = ss.str();
}

//���ز����������ȼ� 
int getOperationValue(string oper) {
	int res=0;
	if (oper.compare("+") == 0) {
		res = 1;
	}else if (oper.compare("-") == 0) {
		res = 2;
	}else if (oper.compare("*") == 0) {
		res = 3;
	}else if (oper.compare("/") == 0 || oper.compare("%") == 0) {
		res = 3;
	}else if (oper.compare("^") == 0) {
		res = 4;
	}else if (oper.compare("!") == 0) {
		res = 5;
	}else if (oper.compare("|") == 0) {
		res = 5;
	}else if (oper.compare("sin") == 0 || oper.compare("asin") == 0 || oper.compare("cos") == 0 || oper.compare("acos") == 0 || oper.compare("tan") == 0 || oper.compare("atan") == 0) {
		res = 6;
	}else if (oper.compare("log") == 0 || oper.compare("ln") == 0) {
		res = 7;
	}
	return res;

}

//��׺���ʽת����
vector<string> toInfixExpressionList(string s) {
	vector<string> ls;
	const char* c = s.c_str();//�ַ���תΪ�ַ����� 
	int i = 0;//�����ַ�����	
	do {
		if ((c[i] >= '0' && c[i] <= '9') || c[i] == '.') {
			//��������
			char str[100];//�����ַ���ƴ��
			int j = 0;
			while (i < s.length() && ((c[i] >= '0' && c[i] <= '9') || c[i] == '.')) {
				str[j] = c[i];
				j++;
				i++;
			}
			str[j] = '\0';
			string num = str;
			ls.push_back(num);
		}
		else {
			//�������������������e pi 
			if (c[i] == ' ' || c[i] == '\n' || c[i] == '\t') {//����������� 
				i++;
			}
			else
				if (c[i] == 'p' && c[i + 1] == 'i') {//����pi 
					ls.push_back("pi");
					i += 2;
				}
				else
					if (c[i] == '!') {//����׳� 
						ls.push_back("!");
						ls.push_back("0");
						i++;
					}
					else
						if (c[i] == '|') {//������ 
							ls.push_back("0");
							ls.push_back("|");
							i++;
						}
						else
							if (c[i] == '-') {//������ 
								if (i == 0 || c[i - 1] == '(') {//�渺�� 
									char str[100] = "-";//�����ַ���ƴ��
									i++;
									int j = 1;
									while (i < s.length() && ((c[i] >= '0' && c[i] <= '9') || c[i] == '.')) {
										str[j] = c[i];
										j++;
										i++;
									}
									str[j] = '\0';
									string num = str;
									ls.push_back(num);
								}
								else {//�ٸ�������ͨ���� 
									ls.push_back("-");
									i++;
								}
							}
							else
								if (c[i] == 's' || c[i] == 'c' || c[i] == 't' || c[i] == 'a') {//�������Ǻ��� 
									if (c[i] == 's') {
										ls.push_back("0");
										ls.push_back("sin");
										i += 3;
									}
									else if (c[i] == 'c') {
											ls.push_back("0");
											ls.push_back("cos");
											i += 3;
										}
									else
											if (c[i] == 't') {
												ls.push_back("0");
												ls.push_back("tan");
												i += 3;
											}
											else
												if (c[i] == 'a') {
													if (c[i + 1] == 's') {
														ls.push_back("0");
														ls.push_back("asin");
														i += 4;
													}
													else
														if (c[i + 1] == 'c') {
															ls.push_back("0");
															ls.push_back("acos");
															i += 4;
														}
														else
															if (c[i + 1] == 't') {
																ls.push_back("0");
																ls.push_back("atan");
																i += 4;
															}
												}
								}
								else
									if (c[i] == 'l') {//������� 
										if (c[i + 1] == 'n') {
											ls.push_back("0");
											ls.push_back("ln");
											i += 2;
										}
										else
											if (c[i + 1] == 'o' && c[i + 2] == 'g') {
												ls.push_back("0");
												ls.push_back("log");
												i += 3;
											}
									}
									else {
										if (c[i] == '(') {
											ls.push_back("(");
											i++;
										}
										else
											if (c[i] == ')') {
												ls.push_back(")");
												i++;
											}
											else
												if (c[i] == '+') {
													ls.push_back("+");
													i++;
												}
												else
													if (c[i] == '-') {
														ls.push_back("-");
														i++;
													}
													else
														if (c[i] == '*') {
															ls.push_back("*");
															i++;
														}
														else
															if (c[i] == '/') {
																ls.push_back("/");
																i++;
															}
															else
																if (c[i] == 'e') {
																	ls.push_back("e");
																	i++;
																}
																else if (c[i] == '^') {
																	ls.push_back("^");
																	i++;
																}
																else if (c[i] == 'x') {
																	ls.push_back("x");
																	i++;
																}else if(c[i] == '%') {
																	ls.push_back("%");
																	i++;
																}
									}
		}

	} while (i < s.length());
	return ls;
}

//��׺���ʽת��׺���ʽ
vector<string> parseSuffixExpressionList(vector<string> ls) {
	errorType = -1;
	//����ջ ��Ϊs2������������û��pop�����������Ҫ������� �Ƚ��鷳 �����vector������
	stack<string> s1;
	vector<string> s2;
	//����ls
	for (int i = 0; i < ls.size(); i++) {
		string item = ls.at(i);
		//�����һ�����������s2
		if (item.compare("pi") == 0 || item.compare("e") == 0 || regex_match(item, re)==1||item.compare("0")==0||item.compare("x")==0) {
			s2.push_back(item);
		}else if (item.compare("(") == 0) {
			s1.push(item);
		}else if (item.compare(")") == 0) {
			while (s1.top().compare("(") != 0) {

				if (s1.empty()) {
					errorType = 7;
					return s2;
				}

				string str = s1.top();
				s1.pop();
				s2.push_back(str);
			}
			s1.pop();
		}else {
			while (s1.size() != 0 && getOperationValue(s1.top()) >= getOperationValue(item)) {
				string str = s1.top();
				s1.pop();
				s2.push_back(str);
			}
			s1.push(item);
		}
	}
	while (s1.size() != 0) {
		string str = s1.top();
		s1.pop();
		s2.push_back(str);
	}
	return s2;
}

//�沨�����ʽ����
double PolandNotionCal(vector<string> ls) {
	if (errorType == 7) {
		return -1;
	}
	stack<string> stack;
	errorType = -1;
	for (int i = 0; i < ls.size(); i++) {
		string item = ls.at(i);
		if (item.compare("pi") == 0 || item.compare("e")==0 || regex_match(item, re) == 1) {
			stack.push(item);
		}else {
			double num1, num2, res = 0;
			if (stack.empty()) {
				errorType = 7;
				return -1;
			}
			string2num(stack.top(), num2);
			stack.pop();
			if (stack.empty()) {
				errorType = 7;
				return -1;
			}
			string2num(stack.top(), num1);
			stack.pop();
			if (item.compare("+")==0) {
				res = num1 + num2;
			}
			if (item.compare("-")==0) {
				res = num1 - num2;
			}
			if (item.compare("*")==0) {
				res = num1 * num2;
			}
			if (item.compare("/")==0) {
				//�������
				if (fabs(num2) <= 1e-10) {
					errorType = 1;
					return -1;
				}
				res = num1 / num2;
			}
			if (item.compare("%") == 0) {
				//�������
				if (num2 - (int)num2 >= 1e-10 || num1 - (int)num1 >= 1e-10 || num1 <0 || num2 <=0) {
					errorType = 2;
					return -1;
				}
				res = (int)num1 % (int)num2;
			}
			if (item.compare("^")==0) {
				res = pow(num1, num2);
			}
			if (item.compare("!")==0) {
				//�������
				if (num1 < 0 || num1 - (int)num1 >= 1e-10) {
					errorType = 3;
					return -1;
				}
				res = FAC(num1);
			}
			if (item.compare("|")==0) {
				//�������
				if (num2 < 0) {
					errorType = 4;
					return -1;
				}
				res = SQRT(num2);
			}
			if (item.compare("sin")==0) {
				res = sin(num2);
			}
			if (item.compare("cos")==0) {
				res = cos(num2);
			}
			if (item.compare("tan")==0) {
				res = tan(num2);
			}
			if (item.compare("asin")==0) {
				//�������
				if (num2 >1 || num2 < -1) {
					errorType = 5;
					return -1;
				}
				res = asin(num2);
			}
			if (item.compare("acos")==0) {
				//�������
				if (num2 > 1 || num2 < -1) {
					errorType = 5;
					return -1;
				}
				res = acos(num2);
			}
			if (item.compare("atan")==0) {
				//�������
				if (num2 > 1 || num2 < -1) {
					errorType = 5;
					return -1;
				}
				res = atan(num2);
			}
			if (item.compare("ln")==0) {
				//�������
				if (num2 < 0) {
					errorType = 6;
					return -1;
				}
				res = log(num2);
			}
			if (item.compare("log")==0) {
				//�������
				if (num2 < 0) {
					errorType = 6;
					return -1;
				}
				res = log10(num2);
			}
			string sres;
			num2string(res, sres);
			stack.push(sres);
		}
	}
	double rres;
	if (stack.empty()) {
		errorType = 7;
		return -1;
	}
	string2num(stack.top(), rres);
	return rres;
}

//������ʽ��ֵ
double PoLandNotionCalX(vector<string> ls, double x) {
	if (errorType == 7) {
		return -1;
	}
	errorType = -1;
	stack<string> stack;
	for (int i = 0; i < ls.size(); i++) {
		string item = ls.at(i);
		if (item.compare("pi") == 0 || item.compare("e") == 0 || regex_match(item, re) == 1||item.compare("x")==0) {
			stack.push(item);
		}
		else {
			double num1, num2, res = 0;
			if (stack.empty()) {
				errorType = 7;
				return -1;
			}
			if (stack.top().compare("x") == 0) {
				num2 = x;
			}
			else {
				string2num(stack.top(), num2);
			}
			stack.pop();
			if (stack.empty()) {
				errorType = 7;
				return -1;
			}
			if (stack.top().compare("x") == 0) {
				num1 = x;
			}
			else {
				string2num(stack.top(), num1);
			}
			stack.pop();

			if (item.compare("+") == 0) {
				res = num1 + num2;
			}
			if (item.compare("-") == 0) {
				res = num1 - num2;
			}
			if (item.compare("*") == 0) {
				res = num1 * num2;
			}
			if (item.compare("/") == 0) {
				//�������
				if (num2 <= 1e-10) {
					errorType = 1;
					return -1;
				}
				res = num1 / num2;
			}
			if (item.compare("%") == 0) {
				//�������
				if (num2 - (int)num2 >= 1e-10 || num1 - (int)num1 >= 1e-10 || num1 < 0 || num2 <= 0) {
					errorType = 2;
					return -1;
				}
				res = (int)num1 % (int)num2;
			}
			if (item.compare("^") == 0) {
				res = pow(num1, num2);
			}
			if (item.compare("!") == 0) {
				//�������
				if (num1 < 0 || num1 - (int)num1 >= 1e-10) {
					errorType = 3;
					return -1;
				}
				res = FAC(num1);
			}
			if (item.compare("|") == 0) {
				//�������
				if (num2 < 0) {
					errorType = 4;
					return -1;
				}
				res = SQRT(num2);
			}
			if (item.compare("sin") == 0) {
				res = sin(num2);
			}
			if (item.compare("cos") == 0) {
				res = cos(num2);
			}
			if (item.compare("tan") == 0) {
				res = tan(num2);
			}
			if (item.compare("asin") == 0) {
				//�������
				if (num2 > 1 || num2 < -1) {
					errorType = 5;
					return -1;
				}
				res = asin(num2);
			}
			if (item.compare("acos") == 0) {
				//�������
				if (num2 > 1 || num2 < -1) {
					errorType = 5;
					return -1;
				}
				res = acos(num2);
			}
			if (item.compare("atan") == 0) {
				//�������
				if (num2 > 1 || num2 < -1) {
					errorType = 5;
					return -1;
				}
				res = atan(num2);
			}
			if (item.compare("ln") == 0) {
				//�������
				if (num2 < 0) {
					errorType = 6;
					return -1;
				}
				res = log(num2);
			}
			if (item.compare("log") == 0) {
				//�������
				if (num2 < 0) {
					errorType = 6;
					return -1;
				}
				res = log10(num2);
			}
			string sres;
			num2string(res, sres);
			stack.push(sres);
		}
	}
	double rres;
	if (stack.empty()) {
		errorType = 7;
		return -1;
	}
	string2num(stack.top(), rres);
	return rres;
}

//����������
double CALCULATOR(string s) {
	vector<string> ls = toInfixExpressionList(s);
	vector<string> lls = parseSuffixExpressionList(ls);
	return PolandNotionCal(lls);
}

//����������ʽ��ֵ
double CALCULATORX(string s, double x) {
	vector<string> ls = toInfixExpressionList(s);
	vector<string> lls = parseSuffixExpressionList(ls);
	return PoLandNotionCalX(lls,x);
}

//��(a,b)�Ļ���
double INTEGRAL(string s, double a, double b) {
	vector<string> ls = toInfixExpressionList(s);
	vector<string> lls = parseSuffixExpressionList(ls);

	
	double ans = 0;
	for (double x = a; x <= b; x += stepi) {
		ans += PoLandNotionCalX(lls, x)*stepi;
	}
	return ans;
}

//��
double DERIVATION(string s, double x) {
	vector<string> ls = toInfixExpressionList(s);
	vector<string> lls = parseSuffixExpressionList(ls);

	double ans = (PoLandNotionCalX(lls, x + stepd) - PoLandNotionCalX(lls, x - stepd)) / (2 * stepd);
	return ans;
}

//������� ֻ����һ���� ������ͼ��ʹ��
double getRoot(vector<string> lls, double a, double b) {
	double mid = (a + b) / 2;

	if (fabs(PoLandNotionCalX(lls, mid)) < esp) {
		return mid;
	}else if (PoLandNotionCalX(lls, mid) * PoLandNotionCalX(lls, a) < 0) {
		return getRoot(lls, a, mid);
	}else {
		return getRoot(lls, mid, b);
	}
}
double ROOT(string s, double a, double b) {
	vector<string> ls = toInfixExpressionList(s);
	vector<string> lls = parseSuffixExpressionList(ls);
	if (PoLandNotionCalX(lls, a) * PoLandNotionCalX(lls, b) > 0) {
		return a-1;
	}
	return getRoot(lls, a, b);
}
