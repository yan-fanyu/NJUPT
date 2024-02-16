#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_buttonRead_clicked();



    void on_buttonBox_accepted();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_buttonBox_3_accepted();

    void on_buttonBox_2_accepted();

    void on_buttonBox_4_accepted();

    void on_pushButton_3_clicked();


    void deleteOnelineInFile(int, QString &);
    void DeleteOneline(int, QString &);

    void creatRandRecords(QString, QString );

    void on_pushButton_4_clicked();


    void emptyData(QString, QString, QString);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

