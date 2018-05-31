#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calc.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_enter_clicked()
{
    ui->result->setText(calculate_wrapper(ui->input->text().toStdString()));
}

void MainWindow::on_input_returnPressed()
{
    ui->result->setText(calculate_wrapper(ui->input->text().toStdString()));
}

void MainWindow::on_bnt_zero_clicked()
{
    ui->input->setText(ui->input->text()+'0');
}

void MainWindow::on_btn_one_clicked()
{
    ui->input->setText(ui->input->text()+'1');
}

void MainWindow::on_btn_two_clicked()
{
    ui->input->setText(ui->input->text()+'2');
}

void MainWindow::on_btn_three_clicked()
{
    ui->input->setText(ui->input->text()+'3');
}

void MainWindow::on_btn_four_clicked()
{
    ui->input->setText(ui->input->text()+'4');
}

void MainWindow::on_btn_five_clicked()
{
    ui->input->setText(ui->input->text()+'5');
}

void MainWindow::on_btn_six_clicked()
{
    ui->input->setText(ui->input->text()+'6');
}

void MainWindow::on_btn_seven_clicked()
{
    ui->input->setText(ui->input->text()+'7');
}

void MainWindow::on_btn_eight_clicked()
{
    ui->input->setText(ui->input->text()+'8');
}

void MainWindow::on_btn_nine_clicked()
{
    ui->input->setText(ui->input->text()+'9');
}

void MainWindow::on_btn_colon_clicked()
{
    ui->input->setText(ui->input->text()+',');
}

void MainWindow::on_btn_plus_clicked()
{
    ui->input->setText(ui->input->text()+'+');
}

void MainWindow::on_btn_minus_clicked()
{
    ui->input->setText(ui->input->text()+'-');
}

void MainWindow::on_btn_mul_clicked()
{
    ui->input->setText(ui->input->text()+'*');
}

void MainWindow::on_btn_div_clicked()
{
    ui->input->setText(ui->input->text()+'/');
}

void MainWindow::on_btn_braket_open_clicked()
{
    ui->input->setText(ui->input->text()+'(');
}

void MainWindow::on_btn_braket_close_clicked()
{
    ui->input->setText(ui->input->text()+')');
}

void MainWindow::on_btn_clear_clicked()
{
    ui->input->setText("");
}

void MainWindow::on_btn_copy_clicked()
{
    ui->input->setText(ui->result->text());
    ui->input->setFocus();
    ui->input->selectAll();
}
