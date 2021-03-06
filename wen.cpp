
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<stack>
#include<map>
#include<math.h>
#include <QDebug>



using namespace std;

typedef struct ExpDetail {
	string expression;
	int prior;
}MyExp;

typedef struct fenshu {
	int fenzi;
	int fenmu;
}fenshu;

typedef struct fanhui {
	string express;
	string result;
}fanhui;

fanhui expResult[10000];
int resu = 0;

#define eq ==
#define maxlen 8

map<string, int> mapException;
int num_ques = 0;
int scalemax_op = 10;
int scalemin_op = 0;
int num_op = 5;
int num_float = 0;
bool is_real = 0;
bool is_decimal = 0;
bool is_power = 0;
int result_max=100;
int result_min;
int is_add = 1;
int is_sub = 1;
int is_mul = 1;
int is_div = 1;

typedef struct canshu {
	string num_ques;
	string scalemax_op;
	string num_op;
	string num_float;
    string is_real;//分数
    string is_decimal;//小数
    string is_power;//乘方
	string is_add;
	string is_sub;
	string is_mul;
	string is_div;
	string result_max;
	string result_min;
}canshu;

canshu sample;

char randsign();

int jiexi(string can)
{
    int a[maxlen],i,result=0,shi=1;
    for (i = 0; i < can.length(); i++)
    {
        if (can[i] >= '0'&&can[i] <= '9') a[i] = can[i] - '0';
        else break;
    }
    if (can[i] != ' ') return -1;
    else
    {
        if (can[i + 1] == '\0')
        {
            i--;
            while (i >= 0)
            {
                result += shi * a[i];
                shi *= 10;
                i--;
            }
            return result;
        }
        else return -1;
    }
}

int JudgePrior(char operation)
{
	switch (operation)
	{
	case '+': return 0;
	case '-': return 0;
    case '*': return 1;
	case '/': return 1;
	case '^': return 2;
	default:
		break;
	}
}

bool Judgeoperation(char operation)
{
	if ((operation >= '0') && (operation <= '9'))
	{
		return false;
	}
	else
	{
		return true;
	}
}

void AddBracket(string &exp)
{
	int length = size(exp);
	string real_exp;
	real_exp = "(" + exp + ")";
	exp = real_exp;
}

void ExpTranslate(string Suffix_exp,string result)
{
	stack<MyExp> exp_stk;
	MyExp number_exp;
	int Const_number = 5;
	number_exp.expression = "";
	number_exp.prior = Const_number;
	MyExp oper_first,oper_second,oper_finally;
	int prior;
	int length = size(Suffix_exp);
	for (int i = 0; i < length; i++)
	{
		if (Suffix_exp.at(i) != ' ')
		{
			number_exp.expression += Suffix_exp.at(i);
		}
		else
		{
			if (size(number_exp.expression) == 1)
			{
				if (Judgeoperation(number_exp.expression.at(0)))
				{
					prior = JudgePrior(number_exp.expression.at(0));
					oper_first = exp_stk.top();
					exp_stk.pop();
					oper_second = exp_stk.top();
					exp_stk.pop();
					if (oper_first.prior < prior)
					{
						AddBracket(oper_first.expression);
					}
					if (oper_second.prior < prior)
					{
						AddBracket(oper_second.expression);
					}
					oper_finally.expression = oper_second.expression + number_exp.expression.at(0) + oper_first.expression;
					oper_finally.prior = prior;
					exp_stk.push(oper_finally);
					number_exp.expression = "";
					number_exp.prior = Const_number;
				}
				else
				{
					exp_stk.push(number_exp);
					number_exp.expression = "";
					number_exp.prior = Const_number;
				}
			}
			else
			{
				exp_stk.push(number_exp);
				number_exp.expression = "";
				number_exp.prior = Const_number;
			}
		}
	}
	oper_finally = exp_stk.top();
	exp_stk.pop();
	expResult[resu].express = oper_finally.expression;
	expResult[resu].result = result;
	resu++;
} 

