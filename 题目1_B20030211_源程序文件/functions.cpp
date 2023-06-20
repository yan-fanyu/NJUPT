#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP

#include "functions.h"

/**判断是否为分隔符**/
bool IsSeparater(char ch){
    for (int i = 0; i<2; i++){
        if (SEPARATER[i] == ch){
            return true;
        }
    }
    return false;
}

/**判断是否为运算符**/
bool IsOperator(char ch){
    for (int i = 0; i<5; i++){
        if (OPERATOR[i] == ch){
            return true;
        }
    }
    return false;
}
/**判断是否为过滤符**/
bool IsFilter(char ch){
    for (int i = 0; i<4; i++){
        if (FILTER[i] == ch){
            return true;
        }
    }
    return false;
}
/**判断是否为数字**/
bool IsDigit(char ch){
    cout << "input\t" << ch<<endl;
    if (ch >= '0' && ch <= '9' || ch=='.') return true;
    return false;
}

/**词法分析**/
vector<string> analyse(string expression, vector<string>& v){
    vector<string> vec;
    char ch = ' ';
    for (int i = 0; i < expression.length(); i++)
    {
        string arr = "";
        ch = expression[i];
        if (IsFilter(ch)){}              //判断是否为过滤符
        else if (IsDigit(ch)){           //判断是否为数字
            while (IsDigit(ch) || IsFilter(ch)){
                if (IsDigit(ch))
                    arr += ch;
                i++;
                ch = expression[i];
            }
            i--;
            v.push_back(string(arr) + " : number");
            cout << "\t\t\t< int, " << arr <<">"<< endl;
            vec.push_back(arr);		//将一个新的元素加到vector后面，位置为当前最后一个元素的下一个元素
        }
        else if (IsOperator(ch))
        {
            arr += ch;
            v.push_back(string(arr) + " : operator");
            cout << "\t\t\t< operator, " <<  arr << ">" << endl;
            vec.push_back(arr);
        }
        else if (IsSeparater(ch))
        {
            arr += ch;
            v.push_back(string(arr) + " : delimiter");
            cout << "\t\t\t< delimiter, " << arr << ">" << endl;
            vec.push_back(arr);
        }
        else
        {
            v.push_back(string(arr) + ": operator");
            cout << "\t\t\t\"" << ch << "\":Unrecognized characters！" << endl;
            vec.clear();
            return vec;
        }
    }
    return vec;
}

//*********************中间代码生成器******************************//
string InversePolish(string s_mid)
{
    string s_beh = "";
    stack<char> stk;

    map<char, int> op;//利用map来实现运算符对应其优先级
    op['('] = 0;
    op[')'] = 0;
    op['+'] = 1;
    op['-'] = 1;
    op['*'] = 2;
    op['/'] = 2;
    string::iterator it = s_mid.begin();
    //迭代器，遍历并选择序列中的对象，他提供了一种访问一个容器对象的中各个元素，而又不必保留该对象内部细节的方法。
    while (it != s_mid.end())
    {
        if (op.count(*it))//判断该元素是否为运算符
        {
            if (*it == ')')//若为’）‘，把栈中的运算符依次加入后缀表达式，直到出现'（'，’（‘出栈，退出该次循环
            {
                while (stk.top() != '(')
                {
                    s_beh += stk.top();		//取出栈顶元素
                    s_beh += " ";
                    stk.pop();
                }
                stk.pop();		//弹出栈顶元素
            }
            else if (stk.empty() || *it == '(' || op[*it]>op[stk.top()])
                //若为‘（’，入栈 ; 要入栈的运算符优先级大于等于栈顶的运算符的优先级，直接入栈
            {
                stk.push(*it);	//在栈顶增加元素
            }
            else if (op[*it] <= op[stk.top()])
                // 入栈的运算符优先级小于等于栈顶的运算符的优先级，栈顶运算符出栈，再次比较，直到出现优先级低的运算符，或者栈为空，退出
            {
                while (op[*it] <= op[stk.top()] && (!stk.empty()))
                {
                    s_beh += stk.top();
                    s_beh += " ";
                    stk.pop();
                    if (stk.empty()) break;
                }
                stk.push(*it);
            }
        }
        else
        {
            s_beh += *it;
            it++;
            if (it != s_mid.end() && op.count(*it))
                //count，返回被查找元素个数，返回1/0，有/无；find 返回被查找元素的位置，没有返回map.end()
                s_beh += " ";
            it--;
        }
        it++;

        if (it == s_mid.end())//当中缀表达式输出完成，所有元素出栈
        {
            while (!stk.empty())
            {
                s_beh += " ";
                s_beh += stk.top();
                stk.pop();
            }
            break;
        }
    }
    cout <<"逆波兰表达式："<< s_beh << endl;
    return s_beh;
}

//*********************后缀表达式计算******************************//
float Op(float a, char op, float b)
{
    switch (op)
    {
    case '+':return a + b; break;
    case '-':return a - b; break;
    case '*':return a*b; break;
    case '/':return a / b; break;
    }
}

float calculate(char *str)
{
    stack<float> s;   //暂存操作数
    int i = 0;
    int offset = 0;
    int flag = 0;
    int Length = strlen(str);
    float Result;
    while (i < Length)
    {
        string One = "";
        for (i; i < Length; i++)
        {

            One += str[i];
            if (((str[i] == ' ')&&(str[i+1]!=' ')) || (i == Length - 1))
            {
                char* OneNumber = (char*)One.data();
                cout << OneNumber <<endl;
                float Number = atof(One.c_str());
                cout << "NUM = " << Number <<endl;
                //atoi字符串转整数，c_str返回一个指向正规c字符串的指针常量，内容与其中string同。（为了与c语言兼容）

                if (IsOperator(*OneNumber))
                {
                    Number = 0;
                }
                cout << "198  " <<Number<<endl;
                s.push(Number);

                if (IsOperator(*OneNumber))
                {
                    s.pop();
                    float x = s.top();
                    s.pop();
                    float y = s.top();
                    s.pop();
                    Result = Op(y, *OneNumber, x);
                    s.push(Result);
                }
                offset = i + 1;
                break;
            }
        }
        i = offset;
    }
    return s.top();
}
#endif // FUNCTIONS_CPP
