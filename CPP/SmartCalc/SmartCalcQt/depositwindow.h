#ifndef DEPOSITWINDOW_H
#define DEPOSITWINDOW_H

#include <QDate>
#include <QDialog>
#include <QDoubleValidator>
#include <QStatusBar>
#include <QString>

#include "CHeader.h"

namespace Ui {
class depositWindow;
}

class depositWindow : public QDialog {
  Q_OBJECT

 public:
  explicit depositWindow(QWidget *parent = nullptr);
  ~depositWindow();

 private slots:
  void on_CalcButton_clicked();

  void on_checkBoxCapitalization_clicked();

 private:
  Ui::depositWindow *ui;
  QStatusBar *statusBar;
};

#endif  // DEPOSITWINDOW_H
