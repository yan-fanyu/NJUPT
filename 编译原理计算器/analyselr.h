#ifndef ANALYSELR_H
#define ANALYSELR_H

#include <QString>
#include<iostream>
#include<string>
#include<vector>	//STL容器，动态数组，序列性容器+动态增长+可定制的内存分配策略
#include<iomanip>	//I/O控制流头文件
#include <stack>
#include <map>
using namespace std;
class AnalyseLR
{
private:
    int step;
    string inputstr;        //布尔表达式
    stack<int> state;       //状态栈
    stack<string> symbol;   //符号栈
    stack<float> data;        //数据栈
public: vector<pair<string, string>> all_state;
    QString error;
    int xxx = 100;

public:
    //构造函数
    AnalyseLR();
    //初始化两个栈
    void initstack();
    //这是一个输出提示函数
    void printInfo(string str);
    //这是两个输出提示函数的增强版
    void printInfoEX(string str1, string str2, string str3, string str4, string str5);
    void printfInfoEX(int str1, stack<int> state, stack<string> symbol, string str4, string str5);
    //初始化界面函数
    void initstageInfo();
    //提示输入的函数
    void initInputstr(QString s);
    //将终结符和非终结符转换为action和gotol表中对应的列号
    int strtoInt(string str);
    //判断字符是终结符还是非终结符
    bool judgeSymbol(string str);
    //根据产生式选择非终结符
    int chooseNoEnds(int num);
    //计算字符串中元素的个数
    int calculatenum(string str);
    //将vector容器中的字符串连起来
    string linkVectorstr(vector<string> &vecs, vector<string>::iterator iter);
    int Start(QString s, float& output);
    //LR分析函数
    int actionGoto(string str, string str1,vector<string> vec,bool &flag);
    // 打印状态栈
    void printState(stack<int> s);
    //符号栈 输出栈内的所有元素
    void printSymbol(stack<string> s);
    void Print();


    bool Check(QString str0);

public:
    vector<string> Lexical;
    vector<int> step0;
    vector<string> state00;
    vector<string> marker;
    vector<string> inputstring;
    vector<string> oper;


};



#endif // ANALYSELR_H
