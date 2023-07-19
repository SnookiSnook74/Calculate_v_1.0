#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "parser.h"
#include "qcustomplot.h"
#include "stack.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), isXPressed(false) {
  ui->setupUi(this);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digit_pressed()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(operation_pressed()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(operation_pressed()));
  connect(ui->pushButton_multy, SIGNAL(clicked()), this,
          SLOT(operation_pressed()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this,
          SLOT(operation_pressed()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this,
          SLOT(operation_pressed()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(operation_pressed()));
  connect(ui->pushButton_left_bracket, SIGNAL(clicked()), this,
          SLOT(bracket_pressed()));
  connect(ui->pushButton_right_bracket, SIGNAL(clicked()), this,
          SLOT(bracket_pressed()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(trigonometry()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(trigonometry()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(trigonometry()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(trigonometry()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(trigonometry()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(trigonometry()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(trigonometry()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(trigonometry()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(trigonometry()));
}

MainWindow::~MainWindow() { delete ui; }

// Этот метод вызывается, когда одна из цифровых кнопок (0-9) нажата.
void MainWindow::digit_pressed() {
  QPushButton *button = (QPushButton *)sender();
  QString currentText = ui->result->text();

  if (currentText == "0" && !button->text().startsWith('.')) {
    currentText.clear();
  }

  QString newText = currentText + button->text();

  QString lastNumber = "";
  for (int i = newText.length() - 1; i >= 0; --i) {
    if (newText[i].isDigit() || newText[i] == '.') {
      lastNumber.prepend(newText[i]);
    } else {
      break;
    }
  }
  if (lastNumber.toDouble() > 100000000) {
    return;
  }
  // Проверка на количество символов после точки
  int dotPos = lastNumber.indexOf('.');
  if (dotPos != -1 && (lastNumber.length() - dotPos - 1) > 5) {
    return;
  }

  currentText.append(button->text());
  ui->result->setText(currentText);
}

void MainWindow::operation_pressed() {
  QPushButton *button = (QPushButton *)sender();
  QString currentText = ui->result->text();
  QChar lastChar = currentText.isEmpty()
                       ? QChar()
                       : currentText.at(currentText.length() - 1);

  if (currentText.isEmpty() ||
      (!lastChar.isDigit() && lastChar != ')' && lastChar != 'x')) {
    if (button->text() == "^" || button->text() == "%" ||
        button->text() == "*" || button->text() == "/")
      return;
    else if ((button->text() == "-" || button->text() == "+") &&
             lastChar == button->text())
      return;  // Если текущий символ "-" или "+" и последний символ также "-",
               // или "+", не дайте пользователю ввести еще один "-", или "+"
  }

  currentText.append(button->text());
  ui->result->setText(currentText);
}

void MainWindow::on_pushButton_AC_clicked() { ui->result->setText("0"); }

void MainWindow::on_pushButton_point_clicked() {
  QString currentString = ui->result->text();
  if (if_last_is_digit() && !lastNumberHasPoint()) {
    ui->result->setText(currentString + '.');
  }
}

// Эта функция проверяет, является ли последний символ в тексте цифрой.
bool MainWindow::if_last_is_digit() {
  QString currentText = ui->result->text();
  if (currentText.isEmpty() || !currentText.back().isDigit()) {
    return false;
  }
  return true;
}

bool MainWindow::lastNumberHasPoint() {
  QString currentText = ui->result->text();
  // Находит индекс последнего оператора
  int indexOfLastOperator =
      std::max({currentText.lastIndexOf('+'), currentText.lastIndexOf('-'),
                currentText.lastIndexOf('*'), currentText.lastIndexOf('/'),
                currentText.lastIndexOf('%')});
  // Извлекаем подстроку
  QString lastNumber = currentText.mid(indexOfLastOperator + 1);
  return lastNumber.contains('.');
}

void MainWindow::bracket_pressed() {
  QPushButton *button = (QPushButton *)sender();
  QString currentText = ui->result->text();
  if (currentText == "0") {
    currentText.clear();
  }
  currentText.append(button->text());
  ui->result->setText(currentText);
}

// Меняет знак последнего числа в тексте.
void MainWindow::on_pushButton_plus_minus_clicked() {
  QString currentText = ui->result->text();
  int indexOfLastOperator =
      std::max({currentText.lastIndexOf('+'), currentText.lastIndexOf('*'),
                currentText.lastIndexOf('/'), currentText.lastIndexOf('%'),
                currentText.lastIndexOf('^'), currentText.lastIndexOf('('),
                currentText.lastIndexOf(')')});
  QString lastNumber = currentText.mid(indexOfLastOperator + 1);
  if (!lastNumber.isEmpty()) {
    double number = lastNumber.toDouble();
    number *= -1;
    currentText = currentText.left(indexOfLastOperator + 1) +
                  QString::number(number, 'g', 15);
    ui->result->setText(currentText);
  }
}

void MainWindow::trigonometry() {
  QPushButton *button = (QPushButton *)sender();
  QString currentText = ui->result->text();

  if (currentText == "0") {
    currentText.clear();
  }

  // Проверяем, является ли последний символ цифрой или закрывающей скобкой
  QChar lastChar = currentText.isEmpty()
                       ? QChar()
                       : currentText.at(currentText.length() - 1);
  if (lastChar.isDigit() || lastChar == ')') {
    // Если последний символ - цифра или закрывающая скобка, добавляем знак
    // умножения
    currentText.append("*");
  }

  currentText.append(button->text() + "(");
  ui->result->setText(currentText);
}

void MainWindow::show_Error() {
  QMessageBox msgBox;
  msgBox.setWindowTitle("Error");
  msgBox.setText("Invalid input!");
  msgBox.setIconPixmap(QPixmap("./error.png"));
  msgBox.exec();

  ui->result->setText("0");
}

void MainWindow::on_pushButton_x_clicked() {
  isXPressed = true;
  QString currentText = ui->result->text();
  QPushButton *button = (QPushButton *)sender();
  QChar lastChar = currentText.isEmpty()
                       ? QChar()
                       : currentText.at(currentText.length() - 1);
  if (lastChar == 'x') {
    return;
  }
  if (lastChar.isDigit() || lastChar == ')') {
    // Если последний символ - цифра или закрывающая скобка, добавляем знак
    // умножения, если текущий текст не равен "0"
    if (currentText != "0") {
      currentText.append("*");
    }
  }
  if (currentText == "0") {
    currentText =
        button->text();  // Если текущий текст равен "0", заменяем его на "x"
  } else {
    currentText.append(button->text());
  }

  ui->result->setText(currentText);
}

void MainWindow::graph_draw(const QString &func) {
  // Получаем границы по осям x и y из пользовательского интерфейса
  double xMax = ui->Xmax->text().toDouble();
  double xMin = ui->Xmin->text().toDouble();
  double yMax = ui->Ymax->text().toDouble();
  double yMin = ui->Ymin->text().toDouble();

  if ((xMax > 1000000) || (xMin < -1000000) || (yMax > 1000000) ||
      (yMin < -1000000)) {
    show_Error();
    return;
  }
  const int numPoints =
      801;  // Количество точек, которые будут отрисованы на графике
  // Инициализируем векторы для хранения значений по осям x и y
  QVector<double> x(numPoints), y(numPoints);
  // Вычисляем шаг для оси x
  double step = (xMax - xMin) / numPoints;
  // Вычисляются значения для каждой точки на графике
  for (int i = 0; i < numPoints; ++i) {
    double xValue = xMin + i * step;  // Вычисляем значение x
    x[i] = xValue;
    QString expr = func;
    // Заменяем "x" в нашем выражении на текущее значение xValue
    expr.replace("x", QString::number(xValue, 'g', 7));
    QByteArray ba = expr.toLatin1();
    char *line = ba.data();
    // Вычисляем значение y для каждого x с помощью нашей функции
    double yValue = calculate(line);
    // Устанавливаем порог, чтобы скрыть асимптоты
    if (yValue > 10 || yValue < -10) {
      yValue = qQNaN();  // Ставим значение "не число", чтобы оно не
                         // отображалось на графике
    }
    y[i] = yValue;
  }
  // Создаем график и присваиваем ему данные:
  ui->graph->addGraph();
  ui->graph->graph(0)->setData(x, y);
  // Устанавливаем названия осей:
  ui->graph->xAxis->setLabel("x");
  ui->graph->yAxis->setLabel("y");
  // Устанавливаем диапазоны для осей, чтобы отобразить все данные:
  ui->graph->xAxis->setRange(xMin, xMax);
  ui->graph->yAxis->setRange(yMin, yMax);
  // Перерисовываем график
  ui->graph->replot();
}

void MainWindow::on_pushButton_equal_clicked() {
  QString currentText = ui->result->text();
  currentText.replace("x", ui->lineEdit_x->text());
  ui->graph->clearGraphs();
  ui->graph->replot();
  if (isXPressed && ui->lineEdit_x->text().isEmpty()) {
    QString func = ui->result->text();
    graph_draw(func);
    isXPressed = false;
    return;
  }
  QChar lastChar = currentText[currentText.length() - 1];
  if (currentText.isEmpty() || (!lastChar.isDigit() && lastChar != ')')) {
    show_Error();
    return;
  }
  QByteArray ba = currentText.toLatin1();
  char *line = ba.data();
  double res = calculate(line);
  if (isnan(res)) {
    show_Error();
  } else {
    QString resultString;
    if (res == static_cast<int>(res)) {
      resultString = QString::number(static_cast<int>(res));
    } else {
      resultString = QString::number(res, 'g', 7);
    }
    if (resultString.length() > 10) {
      show_Error();
      return;
    }
    ui->result->setText(resultString);
  }
}

void MainWindow::on_pushButton_credit_clicked() { credit.show(); }

void MainWindow::on_pushButton_deposit_clicked() { deposit.show(); }