int Operate(char op, int num1, int &num2)   
{
	int result = 1;
	int m;
	int fang = rand()%5;
	num2 = fang;
	switch (op)
	{
	case '+': return num1 + num2;
	case '-':
		if (num1 == 0) num2 = 0;
		else
		{
			m = (num1 > scalemax_op) ? scalemax_op : num1;
			num2 = (int)scalemin_op + rand() % (m + scalemin_op);
		}
		return num1 - num2;
	case '*': return num1 * num2;
	case '/':
		if (num2 eq 0) return -2;
		else if (num1 % num2 != 0) return -3;
		else return num1 / num2;
	case '^':
		for (int i = 0; i < num2; i++)
		{
			result *= num1;
		}
		return result;
	}
}   

string translate(int num)
{
	int j = 1;
	string str = "";
	if (num eq 0)
	{
		str = str + '0';
		return str;
	}
	char tem;
	while (num / j != 0)
	{
		j *= 10;
	}
	j /= 10;
	while (j != 1)
	{
		tem = '0' + num / j;
		str = str + tem;
		num = num % j;
		j /= 10;
	}
	tem = '0' + num;
	str = str + tem;
	return str;
}

int Generate_int()
{
	srand((unsigned)time(NULL));
	map<string, int>::iterator iter;
	string op = "";
	string str1 = "", str2 = "";
	char sign;
	int i = 1, j = 0, temp, num1, num2, flag, result;
	stack<int> num;
	/*int number, numop,flagn;
	for (j = 0; j < num_ques; j++) {
	op = "";

	numop = 0;
	num1 = (int)scalemin_op + rand() % (scalemax_op + scalemin_op - 1);
	num2 = (int)scalemin_op + rand() % (scalemax_op + scalemin_op - 1);
	number = 2;
	num.push(num1);
	num.push(num2);
	str1 = translate(num1);
	str2 = translate(num2);
	op = op + str1 + " " + str2 + " ";
	while (number <= num_op)
	{
	if (number > numop+1)
	{
	flagn = rand() % 2;
	if (flagn eq 0)
	{
	temp = rand() % (7);
	switch (temp)
	{
	case 0: sign = '+'; break;
	case 1: sign = '-'; break;
	case 2: sign = '/'; break;
	case 3: sign = '*'; break;
	case 4: sign = '+'; break;
	case 5: sign = '-'; break;
	case 6: sign = '^'; break;
	}
	num2 = num.top();
	num.pop();
	num1 = num.top();
	num.pop();
	flag = Operate(sign, num1, num2);
	while (flag eq - 1 || flag eq - 2 || flag eq - 3 || flag eq - 4)
	{
	num2 = (int)scalemin_op + rand() % (scalemax_op + scalemin_op + 1);
	flag = Operate(sign, num1, num2);
	}
	num.push(flag);
	numop++;
	op = op + sign + " ";
	}
	else
	{
	num2 = (int)scalemin_op + rand() % (scalemax_op + scalemin_op + 1);
	num.push(num2);
	str2 = translate(num2);
	op = op + str2 + " ";
	number++;
	}
	}
	else
	{
	num2 = (int)scalemin_op + rand() % (scalemax_op + scalemin_op + 1);
	num.push(num2);
	str2 = translate(num2);
	op = op + str2 + " ";
	number++;
	}
	}
	while (numop < num_op)
	{
	temp = rand() % (7);
	switch (temp)
	{
	case 0: sign = '+'; break;
	case 1: sign = '-'; break;
	case 2: sign = '/'; break;
	case 3: sign = '*'; break;
	case 4: sign = '+'; break;
	case 5: sign = '-'; break;
	case 6: sign = '^'; break;
	}
	num2 = num.top();
	num.pop();
	num1 = num.top();
	num.pop();
	flag = Operate(sign, num1, num2);
	while (flag eq - 1 || flag eq - 2 || flag eq - 3 || flag eq - 4)
	{
	num2 = (int)scalemin_op + rand() % (scalemax_op + scalemin_op + 1);
	flag = Operate(sign, num1, num2);
	}
	num.push(flag);
	numop++;
	op = op + sign + " ";
	}
	result = num.top();
	op = op + ' ';
	if (result > result_max || result < result_min)
	{
	j--;
	continue;
	}

	iter = mapException.find(op);
	if (iter != mapException.end())
	{
	j--;
	}
	else
	{
	mapException.insert(pair<string, int>(op, result));
	}
	num.pop();
	printf("\n\n");
	ExpTranslate(op);
	printf("%d\n\n", result);
	}*/

	for (j = 0; j < num_ques; j++) {
		op = "";
		for (i = 1; i < num_op; i++)
		{
			sign = randsign();
			num1 = (int)scalemin_op + rand() % (scalemax_op + scalemin_op - 1);
			num2 = (int)scalemin_op + rand() % (scalemax_op + scalemin_op - 1);
			if (i != 1)
			{
				num1 = num.top();
				num.pop();
			}

			flag = Operate(sign, num1, num2);
			while (flag eq - 1 || flag eq - 2 ||flag eq -3||flag eq -4)
			{
				num2 = (int)scalemin_op + rand() % (scalemax_op + scalemin_op - 1);
				flag = Operate(sign, num1, num2);
			}
			num.push(flag);

			if (i eq 1)
			{
				str1 = translate(num1);
				str2 = translate(num2);
				op = op + str1 + " " + str2 + " " + sign;
			}
			else
			{
				str2 = translate(num2);
				op = op + " " + str2 + " " + sign;
			}
		}
		result = num.top();
		op = op + ' ';
		if (result > result_max|| result < result_min)
		{
			j--;
			continue;
		}

		iter = mapException.find(op);
		if (iter != mapException.end())
		{
			j--;
		}
		else
		{
			mapException.insert(pair<string, int>(op, result));
		}
		num.pop();
		string result_str;
		result_str = translate(result);
		ExpTranslate(op,result_str);

	}
	return 0;
}

