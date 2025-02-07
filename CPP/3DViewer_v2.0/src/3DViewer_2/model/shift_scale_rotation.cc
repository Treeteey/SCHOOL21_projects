#include "my_functions.h"
#include <iostream>
#include <limits>

// Конструктор класса ShiftRotationScale.
// Инициализирует параметры сдвига, вращения, масштаба и граничные значения, вызывая функцию ClearData.
s21::ShiftRotationScale::ShiftRotationScale(){
    // x_shift_ = 0.0f, y_shift_ = 0.0f, z_shift_ = 0.0f;
    // x_rotate_ = 0.0f, y_rotate_ = 0.0f, z_rotate_ = 0.0f;
    // center_x_ = 0.0f, center_y_ = 0.0f, center_z_ = 0.0f;
    // max_x_ = -std::numeric_limits<float>::max(), max_y_ = -std::numeric_limits<float>::max(), max_z_ = -std::numeric_limits<float>::max(),
    // min_x_ = std::numeric_limits<float>::max(), min_y_ = std::numeric_limits<float>::max(), min_z_ = std::numeric_limits<float>::max();
    // scale_ = 1.0f;
    ClearData();
}

// Функция для сдвига объекта.
// Получает новые параметры сдвига, вычисляет дельту между текущим и новым сдвигом,
// затем сдвигает объект на эту дельту и обновляет текущие данные сдвига.

// gets new shift parameters, calculate delta between current and new shift
// then shifts by delta and change shift_current data
void s21::ShiftRotationScale::ShiftObject(std::vector<Vector3D>& coords, float x_shift_new_,
                                          float y_shift_new_, float z_shift_new_){
    float x_delta_ = x_shift_new_ - x_shift_;
    float y_delta_ = y_shift_new_ - y_shift_;
    float z_delta_ = z_shift_new_ - z_shift_;
    // std::cout << "\nshift: " << x_shift_ << " " << y_shift_ << " " << z_shift_ << std::endl;
    ShiftObjectByDelta(coords, x_delta_, y_delta_, z_delta_);
    x_shift_ = x_shift_new_;
    y_shift_ = y_shift_new_;
    z_shift_ = z_shift_new_;
    // std::cout << "\n new shift: " << x_shift_ << " " << y_shift_ << " " << z_shift_ << std::endl;
    center_x_ += x_delta_;
    center_y_ += y_delta_;
    center_z_ += z_delta_;
    min_x_ += x_delta_;
    max_x_ += x_delta_;
    min_y_ += y_delta_;
    max_y_ += y_delta_;
    min_z_ += z_delta_;
    max_z_ += z_delta_;
}

// Вспомогательная функция для сдвига объекта на заданную дельту.
// Перемещает каждую координату векторa на заданную величину по каждой из осей.
void s21::ShiftRotationScale::ShiftObjectByDelta(std::vector<Vector3D>& coords, float x_delta,
                                          float y_delta, float z_delta){
    for (Vector3D& i : coords) {
        i.x += x_delta;
        i.y += y_delta;
        i.z += z_delta;
    }
}

// Функция для вращения объекта.
// Вращает объект вокруг заданных осей на указанные углы,
// сдвигает объект к началу координат перед вращением и возвращает его после.
void s21::ShiftRotationScale::RotateObject(std::vector<Vector3D>& coords, float x_rotate_new_,
                                           float y_rotate_new_, float z_rotate_new_){
    // Translate the object to the origin
    ShiftObjectByDelta(coords, -center_x_, -center_y_, -center_z_);

    // rotation around x axis
    float x_delta_ = x_rotate_new_ - x_rotate_;
    float y_delta_ = y_rotate_new_ - y_rotate_;
    float z_delta_ = z_rotate_new_ - z_rotate_;

    float x,y,z;

    if(x_delta_ != 0.f){
        float x_angle = x_delta_ * M_PI / 180.f;
        for(Vector3D& i : coords){
            y = i.y;
            z = i.z;
            i.y = (y * cos(x_angle) - z * sin(x_angle));
            i.z = (y * sin(x_angle) + z * cos(x_angle));
        }
    }

    if(y_delta_ != 0.f){
        float y_angle = y_delta_ * M_PI / 180.f;
        for(Vector3D& i : coords){
            x = i.x;
            z = i.z;
            i.x = (x * cos(y_angle) + z * sin(y_angle));
            i.z = (-x * sin(y_angle) + z * cos(y_angle));
        }
    }

    if(z_delta_ != 0.f){
        float z_angle = z_delta_ * M_PI / 180.f;
        for(Vector3D& i : coords){
            x = i.x;
            y = i.y;
            i.x = (x * cos(z_angle) - y * sin(z_angle));
            i.y = (x * sin(z_angle) + y * cos(z_angle));
        }
    }

    // Translate the object back
    ShiftObjectByDelta(coords, center_x_, center_y_, center_z_);

    x_rotate_ = x_rotate_new_;
    y_rotate_ = y_rotate_new_;
    z_rotate_ = z_rotate_new_;


}

// Функция для масштабирования объекта.
// Изменяет размер объекта на заданный масштаб, изменяя все координаты вектора.
void s21::ShiftRotationScale::ScaleObject(std::vector<Vector3D>& coords, float new_scale){
    if(new_scale > 0 && new_scale != scale_){
        // Translate the object to the origin
        ShiftObjectByDelta(coords, -center_x_, -center_y_, -center_z_);

        float delta = new_scale / scale_;
        for(Vector3D& i : coords){
            i *= delta;
        }
        scale_ = new_scale;

        // Translate the object back
        ShiftObjectByDelta(coords, center_x_, center_y_, center_z_);
    }
}
// Функция для нахождения минимальных и максимальных координат объекта.
// Вычисляет минимальные и максимальные значения по каждой оси и определяет центр объекта.
void s21::ShiftRotationScale::FindMinMax(std::vector<Vector3D>& coords){
    for(const auto &i : coords){
        if(i.x > max_x_) max_x_ = i.x;
        if(i.x < min_x_) min_x_ = i.x;
        if(i.y > max_y_) max_y_ = i.y;
        if(i.y < min_y_) min_y_ = i.y;
        if(i.z > max_z_) max_z_ = i.z;
        if(i.z < min_z_) min_z_ = i.z;
    }
    center_x_ = (max_x_ + min_x_)/2.0f;
    center_y_ = (max_y_ + min_y_)/2.0f;
    center_z_ = (max_z_ + min_z_)/2.0f;
}

// Функция для очистки данных объекта.
// Сбрасывает значения сдвига, вращения, масштаба и граничных значений к начальным.
void s21::ShiftRotationScale::ClearData()
{
    x_shift_ = 0.0f, y_shift_ = 0.0f, z_shift_ = 0.0f;
    x_rotate_ = 0.0f, y_rotate_ = 0.0f, z_rotate_ = 0.0f;
    center_x_ = 0.0f, center_y_ = 0.0f, center_z_ = 0.0f;
    max_x_ = -std::numeric_limits<float>::max(), max_y_ = -std::numeric_limits<float>::max(), max_z_ = -std::numeric_limits<float>::max(),
        min_x_ = std::numeric_limits<float>::max(), min_y_ = std::numeric_limits<float>::max(), min_z_ = std::numeric_limits<float>::max();
    scale_ = 1.0f;
}
