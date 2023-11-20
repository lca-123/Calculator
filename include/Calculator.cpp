#include <graphics.h>
#include <string>
#include "calculatorh.h"
#include<time.h>
using namespace std;

void basicalInit();
void loadPicture(string choice);
void releasePicture();
string mouseJudge(mouse_msg mouseMsg, string choice);
string outterStrJudgeFirst(string str, string outterStr, string beforeStr);
string innerStrJudgeFirst(string str, string innerStr, string beforeStr);
string outterStrJudgeSecond(string str, string outterStr, string beforeStr);
string innerStrJudgeSecond(string str, string innerStr, string beforeStr);
int mainloop();
void string2num(string str, double& num);
void num2string(double num, string& str);

PIMAGE pimg;
string choice = "first";

int main()
{
	basicalInit();
	mainloop();
	releasePicture();
	closegraph();

	return 0;
}

//图像界面的初始化
void basicalInit()
{
	setinitmode(0, 900, 0);
	initgraph(1080, 720, 0);
	setcolor(BLACK);
	setcaption("Wish you a good time with this multifunctional calculator. 191870084    工程管理学院    李畅     191870074    工程管理学院    姜骁睿");
	setfont(70, 0, "Calibri");
	setcolor(BLACK);
	setbkmode(TRANSPARENT);
	loadPicture(choice);
}

