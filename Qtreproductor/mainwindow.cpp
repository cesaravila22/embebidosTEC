#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gstrep = new gstmp3();
    gstudp = new gstserver();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_pushButton_clicked()
{
    gstrep->reproducir(ui->lineEdit->text());
}

void MainWindow::on_pushButton_2_clicked()
{
    gstrep->detener();
}

void MainWindow::on_pushButton_3_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_4_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Look for music"),"/home/cesar/Desktop",tr("MP3 file (*.mp3)"));
    ui->lineEdit->setText(filename);
}

void MainWindow::on_pushButton_5_clicked()
{
    gstudp->reproducir(ui->lineEdit->text(),ui->lineEdit_2->text());
}

void MainWindow::on_pushButton_6_clicked()
{
    gstudp->detener();
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->lineEdit_2->insert("0");
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->lineEdit_2->insert("1");
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->lineEdit_2->insert("2");
}

void MainWindow::on_pushButton_16_clicked()
{
    ui->lineEdit_2->insert("3");
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->lineEdit_2->insert("4");
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->lineEdit_2->insert("5");
}

void MainWindow::on_pushButton_12_clicked()
{
    ui->lineEdit_2->insert("6");
}

void MainWindow::on_pushButton_17_clicked()
{
    ui->lineEdit_2->insert("7");
}

void MainWindow::on_pushButton_13_clicked()
{
    ui->lineEdit_2->insert("8");
}

void MainWindow::on_pushButton_14_clicked()
{
    ui->lineEdit_2->insert("9");
}

void MainWindow::on_pushButton_15_clicked()
{
    ui->lineEdit_2->insert(".");
}

void MainWindow::on_pushButton_18_clicked()
{
    ui->lineEdit_2->setText("");
}
