
#include "plotwindow.h"

#include <QtConcurrent/QtConcurrentRun>

#include "smartcalc.h"
#include "ui_plotwindow.h"

plotWindow::plotWindow(SmartCalc *window, QWidget *parent)
    : QDialog(parent), ui(new Ui::plotWindow), mainWindow(window) {
  ui->setupUi(this);
  //    connect(ui->calcPlotButton, &QPushButton::clicked, this,
  //    &plotWindow::on_calcPlotButton_clicked);

  ui->minXinput->setValidator(new QDoubleValidator(-1000000, 1000000, 7, this));
  ui->maxXinput->setValidator(new QDoubleValidator(-1000000, 1000000, 7, this));
  ui->minYinput->setValidator(new QDoubleValidator(-1000000, 1000000, 7, this));
  ui->maxYinput->setValidator(new QDoubleValidator(-1000000, 1000000, 7, this));
  ui->stepInput->setValidator(new QDoubleValidator(-1000000, 1000000, 7, this));
}

plotWindow::~plotWindow() { delete ui; }

long double toDoubleCorrectExpr(const QString &expr) {
  QString temp = expr;
  temp.replace(',', '.');
  return temp.toDouble();
}

void plotWindow::on_calcPlotButton_clicked() {
  if (mainWindow && (!mainWindow->exprString->text().isEmpty() ||
                     !ui->calcExprText->text().isEmpty())) {
    QString copyExpr = mainWindow->exprString->text();
    if (!copyExpr.isEmpty()) ui->calcExprText->setText(copyExpr);
    //переводим значения в правильные: 2,34 -> 2.34
    h = toDoubleCorrectExpr(ui->stepInput->text());
    int isMinX = ui->minXinput->text().isEmpty(),
        isMaxX = ui->maxXinput->text().isEmpty();
    ;
    int isMinY = ui->minYinput->text().isEmpty(),
        isMaxY = ui->maxYinput->text().isEmpty();
    if (isMinX)
      minX = -1000000;
    else
      minX = toDoubleCorrectExpr(ui->minXinput->text());
    if (isMaxX)
      maxX = 1000000;
    else
      maxX = toDoubleCorrectExpr(ui->maxXinput->text());
    if (isMinY)
      minY = -1000000;
    else
      minY = toDoubleCorrectExpr(ui->minYinput->text());
    if (isMaxY)
      maxY = 1000000;
    else
      maxY = toDoubleCorrectExpr(ui->maxYinput->text());
    x.clear();
    y.clear();
    if (minX == maxX) minX -= 1;
    if (minY == maxY) minY -= 1;
    if (minX > maxX) {  //если minxX > maxX то меняем местами - ИИ епт
      std::swap(minX, maxX);
    }
    if (minY > maxY) {
      std::swap(minY, maxY);
    }

    // calculate points and add them in QVectors x,y
    calcPlotPoints(ui, x, y, minX, maxX, &h);

    /* если minY maxY установлены так, что диапазон между минимальным и
    максимальным рассчитанным Y занимает меньше 70% то подогнать новые данные
    для setRange() ПРИМЕР: установили для Y диапазон -100...100 и построили
    график sin(x) - будет тонкая кривая линия с Y в диапазоне -1...1, чтоб
    увидеть кривую надо поставить хотя бы -1.5 до 1.5
    */
    long double newMinY = minY, newMaxY = maxY, newMinX = minX, newMaxX = maxX;
    if (isMinY == 1 && isMaxY == 1)  //если не задали диапазон minY-maxY то
                                     //настроить его автоматически
      findNewMinMax(y, minY, maxY, &newMinY, &newMaxY);
    if (isMinX == 1 && isMaxX == 1)
      findNewMinMax(x, minX, maxX, &newMinX, &newMaxX);

    setupPlotAndAddData(ui, x, y, newMinX, newMaxX, newMinY, newMaxY, h, isMinX,
                        isMaxX, isMinY, isMaxY);
  }
}

