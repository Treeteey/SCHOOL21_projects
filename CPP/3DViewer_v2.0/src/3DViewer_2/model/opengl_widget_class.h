#ifndef OPENGLWIDGETCLASS_H
#define OPENGLWIDGETCLASS_H


#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QVector3D>
#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QWheelEvent>

#include "../controller/controller.h"

namespace s21{

class Controller;
struct GlobalData;

class OpenGLWidgetClass : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
public:
    // explicit запрещает неявное создание класса
    // можно вызвать ТОЛЬКО конструктор
    // widget_ = new OpenGLWidgetClass(central_layout_);
    // нельзя вызвать просто
    // widget_ = new OpenGLWidgetClass
    explicit OpenGLWidgetClass(QWidget *parent = nullptr);
    ~OpenGLWidgetClass();
    Controller *controller_;
    GlobalData& globalData_;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    void SetLineType();
    void SetProjection();
};


} //end s21 namespace
#endif  // OPENGLWIDGETCLASS_H
