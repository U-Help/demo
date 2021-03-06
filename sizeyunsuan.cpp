
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<stack>
#include<map>
#include<math.h>
#include<string>

using namespace std;

typedef struct ExpDetail {
	string expression;
	int prior;
}MyExp;
#define eq ==
map<string, int> mapException;
int num_ques = 0;
int scalemax_op = 0;
int scalemin_op = 0;
int num_op = 0;
int num_float = 0;
bool is_real = 0;
bool is_decimal = 0;
bool is_power = 0;

typedef struct canshu {
    string num_ques;    //问题数量 10000以内
    string scalemax_op; //操作数最大范围 有乘方（乘法）只能20以内
    string num_op;      //等式的长度
    string num_float;   //浮点数的小数位数
    string is_real;     //是否支持分数，“1”表示是，“0”表示否
    string is_decimal;  //是否支持小数，“1”表示是，“0”表示否
    string is_power;    //是否支持乘方，“1”表示是，“0”表示否
        string is_add;
    string is_sub;
    string is_mul;
    string is_div;
    string result_max;  //结果的最大值
    string result_min;  //结果的最小值
}canshu;

string a;

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
void ExpTranslate(string Suffix_exp)
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
//	printf("%s = \n", (char*)oper_finally.expression.data());
    //QString q_str = QString::fromStdString(c_str);
    a=oper_finally.expression;
}

int Setting()
{

    //num_ques = 5;          //问题数量
    scalemax_op = 10;       //操作数的最大
	scalemin_op = 0;        //操作数的最小
    num_op = 3;            //操作符的数量
	num_float = 2;          //小数的精度
	is_real = 0;            //有没有分数
    is_decimal = 0;         //有没有小数
	is_power = 0;           //有没有乘方
	return 0;
}

int Operate(char op, int num1, int num2)
{
	switch (op)
	{
	case '+': return num1 + num2;
	case '-':
		if (num1 - num2 < 0)return -1;
		return num1 - num2;
	case '*': return num1 * num2;
	case '/':
		if (num2 eq 0) return -1;
		else if (num1 % num2 != 0) return -1;
		else return num1 / num2;
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

string translate_float(float num)
{
	int int_part = 0;
	string int_str, float_str;
	num = num * pow(10.0,num_float);
	num = (int)(num + 0.5);
	num = num / pow(10, num_float);
	int_part = (int)num;
	int_str = translate(int_part);
	num = num - int_part;
	float_str = "";
	for (int i = 1; i <= num_float; i++)
	{
		num = num*10;
		float_str += translate(int(num)%10);
	}
	return int_str + "." + float_str;
}

int Generate()
{
	srand((unsigned)time(NULL));
	map<string, int>::iterator iter;
	string op = "";
	string str1 = "", str2 = "";
	char sign;
	int i = 1, j = 0, temp, num1, num2, flag, result;
	stack<int> num;

	for (j = 0; j < num_ques; j++) {
		op = "";
		for (i = 1; i < num_op; i++)
		{
			temp = rand() % (6);
			switch (temp)
			{
			case 0: sign = '+'; break;
			case 1: sign = '-'; break;
			case 2: sign = '/'; break;
			case 3: sign = '*'; break;
			case 4: sign = '+'; break;
			case 5: sign = '-'; break;
			}

			num1 = (int)scalemin_op + rand() % (scalemax_op + scalemin_op - 1);
			num2 = (int)scalemin_op + rand() % (scalemax_op + scalemin_op - 1);
			if (i != 1)
			{
				num1 = num.top();
				num.pop();
			}

			flag = Operate(sign, num1, num2);
			while (flag eq - 1 || flag eq - 2)
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
		/*iter = mapException.find(op);
		if (iter != mapException.end())
		{
			j--;
		}
		else
		{
			mapException.insert(pair<string, int>(op, result));
		}
		num.pop();*/
		printf("\n\n");
		ExpTranslate(op);
		printf("%d\n\n",  result);
	}
	return 0;
}

void hehe(){
    return;
}


/*int main()
{
	string exm;
	Setting();
	Generate();
	//exm = translate_float((float)0.999999999);
	//ExpTranslate("164 2425 + 3532 4643 + * ");
	return 0;
}*/


