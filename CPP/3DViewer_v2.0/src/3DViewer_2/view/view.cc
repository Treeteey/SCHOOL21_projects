#include "view.h"
#include "ui_view.h"
#include <iostream>

// Конструктор класса View
s21::View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new s21::UiView)
    , globalData_(GlobalData::getInstance())
{
    ui_->SetupUi(this);
    controller_ = new Controller(ui_->widget_);
    ui_->widget_->controller_ = controller_;
    SetValidatorsToLineEdits();
    SetConnectsToSlots();
    timer_ = new QTimer(0);
    connect(timer_, &QTimer::timeout, this, &View::MakeGIF);

    ChangeDisplayMethodData(0);
    globalData_.gif_recording_ = false;
    SetButtonColors();


    // Load settings when the application starts
    LoadSettings();
    ui_->widget_->update();
}

// Деструктор класса View
s21::View::~View()
{
    // Save settings when the application is closed
    SaveSettings();
    delete ui_;
}


// Открывает файл, если он выбран, и загружает его данные
void s21::View::OpenFile() {

  if (ui_ && globalData_.filepath_ != "") {
    qDebug() << "Selected file path:" << globalData_.filepath_;
    if (controller_->ControllerLoadOBJ(globalData_.filepath_)) {
      QFileInfo file_info(globalData_.filepath_);
      QString filename_ = file_info.fileName();
      ui_->filename_label_->setText(filename_);
      ui_->vertex_count_->setText(
          "vertices: " + QString::number(controller_->GetCoords().size()));
      ui_->faces_count_->setText(
          "faces: " + QString::number(controller_->GetFaces().size()));
      ui_->widget_->update();
    }
  }
}


// Открывает диалог выбора нового файла OBJ. При выборе закрывает текущий файл и открывает новый.
void s21::View::ChooseFile() {
    QString new_file_path_ =
        QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(),
                                     tr("Object Files (*.obj);;All Files (*)"));

    if (!new_file_path_.isEmpty() &&
        new_file_path_ != globalData_.filepath_) {

        CloseFile();
        globalData_.filepath_ = new_file_path_;
        OpenFile();
    }
}


// Закрывает текущий открытый файл и сбрасывает связанные с ним настройки и элементы пользовательского интерфейса.
void s21::View::CloseFile() {
    if (!globalData_.filepath_.isEmpty()) {
        globalData_.filepath_ = "";
        ClearSettings();
        ui_->widget_->update();
        qDebug() << "Closing file\n";
    }
}

// Обрабатывает нажатие кнопки для переключения на ортографическую проекцию и обновляет вид.

// 0 - ortho, 1 - perspective
void s21::View::OnOrthoButtonClicked() {
    globalData_.projection_ = 0;
    ui_->widget_->update();
}

// Обрабатывает нажатие кнопки для переключения на перспективную проекцию и обновляет вид.
void s21::View::OnPerspectiveButtonClicked() {
    globalData_.projection_ = 1;
    ui_->widget_->update();
}


// Обрабатывает изменения в полях для смещения объекта. Соответственно обновляет положение объекта.
void s21::View::OnAxisShiftLineEdited() {
    QString x_shift_ = ui_->x_shift_line_edit_->text(),
            y_shift_ = ui_->y_shift_line_edit_->text(),
            z_shift_ = ui_->z_shift_line_edit_->text();

    controller_->ControllerShiftObject(x_shift_, y_shift_, z_shift_);
    ui_->widget_->update();
}


// Обрабатывает изменения в полях для вращения объекта. Соответственно обновляет вращение объекта.
void s21::View::OnRotationLineEdited() {
    QString x_rotation_ = ui_->x_rotation_line_edit_->text(),
            y_rotation_ = ui_->y_rotation_line_edit_->text(),
            z_rotation_ = ui_->z_rotation_line_edit_->text();

    controller_->ControllerRotateObject(x_rotation_, y_rotation_, z_rotation_);
    ui_->widget_->update();
}


