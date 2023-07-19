#ifndef CREDIT_H
#define CREDIT_H

#include <result_credit.h>

#include <QMessageBox>
#include <QWidget>

namespace Ui {
class Credit;
}

class Credit : public QWidget {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 private slots:
  void on_pushButton_calc_clicked();

 private:
  Ui::Credit *ui;
  Result_credit *credit;
};

#endif  // CREDIT_H
