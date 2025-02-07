#include "creditwindow.h"

#include <QMainWindow>
#include <QString>
#include <iostream>

#include "smartcalc.h"
#include "ui_creditwindow.h"
using namespace std;

creditWindow::creditWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::creditWindow) {
  ui->setupUi(this);
  // can input only numbers!
  ui->CreditSumInput->setValidator(
      new QDoubleValidator(0, std::numeric_limits<double>::max(), 2, this));
  ui->TimeInput->setValidator(
      new QIntValidator(0, std::numeric_limits<int>::max(), this));
  ui->InterestInput->setValidator(
      new QDoubleValidator(0, std::numeric_limits<double>::max(), 2, this));

  statusBar = new QStatusBar(this);
  statusBar->geometry().bottomLeft();
  //    setStatusBar(statusBar);
}

creditWindow::~creditWindow() { delete ui; }

void creditWindow::on_calcButton_clicked() {
  if (ui->CreditSumInput->text().isEmpty()) {
    statusBar->showMessage("Введи сумму", 2000);
  } else if (ui->TimeInput->text().isEmpty()) {
    statusBar->showMessage("Введи длительность кредита", 2000);
  } else if (ui->InterestInput->text().isEmpty()) {
    statusBar->showMessage("Введи процентную ставку", 2000);
  } else if (!ui->TimeInMonth->isChecked() && !ui->TimeInYears->isChecked()) {
    statusBar->showMessage("Выбери тип времени кредита", 2000);
  } else if (!ui->annuity->isChecked() && !ui->differ->isChecked()) {
    statusBar->showMessage("Выбери тип ежемесячных платежей", 2000);
  } else {
    long double creditSum =
        toDoubleCorrectExpr(ui->CreditSumInput->text());  //сумма кредита
    long double interest =
        toDoubleCorrectExpr(ui->InterestInput->text());  //процентная ставка
    int typeTime =
        (ui->TimeInMonth->isChecked()) ? 1 : 0;  // 1 - month, 0 - years
    int time = ui->TimeInput->text().toInt();
    int typeOfCredit =
        (ui->annuity->isChecked()) ? 0 : 1;  // 1 - differentiated, 0 - annuity

    long double *monthPayment = NULL;
    long double total = 0;
    long double tax = 0;

    if (creditCalc(interest, creditSum, typeTime, time, typeOfCredit,
                   &monthPayment, &tax, &total)) {
      if (typeOfCredit == 0) {
        ui->MinPaymentOutput->setText(QString::number(monthPayment[0], 'f', 2));
        ui->MaxPaymentOutput->setText("");
      } else {
        time = time * ((typeTime) ? 1 : 12);
        ui->MinPaymentOutput->setText(QString::number(monthPayment[0], 'f', 2));
        ui->MaxPaymentOutput->setText(
            QString::number(monthPayment[time - 1], 'f', 2));
      }
      ui->TotalOutput->setText(QString::number(total, 'f', 2));
      ui->TaxOutput->setText(QString::number(tax, 'f', 2));
      if (monthPayment != NULL) {
        free(monthPayment);
      }
    }
  }
}