// Обрабатывает изменения в поле масштаба. Соответственно обновляет масштаб объекта.
void s21::View::OnScaleLineEdited() {
    QString scale_ = ui_->scale_edit_->text();

    controller_->ControllerScaleObject(scale_);
    ui_->widget_->update();
}


// Обрабатывает изменения в поле толщины линии и применяет его.
void s21::View::OnLineThicknessEdited() {
    QString line_thickness_ = ui_->line_thickness_edit_->text();
    globalData_.line_width_ = line_thickness_.toFloat();
    ui_->widget_->update();
}

// Обрабатывает изменения в поле размера круга или квадрата и применяет его.
void s21::View::OnCircleSquareSizeEdited() {
    QString circle_square_size_ = ui_->circle_square_size_edit_->text();
    globalData_.circle_square_size_ = circle_square_size_.toFloat();
    ui_->widget_->update();
}

// Обрабатывает выбор типа линии из выпадающего списка и применяет его.
void s21::View::OnLineTypeBoxActivated() {
    int index_ = ui_->line_type_box_->currentIndex();
    if (index_ == 0) {
        globalData_.line_type_ = 0;
    } else if (index_ == 1) {
        globalData_.line_type_ = 1;
    }
    ui_->widget_->update();
}







// Обрабатывает нажатие кнопки для выбора цвета линии и применяет его
void s21::View::OnLineColorButtonClicked() {
    QColor new_color_ = QColorDialog::getColor(Qt::white, this, "Choose color");
    controller_->ControllerCalcStyleSheetForButton(ui_->line_color_button_, globalData_.line_color_, new_color_, "line");
    ui_->widget_->update();
}

// Обрабатывает нажатие кнопки для выбора цвета фона и применяет его
void s21::View::OnBackgroundColorButtonClicked() {
    QColor new_color_ = QColorDialog::getColor(Qt::white, this, "Choose color");
    controller_->ControllerCalcStyleSheetForButton(ui_->background_color_button_, globalData_.background_color_, new_color_, "background");
    ui_->widget_->update();
}

// Обрабатывает нажатие кнопки для выбора цвета вершин и применяет его
void s21::View::OnVertexColorButtonClicked() {
    QColor new_color_ = QColorDialog::getColor(Qt::white, this, "Choose color");
    controller_->ControllerCalcStyleSheetForButton(ui_->vertex_color_button_, globalData_.vertex_color_, new_color_, "vertex");
    ui_->widget_->update();
}

// Сбрасывает цвета кнопок на значения по умолчанию
void s21::View::ResetButtonColors() {
    controller_->ControllerResetButtonColors(ui_->background_color_button_, globalData_.background_color_,
                                            ui_->vertex_color_button_, globalData_.vertex_color_,
                                            ui_->line_color_button_, globalData_.line_color_);
    ui_->widget_->update();
}

// Устанавливает цвета кнопок на основе текущих настроек
void s21::View::SetButtonColors() {
    controller_->ControllerCalcStyleSheetForButton(ui_->vertex_color_button_, globalData_.vertex_color_,
                                                  globalData_.vertex_color_, "vertex");
    controller_->ControllerCalcStyleSheetForButton(ui_->background_color_button_, globalData_.background_color_,
                                                  globalData_.background_color_, "background");
    controller_->ControllerCalcStyleSheetForButton(ui_->line_color_button_, globalData_.line_color_,
                                                  globalData_.line_color_, "line");
    ui_->widget_->update();                                                  
}




// Обрабатывает изменение выбранного метода отображения и обновляет виджет
void s21::View::OnDisplayMethodBoxActivated(int index_) {
    ChangeDisplayMethodData(index_);
    ui_->widget_->update();
}

