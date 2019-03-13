#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<stack>
#include<map>
#include<math.h>
#include <string>

#ifndef SIZEYUNSUAN_H
#define SIZEYUNSUAN_H

using namespace std;

int JudgePrior(char operation);
bool Judgeoperation(char operation);
void AddBracket(string &exp);
void ExpTranslate(string Suffix_exp);
int Setting();
int Operate(char op, int num1, int num2);
string translate(int num);
string translate_float(float num);
int Generate();
void hehe();

#endif // SIZEYUNSUAN_H
