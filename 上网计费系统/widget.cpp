#include "widget.h"
#include "ui_widget.h"
#include<QFileDialog>
#include<QFile>
#include<QDebug>
#include<QTextStream>
#include <QPushButton>
#include <qinputdialog.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("添加客户"));//按钮命名
    this->ui->buttonBox_2->button(QDialogButtonBox::Ok)->setText(tr("删除上网记录"));//按钮命名
    this->ui->buttonBox_3->button(QDialogButtonBox::Ok)->setText(tr("添加上网记录"));//按钮命名
    this->ui->buttonBox_4->button(QDialogButtonBox::Ok)->setText(tr("删除客户"));//按钮命名
}


Widget::~Widget()
{
    delete ui;
}


//读取客户列表
void Widget::on_buttonRead_clicked()
{
    QFile file("D:\\用户基本资料.txt");
    bool bRet  =file.open(QIODevice::ReadOnly);
    if(bRet == true)
    {
        int i= 0;

        QString ab;
        //QByteArray array ;
        while(file.atEnd() == false)
        {
            if(i<10)
            {
               // ab= ab+"("+QString::number(i++)+ ")     ";
            }
           else if(i<100)
            {
                ab= ab+"("+QString::number(i++)+ ")    ";
            }
            else if(i<1000)
            {
                ab= ab+"("+QString::number(i++)+ ")   ";
            }
           ab += file.readLine();

        }

        ui->textEdit->setText(ab);
    }
    file.close();

}

//读取记录列表
void Widget::on_pushButton_clicked()
{
    QFile file("D:\\线上使用时间.txt");
    bool bRet  =file.open(QIODevice::ReadOnly);
    if(bRet == true)
    {
        int i= 0;

        QString ab;
        while(file.atEnd() == false)
        {
            if(i<10)
            {
                ab= ab+"("+QString::number(i++)+ ")     ";
            }
           else if(i<100)
            {
                ab= ab+"("+QString::number(i++)+ ")    ";
            }
            else if(i<1000)
            {
                ab= ab+"("+QString::number(i++)+ ")   ";
            }
           ab += file.readLine();

        }

        ui->textEdit->setText(ab);
    }
    file.close();
}

//读取账单列表
void Widget::on_pushButton_2_clicked()
{
    QFile file("D:\\用户报表.txt");
    bool bRet  =file.open(QIODevice::ReadOnly);
    if(bRet == true)
    {
        int i= 0;

        QString ab;
        while(file.atEnd() == false)
        {
            if(i<10)
            {
                ab= ab+"("+QString::number(i++)+ ")     ";
            }
           else if(i<100)
            {
                ab= ab+"("+QString::number(i++)+ ")    ";
            }
            else if(i<1000)
            {
                ab= ab+"("+QString::number(i++)+ ")   ";
            }
           ab += file.readLine();

        }

        ui->textEdit->setText(ab);
    }
    file.close();
}




//添加客户
void Widget::on_buttonBox_accepted()
{

    bool ok;

    QString text = QInputDialog::getText(this, tr("添加客户"),tr("请输入用户名 ID 计费方式"), QLineEdit::Normal,nullptr, &ok);
    if (ok && !text.isEmpty())
    {

        QFile file("D:\\用户基本资料.txt");
        if (file.open(QIODevice::WriteOnly|QIODevice::Append)) //QIODevice::ReadWrite支持读写
        {
         QTextStream stream(&file);

         stream << text << endl;
        }
        file.close();
    }
}


//添加上网记录
void Widget::on_buttonBox_3_accepted()
{
    bool ok;

    QString text = QInputDialog::getText(this, tr("添加上网记录"),tr("请输入用户ID 起始时间 终止时间(空格分隔)"), QLineEdit::Normal,nullptr, &ok);
    if (ok && !text.isEmpty())
    {

        QFile file("D:\\线上使用时间.txt");
        if (file.open(QIODevice::WriteOnly|QIODevice::Append)) //QIODevice::ReadWrite支持读写
        {
         QTextStream stream(&file);

         stream << text << endl;
        }
        file.close();
    }
}

//5删除一条上网记录
void Widget::on_buttonBox_2_accepted()
{
    bool ok;

    QString text = QInputDialog::getText(this, tr("删除记录"),tr("请输入要删除的上网记录编号"), QLineEdit::Normal,nullptr, &ok);
    if (ok && !text.isEmpty())
    {

        QString filename="D:\\线上使用时间.txt";

        int index = text.toInt();

        deleteOnelineInFile(index,filename);

    }
}


//删除客户
void Widget::on_buttonBox_4_accepted()
{
    bool ok;

    QString text = QInputDialog::getText(this, tr("删除客户"),tr("输入要删除的用户序号"), QLineEdit::Normal,nullptr, &ok);
    if (ok && !text.isEmpty())
    {

        QString filename="D:\\用户基本资料.txt";

        int index = text.toInt();

        deleteOnelineInFile(index,filename);


    }
}