// Изменяет данные метода отображения на основе выбранного индекса
void s21::View::ChangeDisplayMethodData(int index_) {
    if (index_ == 0) {
        globalData_.display_method_ = 0;
        ui_->circle_square_size_edit_->setText("0.0");
        ui_->circle_square_size_label_->setText("Choose display method");
        ui_->circle_square_size_edit_->setReadOnly(true);
    } else if (index_ == 1) {
        globalData_.display_method_ = 1;
        ui_->circle_square_size_label_->setText("Circle radius");
        ui_->circle_square_size_edit_->setReadOnly(false);
    } else if (index_ == 2) {
        globalData_.display_method_ = 2;
        ui_->circle_square_size_label_->setText("Square size");
        ui_->circle_square_size_edit_->setReadOnly(false);
    }
}

// Очищает все настройки и восстанавливает значения по умолчанию
void s21::View::ClearSettings() {
    // app_settings_->clear();

    ui_->scrolling_speed_edit_->setText("0.0");
    ui_->x_shift_line_edit_->setText("0.0");
    ui_->y_shift_line_edit_->setText("0.0");
    ui_->z_shift_line_edit_->setText("0.0");

    ui_->x_rotation_line_edit_->setText("0.0");
    ui_->y_rotation_line_edit_->setText("0.0");
    ui_->z_rotation_line_edit_->setText("0.0");

    ui_->scale_edit_->setText("1.0");

    ui_->line_thickness_edit_->setText("1.0");

    ui_->line_type_box_->setCurrentIndex(0);
    ui_->display_method_box_->setCurrentIndex(0);

    ui_->filename_label_->clear();
    ui_->vertex_count_->clear();
    ui_->faces_count_->clear();

    globalData_.ClearGlobalSetting();
    controller_->ControllerClearObjData();
    ResetButtonColors();
    OpenFile();
    ui_->widget_->update();
}

// Функция сохранения настроек
void s21::View::SaveSettings() {

    QSettings app_settings_("settings.ini", QSettings::IniFormat);
    app_settings_.beginGroup("app_settings_");

    app_settings_.setValue("background_color_", globalData_.background_color_);
    app_settings_.setValue("line_color_", globalData_.line_color_);
    app_settings_.setValue("vertex_color_", globalData_.vertex_color_);

    app_settings_.setValue("filepath_", globalData_.filepath_);
    app_settings_.setValue("x_shift_", globalData_.x_shift_);
    app_settings_.setValue("y_shift_", globalData_.y_shift_);
    app_settings_.setValue("z_shift_", globalData_.z_shift_);
    app_settings_.setValue("x_rotate_", globalData_.x_rotate_);
    app_settings_.setValue("y_rotate_", globalData_.y_rotate_);
    app_settings_.setValue("z_rotate_", globalData_.z_rotate_);
    app_settings_.setValue("scale_", globalData_.scale_);

    app_settings_.setValue("line_width_", globalData_.line_width_);
    app_settings_.setValue("circle_square_size_", globalData_.circle_square_size_);

    app_settings_.setValue("line_type_", globalData_.line_type_);
    app_settings_.setValue("display_method_", globalData_.display_method_);
    app_settings_.setValue("projection_", globalData_.projection_);

    app_settings_.endGroup();
}