double Operate_float(char op, double num1, double num2)
{
	switch (op)
	{
	case '+': return num1 + num2;
	case '-':
		if (num1 - num2 < 0)return -1;
		return num1 - num2;
	case '*': return num1 * num2;
	case '/':
		if (fabs(num2)<1e-6) return -1;
        return num1 / num2;
	}
}

string translate_float(double num)
{
	int int_part = 0;
	string int_str, float_str;
	num = num * pow(10.0, num_float);
	num = (int)(num + 0.5);
	num = num / pow(10, num_float);
	int_part = (int)num;
	int_str = translate(int_part);
	num = num - int_part;
	float_str = "";
	for (int i = 1; i <= num_float; i++)
	{
		num = num * 10;
		float_str += translate(int(num) % 10);
	}
	return int_str + "." + float_str;
}

int Generate_float()
{
	srand((unsigned)time(NULL));
	map<string, int>::iterator iter;
	string op = "";
	string str1 = "", str2 = "";
	char sign;
	int i = 1, j = 0, temp;
	double num1, num2;
	double result, flag;
	stack<float> num;

	for (j = 0; j < num_ques; j++) {
		op = "";
		for (i = 1; i < num_op; i++)
		{
			sign = randsign();

			int jin = 1;
			for (size_t jingdu = 0; jingdu < num_float; jingdu++)
			{
				jin *= 10;
			}

			num1 = (double)scalemin_op + rand() % (scalemax_op + scalemin_op - 1)+ ((double)(rand() % (jin)) / jin);
			num2 = (double)scalemin_op + rand() % (scalemax_op + scalemin_op - 1)+ ((double)(rand() % (jin)) / jin);
			if (i != 1)
			{
				num1 = num.top();
				num.pop();
			}
			
			int fang;
			if(sign eq '^')
			{
				flag = 1;
				fang = rand() % 5;
				for (int k = 0; k < fang; k++)
				{
					flag *= num1;
				}
			}
			else flag = Operate_float(sign, num1, num2);

			while (fabs(flag + 1)<1e-5 || fabs(flag + 2)<1e-5)
			{
				num2 = (double)scalemin_op + rand() % (scalemax_op + scalemin_op - 1)+((double)(rand() % (jin)) / jin);
				flag = Operate_float(sign, num1, num2);
			}
			num.push(flag);

			if (i eq 1)
			{
				str1 = translate_float(num1);
				if(sign != '^') str2 = translate_float(num2);
				else str2 = translate(fang);
				op = op + str1 + " " + str2 + " " + sign;
			}
			else
			{
				if (sign != '^') str2 = translate_float(num2);
				else str2 = translate(fang);
				op = op + " " + str2 + " " + sign;
			}
		}
		op = op + ' ';
		result = num.top();
		if (result - result_max > 0|| result - result_min < 0)
		{
			j--;
			continue;
		}

		iter = mapException.find(op);
		if (iter != mapException.end())
		{
		j--;
		}
		else
		{
		mapException.insert(pair<string, int>(op, result));
		}
		num.pop();

		string result_str;
		result_str = translate_float(result);
		ExpTranslate(op,result_str);		
	}
	return 0;
}