//如果是5行，nNum最大为4
void Widget::DeleteOneline(int nNum, QString &strall)//
{
    int nLine=0;
    int Index=0;
    //算出行数nLine
    while(Index!=-1)
    {
        Index=strall.indexOf('\n',Index+1);
        nLine++;
    }


    if(nNum==0)
    {
        int nIndex=strall.indexOf('\n');
        strall.remove(0,nIndex+1);
    }
    else
    {
        int nTemp=nNum;
        int nIndex=0,nIndex2=0;
        while(nTemp--)
        {
            //
            nIndex=strall.indexOf('\n',nIndex+1);//这里会更新nIndex
            if(nIndex!=-1)//说明是有效的
            {
                nIndex2=strall.indexOf('\n',nIndex+1);
            }
        }
        //删除的行不是最后一行（从nIndex+1这个位置起nIndex2-nIndex个字符全部抹去）
        if(nNum<nLine-1)
        {
            strall.remove(nIndex+1, nIndex2-nIndex);//不用减一
        }
        //删除的是最后一行（从nIndex起始len-nIndex个字符全抹去）
        //不能从nIndex+1处开始，
        else if(nNum==nLine-1)
        {
            int len=strall.length();
            strall.remove(nIndex,len-nIndex);
        }
        else
        {

        }

    }
}

//删除文件中的一行
void Widget::deleteOnelineInFile(int nNumLine, QString &filename)
{
    QString strall;
    QFile readfile(filename);
    if(readfile.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&readfile);
        strall=stream.readAll();
    }
    readfile.close();
    DeleteOneline(nNumLine, strall);

    QFile writefile(filename);
    if(writefile.open(QIODevice::WriteOnly))
    {
        QTextStream wrtstream(&writefile);
        wrtstream<<strall;
    }
    writefile.close();
}

void Widget::creatRandRecords(QString customer, QString record)
{
     emptyData("D:\\用户基本资料.txt","D:\\线上使用时间.txt","D:\\用户报表.txt");
   // QString::number(i++)

    srand((unsigned int)time(nullptr));
    int year, month, day, hour, minute, second, b = 0, year2, month2, day2, hour2, minute2, second2;
    QString k[15]{ "0001","0002","0003","0004","0005","0006","0007","0008","0009","0010","0011","0012","0013","0014","0015" };
    QString month1, day1, hour1, minute1, second1, begin, end, name, id, method;
    //ofstream ofile1, ofile2;
    //bool flag = 1;


    for (int s = 0; s < 15; s++)
    {
        QString n = "0";
        int f = rand() % 5;
        method = QString::number(f);
        QFile file(customer);
        if (file.open(QIODevice::WriteOnly|QIODevice::Append)) //QIODevice::ReadWrite支持读写
        {
         QTextStream stream(&file);

         stream << n << " " << k[s] << " " << method << endl;
        }
        file.close();


    }


    for (int i = 30; i > 0; )
    {
        int a = rand() % 15;
        year = rand() % 10 + 2010;

        month = rand() % 12 + 1;
        if (month - 10 < 0)
            month1 = QString::number(b) + QString::number(month);
        else
            month1 = QString::number(month);

        day = rand() % 25 + 1;

        if (day - 10 < 0)
            day1 = QString::number(b) + QString::number(day);
        else
            day1 = QString::number(day);

        hour = rand() % 24;
        if (hour - 10 < 0)
            hour1 = QString::number(b) + QString::number(hour);
        else
            hour1 = QString::number(hour);

        minute = rand() % 60;
        if (minute - 10 < 0)
            minute1 = QString::number(b) + QString::number(minute);
        else
            minute1 = QString::number(minute);

        second = rand() % 60;
        if (second - 10 < 0)
            second1 = QString::number(b) + QString::number(second);
        else
            second1 = QString::number(second);

        begin = QString::number(year) + month1 + day1 + hour1 + minute1 + second1;

        year2 = year + rand() % 3;

        month2 = rand() % 12 + 1;
        if (month > month2)
            continue;
        if (month2 - 10 < 0)
            month1 = QString::number(b) + QString::number(month2);
        else
            month1 = QString::number(month2);
        day2 = day + rand() % 5 + 1;
        if (day2 - 10 < 0)
            day1 = QString::number(b) + QString::number(day2);
        else
            day1 = QString::number(day2);
        if (day > day2)
            continue;
        hour2 = rand() % 24;
        if (hour2 - 10 < 0)
            hour1 = QString::number(b) + QString::number(hour2);
        else
            hour1 = QString::number(hour2);
        if (hour > hour2)
            continue;
        minute2 = rand() % 60;
        if (minute2 - 10 < 0)
            minute1 = QString::number(b) + QString::number(minute2);
        else
            minute1 = QString::number(minute2);
        if (minute > minute2)
            continue;
        second2 = rand() % 60;
        if (second2 - 10 < 0)
            second1 = QString::number(b) + QString::number(second2);
        else
            second1 = QString::number(second2);
        if (second >= second2)
            continue;

        end = QString::number(year2) + month1 + day1 + hour1 + minute1 + second1;

        QFile file(record);
        if (file.open(QIODevice::WriteOnly|QIODevice::Append)) //QIODevice::ReadWrite支持读写
        {
         QTextStream stream(&file);

         stream << k[a] << " " << begin << " " << end << endl;
        }
        file.close();



        i--;
    }
}

//随机生成
void Widget::on_pushButton_3_clicked()
{
    creatRandRecords("D:\\用户基本资料.txt","D:\\线上使用时间.txt");
}


//清空文件
void Widget::emptyData(QString customer, QString record, QString tabel)
{
    // fileName 为文件名
    QFile file(customer);

    file.open(QFile::WriteOnly|QFile::Truncate);

    file.close();

    QFile file2(record);

    file2.open(QFile::WriteOnly|QFile::Truncate);

    file2.close();

    QFile file3(tabel);

    file3.open(QFile::WriteOnly|QFile::Truncate);

    file3.close();


}

//清空文件
void Widget::on_pushButton_4_clicked()
{
    emptyData("D:\\用户基本资料.txt","D:\\线上使用时间.txt","D:\\用户报表.txt");
}
