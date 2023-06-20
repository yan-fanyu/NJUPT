#include "analyselr.h"

#include <QString>
#include<iostream>
#include<string>
#include<vector>	//STL容器，动态数组，序列性容器+动态增长+可定制的内存分配策略
#include<iomanip>	//I/O控制流头文件
#include <stack>
#include <map>
using namespace std;
#include <list>

#include "functions.h"


    //构造函数
    AnalyseLR::AnalyseLR()
    {
        step = 0;
        inputstr = "";
    }
    //初始化两个栈
    void AnalyseLR::initstack()
    {
        state.push(0);
        symbol.push("=");

    }
    //这是一个输出提示函数
    void AnalyseLR::printInfo(string str)
    {
        cout << str << endl;
    }

    //这是两个输出提示函数的增强版
    void AnalyseLR::printInfoEX(string str1, string str2, string str3, string str4, string str5)
    {
        //all_state.push_back(make_pair(data, symbol));
        cout << setw(6) << setiosflags(ios_base::left) << str1;	// setiosflags(ios_base::left) 左对齐值，用填充字符填充右边
        cout << setw(15) << setiosflags(ios_base::left) << str2;
        cout << setw(15) << setiosflags(ios_base::left) << str3;
        cout << setw(30) << setiosflags(ios_base::left) << str4;
        cout << setw(10) << setiosflags(ios_base::left) << str5 << endl;
    }

    void AnalyseLR::printfInfoEX(int str1, stack<int> state, stack<string> symbol, string str4, string str5)
    {

        cout << setw(6) << setiosflags(ios_base::left) << str1;
        step0.push_back(str1);
        printState(state);

        printSymbol(symbol);
        cout << setw(30) << setiosflags(ios_base::left) << str4;

        inputstring.push_back(str4);
        cout << setw(10) << setiosflags(ios_base::left) << str5 << endl;
        oper.push_back(str5);




    }

    //初始化界面函数
    void AnalyseLR::initstageInfo()
    {
        cout << "\n\t     welcom" << endl;
        cout << "\t-----------------------------------------" << endl;
        cout<<"\t  expression as follows \n"<<endl;
        cout << "\t\t(0)  E’-> E " << endl;
        cout << "\t\t(1)  E  -> E + T" << endl;
        cout << "\t\t(2)  E  -> E - T" << endl;
        cout << "\t\t(3)  E  -> T " << endl;
        cout << "\t\t(4)  T  -> T * F" << endl;
        cout << "\t\t(5)  T  -> T / F" << endl;
        cout << "\t\t(6)  T  -> F " << endl;
        cout << "\t\t(7)  F  -> ( E ) " << endl;
        cout << "\t\t(8)  F  -> id " << endl;
        cout << "\t------------------------------------------" << endl;
    }

    //提示输入的函数
    void AnalyseLR::initInputstr(QString s)
    {

        inputstr = s.toStdString();

    }

    //将终结符和非终结符转换为action和gotol表中对应的列号
    int AnalyseLR::strtoInt(string str)
    {
        if (str == "+")
            return 0;
        if (str == "-")
            return 1;
        if (str == "*")
            return 2;
        if (str == "/")
            return 3;
        if (str == "(")
            return 4;
        if (str == ")")
            return 5;
        //if (str == "id")
            //return 6;
        if (str == "=")  //$
            return 7;
        if (str == "E")
            return 0;
        if (str == "T")
            return 1;
        if (str == "F")
            return 2;
        //return 111;
        return 6;
    }
    //判断字符是终结符还是非终结符
    bool AnalyseLR::judgeSymbol(string str)
    {
        for (int i = 0; i<3; i++)
        {
            if (noends[i] == str)
                return false;
        }
        return true;
    }
    //根据产生式选择非终结符
    int AnalyseLR::chooseNoEnds(int num)
    {
        if (num == 1 || num == 2 || num == 3)
            return 0;//选择“E”
        if (num == 4 || num == 5 || num == 6)
            return 1;//选择“T”
        return 2;//选择“F”
    }
    //计算字符串中元素的个数
    int AnalyseLR::calculatenum(string str)
    {
        int num = 0;
        if (str == "id") num = 1;
        else num = str.size();
        return num;
    }
    //将vector容器中的字符串连起来
    string AnalyseLR::linkVectorstr(vector<string> &vecs, vector<string>::iterator iter)
    {
        string str = "";
        vector<string>::iterator it;
        it = iter;
        for (it; it<vecs.end(); it++)
        {
            //cout<<*it;
            str += *it;
        }
        return str;
    }

    int AnalyseLR::Start(QString s, float& output)//开始函数.
    {
        if(!Check(s))
        {
            this->error = "括号不匹配";
            return -999;
        }
        initstageInfo();
        initstack();//初始化两个栈
        initInputstr(s);
        printInfo("\n---------------------------word analysis----------------------------------");
        printInfo("\t\t\t记号名\t属性值");
        vector<string> vec = analyse(inputstr, this->Lexical);//分开布尔表达式
        if (vec.empty()) {}
        else{
            vector<string>::iterator iter = vec.begin();



            printInfo("\n---------------------------grammar analysis----------------------------------");
            printInfoEX("step", "state stack", "marker stack", "input string", "operation");
            bool flag;
            for (iter; iter != vec.end(); ++iter)//依次遍历字符
            {
                flag = 1;
                string str1 = linkVectorstr(vec, iter);
                actionGoto(*iter, str1, vec,flag);
                if (!flag)
                {
                    if(this->xxx == -10)
                    {
                        this->error= "除数不能为0";
                    }
                    else
                    {
                        this->error= "运算符错误";
                    }
                    return -999;
                }
            }
            iter--;
            if (*iter != "=")
            {
                flag = 0;
                cout << "pelase end with '='"<< endl;
            }
            if (flag)
            {
                cout << "success!" << endl;
                printInfo("\n---------------------------Intermediate code----------------------------------");
                vector<string>::iterator iter2 = vec.begin();
                string s_mid = linkVectorstr(vec, iter2);   //连接成一个字符串
                s_mid = s_mid.substr(0, s_mid.length() - 1);  //删除最后的等于，用substr实现截取功能
                string HZ = InversePolish(s_mid);//转后缀表达式
                printInfo("\n---------------------------Calculation results----------------------------------");
                char* stringofchar = (char*)HZ.data();//加const  或者用char * p=(char*)str.data();的形式
                float Result = calculate(stringofchar);
                output = Result;
                cout << "result is " << Result << endl;
            }
            //printForsInfo();
        }
        return 1;
    }


    //状态栈


    void AnalyseLR::printState(stack<int> s)//输出栈内的所有元素
    {
        string str = " ";
        int* pre;

        vector<int> v;

        while (!s.empty())
        {
            v.push_back(s.top());
            s.pop();
        }

        for (int i = s.size(); i >=0; i--)
        {
            if (v[i] > 9)   // 栈中保存的10转换成1、0
            {
                char ch1 = (v[i] / 10) + 48;
                char ch2 = (v[i] % 10) + 48;
                str += ch1;
                str += ch2;
            }
            else
            {
                char ch = v[i] + 48;
                str += ch;
            }
        }
        cout << setw(15) << setiosflags(ios_base::left) << str;
        this->state00.push_back(str);
    }


    //符号栈 输出栈内的所有元素
    void AnalyseLR::printSymbol(stack<string> s)
    {
        string str = "";
        vector<string> v;
        while (!s.empty())
        {
            v.push_back(s.top());
            s.pop();
        }
        for (int i = v.size() - 1; i >= 0; i--)
        {
            str += v[i];
        }
        cout << setw(15) << setiosflags(ios_base::left) << str;
        this->marker.push_back(str);
    }

    void AnalyseLR::Print()
    {
        for(string s: this->marker)
        {
            cout << s << endl;
        }
    }

    bool AnalyseLR::Check(QString str0)
    {


                string str = str0.toStdString();
                list<char> lChar;
                int nStrLen = str.length();

                for (int i = 0; i < nStrLen; i++)
                {
                    if (str[i] == '(')
                    {
                        lChar.push_back(str[i]);
                    }
                    if (str[i] == ')')
                    {
                        if (lChar.empty())
                            return false;
                        lChar.pop_back();
                    }
                }
                if (lChar.empty())
                    return true;
                return false;



    }



    //LR分析函数
    int AnalyseLR::actionGoto(string str, string str1,vector<string> vec,bool &flag)
    {
        int x = state.top();//当前栈顶状态
        int y = strtoInt(str);//当前将要输入的字符
        if (action[x][y] == 0)
        {
            cout << "grammar analysis fail" << endl;
            flag=0;
        }
        if (action[x][y]>0 && judgeSymbol(str) && (str != "="))//移进
        {
            printfInfoEX(step, state, symbol, str1, "移入" + str);
            state.push(action[x][y]);
            symbol.push(str);
            ++step;
        }
        if (action[x][y]<0 && judgeSymbol(str))//规约
        {
            int z = -action[x][y];//用-action[x][y]对应的产生式规约
            string lenstr = products[z];//生成需要规约的产生式
            int n = calculatenum(lenstr);//计算产生式的长度，进行规约
            int c = chooseNoEnds(z);
            string ch = noends[c];//生成规约后的非终结符
            printfInfoEX(step, state, symbol, str1, "规约" + noends[c] + "->" + products[z]);

            switch (z)
            {
            case 1:
            {
                int a = data.top();
                data.pop();
                int b = data.top();
                data.pop();
                b += a;
                data.push(b);
                break;
            }
            case 2:
            {
                int a = data.top();
                data.pop();
                int b = data.top();
                data.pop();
                b -= a;
                data.push(b);
                break;
            }
            case 4:
            {
                int a = data.top();
                data.pop();
                int b = data.top();
                data.pop();
                b *= a;
                data.push(b);
                break;
            }
            case 5:
            {
                int a = data.top();
                if (a == 0)
                {
                    flag = 0;
                    cout << "\n除数为0！" << endl;
                    this->xxx = -10;
                    return flag;
                }
                data.pop();
                int b = data.top();
                data.pop();
                b /= a;
                data.push(b);
                break;
            }
            case 8:
            {
                string b = symbol.top();
                int c = atoi(b.c_str());
                data.push(c);
                break;
            }

            default:
                break;
            }

            for (int i = 0; i < n; i++)
            {
                state.pop();
                symbol.pop();
            }


            int m = state.top();//获取规约后的栈顶状态
            if (gotol[m][c]>0)
            {
                int g = gotol[m][c];
                state.push(g);
                symbol.push(ch);
            }
            ++step;
            actionGoto(str, str1,vec,flag);
        }
        //cout << str<<" "<<str1 << endl;
        if ((action[x][y] == 100) &&(str1=="="))
        {
            flag = 1;
            printfInfoEX(step, state, symbol, str1, "分析完成");

            cout << "\nGrammar analysis calculation results: "<<data.top() << endl;
        }
        else if ((action[x][y] == 100))
        {
            cout << "Grammar parsing failed!" << endl;
            flag = 0;
        }

        return flag;
    }