// Функция загрузки настроек
void s21::View::LoadSettings() {

    QSettings app_settings_("settings.ini", QSettings::IniFormat);
    app_settings_.beginGroup("app_settings_");
    qDebug() << "filepath: " << app_settings_.value("filePath_");
    if (app_settings_.value("filePath_").toString().isEmpty()) {
        qDebug() << "Loading settings...";

        globalData_.filepath_ = app_settings_.value("filepath_").toString();
        OpenFile();

        globalData_.background_color_ = app_settings_.value("background_color_").value<QColor>();
        controller_->ControllerCalcStyleSheetForButton(ui_->background_color_button_,
                                                       globalData_.base_background_color_,
                                                       globalData_.background_color_,
                                                       "background");
        globalData_.line_color_ = app_settings_.value("line_color_").value<QColor>();
        controller_->ControllerCalcStyleSheetForButton(ui_->line_color_button_,
                                                       globalData_.base_line_color_,
                                                       globalData_.line_color_,
                                                       "line");
        globalData_.vertex_color_ = app_settings_.value("vertex_color_").value<QColor>();
        controller_->ControllerCalcStyleSheetForButton(ui_->vertex_color_button_,
                                                       globalData_.base_vertex_color_,
                                                       globalData_.vertex_color_,
                                                       "vertex");


        globalData_.x_shift_ = app_settings_.value("x_shift_").toFloat();
        globalData_.y_shift_ = app_settings_.value("y_shift_").toFloat();
        globalData_.z_shift_ = app_settings_.value("z_shift_").toFloat();
        ui_->x_shift_line_edit_->setText(app_settings_.value("x_shift_").toString());
        ui_->y_shift_line_edit_->setText(app_settings_.value("y_shift_").toString());
        ui_->z_shift_line_edit_->setText(app_settings_.value("z_shift_").toString());
        controller_->ControllerShiftObject(ui_->x_shift_line_edit_->text(),
                                           ui_->y_shift_line_edit_->text(),
                                           ui_->z_shift_line_edit_->text());

        globalData_.x_rotate_ = app_settings_.value("x_rotate_").toFloat();
        globalData_.y_rotate_ = app_settings_.value("y_rotate_").toFloat();
        globalData_.z_rotate_ = app_settings_.value("z_rotate_").toFloat();
        ui_->x_rotation_line_edit_->setText(app_settings_.value("x_rotate_").toString());
        ui_->y_rotation_line_edit_->setText(app_settings_.value("y_rotate_").toString());
        ui_->z_rotation_line_edit_->setText(app_settings_.value("z_rotate_").toString());
        controller_->ControllerRotateObject(ui_->x_rotation_line_edit_->text(),
                                            ui_->y_rotation_line_edit_->text(),
                                            ui_->z_rotation_line_edit_->text());

        globalData_.scale_ = app_settings_.value("scale_").toFloat();
        ui_->scale_edit_->setText(app_settings_.value("scale_").toString());
        controller_->ControllerScaleObject(ui_->scale_edit_->text());

        globalData_.line_type_ = app_settings_.value("line_type_").toInt();
        ui_->line_type_box_->setCurrentIndex(globalData_.line_type_);

        globalData_.display_method_ = app_settings_.value("display_method_").toInt();
        ui_->display_method_box_->setCurrentIndex(globalData_.display_method_);
        ChangeDisplayMethodData(globalData_.display_method_);

        globalData_.projection_ = app_settings_.value("projection_").toInt();

        globalData_.line_width_ = app_settings_.value("line_width_").toFloat();
        ui_->line_thickness_edit_->setText(app_settings_.value("line_width_").toString());

        globalData_.circle_square_size_ = app_settings_.value("circle_square_size_").toFloat();
        ui_->circle_square_size_edit_->setText(app_settings_.value("circle_square_size_").toString());

        qDebug() << "Settings loaded";
    }
}

