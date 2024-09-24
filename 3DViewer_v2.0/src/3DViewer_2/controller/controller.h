#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/model.h"

namespace s21 {

class OpenGLWidgetClass;

class Controller
{
public:
    Controller(OpenGLWidgetClass* widget) : model_(new Model()), widget_(widget) {};
    ~Controller();
    void ControllerCalcStyleSheetForButton(QPushButton *button_, QColor &base_color_,
                                           QColor new_color_,
                                           QString which_color_button_);
    void ControllerResetButtonColors(QPushButton *button_background_, QColor &o_background_color_,
                                     QPushButton *button_vertex_, QColor &o_vertex_color_,
                                     QPushButton *button_line_, QColor &o_line_color_);
    bool ControllerLoadOBJ(const QString &filepath_);
    void ControllerClearObjData();
    void ControllerShiftObject(QString x_shift_new_,
                               QString y_shift_new_, QString z_shift_new_);
    void ControllerRotateObject(QString x_rotate_new_,
                                QString y_rotate_new_, QString z_rotate_new_);
    void ControllerScaleObject(QString scale);

    std::vector<s21::Vector3D>& GetCoords();
    std::vector<std::vector<long>>& GetFaces();

private:
    Model* model_;
    OpenGLWidgetClass* widget_;
};


} //end s21 namespace
#endif // CONTROLLER_H