int GreatCommon(int fenzi, int fenmu)
{
	int n;
	do
	{
		n = fenzi % fenmu;
		fenzi = fenmu;
		fenmu = n;

	} while (n != 0);
	return fenzi;
}

void Simplify(fenshu &sample)
{
	int max;
	max = GreatCommon(sample.fenzi, sample.fenmu);
	sample.fenmu /= max;
	sample.fenzi /= max;
}

fenshu Add(fenshu a1, fenshu a2)
{
	fenshu a3;
	a3.fenmu = a1.fenmu*a2.fenmu;
	a3.fenzi = a1.fenzi*a2.fenmu + a1.fenmu*a2.fenzi;
	return a3;
}

fenshu Sub(fenshu a1, fenshu a2)
{
	fenshu a3;
	a3.fenmu = a1.fenmu*a2.fenmu;
	a3.fenzi = a1.fenzi*a2.fenmu - a1.fenmu*a2.fenzi;
	return a3;
}

fenshu chen(fenshu a1, fenshu a2)
{
	fenshu a3;
	a3.fenmu = a1.fenmu*a2.fenmu;
	a3.fenzi = a1.fenzi*a2.fenzi;
	return a3;
}

fenshu chu(fenshu a1, fenshu a2)
{
	fenshu a3;
	a3.fenmu = a1.fenmu*a2.fenzi;
	a3.fenzi = a1.fenzi*a2.fenmu;
	return a3;
}

fenshu Operate_fenshu(char op, fenshu num1, fenshu &num2)
{
	fenshu temp;
	fenshu cuowu;
	cuowu.fenzi = 1;
	switch (op)
	{
	case '+': return Add(num1,num2);
	case '-':
		if (num1.fenzi == 0) 
		{
			num2.fenzi = 0;
			temp = Sub(num1, num2);
			return temp;
		}
		else
		{
			//num2.fenzi = (int)scalemin_op + rand() % (num1.fenzi + scalemin_op);
			//num2.fenmu = num1.fenmu;
			temp = Sub(num1, num2);
			if (temp.fenzi < 0) {
				cuowu.fenmu = 0;
				return cuowu;
			}
			return temp;
		}
	case '*': return chen(num1,num2);
	case '/':
		if (num2.fenzi eq 0) {
			cuowu.fenmu = 0;
			return cuowu;
		}
		return chu(num1, num2);
	}
}

string translate_fenshu(fenshu sample)
{
	string str = "[";
	if (sample.fenzi eq 0) 
	{
		str = "0";
		return str;
	}
	if (sample.fenmu == 1)
	{
		str = translate(sample.fenzi);
		return str;
	}
	else
	{
		if (sample.fenzi > sample.fenmu)
		{
			int k = sample.fenzi / sample.fenmu;
			int j = sample.fenzi % sample.fenmu;
			str += translate(k) + '`' + translate(j) + '/' + translate(sample.fenmu);
		}
		else
		{
			str += translate(sample.fenzi) + '/' + translate(sample.fenmu);
		}
	}
	str += ']';
	return str;
}

