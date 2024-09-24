#include "controller.h"

// Деструктор для контроллера. Освобождает память, занятую моделью.


//this function calls model::ModelCalcStyleSheetForButton()
//and send "button" (need to change color of button by changing its styleSheet,
//"base_color" - will be replaced by new_color,
//new_color - used to make inversed color from it and get their names
//and flag "which_color_button_" to change corresponding color
s21::Controller::~Controller()
{
    delete model_;
}


// Эта функция вызывает model::ModelCalcStyleSheetForButton() и передает кнопке новый цвет.
// Она изменяет стиль кнопки, заменяя base_color на new_color, и обновляет флаг which_color_button_,
// чтобы изменить соответствующий цвет.
void s21::Controller::ControllerCalcStyleSheetForButton(QPushButton *button_, QColor &base_color_,
                                      QColor new_color_,
                                      QString which_color_button_)
{
    model_->buttons_colors_.ModelCalcStyleSheetForButton(button_, base_color_, new_color_,
                                                            which_color_button_);
}

// Эта функция сбрасывает цвета кнопок на их исходные значения.
// Она отправляет указатели на кнопки в модель для их обновления.

//resets buttons color
//send buttons pointers
void s21::Controller::ControllerResetButtonColors(QPushButton *button_background_, QColor &o_background_color_,
                                                  QPushButton *button_vertex_, QColor &o_vertex_color_,
                                                  QPushButton *button_line_, QColor &o_line_color_)
{
  model_->buttons_colors_.ModelResetButtonColors(button_background_, o_background_color_,
                                                button_vertex_, o_vertex_color_,
                                                button_line_, o_line_color_);
}

// Загружает OBJ-файл, используя соответствующую функцию модели.
bool s21::Controller::ControllerLoadOBJ(const QString &filepath_){
    return model_->ModelLoadOBJ(filepath_);
}

// Возвращает вектор граней из модели.
std::vector<std::vector<long>>& s21::Controller::GetFaces() {
    return model_->GetFaces();
}

// Возвращает вектор координат из модели.
std::vector<s21::Vector3D>& s21::Controller::GetCoords() {
    return model_->GetCoords();
}

// Очищает данные объекта в модели, удаляя загруженные координаты и грани.
void s21::Controller::ControllerClearObjData()
{
    model_->ClearObjData();
}

// Сдвигает объект по осям x, y, z, используя соответствующую функцию модели.
void s21::Controller::ControllerShiftObject(QString x_shift_new_, QString y_shift_new_,
                                            QString z_shift_new_){
    model_->ModelShiftObject(x_shift_new_, y_shift_new_, z_shift_new_);
}

// Вращает объект вокруг осей x, y, z, используя соответствующую функцию модели.
void s21::Controller::ControllerRotateObject(QString x_rotate_new_, QString y_rotate_new_,
                                             QString z_rotate_new_){
    model_->ModelRotateObject(x_rotate_new_, y_rotate_new_, z_rotate_new_);
}

// Масштабирует объект, используя соответствующую функцию модели.
void s21::Controller::ControllerScaleObject(QString scale){
    model_->ModelScaleObject(scale);
}
