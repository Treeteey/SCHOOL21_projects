#include "depositwindow.h"

#include <iostream>

#include "smartcalc.h"
#include "ui_depositwindow.h"
using namespace std;

depositWindow::depositWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::depositWindow) {
  ui->setupUi(this);

  ui->InputDepositSum->setValidator(
      new QDoubleValidator(0, std::numeric_limits<double>::max(), 2, this));
  ui->InputTimeOfDeposit->setValidator(
      new QIntValidator(0, std::numeric_limits<int>::max(), this));
  ui->InputInterest->setValidator(
      new QDoubleValidator(0, std::numeric_limits<double>::max(), 2, this));
  ui->InputTax->setValidator(
      new QDoubleValidator(0, std::numeric_limits<double>::max(), 2, this));
  statusBar = new QStatusBar(this);
  ui->EditStartDate->setDate(QDate::currentDate());
}

depositWindow::~depositWindow() { delete ui; }

void depositWindow::on_CalcButton_clicked() {
  long double depositSum = toDoubleCorrectExpr(ui->InputDepositSum->text());
  long double interest = toDoubleCorrectExpr(ui->InputInterest->text());
  long double inputTax = toDoubleCorrectExpr(ui->InputTax->text());

  int timeOfDeposit = ui->InputTimeOfDeposit->text().toInt();
  int startDay = ui->EditStartDate->date().day();
  int startMonth = ui->EditStartDate->date().month() - 1;
  int startYear = ui->EditStartDate->date().year();
  int postingPeriod = -1;
  if (ui->radioDaysPosting->isChecked())
    postingPeriod = 0;
  else if (ui->radioMonthPosting->isChecked())
    postingPeriod = 1;
  else if (ui->radioYearsPosting->isChecked())
    postingPeriod = 2;
  int payoutPeriod = -1;
  if (ui->PeriodEndOfDate->isChecked())
    payoutPeriod = 0;
  else if (ui->PeriodEachDay->isChecked())
    payoutPeriod = 1;
  else if (ui->PeriodEachWeek->isChecked())
    payoutPeriod = 2;
  else if (ui->PeriodEachMonth->isChecked())
    payoutPeriod = 3;
  else if (ui->PeriodEachQuartal->isChecked())
    payoutPeriod = 4;
  else if (ui->PeriodEachHalfYear->isChecked())
    payoutPeriod = 5;
  else if (ui->PeriodEachYear->isChecked())
    payoutPeriod = 6;
  int capitalization = (ui->checkBoxCapitalization->isChecked() ? 1 : 0);

  if (depositSum != 0 && interest != 0 && timeOfDeposit != 0 &&
      postingPeriod != -1 && payoutPeriod != -1 && inputTax != 0) {
    long double total = 0, gainedInterest = 0, tax = 0;
    depositCalc(startDay, startMonth, startYear, depositSum, postingPeriod,
                timeOfDeposit, interest, payoutPeriod, &total, &gainedInterest,
                &tax, capitalization, inputTax);
    ui->TotalOutput->setText(
        QString::number(static_cast<long double>(total), 'f', 2));
    ui->GainedInterestOutput->setText(
        QString::number(static_cast<long double>(gainedInterest), 'f', 2));
    ui->TaxOutput->setText(
        QString::number(static_cast<long double>(tax), 'f', 2));
  }
}

void depositWindow::on_checkBoxCapitalization_clicked() {
  if (ui->checkBoxCapitalization->isChecked()) {
    ui->PeriodEndOfDate->hide();
    ui->PeriodicityOfPayments->setText("Периодичность капитализации");
  } else {
    ui->PeriodEndOfDate->show();
    ui->PeriodicityOfPayments->setText("Периодичность выплат");
  }
}
