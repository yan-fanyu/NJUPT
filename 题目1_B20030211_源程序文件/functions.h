#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "const.h"

/**判断是否为分隔符**/
bool IsSeparater(char ch);

/**判断是否为运算符**/
bool IsOperator(char ch);

/**判断是否为过滤符**/
bool IsFilter(char ch);

/**判断是否为数字**/
bool IsDigit(char ch);

/**词法分析**/
vector<string> analyse(string expression, vector<string>& v);

//*********************中间代码生成器******************************//
string InversePolish(string s_mid);

//*********************后缀表达式计算******************************//
float Op(float a, char op, float b);

float calculate(char *str);




#endif // FUNCTIONS_H