//与用户的交互操作
int mainloop()
{
	string outterStr, innerStr, beforeStr, str = " ";
	string resultStr, upperLimStr, lowerLimStr, nowRunningStr = "";
	string stateLimit, innerStr2;

	//打开日志文件
	FILE* fp = fopen("logs\\logs.txt", "a");
	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);

	fprintf(fp, "\n\n%d - %d - %d %d:%d:%d \n",1900+p->tm_year,1+p->tm_mon,p->tm_mday,8+p->tm_hour,p->tm_min,p->tm_sec);
	

	//主循环
	for (; is_run(); delay_fps(60)) {
		mouse_msg mouseMsg = { 0 };
		while (mousemsg()) {
			mouseMsg = getmouse();
		}
		if (mouseMsg.is_left() && mouseMsg.is_down()) {
				beforeStr = str;
				str = mouseJudge(mouseMsg, choice);
				if (str == "first" || str == "second") {
					if (str != choice) {
						releasePicture();
						choice = str;
						innerStr = "";
						outterStr = "";
						resultStr = "";
						upperLimStr = "";
						lowerLimStr = "";
						loadPicture(choice);
					}
				}
				if (choice == "first") {
					setfont(70, 0, "Calibri");
					if (str == "=") {
						releasePicture();
						cleardevice();
						loadPicture(choice);
						if (outterStr == "") {
							outterStr = "";
						}
						else {
							double ans = CALCULATOR(innerStr);
							if (errorTest().compare("RIGHT") != 0) {
								fprintf(fp, "%s,%s\n",innerStr.c_str(),errorTest().c_str());
								outterStr = errorTest();
								innerStr = "";
							}
							else {
								fprintf(fp,"%s,%lf\n", innerStr.c_str(), ans);
								num2string(ans, outterStr);
								num2string(ans, innerStr);
							}
						}
					}
					if (str == "c" || str == "del") {
						releasePicture();
						cleardevice();
						loadPicture(choice);
					}
					innerStr = innerStrJudgeFirst(str, innerStr, beforeStr);
					outterStr = outterStrJudgeFirst(str, outterStr, beforeStr);
					xyprintf(223, 55, "%s", outterStr.c_str());
				}
				else if (choice == "second") {
					setfont(30, 0, "Calibri");
					if (str == "c") {
						releasePicture();
						cleardevice();
						loadPicture(choice);
						nowRunningStr = "";
						resultStr = "";
						upperLimStr = "";
						lowerLimStr = "";
						outterStr = "";
						innerStr = "";
					}
					if (str == "derivation") {
						nowRunningStr = "derivation";
						resultStr = "";
						upperLimStr = "";
						lowerLimStr = "";
						releasePicture();
						cleardevice();
						loadPicture(choice);
						xyprintf(285, 512, "%s", outterStr.c_str());
					}
					if (str == "integration") { 
						nowRunningStr = "integration";
						resultStr = "";
						upperLimStr = "";
						lowerLimStr = "";
						releasePicture();
						cleardevice();
						loadPicture(choice);
						xyprintf(285, 512, "%s", outterStr.c_str());
					}
					if (str == "seeking roots") {
						nowRunningStr = "seeking roots";
						resultStr = "";
						upperLimStr = "";
						lowerLimStr = "";
						releasePicture();
						cleardevice();
						loadPicture(choice);
						xyprintf(285, 512, "%s", outterStr.c_str());
					}
					if (nowRunningStr == "") {
						if (str == "del") {
							releasePicture();
							cleardevice();
							loadPicture(choice);
						}
						innerStr = innerStrJudgeSecond(str, innerStr, beforeStr);
						outterStr = outterStrJudgeSecond(str, outterStr, beforeStr);
						xyprintf(285, 512, "%s", outterStr.c_str());
						if (str == "run") {
							if (innerStr == "") continue;
							else {
								int i1, j1,i,j;
								ege_enable_aa(true);
								double x, y = CALCULATORX(innerStr, -220 / 200.0 * 30), new_y;
								if (errorTest() == "Operator Error") {
									outterStr = errorTest();
									fprintf(fp, "ERROR %s \n", errorTest().c_str());
									xyprintf(320, 580, "%s", outterStr.c_str());
								}
								else {
									for (x = -220; x < 220; x++) {
										new_y = CALCULATORX(innerStr, x / 220 * 30);
										i1 = (int)x;
										j1 = (int)new_y;
										i = (int)(x - 1);
										j = (int)y;
										setlinestyle(0, NULL, 2, NULL);									
										y = new_y;
										if ((240 - j1) < 30 || (240 - j1) > 460) continue;
										else if ((240 - j) < 30 || (240 - j) > 460) continue;
										else {
											line(i + 450, 240 - j, i1 + 450, 240 - j1);
										}
									}

									fprintf(fp, "the founction image of [%s] has been drawn \n",innerStr.c_str());
								}
								
							}
						}
					}
					if (nowRunningStr == "derivation") {
						if (str == "del") {
							releasePicture();
							cleardevice();
							loadPicture(choice);
							xyprintf(285, 512, "%s", outterStr.c_str());
						}
						upperLimStr = outterStrJudgeSecond(str, upperLimStr, beforeStr);
						xyprintf(535, 580, "%s", upperLimStr.c_str());
						if (str == "run") {
							double point;
							string2num(upperLimStr, point);
							double ans = DERIVATION(innerStr, point);
							if (errorTest().compare("RIGHT") != 0) {
								fprintf(fp, "%s,point:%lf,DERIVATION,%s\n", innerStr.c_str(), point, errorTest().c_str());
								outterStr = errorTest();
								innerStr = "";
								xyprintf(320, 580, "%s", outterStr.c_str());
							}
							else {
								fprintf(fp, "%s,point:%lf,DERIVATION,%lf\n", innerStr.c_str(), point, ans);
								num2string(ans, resultStr);
								xyprintf(320, 580, "%s", resultStr.c_str());
							}
						}
					}
					if (nowRunningStr == "integration") {
						if (str == "upperLimit") stateLimit = "upperLimit";
						if (str == "lowerLimit") stateLimit = "lowerLimit";
						if (str == "del") {
							releasePicture();
							cleardevice();
							loadPicture(choice);
							xyprintf(285, 512, "%s", outterStr.c_str());
						}
						if (stateLimit == "upperLimit") {
							upperLimStr = outterStrJudgeSecond(str, upperLimStr, beforeStr);
							xyprintf(535, 580, "%s", upperLimStr.c_str());
						}
						if (stateLimit == "lowerLimit") {
							lowerLimStr = outterStrJudgeSecond(str, lowerLimStr, beforeStr);
							xyprintf(623, 580, "%s", lowerLimStr.c_str());
						}
						if (str == "run") {
							double upperPoint;
							double lowerPoint;
							string2num(upperLimStr, upperPoint);
							string2num(lowerLimStr, lowerPoint);
							double ans = INTEGRAL(innerStr, upperPoint, lowerPoint);
							if (errorTest().compare("RIGHT") != 0) {
								fprintf(fp, "%s,[%lf,%lf],INTEGRAL,%s\n",innerStr.c_str(),upperPoint,lowerPoint,errorTest().c_str());
								outterStr = errorTest();
								innerStr = "";
								xyprintf(320, 580, "%s", outterStr.c_str());
							}
							else {
								int temp;
								temp = (int)(ans * (1000000));
								ans = temp/1000000.0;
								fprintf(fp, "%s,[%lf,%lf],INTEGRAL,%lf\n", innerStr.c_str(), upperPoint, lowerPoint, ans);
								num2string(ans, resultStr);
								xyprintf(320, 580, "%s", resultStr.c_str());
							}
						}
					}
					if (nowRunningStr == "seeking roots") {
						if (str == "upperLimit") stateLimit = "upperLimit";
						if (str == "lowerLimit") stateLimit = "lowerLimit";
						if (str == "del") {
							releasePicture();
							cleardevice();
							loadPicture(choice);
							xyprintf(285, 512, "%s", outterStr.c_str());
						}
						if (stateLimit == "upperLimit") {
							upperLimStr = outterStrJudgeSecond(str, upperLimStr, beforeStr);
							xyprintf(535, 580, "%s", upperLimStr.c_str());
						}
						if (stateLimit == "lowerLimit") {
							lowerLimStr = outterStrJudgeSecond(str, lowerLimStr, beforeStr);
							xyprintf(623, 580, "%s", lowerLimStr.c_str());
						}
						if (str == "run") {
							double upperPoint;
							double lowerPoint;
							string2num(upperLimStr, upperPoint);
							string2num(lowerLimStr, lowerPoint);
							double ans = ROOT(innerStr, upperPoint, lowerPoint);
							if (errorTest().compare("RIGHT") != 0) {
								fprintf(fp, "%s,[%lf,%lf],ROOT,%s\n",innerStr.c_str(),upperPoint,lowerPoint,errorTest().c_str());
								outterStr = errorTest();
								innerStr = "";
								xyprintf(320, 580, "%s", outterStr.c_str());
							}
							else {
								int temp;
								temp = (int)(ans * (1000000));
								ans = temp / 1000000.0;
								fprintf(fp, "%s,[%lf,%lf],ROOT,%lf\n", innerStr.c_str(), upperPoint, lowerPoint, ans);
								num2string(ans, resultStr);
								xyprintf(320, 580, " x = %s", resultStr.c_str());
							}
						}
					}
				}
		}
	}
	fprintf(fp, "\n\n");
	fclose(fp);
	return 0;
}