int Generate_fenshu()
{
	srand((unsigned)time(NULL));
	map<string, int>::iterator iter;
	string op = "";
	string str1 = "", str2 = "";
	char sign;
	int i = 1, j = 0, temp;
	fenshu num1, num2;
	fenshu result, flag;
	int jj = 0;
	stack<fenshu> num;

	for (j = 0; j < num_ques; j++) {
		op = "";
		for (i = 1; i < num_op; i++)
		{
			sign = randsign();

			num1.fenzi = (int)scalemin_op + rand() % (scalemax_op + scalemin_op );
			num1.fenmu = (int)scalemin_op + rand() % (scalemax_op + scalemin_op );
			
			while(num1.fenmu == 0) num1.fenmu = (int)scalemin_op + rand() % (scalemax_op + scalemin_op);
			num2.fenmu = (int)scalemin_op + rand() % (scalemax_op + scalemin_op);
			while (num2.fenmu == 0) num2.fenmu = (int)scalemin_op + rand() % (scalemax_op + scalemin_op );
			num2.fenzi = (int)scalemin_op + rand() % (scalemax_op + scalemin_op );
			
			if (i != 1)
			{
				num1 = num.top();
				num.pop();
			}

			int fang;
			if (sign eq '^')
			{
				flag.fenmu = 1;
				flag.fenzi = 1;
				fang = rand() % 4;
				if (num1.fenzi < 10 && num1.fenzi < 10) 
				{
					for (int k = 0; k < fang; k++)
					{
						flag = chen(flag, num1);
					}
				}
				else 
				{
					j--;
					jj = 1;
					break;
				}
			}
			else flag = Operate_fenshu(sign, num1, num2);

			while (flag.fenmu == 0)
			{
				num2.fenmu = (int)scalemin_op + rand() % (scalemax_op + scalemin_op );
				while (num2.fenmu == 0)num2.fenmu = (int)scalemin_op + rand() % (scalemax_op + scalemin_op );
				num2.fenzi = (int)scalemin_op + rand() % (scalemax_op + scalemin_op );
			
				flag = Operate_fenshu(sign, num1, num2);
			}
			Simplify(flag);
			
			num.push(flag);

			if (i eq 1)
			{
				Simplify(num1);
				Simplify(num2);
				str1 = translate_fenshu(num1);
				if (sign != '^') str2 = translate_fenshu(num2);
				else str2 = translate(fang);
				op = op + str1 + " " + str2 + " " + sign;
			}
			else
			{
				Simplify(num2);
				if (sign != '^') str2 = translate_fenshu(num2);
				else str2 = translate(fang);
				op = op + " " + str2 + " " + sign;
			}
		}
		if (jj == 1) 
		{
			jj = 0;
			continue;
		}
		op = op + ' ';
		
		result = num.top();
		if (result.fenmu > result_max || result.fenmu < result_min)
		{
			j--;
			continue;
		}
		if (result.fenzi > result_max|| result.fenzi < result_min)
		{
			j--;
			continue;
		}
		iter = mapException.find(op);
		if (iter != mapException.end())
		{
		    j--;
		}
		else
		{
		mapException.insert(pair<string, int>(op, 1));
		}
		num.pop();
	    
		
		string result_str;
		result_str = translate_fenshu(result);
		ExpTranslate(op,result_str);
	}
	return 0;
}

char randsign()
{
	int temp;
	char sign;
	temp = rand() % (7);
	switch (temp)
	{
	case 0: if (is_add) { sign = '+'; break; }
	case 1: if (is_sub) { sign = '-'; break; }
	case 2: if (is_div) { sign = '/'; break; }
	case 3: if (is_mul) { sign = '*'; break; }
	case 4: if (is_add) { sign = '+'; break; }
	case 5: if (is_sub) { sign = '-'; break; }
	case 6: if (is_power) { sign = '^'; break; }
	default:
		if (is_add) { sign = '+'; break; }
		if (is_sub) { sign = '-'; break; }
		if (is_mul) { sign = '*'; break; }
		if (is_div) { sign = '/'; break; }
	}
	return sign;
}

