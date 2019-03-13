#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include "wen.h"
#define TIME 22000

using namespace std;
int num=0;
extern QTimer *timer;
extern QTimer *tim;
int circle=1,total,sum=0;  //ciecle is current number of exercise,total is the total number of exercises,sum is the total score
extern int *score;
extern int num_ques;
extern fanhui expResult[10000];
extern canshu sample;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pushButton_4->setVisible(false);
    ui->pushButton_5->setVisible(false);//at the beginning,hide "xia yi ti" and "ti jiao" button
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()//OK Button
{
    QString a=tr("叮咚！题目已生成:");
    QString b=ui->lineEdit_2->text();
    QString str=a+b;
    QString exe;
    QString truestr="1 ";
    QString falsestr="0 ";

    bool ok;
    int sign;
    total=b.toInt(&ok,10); //将字符串转换为int整形数据

    string c_str;
    c_str=ui->lineEdit_2->text().toStdString();
    sample.num_ques=c_str;

    ok=ui->checkBox_6->checkState();//是否支持加法运算
    qDebug()<<ok;
    if(ok==true)
        sample.is_add=truestr.toStdString();
    else
        sample.is_add=falsestr.toStdString();
    QString qstr;
    qstr = QString::fromStdString(sample.is_add);
    qDebug()<<qstr;
    /*
    ok=ui->checkBox_7->checkState();//是否支持减法运算
    if(ok==true)
        sample.is_sub="1 ";
    else
        sample.is_sub="0 ";
    ok=ui->checkBox_8->checkState();//是否支持乘法运算
    if(ok==true)
        sample.is_mul="1 ";
    else
        sample.is_mul="0 ";
    ok=ui->checkBox_9->checkState();//是否支持除法运算
    if(ok==true)
        sample.is_div="1 ";
    else
        sample.is_div="0 ";
    /*ok=ui->checkBox_3->checkState();//是否支持小数运算
    if(ok==true)
        sample.is_decimal="1 ";
    else
        sample.is_decimal="0 ";
    ok=ui->checkBox_4->checkState();//是否支持真分数运算
    if(ok==true)
        sample.is_real="1 ";
    else
        sample.is_real="0 ";*/
    /*ok=ui->checkBox_5->checkState();//是否支持乘方运算
    if(ok==true)
        sample.is_power="1 ";
    else
        sample.is_power="0 ";*/

    /*c_str=ui->lineEdit->text().toStdString();//操作数的个数
    sample.num_op=c_str;*/
    c_str=ui->lineEdit_3->text().toStdString();//操作数的最大值
    sample.scalemax_op=c_str;
    /*c_str=ui->lineEdit_5->text().toStdString();//结果精度
    sample.num_float=c_str;
    c_str=ui->lineEdit_6->text().toStdString();//结果最大值
    sample.result_max=c_str;*/
//    QString qstr;
    qstr = QString::fromStdString(sample.is_add);
    qDebug()<<qstr;

    sign=Setting();
    if(sign==-1)
    {
        QMessageBox::warning(this, tr("提示"),tr("非法输入"));
        ui->lineEdit_2->clear();    //clear lineEdit_2, make users fill in the number of exercise again
        return;
    }//how to deal with error input?

    score=(int *)malloc(sizeof(int)*total);  //allot saving spaces
    if(total==1)
        ui->pushButton_4->setEnabled(false);//if there is one exercise,disenable "xia yi ti" button
    for(int i=0;i<total;i++)
        score[i]=0;

    exe=QString::fromStdString(expResult[circle-1].express);
    ui->label_3->setText(exe);
    ui->lineEdit_2->clear();   //clear lineEdit_2, and users put the answer in it
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);  //make "OK" and "Cancel" buttons unvisible
    ui->pushButton_4->setVisible(true);
    ui->pushButton_5->setVisible(true);   //make "xia yi ti" and "ti jiao" buttons visible
    QMessageBox::information(this, tr("提示"), str);//tell users the exercise have been placed

    timer = new QTimer(this);
    tim = new  QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(showTimelimit()));
    connect(tim, SIGNAL(timeout()), this, SLOT(on_pushButton_4_clicked()));

    timer->start(1000);
    tim->start(TIME);
    if(total==1)
    {
        disconnect(tim, SIGNAL(timeout()), this, SLOT(on_pushButton_4_clicked()));
        connect(tim, SIGNAL(timeout()), this, SLOT(on_pushButton_5_clicked()));
    }

    if(num>=20)
    {
        timer->stop();
 //       tim->stop();
    }
}