//判断鼠标点击信息
string mouseJudge(mouse_msg mouseMsg, string choice)
{
	string str;
	if (choice == "first") {
		if (mouseMsg.x >= 210 && mouseMsg.x <= 334 && mouseMsg.y >= 211.9 && mouseMsg.y <= 291.9) {
			str = "("; return str;
		}
		if (mouseMsg.x >= 210 && mouseMsg.x <= 334 && mouseMsg.y >= 292.9 && mouseMsg.y <= 372.9) {
			str = "sin("; return str;
		}
		if (mouseMsg.x >= 210 && mouseMsg.x <= 334 && mouseMsg.y >= 373.9 && mouseMsg.y <= 453.9) {
			str = "cos("; return str;
		}
		if (mouseMsg.x >= 210 && mouseMsg.x <= 334 && mouseMsg.y >= 454.9 && mouseMsg.y <= 534.9) {
			str = "tan("; return str;
		}
		if (mouseMsg.x >= 210 && mouseMsg.x <= 334 && mouseMsg.y >= 536 && mouseMsg.y <= 616) {
			str = "log("; return str;
		}
		if (mouseMsg.x >= 210 && mouseMsg.x <= 334 && mouseMsg.y >= 617 && mouseMsg.y <= 697) {
			str = "^"; return str;
		}
		if (mouseMsg.x >= 355 && mouseMsg.x <= 499 && mouseMsg.y >= 211.9 && mouseMsg.y <= 291.9) {
			str = ")"; return str;
		}
		if (mouseMsg.x >= 355 && mouseMsg.x <= 499 && mouseMsg.y >= 292.9 && mouseMsg.y <= 372.9) {
			str = "asin("; return str;
		}
		if (mouseMsg.x >= 355 && mouseMsg.x <= 499 && mouseMsg.y >= 373.9 && mouseMsg.y <= 453.9) {
			str = "acos("; return str;
		}
		if (mouseMsg.x >= 355 && mouseMsg.x <= 499 && mouseMsg.y >= 454.9 && mouseMsg.y <= 534.9) {
			str = "atan("; return str;
		}
		if (mouseMsg.x >= 355 && mouseMsg.x <= 499 && mouseMsg.y >= 536 && mouseMsg.y <= 616) {
			str = "ln("; return str;
		}
		if (mouseMsg.x >= 355 && mouseMsg.x <= 499 && mouseMsg.y >= 617 && mouseMsg.y <= 697) {
			str = "!"; return str;
		}
		if (mouseMsg.x >= 500 && mouseMsg.x <= 644 && mouseMsg.y >= 211.9 && mouseMsg.y <= 291.9) {
			str = "c"; return str;
		}
		if (mouseMsg.x >= 500 && mouseMsg.x <= 644 && mouseMsg.y >= 292.9 && mouseMsg.y <= 372.9) {
			str = "÷"; return str;
		}
		if (mouseMsg.x >= 500 && mouseMsg.x <= 644 && mouseMsg.y >= 373.9 && mouseMsg.y <= 453.9) {
			str = "1"; return str;
		}
		if (mouseMsg.x >= 500 && mouseMsg.x <= 644 && mouseMsg.y >= 454.9 && mouseMsg.y <= 534.9) {
			str = "4"; return str;
		}
		if (mouseMsg.x >= 500 && mouseMsg.x <= 644 && mouseMsg.y >= 536 && mouseMsg.y <= 616) {
			str = "7"; return str;
		}
		if (mouseMsg.x >= 500 && mouseMsg.x <= 644 && mouseMsg.y >= 617 && mouseMsg.y <= 697) {
			str = "00"; return str;
		}
		if (mouseMsg.x >= 645 && mouseMsg.x <= 789 && mouseMsg.y >= 211.9 && mouseMsg.y <= 291.9) {
			str = "%"; return str;
		}
		if (mouseMsg.x >= 645 && mouseMsg.x <= 789 && mouseMsg.y >= 292.9 && mouseMsg.y <= 372.9) {
			str = "-"; return str;
		}
		if (mouseMsg.x >= 645 && mouseMsg.x <= 789 && mouseMsg.y >= 373.9 && mouseMsg.y <= 453.9) {
			str = "2"; return str;
		}
		if (mouseMsg.x >= 645 && mouseMsg.x <= 789 && mouseMsg.y >= 454.9 && mouseMsg.y <= 534.9) {
			str = "5"; return str;
		}
		if (mouseMsg.x >= 645 && mouseMsg.x <= 789 && mouseMsg.y >= 536 && mouseMsg.y <= 616) {
			str = "8"; return str;
		}
		if (mouseMsg.x >= 645 && mouseMsg.x <= 789 && mouseMsg.y >= 617 && mouseMsg.y <= 697) {
			str = "0"; return str;
		}
		if (mouseMsg.x >= 790 && mouseMsg.x <= 934 && mouseMsg.y >= 211.9 && mouseMsg.y <= 291.9) {
			str = "√"; return str;
		}
		if (mouseMsg.x >= 790 && mouseMsg.x <= 934 && mouseMsg.y >= 292.9 && mouseMsg.y <= 372.9) {
			str = "+"; return str;
		}
		if (mouseMsg.x >= 790 && mouseMsg.x <= 934 && mouseMsg.y >= 373.9 && mouseMsg.y <= 453.9) {
			str = "3"; return str;
		}
		if (mouseMsg.x >= 790 && mouseMsg.x <= 934 && mouseMsg.y >= 454.9 && mouseMsg.y <= 534.9) {
			str = "6"; return str;
		}
		if (mouseMsg.x >= 790 && mouseMsg.x <= 934 && mouseMsg.y >= 536 && mouseMsg.y <= 616) {
			str = "9"; return str;
		}
		if (mouseMsg.x >= 790 && mouseMsg.x <= 934 && mouseMsg.y >= 617 && mouseMsg.y <= 697) {
			str = "."; return str;
		}
		if (mouseMsg.x >= 935 && mouseMsg.x <= 1079 && mouseMsg.y >= 211.9 && mouseMsg.y <= 291.9) {
			str = "del"; return str;
		}
		if (mouseMsg.x >= 935 && mouseMsg.x <= 1079 && mouseMsg.y >= 292.9 && mouseMsg.y <= 372.9) {
			str = "×"; return str;
		}
		if (mouseMsg.x >= 935 && mouseMsg.x <= 1079 && mouseMsg.y >= 373.9 && mouseMsg.y <= 453.9) {
			str = "pi"; return str;
		}
		if (mouseMsg.x >= 935 && mouseMsg.x <= 1079 && mouseMsg.y >= 454.9 && mouseMsg.y <= 534.9) {
			str = "e"; return str;
		}
		if (mouseMsg.x >= 935 && mouseMsg.x <= 1079 && mouseMsg.y >= 536 && mouseMsg.y <= 697) {
			str = "="; return str;
		}
		if (mouseMsg.x >= 0 && mouseMsg.x <= 209 && mouseMsg.y >= 11 && mouseMsg.y <= 61) {
			return "first";
		}
		if (mouseMsg.x >= 0 && mouseMsg.x <= 209 && mouseMsg.y >= 64 && mouseMsg.y <= 114) {
			return "second";
		}
	}
	else if (choice == "second") {
		if (mouseMsg.x >= 694 && mouseMsg.x <= 822 && mouseMsg.y >= 9 && mouseMsg.y <= 77.1) {
			return "sin(";
		}
		if (mouseMsg.x >= 823 && mouseMsg.x <= 951 && mouseMsg.y >= 9 && mouseMsg.y <= 77.1) {
			return "cos(";
		}
		if (mouseMsg.x >= 952 && mouseMsg.x <= 1080 && mouseMsg.y >= 9 && mouseMsg.y <= 77.1) {
			return "tan(";
		}
		if (mouseMsg.x >= 694 && mouseMsg.x <= 822 && mouseMsg.y >= 78 && mouseMsg.y <= 146.2) {
			return "log(";
		}
		if (mouseMsg.x >= 823 && mouseMsg.x <= 951 && mouseMsg.y >= 78 && mouseMsg.y <= 146.2) {
			return "ln(";
		}
		if (mouseMsg.x >= 952 && mouseMsg.x <= 1080 && mouseMsg.y >= 78 && mouseMsg.y <= 146.2) {
			return "arc";
		}
		if (mouseMsg.x >= 694 && mouseMsg.x <= 822 && mouseMsg.y >= 147.1 && mouseMsg.y <= 215.3) {
			return "(";
		}
		if (mouseMsg.x >= 823 && mouseMsg.x <= 951 && mouseMsg.y >= 147.1 && mouseMsg.y <= 215.3) {
			return ")";
		}
		if (mouseMsg.x >= 952 && mouseMsg.x <= 1080 && mouseMsg.y >= 147.1 && mouseMsg.y <= 215.3) {
			return "^";
		}
		if (mouseMsg.x >= 694 && mouseMsg.x <= 822 && mouseMsg.y >= 216.29 && mouseMsg.y <= 284.4) {
			return "c";
		}
		if (mouseMsg.x >= 823 && mouseMsg.x <= 951 && mouseMsg.y >= 216.29 && mouseMsg.y <= 284.4) {
			return "x";
		}
		if (mouseMsg.x >= 952 && mouseMsg.x <= 1080 && mouseMsg.y >= 216.29 && mouseMsg.y <= 284.4) {
			return "del";
		}
		if (mouseMsg.x >= 694 && mouseMsg.x <= 822 && mouseMsg.y >= 285.39 && mouseMsg.y <= 353.5) {
			return "+";
		}
		if (mouseMsg.x >= 823 && mouseMsg.x <= 951 && mouseMsg.y >= 285.39 && mouseMsg.y <= 353.5) {
			return "×";
		}
		if (mouseMsg.x >= 952 && mouseMsg.x <= 1080 && mouseMsg.y >= 285.39 && mouseMsg.y <= 353.5) {
			return "÷";
		}
		if (mouseMsg.x >= 694 && mouseMsg.x <= 822 && mouseMsg.y >= 354.49 && mouseMsg.y <= 422.6) {
			return "-";
		}
		if (mouseMsg.x >= 823 && mouseMsg.x <= 951 && mouseMsg.y >= 354.49 && mouseMsg.y <= 422.6) {
			return "e";
		}
		if (mouseMsg.x >= 952 && mouseMsg.x <= 1080 && mouseMsg.y >= 354.49 && mouseMsg.y <= 422.6) {
			return "pi";
		}
		if (mouseMsg.x >= 694 && mouseMsg.x <= 822 && mouseMsg.y >= 423.59 && mouseMsg.y <= 491.7) {
			return "1";
		}
		if (mouseMsg.x >= 823 && mouseMsg.x <= 951 && mouseMsg.y >= 423.59 && mouseMsg.y <= 491.7) {
			return "2";
		}
		if (mouseMsg.x >= 952 && mouseMsg.x <= 1080 && mouseMsg.y >= 423.59 && mouseMsg.y <= 491.7) {
			return "3";
		}
		if (mouseMsg.x >= 694 && mouseMsg.x <= 822 && mouseMsg.y >= 492.69 && mouseMsg.y <= 560.8) {
			return "4";
		}
		if (mouseMsg.x >= 823 && mouseMsg.x <= 951 && mouseMsg.y >= 492.69 && mouseMsg.y <= 560.8) {
			return "5";
		}
		if (mouseMsg.x >= 952 && mouseMsg.x <= 1080 && mouseMsg.y >= 492.69 && mouseMsg.y <= 560.8) {
			return "6";
		}
		if (mouseMsg.x >= 694 && mouseMsg.x <= 822 && mouseMsg.y >= 561.78 && mouseMsg.y <= 629.89) {
			return "7";
		}
		if (mouseMsg.x >= 823 && mouseMsg.x <= 951 && mouseMsg.y >= 561.78 && mouseMsg.y <= 629.89) {
			return "8";
		}
		if (mouseMsg.x >= 952 && mouseMsg.x <= 1080 && mouseMsg.y >= 561.78 && mouseMsg.y <= 629.89) {
			return "9";
		}
		if (mouseMsg.x >= 694 && mouseMsg.x <= 822 && mouseMsg.y >= 630.88 && mouseMsg.y <= 698.99) {
			return ".";
		}
		if (mouseMsg.x >= 823 && mouseMsg.x <= 951 && mouseMsg.y >= 630.88 && mouseMsg.y <= 698.99) {
			return "0";
		}
		if (mouseMsg.x >= 952 && mouseMsg.x <= 1080 && mouseMsg.y >= 630.88 && mouseMsg.y <= 698.99) {
			return "run";
		}
		if (mouseMsg.x >= 211 && mouseMsg.x <= 371 && mouseMsg.y >= 630.88 && mouseMsg.y <= 698.99) {
			return "derivation";
		}
		if (mouseMsg.x >= 372 && mouseMsg.x <= 532 && mouseMsg.y >= 630.88 && mouseMsg.y <= 698.99) {
			return "integration";
		}
		if (mouseMsg.x >= 533 && mouseMsg.x <= 612.5 && mouseMsg.y >= 561.78 && mouseMsg.y <= 629.89) {
			return "upperLimit";
		}
		if (mouseMsg.x >= 613.5 && mouseMsg.x <= 692.5 && mouseMsg.y >= 561.78 && mouseMsg.y <= 629.89) {
			return "lowerLimit";
		}
		if (mouseMsg.x >= 533 && mouseMsg.x <= 693 && mouseMsg.y >= 630.88 && mouseMsg.y <= 698.99) {
			return "seeking roots";
		}
		if (mouseMsg.x >= 0 && mouseMsg.x <= 209 && mouseMsg.y >= 11 && mouseMsg.y <= 61) {
			return "first";
		}
		if (mouseMsg.x >= 0 && mouseMsg.x <= 209 && mouseMsg.y >= 64 && mouseMsg.y <= 114) {
			return "second";
		}
	}
	return "";
}