void findNewMinMax(QVector<double> y, long double min, long double max,
                   long double *newMin, long double *newMax) {
  long double tempMin =
      y.isEmpty() ? 0 : *std::min_element(y.constBegin(), y.constEnd());
  long double tempMax =
      y.isEmpty() ? 0 : *std::max_element(y.constBegin(), y.constEnd());

  long double delta = (tempMax - tempMin) * 0.15;
  if (tempMax == tempMin) {
    tempMin -= 0.15;
    tempMax += 0.15;
  } else {
    if ((tempMin - delta) < -1000000)
      tempMin = -1000000;
    else
      tempMin -= delta;
    if ((tempMax + delta) > 1000000)
      *newMax = 1000000;
    else
      tempMax += delta;
  }
  *newMin = (tempMin < min) ? min : tempMin;
  *newMax = (tempMax > max) ? max : tempMax;
}

void calcPlotPoints(Ui::plotWindow *ui, QVector<double> &x, QVector<double> &y,
                    long double minX, long double maxX, long double *h) {
  long double temp = 0;
  QByteArray inputExpr = ui->calcExprText->text().toLocal8Bit();
  const char *expr = inputExpr.constData();
  int width = ui->myPlot->width();  //ширина графика в пикселях
  long double pixelsPerPoint = (maxX - minX) / width;
  //если шаг будет настолько мелкий что в одном пикселе будут считаться
  //выражения для нескольких Х, то сделать шаг = pixelsPerPoint
  // + автоматический шаг
  if (*h < pixelsPerPoint || ui->automaticStep->isChecked()) {
    *h = pixelsPerPoint;
  }
  for (long double X = minX; X <= maxX; X += *h) {
    if (calcPlotExprWithX(expr, X,
                          &temp)) {  //если смогли рассчитать то добавить в
                                     //вектор для постройки точки
      x.push_back(X);
      y.push_back(temp);
    }
  }
};

void setupPlotAndAddData(Ui::plotWindow *ui, QVector<double> x,
                         QVector<double> y, long double newMinX,
                         long double newMaxX, long double newMinY,
                         long double newMaxY, long double h, int isMinX,
                         int isMaxX, int isMinY, int isMaxY) {
  double scale = 0;
  if ((newMaxY - newMinY) != 0) {
    scale = (newMaxX - newMinX) / (newMaxY - newMinY);
  }
  QString scaleOutput = "";
  if (scale > 1) {
    scaleOutput += QString::number(static_cast<long double>(scale), 'f', 7);
    scaleOutput += " : 1";
  } else if (scale < 1 && scale != 0) {
    scaleOutput += "1 : ";
    scaleOutput += QString::number(static_cast<long double>(1 / scale), 'f', 7);
  }
  ui->scaleOutput->setText(scaleOutput);

  ui->myPlot->clearGraphs();
  if (ui->myPlot->graphCount() == 0) {
    ui->myPlot->addGraph();
  }
  ui->myPlot->graph(0)->setData(x, y);
  ui->myPlot->graph(0)->setLineStyle(QCPGraph::lsStepCenter);
  ui->stepInput->setText(QString::number(static_cast<double>(h)));

  if (!(isMinY && isMaxY)) {  // minY maxY empty
    ui->minYinput->setText(QString::number(static_cast<double>(newMinY)));
    ui->maxYinput->setText(QString::number(static_cast<double>(newMaxY)));
  }
  if (!(isMinX && isMaxX)) {
    ui->minXinput->setText(QString::number(static_cast<double>(newMinX)));
    ui->maxXinput->setText(QString::number(static_cast<double>(newMaxX)));
  }
  ui->myPlot->yAxis->setRange(newMinY, newMaxY);
  ui->myPlot->xAxis->setRange(
      newMinX, newMaxX);  //устанавливаем диапазон видимости на графике
  ui->myPlot->xAxis->setLabel("x");
  ui->myPlot->yAxis->setLabel("y");
  ui->myPlot->replot();
  ui->myPlot->update();
}
