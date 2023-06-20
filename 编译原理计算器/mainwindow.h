#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "analyselr.h"
#include <QKeyEvent>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:




    void on_insert_clicked();

    void on_add_clicked();

private:
    Ui::MainWindow *ui;
    void Init();


public:
    AnalyseLR ana;

    void InsertLexicalOutput(QString);
    void InsertGrammarOutput(QString);


    void digitBtn(char ch);


    /**词法分析**/
    vector<string> analyse00(string expression, vector<string>& v);


private slots:

    void on_btn0_clicked();
    void on_btn1_clicked();
    void on_btn2_clicked();
    void on_btn3_clicked();
    void on_btn4_clicked();
    void on_btn5_clicked();
    void on_btn6_clicked();
    void on_btn7_clicked();
    void on_btn8_clicked();
    void on_btn9_clicked();

   void keyPressEvent(QKeyEvent *event);


    void on_btnAdd_clicked();
    void on_btnSub_clicked();
    void on_btnMuti_clicked();
    void on_btnDivi_clicked();

    void on_btnClear_clicked(); // 删除



    void on_btnBack_clicked();
    void on_btnEqual_clicked(); // 等于
    void on_analysis_clicked();

    void on_btnLeft_clicked();

    void on_btnRight_clicked();

    //void on_pushButton_8_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void PrintStack(string, string, string, string next = "");



    void on_showstep_clicked();

    void on_backinit_clicked();

    void on_dot_clicked();

private:


};
#endif // MAINWINDOW_H
