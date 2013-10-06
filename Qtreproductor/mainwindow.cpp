#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gstrep = new gstmp3();
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
