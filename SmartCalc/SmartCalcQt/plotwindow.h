

#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QString>
#include <QVector>

namespace Ui {
class plotWindow;
}

class SmartCalc;  // forward declaration

class plotWindow : public QDialog {
  Q_OBJECT

 signals:
  void windowClosed();

 public:
  explicit plotWindow(
      SmartCalc *window,
      QWidget *parent = nullptr);  //закинуть ссылку на основное окно, чтоб
                                   //можно было считать выражение из него
  ~plotWindow();
  long double minX;
  long double maxX;
  long double minY;
  long double maxY;
  long double h;

 private slots:
  void on_calcPlotButton_clicked();

 private:
  Ui::plotWindow *ui;
  QVector<double> x, y;
  SmartCalc *mainWindow;
};

void findNewMinMax(QVector<double> y, long double min, long double max,
                   long double *newMin, long double *newMax);
void calcPlotPoints(Ui::plotWindow *ui, QVector<double> &x, QVector<double> &y,
                    long double minX, long double maxX, long double *h);
void setupPlotAndAddData(Ui::plotWindow *ui, QVector<double> x,
                         QVector<double> y, long double newMinX,
                         long double newMaxX, long double newMinY,
                         long double newMaxY, long double h, int isMinX,
                         int isMaxX, int isMinY, int isMaxY);

#endif  // PLOTWINDOW_H
