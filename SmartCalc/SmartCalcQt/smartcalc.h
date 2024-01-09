#ifndef SMARTCALC_H
#define SMARTCALC_H

#include <QLabel>
#include <QLocale>
#include <QMainWindow>
#include <QPointer>
#include <QRegularExpression>
#include <QString>
#include <iostream>

#include "CHeader.h"
#include "creditwindow.h"
#include "depositwindow.h"
#include "plotwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SmartCalc;
}
QT_END_NAMESPACE

//обрабатывать выражение только после =!
//если например будет 2.41.5+4 , то не проверять после каждого символа, а только
//после нажатия =!
/*
 * скачать pacman -S mingw-w64-x86_64-pcre2   - Windows MSYS2
 *
 *
 *
 */

class SmartCalc : public QMainWindow {
  Q_OBJECT

 public:
  SmartCalc(QWidget *parent = nullptr);
  ~SmartCalc();
  Ui::SmartCalc *ui;
  QLabel *exprString;
  QPointer<plotWindow> plotWindowInstance = nullptr;

 private:
  bool isPlotWindowOpen;  // flag to check if plotwindow is already opened

 signals:
  void sendString(const QString &data);

 private slots:
  void digits_numbers();
  void operations();
  void on_Button_clear_clicked();
  void on_Button_equal_clicked();
  void math_operations();
  void on_Button_delete_clicked();
  void on_CreditButton_clicked();
  void on_DepositButton_clicked();
  void on_PlotButton_clicked();
};

long double toDoubleCorrectExpr(const QString &expr);

#endif  // SMARTCALC_H
