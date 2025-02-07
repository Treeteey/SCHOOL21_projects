#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDialog>
#include <QDoubleValidator>
#include <QStatusBar>

#include "CHeader.h"
namespace Ui {
class creditWindow;
}

class creditWindow : public QDialog {
  Q_OBJECT

 public:
  explicit creditWindow(QWidget *parent = nullptr);
  ~creditWindow();

 private slots:
  void on_calcButton_clicked();

 private:
  Ui::creditWindow *ui;
  QStatusBar *statusBar;
};

#endif  // CREDITWINDOW_H
