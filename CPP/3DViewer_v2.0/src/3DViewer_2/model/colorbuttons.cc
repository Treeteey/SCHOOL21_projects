#include "model.h"

// Конструктор ColorButtons инициализирует базовые цвета для фона, линий и вершин.
s21::ColorButtons::ColorButtons()
    : base_background_color_(QColor(255, 255, 255)),
    base_line_color_(QColor(0, 0, 0)),
    base_vertex_color_(QColor(255, 255, 255))
{
}

// Эта функция сбрасывает цвета кнопок на базовые значения, изменяя их стиль на основе базовых цветов.
void s21::ColorButtons::ModelResetButtonColors(QPushButton *button_background_, QColor &o_background_color_,
                                               QPushButton *button_vertex_, QColor &o_vertex_color_,
                                               QPushButton *button_line_, QColor &o_line_color_) {
    button_background_->setStyleSheet(CalcStringStyleSheet(base_background_color_));
    button_vertex_->setStyleSheet(CalcStringStyleSheet(base_vertex_color_));
    button_line_->setStyleSheet(CalcStringStyleSheet(base_line_color_));
    o_background_color_ = base_background_color_;
    o_vertex_color_ = base_vertex_color_;
    o_line_color_ = base_line_color_;
}


// Эта функция изменяет стиль кнопки, устанавливая новый цвет. В зависимости от типа кнопки,
// она обновляет соответствующий базовый цвет.
void s21::ColorButtons::ModelCalcStyleSheetForButton(QPushButton *button_, QColor &base_color_,
                                                     QColor new_color_,
                                                     QString which_color_button_) {
    if (new_color_.isValid()) {
        QString styleSheet = CalcStringStyleSheet(new_color_);
        button_->setStyleSheet(styleSheet);

        // Update the appropriate color based on the button type
        if (which_color_button_ == "background") {
            background_color_ = new_color_;
            base_color_ = background_color_;
        } else if (which_color_button_ == "vertex") {
            vertex_color_ = new_color_;
            base_color_ = vertex_color_;
        } else if (which_color_button_ == "line") {
            line_color_ = new_color_;
            base_color_ = line_color_;
        }
    }
}

// Эта функция создает строку стиля для кнопки, используя заданный цвет и его инверсию.
QString s21::ColorButtons::CalcStringStyleSheet(const QColor &color_) const {
    QColor inverse_color = InverseColor(color_);
    return QString("background-color: %1; color: %2;")
        .arg(color_.name())
        .arg(inverse_color.name());
}

// Эта функция вычисляет инверсный цвет для заданного цвета.
QColor s21::ColorButtons::InverseColor(const QColor &color_) const {
    int red = 255 - color_.red();
    int green = 255 - color_.green();
    int blue = 255 - color_.blue();
    return QColor(red, green, blue);
}
