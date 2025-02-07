#include "model.h"


// Конструктор Model.
s21::Model::Model() : globalData_(GlobalData::getInstance())
{

}


// Загружает OBJ-файл и обновляет соответствующие данные в глобальных переменных.
// Также вычисляет минимальные и максимальные координаты и радиус объекта.
bool s21::Model::ModelLoadOBJ(const QString &filepath_){

    std::string stdfilepath = filepath_.toStdString();
    bool ret = object_.LoadOBJ(stdfilepath);
    if(ret){
        shift_rotation_scale_data_.FindMinMax(object_.objreader_coords_);
        globalData_.min_x_ = shift_rotation_scale_data_.min_x_;
        globalData_.max_x_ = shift_rotation_scale_data_.max_x_;
        globalData_.min_y_ = shift_rotation_scale_data_.min_y_;
        globalData_.max_y_ = shift_rotation_scale_data_.max_y_;
        globalData_.min_z_ = shift_rotation_scale_data_.min_z_;
        globalData_.max_z_ = shift_rotation_scale_data_.max_z_;

        globalData_.base_min_x_ = globalData_.min_x_;
        globalData_.base_max_x_ = globalData_.max_x_;
        globalData_.base_min_y_ = globalData_.min_y_;
        globalData_.base_max_y_ = globalData_.max_y_;
        globalData_.base_min_z_ = globalData_.min_z_;
        globalData_.base_max_z_ = globalData_.max_z_;

        globalData_.center_x_ = shift_rotation_scale_data_.center_x_;
        globalData_.center_y_ = shift_rotation_scale_data_.center_y_;
        globalData_.center_z_ = shift_rotation_scale_data_.center_z_;

        globalData_.base_center_x_ = globalData_.center_x_;
        globalData_.base_center_y_ = globalData_.center_y_;
        globalData_.base_center_z_ = globalData_.center_z_;

        float delta_x = (globalData_.base_max_x_ - globalData_.base_min_x_),
            delta_y = globalData_.base_max_y_ - globalData_.base_min_y_,
            delta_z = globalData_.base_max_z_ - globalData_.base_min_z_;
        globalData_.max_radius_ = sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
    }
    return ret;
}

// Возвращает вектор граней объекта.
std::vector<std::vector<long>>& s21::Model::GetFaces() {
    return object_.objreader_faces_;
}

// Возвращает вектор координат объекта.
std::vector<s21::Vector3D>& s21::Model::GetCoords() {
    return object_.objreader_coords_;
}

// Очищает данные OBJ-файла, удаляя координаты и грани из памяти.
void s21::Model::ClearObjData(){
    if(!object_.objreader_coords_.empty()){
        object_.objreader_coords_.clear();
    }
    if(!object_.objreader_faces_.empty()){
        object_.objreader_faces_.clear();
    }
    shift_rotation_scale_data_.ClearData();
}

// Сдвигает объект по осям x, y, z и обновляет глобальные данные.
void s21::Model::ModelShiftObject(QString x_shift_new_, QString y_shift_new_,
                                  QString z_shift_new_){
    shift_rotation_scale_data_.ShiftObject(object_.objreader_coords_, x_shift_new_.toFloat(),
                                           y_shift_new_.toFloat(), z_shift_new_.toFloat());
    CopyToGlobalData();
}

// Вращает объект вокруг осей x, y, z и обновляет глобальные данные.
void s21::Model::ModelRotateObject(QString x_rotate_new_, QString y_rotate_new_,
                                   QString z_rotate_new_){
    shift_rotation_scale_data_.RotateObject(object_.objreader_coords_, x_rotate_new_.toFloat(),
                                            y_rotate_new_.toFloat(), z_rotate_new_.toFloat());
    CopyToGlobalData();
}

// Масштабирует объект и обновляет глобальные данные.
void s21::Model::ModelScaleObject(QString scale){
    shift_rotation_scale_data_.ScaleObject(object_.objreader_coords_, scale.toFloat());
    CopyToGlobalData();
}

// Копирует данные сдвига, вращения и масштаба в глобальные данные для дальнейшего использования.
void s21::Model::CopyToGlobalData()
{
    globalData_.x_shift_ = shift_rotation_scale_data_.x_shift_,
        globalData_.y_shift_ = shift_rotation_scale_data_.y_shift_,
        globalData_.z_shift_ = shift_rotation_scale_data_.z_shift_;
    globalData_.x_rotate_ = shift_rotation_scale_data_.x_rotate_,
        globalData_.y_rotate_ = shift_rotation_scale_data_.y_rotate_,
        globalData_.z_rotate_ = shift_rotation_scale_data_.z_rotate_;
    globalData_.max_x_ = shift_rotation_scale_data_.max_x_,
        globalData_.max_y_ = shift_rotation_scale_data_.max_y_,
        globalData_.max_z_ = shift_rotation_scale_data_.max_z_,
        globalData_.min_x_ = shift_rotation_scale_data_.min_x_,
        globalData_.min_y_ = shift_rotation_scale_data_.min_y_,
        globalData_.min_z_ = shift_rotation_scale_data_.min_z_;
    globalData_.center_x_ = shift_rotation_scale_data_.center_x_,
        globalData_.center_y_ = shift_rotation_scale_data_.center_y_,
        globalData_.center_z_ = shift_rotation_scale_data_.center_z_;
    globalData_.scale_ = shift_rotation_scale_data_.scale_;
}


//------------------- GLOBAL DATA -------------------

//Эта функция очищает глобальные настройки и сбрасывает их до значений по умолчанию.
void s21::GlobalData::ClearGlobalSetting(){
    max_x_ = -std::numeric_limits<float>::max(),
        max_y_ = -std::numeric_limits<float>::max(),
        max_z_ = -std::numeric_limits<float>::max(),
    min_x_ = std::numeric_limits<float>::max(),
        min_y_ = std::numeric_limits<float>::max(),
        min_z_ = std::numeric_limits<float>::max();
    center_x_ = 0, center_y_ = 0, center_z_ = 0;

    base_max_x_ = 0, base_max_y_ = 0,
        base_max_z_ = 0, base_min_x_ = 0,
        base_min_y_ = 0, base_min_z_ = 0;
    base_center_x_ = 0, base_center_y_ = 0, base_center_z_ = 0;
    scale_ = 1.0;
    translate_z_ = 0;
    line_type_ = 0;
    display_method_ = 0;
    line_width_ = 1;
    circle_square_size_ = 0;
    line_color_ = base_line_color_;
    background_color_ = base_background_color_;
    vertex_color_ = base_vertex_color_;
    filepath_.clear();
}

//Инициализация глобальных данных с начальными значениями по умолчанию.
s21::GlobalData::GlobalData() {
    line_type_ = 0;
    display_method_ = 0;
    line_width_ = 0;
    line_color_ = QColor(0, 0, 0), background_color_ = QColor(255, 255, 255),
        vertex_color_ = QColor(0, 0, 0);
    base_line_color_ = QColor(0, 0, 0),
        base_background_color_ = QColor(255, 255, 255),
        base_vertex_color_ = QColor(0, 0, 0);
    circle_square_size_ = 0.f;
    scale_ = 1.f;
}