void Widget::on_pushButton_2_clicked()//Cancel
{
    ui->lineEdit_2->clear();    //clear lineEdit_2, make users fill in the number of exercise again
}

void Widget::on_pushButton_3_clicked()//Reset
{
    timerinit();
    timinit();

    ui->pushButton->setVisible(true);
    ui->pushButton_2->setVisible(true);//make "OK" and "Cancel" buttons visible
    ui->pushButton_4->setVisible(false);
    ui->pushButton_5->setVisible(false);//make "xia yi ti" and "ti jiao" buttons unvisible
    ui->lineEdit_2->clear();   //clear lineEdit_2, make users fill in the number of exercise again
    ui->label_3->setText(tr("请在下行中输入题目总数"));
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_5->setEnabled(true);
    ui->label_2->clear();
    circle=1;
    sum=0;
    if(score!=NULL)
    {
        free(score);
        score=NULL;
    }
}

void Widget::on_pushButton_4_clicked()//下一题按钮
{
    timerinit();
    timinit();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTimelimit()));
    tim = new QTimer(this);
    connect(tim, SIGNAL(timeout()), this, SLOT(on_pushButton_4_clicked()));

    timer->start(1000);
    tim->start(TIME);

    if(num>=20)
    {
        timer->stop();
//        tim->stop();
    }

    circle++;
    QString c="题目";
    QString d=QString::number(circle, 10);
    QString str1;
    QString e,exe;
    string f;

    if(circle<=total)
    {
        if(circle==total)
        {
            ui->pushButton_4->setEnabled(false);
            disconnect(timer, SIGNAL(timeout()), this, SLOT(showTimelimit()));
            disconnect(tim, SIGNAL(timeout()), this, SLOT(on_pushButton_4_clicked()));
            connect(timer, SIGNAL(timeout()), this, SLOT(showTimelimit()));
            connect(tim, SIGNAL(timeout()), this, SLOT(on_pushButton_5_clicked()));
        }
        exe= QString::fromStdString(expResult[circle-1].express);
        str1=c+d+":"+exe;
        ui->label_3->setText(str1);
        e=ui->lineEdit_2->text();
        f=e.toStdString();
        if(f.compare(expResult[circle-2].result)==0)
            score[circle-2]=1;
        else
            score[circle-2]=0;    //judge whether the answer is correct
        ui->lineEdit_2->clear();
    }
}

void Widget::on_pushButton_5_clicked()//hand in button
{
    timerinit();
    timinit();

    QString a,b,e,str;
    int i;
    string f;
    e=ui->lineEdit_2->text();
    f=e.toStdString();
    if(f.compare(expResult[circle-1].result)==0)
        score[circle-1]=1;
    else
        score[circle-1]=0;    //judge whether the answer is correct
    ui->lineEdit_2->clear();
    for(i=0;i<total;i++)
    {
        sum+=score[i];
    }
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->label_3->clear();
    ui->label_2->clear();
    a=tr("提交成功！您的成绩为:");
    b=QString::number(sum, 10);
    str=a+b;
    QMessageBox::information(this, tr("提示"), str);  //give the score
}

void Widget::showTimelimit(){
    QString a;
    a=QString::number(20-num,10);
    ui->label_2->setText(a);
    if(num>=20)
    {
        timer->stop();
        return;
    }
    num++;
}

void Widget::timerinit(){
    if(timer!=NULL){
        timer->stop();
        delete timer;
        timer=NULL;
    }
    num=0;
//    return;
}

void Widget::timinit(){
    if(tim!=NULL){
        tim->stop();
        delete tim;
        tim=NULL;
    }
    num=0;
}

