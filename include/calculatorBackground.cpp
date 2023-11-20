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
//错误类型
//1. 除数为0
//2.取模的两个操作数不是整数
//3.阶乘不是正整数
//4.开根为负数
//6.取对数不能为负数
//5.反三角函数定义域
//7.操作符有误
*/
string errorTest() {
	if (errorType == 1) {
		return "Zero divisor！";
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

//阶乘
double FAC(double num) {
	if (num < 0) {
		printf("负数不能阶乘");
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
		printf("小数不能阶乘");
		exit(0);
	}
	return 0;
}

//开根号
double SQRT(double num) {
	if (num < 0) {
		printf("负数不能开跟");
		exit(0);
	}
	else {
		return sqrt(num);
	}
	return 0;
}

//字符串转double
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

//double转字符串
void num2string(double num, string& str) {
	stringstream ss;
	ss << num;
	str = ss.str();
}

//返回操作符的优先级 
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

//中缀表达式转集合
vector<string> toInfixExpressionList(string s) {
	vector<string> ls;
	const char* c = s.c_str();//字符串转为字符数组 
	int i = 0;//遍历字符数组	
	do {
		if ((c[i] >= '0' && c[i] <= '9') || c[i] == '.') {
			//处理数字
			char str[100];//用于字符串拼接
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
			//处理操作符和特殊数字e pi 
			if (c[i] == ' ' || c[i] == '\n' || c[i] == '\t') {//处理冗余符号 
				i++;
			}
			else
				if (c[i] == 'p' && c[i + 1] == 'i') {//处理pi 
					ls.push_back("pi");
					i += 2;
				}
				else
					if (c[i] == '!') {//处理阶乘 
						ls.push_back("!");
						ls.push_back("0");
						i++;
					}
					else
						if (c[i] == '|') {//处理开跟 
							ls.push_back("0");
							ls.push_back("|");
							i++;
						}
						else
							if (c[i] == '-') {//处理负数 
								if (i == 0 || c[i - 1] == '(') {//真负数 
									char str[100] = "-";//用于字符串拼接
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
								else {//假负数，普通减号 
									ls.push_back("-");
									i++;
								}
							}
							else
								if (c[i] == 's' || c[i] == 'c' || c[i] == 't' || c[i] == 'a') {//处理三角函数 
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
									if (c[i] == 'l') {//处理对数 
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

//中缀表达式转后缀表达式
vector<string> parseSuffixExpressionList(vector<string> ls) {
	errorType = -1;
	//定义栈 因为s2在整个过程中没有pop操作且最后需要逆序输出 比较麻烦 因此用vector代替它
	stack<string> s1;
	vector<string> s2;
	//遍历ls
	for (int i = 0; i < ls.size(); i++) {
		string item = ls.at(i);
		//如果是一个数，则加入s2
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

//逆波兰表达式计算
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
				//错误检验
				if (fabs(num2) <= 1e-10) {
					errorType = 1;
					return -1;
				}
				res = num1 / num2;
			}
			if (item.compare("%") == 0) {
				//错误检验
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
				//错误检验
				if (num1 < 0 || num1 - (int)num1 >= 1e-10) {
					errorType = 3;
					return -1;
				}
				res = FAC(num1);
			}
			if (item.compare("|")==0) {
				//错误检验
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
				//错误检验
				if (num2 >1 || num2 < -1) {
					errorType = 5;
					return -1;
				}
				res = asin(num2);
			}
			if (item.compare("acos")==0) {
				//错误检验
				if (num2 > 1 || num2 < -1) {
					errorType = 5;
					return -1;
				}
				res = acos(num2);
			}
			if (item.compare("atan")==0) {
				//错误检验
				if (num2 > 1 || num2 < -1) {
					errorType = 5;
					return -1;
				}
				res = atan(num2);
			}
			if (item.compare("ln")==0) {
				//错误检验
				if (num2 < 0) {
					errorType = 6;
					return -1;
				}
				res = log(num2);
			}
			if (item.compare("log")==0) {
				//错误检验
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

//计算表达式的值
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
				//错误检验
				if (num2 <= 1e-10) {
					errorType = 1;
					return -1;
				}
				res = num1 / num2;
			}
			if (item.compare("%") == 0) {
				//错误检验
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
				//错误检验
				if (num1 < 0 || num1 - (int)num1 >= 1e-10) {
					errorType = 3;
					return -1;
				}
				res = FAC(num1);
			}
			if (item.compare("|") == 0) {
				//错误检验
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
				//错误检验
				if (num2 > 1 || num2 < -1) {
					errorType = 5;
					return -1;
				}
				res = asin(num2);
			}
			if (item.compare("acos") == 0) {
				//错误检验
				if (num2 > 1 || num2 < -1) {
					errorType = 5;
					return -1;
				}
				res = acos(num2);
			}
			if (item.compare("atan") == 0) {
				//错误检验
				if (num2 > 1 || num2 < -1) {
					errorType = 5;
					return -1;
				}
				res = atan(num2);
			}
			if (item.compare("ln") == 0) {
				//错误检验
				if (num2 < 0) {
					errorType = 6;
					return -1;
				}
				res = log(num2);
			}
			if (item.compare("log") == 0) {
				//错误检验
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

//完整计算器
double CALCULATOR(string s) {
	vector<string> ls = toInfixExpressionList(s);
	vector<string> lls = parseSuffixExpressionList(ls);
	return PolandNotionCal(lls);
}

//完整计算表达式的值
double CALCULATORX(string s, double x) {
	vector<string> ls = toInfixExpressionList(s);
	vector<string> lls = parseSuffixExpressionList(ls);
	return PoLandNotionCalX(lls,x);
}

//求(a,b)的积分
double INTEGRAL(string s, double a, double b) {
	vector<string> ls = toInfixExpressionList(s);
	vector<string> lls = parseSuffixExpressionList(ls);

	
	double ans = 0;
	for (double x = a; x <= b; x += stepi) {
		ans += PoLandNotionCalX(lls, x)*stepi;
	}
	return ans;
}

//求导
double DERIVATION(string s, double x) {
	vector<string> ls = toInfixExpressionList(s);
	vector<string> lls = parseSuffixExpressionList(ls);

	double ans = (PoLandNotionCalX(lls, x + stepd) - PoLandNotionCalX(lls, x - stepd)) / (2 * stepd);
	return ans;
}

//方程求根 只能求一个根 因此配合图像使用
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
