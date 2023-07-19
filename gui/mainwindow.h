#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <credit.h>
#include <deposit.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  bool isXPressed;
  Deposit deposit;
  Credit credit;

 private slots:

  void digit_pressed();
  void on_pushButton_AC_clicked();
  void operation_pressed();
  void on_pushButton_point_clicked();
  bool if_last_is_digit();
  bool lastNumberHasPoint();
  void bracket_pressed();
  void on_pushButton_plus_minus_clicked();
  void trigonometry();
  void on_pushButton_equal_clicked();
  void show_Error();
  void on_pushButton_x_clicked();
  void graph_draw(const QString &func);
  void on_pushButton_credit_clicked();
  void on_pushButton_deposit_clicked();
};
#endif  // MAINWINDOW_H