//多功能计算器中屏幕显示字符串的操作
string outterStrJudgeFirst(string str, string outterStr, string beforeStr) {
	if (str == "first" || str == "second") str = "";
	else if (str == "=") str = "";
	else if (str == "c") {
		outterStr = "";
		return outterStr;
	}
	else if (str == "del") {
		if (outterStr.length() == 0) outterStr = "";
		else {
			int length = outterStr.length();
			if (length != 1) {
				if (beforeStr == "√" || beforeStr == "×" || beforeStr == "÷" ) {
					outterStr.erase(length - 2, length);
				}
				else {
					outterStr.erase(length - 1, length);
				}
			}
			else outterStr = "";
		}
		return outterStr;
	}
	outterStr = outterStr + str;
	return outterStr;
}

//多功能计算器中内部字符串的操作
string innerStrJudgeFirst(string str, string innerStr, string beforeStr) {
	if (str == "first" || str == "second") str = "";
	else if (str == "=") str = "";
	else if (str == "c") {
		innerStr = "";
		return innerStr;
	}
	else if (str == "del") {
		if (innerStr.length() == 0) innerStr = "";
		else {
			int length = innerStr.length();
			if (length != 1) {
				innerStr.erase(length - 1, length);
			}
			else innerStr = "";
		}
		return innerStr;
	}
	else if (str == "√") str = "|";
	else if (str == "÷") str = "/";
	else if (str == "×") str = "*";
	innerStr = innerStr + str;
	return innerStr;
}