int Setting()
{
    QString qstr;
    qstr = QString::fromStdString(sample.is_add);
    qDebug()<<qstr;

    qDebug()<<"sb";
    resu=0;
    int flag;
    flag = jiexi(sample.num_ques);
    if (flag == -1) return -1;
	else {
		if (flag >= 10000) return -1;
		else num_ques = flag;          //问题数量
	}
    qDebug()<<"num_ques";

    /*flag = jiexi(sample.is_power);
    if (flag == -1){
        qDebug()<<"xnq";
        return -1;
    }
	else {
		if (flag==0||flag ==1) is_power = flag;
		else return -1;
    }
    qDebug()<<"power";
    qDebug()<<flag;*/


    flag = jiexi(sample.is_add);//加法
    qDebug()<<flag;

    if (flag == -1) return -1;
    else {
        if (flag == 0 || flag == 1) is_add = flag;
        else return -1;
    }
    qDebug()<<"is_add";
    qDebug()<<flag;

    /*flag = jiexi(sample.is_sub);
	if (flag == -1) return -1;
	else {
		if (flag == 0 || flag == 1) is_sub = flag;
		else return -1;
	}
    qDebug()<<"is_sub";
    qDebug()<<flag;

	flag = jiexi(sample.is_mul);
	if (flag == -1) return -1;
	else {
		if (flag == 0 || flag == 1) is_mul = flag;
		else return -1;
	}
    qDebug()<<"is_mul";
    qDebug()<<flag;

	flag = jiexi(sample.is_div);
	if (flag == -1) return -1;
	else {
		if (flag == 0 || flag == 1) is_div = flag;
		else return -1;
	}
    qDebug()<<"is_div";
    qDebug()<<flag;*/

    /*flag = jiexi(sample.is_real);
	if (flag == -1) return -1;
	else {
		if (flag == 0 || flag == 1) is_real = flag;
		else return -1;
	}
    qDebug()<<"is_real";
    qDebug()<<flag;

	flag = jiexi(sample.is_decimal);
	if (flag == -1) return -1;
	else {
		if (flag == 0 || flag == 1) is_decimal = flag;
		else return -1;
    }
    qDebug()<<"is_decimal";
    qDebug()<<flag;*/

    flag = jiexi(sample.scalemax_op);//操作数最大值
	if (flag == -1) return -1;
	else {
		if(is_power == 1||is_mul == 1){ if (flag >= 20) return -1; else scalemax_op = flag;}
		else { if (flag >= 500) return -1; else scalemax_op = flag; }
    }
    qDebug()<<"scalemax_op";
    qDebug()<<flag;

    /*flag = jiexi(sample.num_op);
	if (flag == -1) return -1;
	else {
		if (flag >= 10) return -1;
        else num_op = flag;         //操作数个数
    }*/

    /*flag = jiexi(sample.num_float);
	if (flag == -1) return -1;
	else {
		if (flag >= 5) return -1;
        else num_float = flag;         //操作数精度
	}

    flag = jiexi(sample.result_max);//结果最大值
	if (flag == -1) return -1;
	else {
		if (flag >= 1000000) return -1;
		else result_max = flag;
    }*/
	result_min = 0;

    if (is_real == 0 && is_decimal == 0) Generate_int();
	else if (is_real == 0 && is_decimal == 1)Generate_float();
	else if (is_real == 1 && is_decimal == 0)Generate_fenshu();
	else if (is_real == 1 && is_decimal == 1)Generate_float();
	for (size_t i = 0; i < num_ques; i++)
	{
		printf("%s = %s\n", (char*)expResult[i].express.data(), (char*)expResult[i].result.data());
		printf("\n");
    }
	return 0;
}

/*int main()
{
	Setting();
	if (is_real == 0 && is_decimal == 0) Generate_int();
	else if (is_real == 0 && is_decimal == 1)Generate_float();
	else if (is_real == 1 && is_decimal == 0)Generate_fenshu();
	else if (is_real == 1 && is_decimal == 1)Generate_float();
	for (size_t i = 0; i < num_ques; i++)
	{
		printf("%s = %s\n", (char*)expResult[i].express.data(), (char*)expResult[i].result.data());
		printf("\n");
	}
	return 0;
}*/


