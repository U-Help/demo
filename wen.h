#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<stack>
#include<map>
#include<math.h>
#include <string>

#ifndef WEN_H
#define WEN_H

using namespace std;

typedef struct fenshu {
    int fenzi;
    int fenmu;
}fenshu;

typedef struct fanhui {
    string express;
    string result;
}fanhui;

typedef struct canshu {
    string num_ques;
    string scalemax_op;
    string scalemin_op;
    string num_op;
    string num_float;
    string is_real;
    string is_decimal;
    string is_power;
    string is_add;
    string is_sub;
    string is_mul;
    string is_div;
    string result_max;
    string result_min;
}canshu;

char randsign();
int jiexi(string can);
int JudgePrior(char operation);
bool Judgeoperation(char operation);
void AddBracket(string &exp);
void ExpTranslate(string Suffix_exp,string result);
int Operate(char op, int num1, int &num2);
string translate(int num);
int Generate_int();
double Operate_float(char op, double num1, double num2);
string translate_float(double num);
int Generate_float();
int GreatCommon(int fenzi, int fenmu);
void Simplify(fenshu &sample);
fenshu Add(fenshu a1, fenshu a2);
fenshu Sub(fenshu a1, fenshu a2);
fenshu chen(fenshu a1, fenshu a2);
fenshu chu(fenshu a1, fenshu a2);
fenshu Operate_fenshu(char op, fenshu num1, fenshu &num2);
 string translate_fenshu(fenshu sample);
 int Generate_fenshu();
 int Setting(void);


#endif // WEN_H