//函数计算器中屏幕显示字符串的操作
string outterStrJudgeSecond(string str, string outterStr, string beforeStr) {
	if (str == "first" || str == "second") str = "";
	else if (str == "run" || str == "derivation" || str == "integration" || str == "seeking roots" || str == "upperLimit" || str == "lowerLimit") str = "";
	else if (str == "c") {
		outterStr = "";
		return outterStr;
	}
	else if (str == "del") {
		if (outterStr.length() == 0) outterStr = "";
		else {
			int length = outterStr.length();
			if (length != 1) {
				if (beforeStr == "√" || beforeStr == "×" || beforeStr == "÷") {
					outterStr.erase(length - 2, length);
				}
				else {
					outterStr.erase(length - 1, length);
				}
			}
			else outterStr = "";
		}
		return outterStr;
	}
	outterStr = outterStr + str;
	return outterStr;
}

//函数计算器中内部字符串的操作
string innerStrJudgeSecond(string str, string innerStr, string beforeStr) {
	if (str == "first" || str == "second") str = "";
	else if (str == "run" || str == "derivation" || str == "integration" || str == "seeking roots" || str == "upperLimit" || str == "lowerLimit") str = "";
	else if (str == "c") {
		innerStr = "";
		return innerStr;
	}
	else if (str == "del") {
		if (innerStr.length() == 0) innerStr = "";
		else {
			int length = innerStr.length();
			if (length != 1) {
				innerStr.erase(length - 1, length);
			}
			else innerStr = "";
		}
		return innerStr;
	}
	else if (str == "√") str = "|";
	else if (str == "÷") str = "/";
	else if (str == "×") str = "*";
	else if (str == "arc") str = "a";
	innerStr = innerStr + str;
	return innerStr;
}

//图片的载入和粘贴
void loadPicture(string choice)
{
	pimg = newimage();
	if(choice == "first") getimage(pimg, "\\Picture\\Calc plus.jpg");
	else if(choice == "second") getimage(pimg, "\\Picture\\Scientific calculator.jpg");
	putimage(0, 0, pimg);
}

//图片的释放和移除
void releasePicture()
{
	delimage(pimg);
}