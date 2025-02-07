#include "smartcalc.h"

#include "ui_smartcalc.h"
//#include "creditwindow.h"
//#include "depositwindow.h"
//#include "plotwindow.h"

bool equalClicked = false;
bool hasXinExpr = false;
SmartCalc::SmartCalc(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SmartCalc) {
  ui->setupUi(this);
  ui->XValue->setValidator(
      new QDoubleValidator(0, std::numeric_limits<double>::max(), 7, this));
  isPlotWindowOpen = false;

  //чтоб точка ставилась а не запятая

  connect(ui->Button_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->Button_dot, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_open, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_close, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_pow, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_cos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_sin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_tan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_acos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_asin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_atan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_sqrt, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_log, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_plus, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_minus, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_mult, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_divide, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->XButton, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  //    connect(ui->Button_dot, SIGNAL(clicked()), this,
  //    SLOT(digits_numbers()));
  connect(ui->Button_unary, SIGNAL(clicked()), this, SLOT(operations()));
  //сигнал чтоб отправить
  //    connect(ui->PlotButton, &QPushButton::clicked, this,
  //    &SmartCalc::on_PlotButton_clicked);

  exprString = ui->exprString;
}

SmartCalc::~SmartCalc() { delete ui; }

void SmartCalc::digits_numbers() {
  if (equalClicked == true) {
    if (ui->exprString->text().isEmpty()) {
      ui->exprString->setText(ui->resultString->text());
      equalClicked = false;
    }
  }
  QPushButton *button = (QPushButton *)sender();
  QString new_label;
  new_label = ui->exprString->text() + button->text();
  if (button->text() == "sin" || button->text() == "cos" ||
      button->text() == "tan" || button->text() == "asin" ||
      button->text() == "acos" || button->text() == "atan" ||
      button->text() == "sqrt" || button->text() == "ln" ||
      button->text() == "log")
    new_label += "(";
  ui->exprString->setText(new_label);
}

void SmartCalc::operations() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;
  if (button->text() == "+/-") {
    double all_numbers = ui->resultString->text().toDouble() * (-1);
    new_label = QString::number(all_numbers, 'g', 15);
    ui->resultString->setText(new_label);
  }
}

void SmartCalc::on_Button_clear_clicked() {
  if (ui->exprString->text() == "")
    ui->resultString->setText("");
  else
    ui->exprString->setText("");
}

void SmartCalc::on_Button_equal_clicked() {
  QByteArray byteExpr = ui->exprString->text().toLocal8Bit();
  const char *sendExpr = byteExpr.constData();
  long double calculation = 0;

  if (isXinExpr(sendExpr)) {  //если есть Х в выражении
    char replacedExpr[300] = {};
    QString xValueString = ui->XValue->text();  // 2,45
    xValueString.replace(',', '.');             // 2.45
    long double X = xValueString.toDouble();    // 2,45 -> 2      2.45 -> 2.45

    if (replaceXinPlotExpr(sendExpr, replacedExpr,
                           X)) {  //если смогли заменить все Х на число в XValue
      long double calculation = 0;
      if (calcExpr(replacedExpr,
                   &calculation))  //если смогли рассчитать выражение
        ui->resultString->setText(
            QString::number(static_cast<long double>(calculation), 'f', 7));
      else
        ui->resultString->setText("cant calculate expression with X");
    }
  } else {  //если просто выражение то рассчитать
    if (calcExpr(sendExpr, &calculation)) {
      ui->resultString->setText(
          QString::number(static_cast<long double>(calculation), 'f', 7));
      equalClicked = true;
    } else {
      ui->resultString->setText("cant calculate expression");
    }
  }
}

void SmartCalc::math_operations() {}

void SmartCalc::on_Button_delete_clicked() {
  QString currentString = ui->exprString->text();
  if (!currentString.isEmpty()) {
    if (currentString[currentString.length() - 1] ==
        '(') {                // "5*sin(" -> "5*sin"
      currentString.chop(1);  // Удаляем последний символ
      if (currentString.length() != 0 && currentString.at(currentString.length() - 1)
              .isLetter()) {  //"5*sin" -> "5*"
        while (!currentString.isEmpty() &&
               currentString.at(currentString.length() - 1).isLetter()) {
          currentString.chop(1);  // Удаляем последний символ
        }
      }
    } else  //"5*" -> "5"
      currentString.chop(1);
  }
  ui->exprString->setText(currentString);
}

void SmartCalc::on_CreditButton_clicked() {
  creditWindow window;
  window.setWindowTitle("Кредитный калькулятор");
  window.setModal(true);
  window.exec();
}

void SmartCalc::on_DepositButton_clicked() {
  depositWindow window;
  window.setWindowTitle("Калькулятор вкладов");
  window.setModal(true);
  window.exec();
}

void SmartCalc::on_PlotButton_clicked() {
  plotWindow *window = new plotWindow(this);
  window->setWindowTitle("Построение графика");
  window->show();
}
