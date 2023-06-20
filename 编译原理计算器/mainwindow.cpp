/*
1. 错误检测
    1.1 除数不能为0
    1.2 运算符错误
    1.3 括号不匹配
2. 浮点数
3. 分析演示
    1.1 语法分析栈 和 余留符号串栈
4. 全部过程 : 包含词法分析和语法分析
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "functions.h"

#include <QDebug>
#include <windows.h>

const int HEIGHT = 650;
const int WIDTH = 520;
const int SHOWHEIGHT = 1200;
const int SHOWWIDTH = 520;
const int ALLHEIGHT = 1200;
const int ALLWIDTH = 2000;

using namespace std;
int Index = 0;

// 输入的表达式 和 结果
QString s;
float output;
bool InputEnable = true;

bool AnalyseFlag = false;


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(WIDTH, HEIGHT);
    ui->analysis->setEnabled(false);
    ui->showstep->setEnabled(false);

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_insert_clicked()
{
    s = ui->input->toPlainText();
    ui->input->setText("插入得内容是"+s);
}

void MainWindow::InsertLexicalOutput(QString s)
{
    ui->word->clear();
    for(string s: ana.Lexical)
    {
        ui->word->append(QString::fromStdString(s));
    }
}

void MainWindow::InsertGrammarOutput(QString s)
{
    ui->step->clear();
    ui->state->clear();
    ui->marker->clear();
    ui->stringleft->clear();
    ui->oper->clear();
    for(int s: ana.step0)
    {
        ui->step->append(QString::number(s));
    }
    for(string s: ana.state00)
    {
        ui->state->append(QString::fromStdString(s));
    }

    for(string s: ana.marker)
    {
        ui->marker->append(QString::fromStdString(s));
    }

    for(string s: ana.inputstring)
    {
        ui->stringleft->append(QString::fromStdString(s));
    }

    for(string s: ana.oper)
    {
        ui->oper->append(QString::fromStdString(s));
    }
}

void MainWindow::on_add_clicked()
{



}

void MainWindow::Init()
{

}





void MainWindow::digitBtn(char ch)
{
    cout << "HAHA";
    s+= ch;
    qDebug(s.toStdString().data());
    ui->input->setPlainText(s);
}

void MainWindow::on_btn0_clicked()
{


    digitBtn('0');
}

void MainWindow::on_btn1_clicked()
{
    digitBtn('1');

}

void MainWindow::on_btn2_clicked()
{
    digitBtn('2');
}

void MainWindow::on_btn3_clicked()
{
    digitBtn('3');
}

void MainWindow::on_btn4_clicked()
{
    digitBtn('4');
}

void MainWindow::on_btn5_clicked()
{
    digitBtn('5');
}

void MainWindow::on_btn6_clicked()
{
    digitBtn('6');
}

void MainWindow::on_btn7_clicked()
{
    digitBtn('7');
}

void MainWindow::on_btn8_clicked()
{
    digitBtn('8');
}

void MainWindow::on_btn9_clicked()
{
    digitBtn('9');
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_C)
            {
                on_btnClear_clicked();
            }

    if(!InputEnable)
        return;

    if(event->key() == Qt::Key_Enter)
    {
        qDebug("回车");
    }

        else if(event->key() == '1' ){
            digitBtn('1');
        }
    else if(event->key() == '.' ){
        digitBtn('.');
    }
        else if(event->key()=='0')
        {
            digitBtn('0');
        }

        else if(event->key()=='2')
        {
            digitBtn('2');
        }

        else if(event->key()=='3')
        {
            digitBtn('3');
        }

        else if(event->key()=='4')
        {
            digitBtn('4');
        }

        else if(event->key()=='5')
        {
            digitBtn('5');
        }

        else if(event->key()=='6')
        {
            digitBtn('6');
        }

        else if(event->key()=='7')
        {
            digitBtn('7');
        }

        else if(event->key()=='8')
        {
            digitBtn('8');
        }

        else if(event->key()=='9')
        {
            digitBtn('9');
        }

        else if(event->key()=='+')
        {
            digitBtn('+');
        }

        else if(event->key()=='-')
        {
            digitBtn('-');
        }

        else if(event->key()=='*')
        {
            digitBtn('*');
        }

        else if(event->key()=='/')
        {
            digitBtn('/');
        }
        else if(event->key()=='=')
        {
            on_btnEqual_clicked();
        }
        else if(event->key()==Qt::Key_C)
        {
            on_btnClear_clicked();
        }

        else if(event->key()=='(')
        {
            on_btnLeft_clicked();
        }

        else if(event->key()==')')
        {
            on_btnRight_clicked();
        }

        else if(event->key()==Qt::Key_Backspace)
        {
            on_btnBack_clicked();
        }


}



void MainWindow::on_btnAdd_clicked()
{

    digitBtn('+');

}

void MainWindow::on_btnSub_clicked()
{
    digitBtn('-');

}

void MainWindow::on_btnMuti_clicked()
{
    digitBtn('*');

}

void MainWindow::on_btnDivi_clicked()
{
    digitBtn('/');

}


//等于号的槽函数。
void MainWindow::on_btnEqual_clicked()
{



    InputEnable = false;

    digitBtn('=');


    ana = AnalyseLR();
    int res = ana.Start(s, output);

    if(res == -999)
    {
        ui->result->setText(ana.error);
        return;
    }
    ui->result->setText(QString::number(output));
    ui->analysis->setEnabled(true);
    ui->showstep->setEnabled(true);
    InsertLexicalOutput("");
    InsertGrammarOutput("");
}


void MainWindow::on_btnClear_clicked()
{
    s = "";
    InputEnable = true;

    this->setFixedSize(WIDTH, HEIGHT);

    ui->analysis->setEnabled(false);
    ui->showstep->setEnabled(false);
    ui->input->setText(s);
    ui->result->setText("");
    ui->z_op->clear();
    ui->z_yufa->clear();
    ui->z_shuzi->clear();
    Index = 0;
}



void MainWindow::on_btnBack_clicked()
{

    s=s.mid(0,s.size()-1);
    ui->input->setText(s);
}




void MainWindow::on_analysis_clicked()
{
    //resize(2000, 1200);
    this->setFixedSize(ALLWIDTH, ALLHEIGHT);
}

void MainWindow::on_dot_clicked()
{
    digitBtn('.');
}

void MainWindow::on_btnLeft_clicked()
{
    digitBtn('(');
}

void MainWindow::on_btnRight_clicked()
{
    digitBtn(')');
}

void MainWindow::on_pushButton_8_clicked()
{
    this->setFixedSize(WIDTH, HEIGHT);

    //ui->analysis->setEnabled(false);

}

// 动态过程
void MainWindow::on_pushButton_9_clicked()
{

}

void MainWindow::PrintStack(string yufa, string shuzi, string op, string next)
{
    cout <<"414 \t" << yufa<<endl;

    vector<string> vvv;
    vector<string> vec = analyse(yufa, vvv);//分开布尔表达式
    ui->z_yufa->clear();

    for(int i = vec.size()-1; i >= 0;i--)
    {
        cout << vec[i];

        ui->z_yufa->append(QString::fromStdString(vec[i]));

    }
    cout << endl;
    ui->z_shuzi->clear();


    for(int i = 0; i < shuzi.length(); i++)
    {

                int st = i;

                if(IsDigit(shuzi[i]))
                {

                 while(IsDigit(shuzi[i]))
                 {
                     if(i < shuzi.length())
                    i++;
                 }
                 ui->z_shuzi->append(QString::fromStdString(shuzi.substr(st, i-st)));

                }

            else
               ui->z_shuzi->append(QString::fromStdString(shuzi.substr(i, 1)));



    }
    cout <<endl;

    ui->z_op->clear();


         ui->z_op->append(QString::fromStdString("下一步: "+op));

}









void MainWindow::on_showstep_clicked()
{

    this->setFixedSize(SHOWWIDTH, SHOWHEIGHT);

    vector<string> marker0 = this->ana.marker;
    vector<string> inputstring0 = this->ana.inputstring;
    vector<string> oper0 = this->ana.oper;

    if(Index < marker0.size())
    {
            cout << "Index = " << Index<<endl;
            string ii = "";
            PrintStack(inputstring0[Index], marker0[Index], oper0[Index], Index == marker0.size()-1 ? "":oper0[Index+1]);
            Index++;
    }
}

void MainWindow::on_backinit_clicked()
{
    this->setFixedSize(WIDTH, HEIGHT);
    Index = 0;
    ui->z_op->clear();
    ui->z_yufa->clear();
    ui->z_shuzi->clear();
}


