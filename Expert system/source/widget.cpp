#include "widget.h"
#include "ui_widget.h"
#include "program.h"

Question Q;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::NQ () {
    Q = NewQuestion();
    ui->QuestionText->setText(Q.text);
    ui->QuestionText->setAlignment(Qt::AlignCenter);
    ui->Answer_1->setText (Q.answers [0].text);
    ui->Answer_2->setText (Q.answers [1].text);
    if (Q.answers.size() == 3) {
        ui->Answer_3->setText (Q.answers [2].text);
        ui->Answer_3->setVisible(true);
    }
    else {
        ui->Answer_3->setText ("");
        ui->Answer_3->setVisible(false);
    }
}

void Widget::NQ (int ans) {
    char c = AddAnswer (ans - 1);
    if (c == 'n') {
        NQ ();
    }
    else {
        ui->Start->setVisible (false);
        ui->Question->setVisible (false);
        ui->End->setVisible (true);

        if (c == 'e') {
            ui->Recommendation->setText ("К сожалению, в данный момент мы не можем вам ничего порекомендовать.");
        }
        else if (c == 'w') {
            ui->Recommendation->setText ("Мы рекомендуем вам не получать образование.");
        }
        else if (c == 'c') {
            ui->Recommendation->setText ("Мы рекомендуем вам получать среднее специальное образование.");
        }
        else if (c == 'u') {
            ui->Recommendation->setText ("Мы рекомендуем вам получать высшее образование");
        }
        else {
            qDebug () << "WTF?!" << c;
        }
        ui->Recommendation->setAlignment(Qt::AlignCenter);
    }
}

void Widget::on_startButton_clicked()
{
    ui->Start->setVisible(false);
    ui->Question->setVisible(true);
    ui->End->setVisible(false);
    Assignment();
    NQ ();

}

void Widget::on_Restart_clicked()
{
    ui->Start->setVisible(false);
    ui->Question->setVisible(true);
    ui->End->setVisible(false);
    newAssigment();
    NQ ();
}

void Widget::on_Answer_1_clicked()
{
    NQ (1);
}

void Widget::on_Answer_2_clicked()
{
    NQ (2);
}

void Widget::on_Answer_3_clicked()
{
    NQ (3);
}
