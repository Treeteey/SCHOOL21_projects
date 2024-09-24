#ifndef MODEL_H
#define MODEL_H

#include <QColor>
#include <QPushButton>
#include <QString>
#include <QColorDialog>
#include <QFile>
#include <QVector3D>


#include "my_functions.h"

namespace s21 {


// singleton class to store all program data
// colors, movement, rotation, scale data,
// filepath, type of projection
struct GlobalData {

    QColor base_background_color_, base_line_color_, base_vertex_color_;
    QColor background_color_, line_color_, vertex_color_;
    // Strings
    QString gif_filename_;
    QString filepath_;
    float x_shift_, y_shift_, z_shift_;
    float x_rotate_, y_rotate_, z_rotate_;
    float scale_;

    float max_x_, max_y_, max_z_, min_x_, min_y_, min_z_;
    float base_max_x_, base_max_y_, base_max_z_, base_min_x_, base_min_y_, base_min_z_; //for glFrustrum() glOrhto() to set camera statically
    float center_x_, center_y_, center_z_;
    float base_center_x_, base_center_y_, base_center_z_; //for glFrustrum() glOrhto() to set camera statically

    float max_radius_;

    float line_width_;
    float circle_square_size_;

    float translate_z_;

    // Integers
    int images_count_ = 0;

    // Booleans
    bool is_centered_ = true;
    bool gif_recording_;

    // ints
    int line_type_; //0 - solid lines, 1 - dashed
    int display_method_; //draw vertexes as: 0 - no, 1 - circle, 2 - square
    int projection_; // 0 - ortho, 1 - perspective

    QPointF last_mouse_pos_;

    // Disable copy constructor and assignment operator
    GlobalData(const GlobalData&) = delete;
    GlobalData& operator=(const GlobalData&) = delete;
    void ClearGlobalSetting();

private:
    // Private constructor to prevent direct instantiation
    GlobalData();
    ~GlobalData() {}

public:
    // Method to get the single instance of the struct
    static GlobalData& getInstance() {
        static GlobalData instance;
        return instance;
    }
};



class ColorButtons{
public:
    ColorButtons();
    QColor base_background_color_, base_line_color_, base_vertex_color_;
    QColor background_color_, line_color_, vertex_color_;

    void ModelCalcStyleSheetForButton(QPushButton *button_, QColor &base_color_,
                                          QColor new_color_,
                                          QString which_color_button_);
    void ModelResetButtonColors(QPushButton *button_background_, QColor &o_background_color_,
                                QPushButton *button_vertex_, QColor &o_vertex_color_,
                                QPushButton *button_line_, QColor &o_line_color_);


private:
    void SetButtonColor(QPushButton *button_, QColor color_);
    void ResetButtonColors();  // to default colors
    QString CalcStringStyleSheet(const QColor &color_) const;    // to openGLWidget colors
    QColor InverseColor(const QColor &color_) const;

};


class Model
{
public:
    Model();
    ColorButtons buttons_colors_;
    OBJReader object_;
    ShiftRotationScale shift_rotation_scale_data_;
    GlobalData& globalData_;
    bool ModelLoadOBJ(const QString &filepath_);
    std::vector<std::vector<long>>& GetFaces();
    std::vector<s21::Vector3D>& GetCoords();
    void ClearObjData();

    void ModelShiftObject(QString x_shift_new_, QString y_shift_new_,
                          QString z_shift_new_);
    void ModelRotateObject(QString x_rotate_new_, QString y_rotate_new_,
                           QString z_rotate_new_);
    void ModelScaleObject(QString scale);
private:
    void CopyToGlobalData();
};





} //end namespace
#endif // MODEL_H
