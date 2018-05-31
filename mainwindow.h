#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_bnt_zero_clicked();

    void on_btn_one_clicked();

    void on_btn_two_clicked();

    void on_btn_three_clicked();

    void on_btn_four_clicked();

    void on_btn_five_clicked();

    void on_btn_six_clicked();

    void on_btn_seven_clicked();

    void on_btn_eight_clicked();

    void on_btn_nine_clicked();

    void on_btn_colon_clicked();

    void on_btn_plus_clicked();

    void on_btn_minus_clicked();

    void on_btn_mul_clicked();

    void on_btn_div_clicked();

    void on_btn_braket_open_clicked();

    void on_btn_braket_close_clicked();

    void on_btn_clear_clicked();

    void on_btn_copy_clicked();

    void on_btn_enter_clicked();

    void on_input_returnPressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