// Установка валидаторов для полей ввода
void s21::View::SetValidatorsToLineEdits() {
    ui_->scrolling_speed_edit_->setValidator(new QDoubleValidator(
        0, std::numeric_limits<double>::max(), 7, this));
    ui_->scrolling_speed_edit_->setText("1.0");

    ui_->line_thickness_edit_->setValidator(new QIntValidator(
        0, std::numeric_limits<int>::max(), this));
    ui_->line_thickness_edit_->setText("1");

    ui_->circle_square_size_edit_->setValidator(new QDoubleValidator(
        0, std::numeric_limits<double>::max(), 7, this));
    ui_->circle_square_size_edit_->setText("1.0");

    ui_->x_shift_line_edit_->setValidator(new QDoubleValidator(
        -std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
        7, this));
    ui_->x_shift_line_edit_->setText("0.0");
    ui_->y_shift_line_edit_->setValidator(new QDoubleValidator(
        -std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
        7, this));
    ui_->y_shift_line_edit_->setText("0.0");
    ui_->z_shift_line_edit_->setValidator(new QDoubleValidator(
        -std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
        7, this));
    ui_->z_shift_line_edit_->setText("0.0");

    ui_->x_rotation_line_edit_->setValidator(new QDoubleValidator(
        -std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
        7, this));
    ui_->x_rotation_line_edit_->setText("0.0");
    ui_->y_rotation_line_edit_->setValidator(new QDoubleValidator(
        -std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
        7, this));
    ui_->y_rotation_line_edit_->setText("0.0");
    ui_->z_rotation_line_edit_->setValidator(new QDoubleValidator(
        -std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
        7, this));
    ui_->z_rotation_line_edit_->setText("0.0");

    ui_->scale_edit_->setValidator(new QDoubleValidator(
        std::numeric_limits<float>::epsilon(), std::numeric_limits<float>::max(),
        7, this));
    ui_->scale_edit_->setText("1.0");
}


// Настройка соединений слотов и сигналов
void s21::View::SetConnectsToSlots() {
    connect(ui_->x_shift_line_edit_, &QLineEdit::editingFinished, this,
            &View::OnAxisShiftLineEdited);
    connect(ui_->y_shift_line_edit_, &QLineEdit::editingFinished, this,
            &View::OnAxisShiftLineEdited);
    connect(ui_->z_shift_line_edit_, &QLineEdit::editingFinished, this,
            &View::OnAxisShiftLineEdited);

    connect(ui_->x_rotation_line_edit_, &QLineEdit::editingFinished, this,
            &View::OnRotationLineEdited);
    connect(ui_->y_rotation_line_edit_, &QLineEdit::editingFinished, this,
            &View::OnRotationLineEdited);
    connect(ui_->z_rotation_line_edit_, &QLineEdit::editingFinished, this,
            &View::OnRotationLineEdited);

    connect(ui_->scale_edit_, &QLineEdit::editingFinished, this,
            &View::OnScaleLineEdited);

    connect(ui_->line_type_box_, &QComboBox::currentIndexChanged, this, &View::OnLineTypeBoxActivated);
    connect(ui_->line_thickness_edit_, &QLineEdit::editingFinished, this,
            &View::OnLineThicknessEdited);


    connect(ui_->circle_square_size_edit_, &QLineEdit::editingFinished, this,
            &View::OnCircleSquareSizeEdited);
    connect(ui_->display_method_box_, &QComboBox::currentIndexChanged, this, &View::OnDisplayMethodBoxActivated);

    connect(ui_->open_file_button_, &QAction::triggered, this,
            &View::ChooseFile);
    connect(ui_->close_file_button_, &QAction::triggered, this,
            &View::CloseFile);
    connect(ui_->delete_settings_button_, &QAction::triggered, this,
            &View::ClearSettings);
    connect(ui_->save_as_image_button_, &QAction::triggered, this,
            &View::SaveImage);
    connect(ui_->record_gif_button_, &QPushButton::released, this, &View::OnRecordGIFButtonClicked);

    connect(ui_->background_color_button_,&QPushButton::released, this, &View::OnBackgroundColorButtonClicked);
    connect(ui_->line_color_button_,&QPushButton::released, this, &View::OnLineColorButtonClicked);
    connect(ui_->vertex_color_button_,&QPushButton::released, this, &View::OnVertexColorButtonClicked);


    connect(ui_->perspective_button_, &QPushButton::released, this, &View::OnPerspectiveButtonClicked);
    connect(ui_->ortho_button_, &QPushButton::released, this, &View::OnOrthoButtonClicked);
}
