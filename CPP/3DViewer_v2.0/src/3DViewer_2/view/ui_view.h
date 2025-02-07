
//*******************************************************************************
//** Form generated from reading UI file 'view.ui'
//**
//** Created by: Qt User Interface Compiler version 6.6.0
//**
//** WARNING! All changes made in this file will be lost when recompiling UI file!
//*******************************************************************************

#ifndef UI_VIEW_H
#define UI_VIEW_H

#include <QtCore/QVariant>
// #include <QtGui/QAction>
#include <QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

#include "../model/opengl_widget_class.h"

//QT_BEGIN_NAMESPACE

namespace s21{

class UiView
{
public:
    // Actions
    QAction* open_file_button_;
    QAction* close_file_button_;
    QAction* delete_settings_button_;
    QAction* save_as_image_button_;

    // Widgets
    QWidget* central_layout_;
    s21::OpenGLWidgetClass* widget_;

    // Layouts
    QGridLayout* grid_layout_;
    QGridLayout* grid_layout_2_;
    QGridLayout* grid_layout_3_;
    QHBoxLayout* horizontal_layout_;

    // Labels
    QLabel* filename_label_;
    QLabel* vertex_count_;
    QLabel* faces_count_;
    QLabel* label_7_;
    QLabel* label_6_;
    QLabel* label_4_;
    QLabel* line_thickness_label_;
    QLabel* label_;
    QLabel* label_10_;
    QLabel* label_3_;
    QLabel* label_2_;
    QLabel* label_5_;
    QLabel* label_8_;
    QLabel* circle_square_size_label_;
    QLabel* label_9_;

    // Line Edits
    QLineEdit* x_shift_line_edit_;
    QLineEdit* y_shift_line_edit_;
    QLineEdit* z_shift_line_edit_;
    QLineEdit* x_rotation_line_edit_;
    QLineEdit* y_rotation_line_edit_;
    QLineEdit* z_rotation_line_edit_;
    QLineEdit* scrolling_speed_edit_;
    QLineEdit* line_thickness_edit_;
    QLineEdit* scale_edit_;
    QLineEdit* circle_square_size_edit_;

    // Push Buttons
    QPushButton* ortho_button_;
    QPushButton* perspective_button_;
    QPushButton* line_color_button_;
    QPushButton* vertex_color_button_;
    QPushButton* background_color_button_;
    QPushButton* center_obj_view_;
    QPushButton* record_gif_button_;

    // Combo Boxes
    QComboBox* display_method_box_;
    QComboBox* line_type_box_;

    // Menus
    QMenuBar* menu_bar_;
    QMenu* menu_;
    QStatusBar* status_bar_;



    void SetupUi(QMainWindow* view) {
        if (view->objectName().isEmpty()) {
            view->setObjectName("VIewer");
        }
        view->resize(1140, 539);
        open_file_button_ = new QAction(view);
        open_file_button_->setObjectName("openFileButton");
        close_file_button_ = new QAction(view);
        close_file_button_->setObjectName("closeFileButton");
        delete_settings_button_ = new QAction(view);
        delete_settings_button_->setObjectName("deleteSettingsButton");
        save_as_image_button_ = new QAction(view);
        save_as_image_button_->setObjectName("saveAsImageButton");
        central_layout_ = new QWidget(view);
        central_layout_->setObjectName("CentralLAyout");
        grid_layout_ = new QGridLayout(central_layout_);
        grid_layout_->setObjectName("gridLayout");
        grid_layout_2_ = new QGridLayout();
        grid_layout_2_->setObjectName("gridLayout_2");
        grid_layout_2_->setContentsMargins(0, 0, 0, 0);
        filename_label_ = new QLabel(central_layout_);
        filename_label_->setObjectName("fileNameLabel");

        grid_layout_2_->addWidget(filename_label_, 1, 0, 1, 2);

        vertex_count_ = new QLabel(central_layout_);
        vertex_count_->setObjectName("vertexCount");
        vertex_count_->setMinimumSize(QSize(50, 30));
        vertex_count_->setMaximumSize(QSize(10000, 30));

        grid_layout_2_->addWidget(vertex_count_, 2, 0, 1, 1);

        faces_count_ = new QLabel(central_layout_);
        faces_count_->setObjectName("facesCount");
        faces_count_->setMinimumSize(QSize(50, 30));
        faces_count_->setMaximumSize(QSize(100000, 30));

        grid_layout_2_->addWidget(faces_count_, 2, 1, 1, 1);

        widget_ = new OpenGLWidgetClass(central_layout_);
        widget_->setObjectName("widget");
        QSizePolicy size_policy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        size_policy.setHorizontalStretch(0);
        size_policy.setVerticalStretch(1);
        size_policy.setHeightForWidth(widget_->sizePolicy().hasHeightForWidth());
        widget_->setSizePolicy(size_policy);
        widget_->setMinimumSize(QSize(300, 300));

        grid_layout_2_->addWidget(widget_, 0, 0, 1, 2);

        grid_layout_3_ = new QGridLayout();
        grid_layout_3_->setObjectName("gridLayout_3");
        y_rotation_line_edit_ = new QLineEdit(central_layout_);
        y_rotation_line_edit_->setObjectName("yRotationLineEdit");
        y_rotation_line_edit_->setMaximumSize(QSize(100, 16777215));

        grid_layout_3_->addWidget(y_rotation_line_edit_, 7, 0, 1, 1);

        ortho_button_ = new QPushButton(central_layout_);
        ortho_button_->setObjectName("orthoButton");
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ortho_button_->sizePolicy().hasHeightForWidth());
        ortho_button_->setSizePolicy(sizePolicy1);
        ortho_button_->setMinimumSize(QSize(100, 30));
        ortho_button_->setMaximumSize(QSize(100, 30));
        ortho_button_->setStyleSheet(QString::fromUtf8("QPushButton {\n"
                                                       "    /* Your other styles */\n"
                                                       "    padding: 6px; /* Optional: Adjust padding */\n"
                                                       "}"));

        grid_layout_3_->addWidget(ortho_button_, 0, 1, 1, 1);

        scale_edit_ = new QLineEdit(central_layout_);
        scale_edit_->setObjectName("scaleEdit");
        scale_edit_->setMaximumSize(QSize(100, 16777215));

        grid_layout_3_->addWidget(scale_edit_, 9, 0, 1, 1);

        label_7_ = new QLabel(central_layout_);
        label_7_->setObjectName("label_7");

        grid_layout_3_->addWidget(label_7_, 10, 1, 1, 1);

        perspective_button_ = new QPushButton(central_layout_);
        perspective_button_->setObjectName("perspectiveButton");
        sizePolicy1.setHeightForWidth(perspective_button_->sizePolicy().hasHeightForWidth());
        perspective_button_->setSizePolicy(sizePolicy1);
        perspective_button_->setMinimumSize(QSize(100, 30));
        perspective_button_->setMaximumSize(QSize(100, 30));

        grid_layout_3_->addWidget(perspective_button_, 0, 0, 1, 1);

        x_shift_line_edit_ = new QLineEdit(central_layout_);
        x_shift_line_edit_->setObjectName("xShiftLineEdit");
        x_shift_line_edit_->setMaximumSize(QSize(100, 16777215));

        grid_layout_3_->addWidget(x_shift_line_edit_, 3, 0, 1, 1);

        display_method_box_ = new QComboBox(central_layout_);
        display_method_box_->addItem(QString());
        display_method_box_->addItem(QString());
        display_method_box_->addItem(QString());
        display_method_box_->setObjectName("displayMethodBox");

        grid_layout_3_->addWidget(display_method_box_, 15, 0, 1, 1);

        label_6_ = new QLabel(central_layout_);
        label_6_->setObjectName("label_6");

        grid_layout_3_->addWidget(label_6_, 5, 1, 1, 1);

        line_type_box_ = new QComboBox(central_layout_);
        line_type_box_->addItem(QString());
        line_type_box_->addItem(QString());
        line_type_box_->setObjectName("lineTypeBox");
        line_type_box_->setMaximumSize(QSize(100, 16777215));

        grid_layout_3_->addWidget(line_type_box_, 10, 0, 1, 1);

        y_shift_line_edit_ = new QLineEdit(central_layout_);
        y_shift_line_edit_->setObjectName("yShiftLineEdit");
        y_shift_line_edit_->setMaximumSize(QSize(100, 16777215));

        grid_layout_3_->addWidget(y_shift_line_edit_, 4, 0, 1, 1);

        circle_square_size_edit_ = new QLineEdit(central_layout_);
        circle_square_size_edit_->setObjectName("circleSquareSizeEdit");
        circle_square_size_edit_->setMaximumSize(QSize(100, 16777215));

        grid_layout_3_->addWidget(circle_square_size_edit_, 16, 0, 1, 1);

        z_rotation_line_edit_ = new QLineEdit(central_layout_);
        z_rotation_line_edit_->setObjectName("zRotationLineEdit");
        z_rotation_line_edit_->setMaximumSize(QSize(100, 16777215));

        grid_layout_3_->addWidget(z_rotation_line_edit_, 8, 0, 1, 1);

        horizontal_layout_ = new QHBoxLayout();
        horizontal_layout_->setObjectName("horizontalLayout");
        line_color_button_ = new QPushButton(central_layout_);
        line_color_button_->setObjectName("colorButton");
        line_color_button_->setMaximumSize(QSize(100, 16777215));

        horizontal_layout_->addWidget(line_color_button_);

        vertex_color_button_ = new QPushButton(central_layout_);
        vertex_color_button_->setObjectName("vertexColorButton");
        vertex_color_button_->setMaximumSize(QSize(100, 16777215));

        horizontal_layout_->addWidget(vertex_color_button_);

        background_color_button_ = new QPushButton(central_layout_);
        background_color_button_->setObjectName("backgroundColorButton");
        background_color_button_->setMaximumSize(QSize(100, 16777215));

        horizontal_layout_->addWidget(background_color_button_);


        grid_layout_3_->addLayout(horizontal_layout_, 12, 0, 1, 2);

        label_4_ = new QLabel(central_layout_);
        label_4_->setObjectName("label_4");

        grid_layout_3_->addWidget(label_4_, 7, 1, 1, 1);

        line_thickness_label_ = new QLabel(central_layout_);
        line_thickness_label_->setObjectName("lineThicknessLabel");

        grid_layout_3_->addWidget(line_thickness_label_, 14, 1, 1, 1);

        label_ = new QLabel(central_layout_);
        label_->setObjectName("label");

        grid_layout_3_->addWidget(label_, 6, 1, 1, 1);

        center_obj_view_ = new QPushButton(central_layout_);
        center_obj_view_->setObjectName("centerObjView");

        grid_layout_3_->addWidget(center_obj_view_, 2, 0, 1, 2);

        label_10_ = new QLabel(central_layout_);
        label_10_->setObjectName("label_10");

        grid_layout_3_->addWidget(label_10_, 9, 1, 1, 1);

        label_3_ = new QLabel(central_layout_);
        label_3_->setObjectName("label_3");

        grid_layout_3_->addWidget(label_3_, 1, 1, 1, 1);

        scrolling_speed_edit_ = new QLineEdit(central_layout_);
        scrolling_speed_edit_->setObjectName("scrollingSpeed");
        scrolling_speed_edit_->setMaximumSize(QSize(100, 16777215));

        grid_layout_3_->addWidget(scrolling_speed_edit_, 1, 0, 1, 1);

        line_thickness_edit_ = new QLineEdit(central_layout_);
        line_thickness_edit_->setObjectName("lineThicknessEdit");
        line_thickness_edit_->setMaximumSize(QSize(100, 16777215));

        grid_layout_3_->addWidget(line_thickness_edit_, 14, 0, 1, 1);

        label_2_ = new QLabel(central_layout_);
        label_2_->setObjectName("label_2");

        grid_layout_3_->addWidget(label_2_, 3, 1, 1, 1);

        label_5_ = new QLabel(central_layout_);
        label_5_->setObjectName("label_5");

        grid_layout_3_->addWidget(label_5_, 4, 1, 1, 1);

        label_8_ = new QLabel(central_layout_);
        label_8_->setObjectName("label_8");

        grid_layout_3_->addWidget(label_8_, 8, 1, 1, 1);

        z_shift_line_edit_ = new QLineEdit(central_layout_);
        z_shift_line_edit_->setObjectName("zShiftLineEdit");
        z_shift_line_edit_->setMaximumSize(QSize(100, 16777215));

        grid_layout_3_->addWidget(z_shift_line_edit_, 5, 0, 1, 1);

        circle_square_size_label_ = new QLabel(central_layout_);
        circle_square_size_label_->setObjectName("circleSquareSizeLabel");

        grid_layout_3_->addWidget(circle_square_size_label_, 16, 1, 1, 1);

        x_rotation_line_edit_ = new QLineEdit(central_layout_);
        x_rotation_line_edit_->setObjectName("xRotationLineEdit");
        x_rotation_line_edit_->setMaximumSize(QSize(100, 16777215));

        grid_layout_3_->addWidget(x_rotation_line_edit_, 6, 0, 1, 1);

        label_9_ = new QLabel(central_layout_);
        label_9_->setObjectName("label_9");

        grid_layout_3_->addWidget(label_9_, 15, 1, 1, 1);

        record_gif_button_ = new QPushButton(central_layout_);
        record_gif_button_->setObjectName("recordGIFButton");

        grid_layout_3_->addWidget(record_gif_button_, 17, 0, 1, 1);


        grid_layout_2_->addLayout(grid_layout_3_, 0, 2, 3, 1);

        grid_layout_2_->setColumnStretch(0, 1);

        grid_layout_->addLayout(grid_layout_2_, 0, 0, 1, 1);

        view->setCentralWidget(central_layout_);
        menu_bar_ = new QMenuBar(view);
        menu_bar_->setObjectName("menubar");
        menu_bar_->setGeometry(QRect(0, 0, 1140, 22));
        menu_ = new QMenu(menu_bar_);
        menu_->setObjectName("menu");
        view->setMenuBar(menu_bar_);
        status_bar_ = new QStatusBar(view);
        status_bar_->setObjectName("statusbar");
        view->setStatusBar(status_bar_);

        menu_bar_->addAction(menu_->menuAction());
        menu_->addAction(open_file_button_);
        menu_->addAction(close_file_button_);
        menu_->addAction(delete_settings_button_);
        menu_->addAction(save_as_image_button_);

        RetranslateUi(view);

        QMetaObject::connectSlotsByName(view);
    } // SetupUi


    void RetranslateUi(QMainWindow* view) {
        view->setWindowTitle(QCoreApplication::translate("VIewer", "VIewer", nullptr));
        open_file_button_->setText(QCoreApplication::translate("VIewer", "Open file", nullptr));
        close_file_button_->setText(QCoreApplication::translate("VIewer", "Close file", nullptr));
        delete_settings_button_->setText(QCoreApplication::translate("VIewer", "Delete saved settings", nullptr));
        save_as_image_button_->setText(QCoreApplication::translate("VIewer", "Save as image", nullptr));
        filename_label_->setText(QString());
        vertex_count_->setText(QString());
        faces_count_->setText(QString());
        ortho_button_->setText(QCoreApplication::translate("VIewer", "Orthographic", nullptr));
        label_7_->setText(QCoreApplication::translate("VIewer", "Choose type of line", nullptr));
        perspective_button_->setText(QCoreApplication::translate("VIewer", "Perspective ", nullptr));
        display_method_box_->setItemText(0, QCoreApplication::translate("VIewer", "none", nullptr));
        display_method_box_->setItemText(1, QCoreApplication::translate("VIewer", "circle", nullptr));
        display_method_box_->setItemText(2, QCoreApplication::translate("VIewer", "square", nullptr));

        label_6_->setText(QCoreApplication::translate("VIewer", "Z-axis shift", nullptr));
        line_type_box_->setItemText(0, QCoreApplication::translate("VIewer", "solid line", nullptr));
        line_type_box_->setItemText(1, QCoreApplication::translate("VIewer", "dashed line", nullptr));

        line_color_button_->setText(QCoreApplication::translate("VIewer", "Line color", nullptr));
        vertex_color_button_->setText(QCoreApplication::translate("VIewer", "Vertex color", nullptr));
        background_color_button_->setText(QCoreApplication::translate("VIewer", "Background color", nullptr));
        label_4_->setText(QCoreApplication::translate("VIewer", "Y-rotation", nullptr));
        line_thickness_label_->setText(QCoreApplication::translate("VIewer", "Line thickness", nullptr));
        label_->setText(QCoreApplication::translate("VIewer", "X-rotation", nullptr));
        center_obj_view_->setText(QCoreApplication::translate("VIewer", "Center object in viewport", nullptr));
        label_10_->setText(QCoreApplication::translate("VIewer", "Scale", nullptr));
        label_3_->setText(QCoreApplication::translate("VIewer", "mouse scrolling speed", nullptr));
        label_2_->setText(QCoreApplication::translate("VIewer", "X-axis shift", nullptr));
        label_5_->setText(QCoreApplication::translate("VIewer", "Y-axis shift", nullptr));
        label_8_->setText(QCoreApplication::translate("VIewer", "Z-rotation", nullptr));
        circle_square_size_label_->setText(QCoreApplication::translate("VIewer", "TextLabel", nullptr));
        label_9_->setText(QCoreApplication::translate("VIewer", "Display method", nullptr));
        record_gif_button_->setText(QCoreApplication::translate("VIewer", "Record GIF", nullptr));
        menu_->setTitle(QCoreApplication::translate("VIewer", "File", nullptr));
    } // retranslateUi



    //    void SetupUi(QMainWindow *View)
    //    {
    //        if (View->objectName().isEmpty())
    //            View->setObjectName("VIewer");
    //        View->resize(1140, 539);
    //        openFileButton = new QAction(View);
    //        openFileButton->setObjectName("openFileButton");
    //        closeFileButton = new QAction(View);
    //        closeFileButton->setObjectName("closeFileButton");
    //        deleteSettingsButton = new QAction(View);
    //        deleteSettingsButton->setObjectName("deleteSettingsButton");
    //        saveAsImageButton = new QAction(View);
    //        saveAsImageButton->setObjectName("saveAsImageButton");
    //        CentralLAyout = new QWidget(View);
    //        CentralLAyout->setObjectName("CentralLAyout");
    //        gridLayout = new QGridLayout(CentralLAyout);
    //        gridLayout->setObjectName("gridLayout");
    //        gridLayout_2 = new QGridLayout();
    //        gridLayout_2->setObjectName("gridLayout_2");
    //        gridLayout_2->setContentsMargins(0, 0, 0, 0);
    //        fileNameLabel = new QLabel(CentralLAyout);
    //        fileNameLabel->setObjectName("fileNameLabel");

    //        gridLayout_2->addWidget(fileNameLabel, 1, 0, 1, 2);

    //        vertexCount = new QLabel(CentralLAyout);
    //        vertexCount->setObjectName("vertexCount");
    //        vertexCount->setMinimumSize(QSize(50, 30));
    //        vertexCount->setMaximumSize(QSize(10000, 30));

    //        gridLayout_2->addWidget(vertexCount, 2, 0, 1, 1);

    //        facesCount = new QLabel(CentralLAyout);
    //        facesCount->setObjectName("facesCount");
    //        facesCount->setMinimumSize(QSize(50, 30));
    //        facesCount->setMaximumSize(QSize(100000, 30));

    //        gridLayout_2->addWidget(facesCount, 2, 1, 1, 1);

    //        widget = new OpenGLWidgetClass(CentralLAyout);
    //        widget->setObjectName("widget");
    //        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //        sizePolicy.setHorizontalStretch(0);
    //        sizePolicy.setVerticalStretch(1);
    //        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
    //        widget->setSizePolicy(sizePolicy);
    //        widget->setMinimumSize(QSize(300, 300));

    //        gridLayout_2->addWidget(widget, 0, 0, 1, 2);

    //        gridLayout_3 = new QGridLayout();
    //        gridLayout_3->setObjectName("gridLayout_3");
    //        yRotationLineEdit = new QLineEdit(CentralLAyout);
    //        yRotationLineEdit->setObjectName("yRotationLineEdit");
    //        yRotationLineEdit->setMaximumSize(QSize(100, 16777215));

    //        gridLayout_3->addWidget(yRotationLineEdit, 7, 0, 1, 1);

    //        orthoButton = new QPushButton(CentralLAyout);
    //        orthoButton->setObjectName("orthoButton");
    //        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //        sizePolicy1.setHorizontalStretch(0);
    //        sizePolicy1.setVerticalStretch(0);
    //        sizePolicy1.setHeightForWidth(orthoButton->sizePolicy().hasHeightForWidth());
    //        orthoButton->setSizePolicy(sizePolicy1);
    //        orthoButton->setMinimumSize(QSize(100, 30));
    //        orthoButton->setMaximumSize(QSize(100, 30));
    //        orthoButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
    //                                                     "    /* Your other styles */\n"
    //                                                     "    padding: 6px; /* Optional: Adjust padding */\n"
    //                                                     "}"));

    //        gridLayout_3->addWidget(orthoButton, 0, 1, 1, 1);

    //        scaleEdit = new QLineEdit(CentralLAyout);
    //        scaleEdit->setObjectName("scaleEdit");
    //        scaleEdit->setMaximumSize(QSize(100, 16777215));

    //        gridLayout_3->addWidget(scaleEdit, 9, 0, 1, 1);

    //        label_7 = new QLabel(CentralLAyout);
    //        label_7->setObjectName("label_7");

    //        gridLayout_3->addWidget(label_7, 10, 1, 1, 1);

    //        perspectiveButton = new QPushButton(CentralLAyout);
    //        perspectiveButton->setObjectName("perspectiveButton");
    //        sizePolicy1.setHeightForWidth(perspectiveButton->sizePolicy().hasHeightForWidth());
    //        perspectiveButton->setSizePolicy(sizePolicy1);
    //        perspectiveButton->setMinimumSize(QSize(100, 30));
    //        perspectiveButton->setMaximumSize(QSize(100, 30));

    //        gridLayout_3->addWidget(perspectiveButton, 0, 0, 1, 1);

    //        xShiftLineEdit = new QLineEdit(CentralLAyout);
    //        xShiftLineEdit->setObjectName("xShiftLineEdit");
    //        xShiftLineEdit->setMaximumSize(QSize(100, 16777215));

    //        gridLayout_3->addWidget(xShiftLineEdit, 3, 0, 1, 1);

    //        displayMethodBox = new QComboBox(CentralLAyout);
    //        displayMethodBox->addItem(QString());
    //        displayMethodBox->addItem(QString());
    //        displayMethodBox->addItem(QString());
    //        displayMethodBox->setObjectName("displayMethodBox");

    //        gridLayout_3->addWidget(displayMethodBox, 15, 0, 1, 1);

    //        label_6 = new QLabel(CentralLAyout);
    //        label_6->setObjectName("label_6");

    //        gridLayout_3->addWidget(label_6, 5, 1, 1, 1);

    //        lineTypeBox = new QComboBox(CentralLAyout);
    //        lineTypeBox->addItem(QString());
    //        lineTypeBox->addItem(QString());
    //        lineTypeBox->setObjectName("lineTypeBox");
    //        lineTypeBox->setMaximumSize(QSize(100, 16777215));

    //        gridLayout_3->addWidget(lineTypeBox, 10, 0, 1, 1);

    //        yShiftLineEdit = new QLineEdit(CentralLAyout);
    //        yShiftLineEdit->setObjectName("yShiftLineEdit");
    //        yShiftLineEdit->setMaximumSize(QSize(100, 16777215));

    //        gridLayout_3->addWidget(yShiftLineEdit, 4, 0, 1, 1);

    //        circleSquareSizeEdit = new QLineEdit(CentralLAyout);
    //        circleSquareSizeEdit->setObjectName("circleSquareSizeEdit");
    //        circleSquareSizeEdit->setMaximumSize(QSize(100, 16777215));

    //        gridLayout_3->addWidget(circleSquareSizeEdit, 16, 0, 1, 1);

    //        zRotationLineEdit = new QLineEdit(CentralLAyout);
    //        zRotationLineEdit->setObjectName("zRotationLineEdit");
    //        zRotationLineEdit->setMaximumSize(QSize(100, 16777215));

    //        gridLayout_3->addWidget(zRotationLineEdit, 8, 0, 1, 1);

    //        horizontalLayout = new QHBoxLayout();
    //        horizontalLayout->setObjectName("horizontalLayout");
    //        colorButton = new QPushButton(CentralLAyout);
    //        colorButton->setObjectName("colorButton");
    //        colorButton->setMaximumSize(QSize(100, 16777215));

    //        horizontalLayout->addWidget(colorButton);

    //        vertexColorButton = new QPushButton(CentralLAyout);
    //        vertexColorButton->setObjectName("vertexColorButton");
    //        vertexColorButton->setMaximumSize(QSize(100, 16777215));

    //        horizontalLayout->addWidget(vertexColorButton);

    //        backgroundColorButton = new QPushButton(CentralLAyout);
    //        backgroundColorButton->setObjectName("backgroundColorButton");
    //        backgroundColorButton->setMaximumSize(QSize(100, 16777215));

    //        horizontalLayout->addWidget(backgroundColorButton);


    //        gridLayout_3->addLayout(horizontalLayout, 12, 0, 1, 2);

    //        label_4 = new QLabel(CentralLAyout);
    //        label_4->setObjectName("label_4");

    //        gridLayout_3->addWidget(label_4, 7, 1, 1, 1);

    //        lineThicknessLabel = new QLabel(CentralLAyout);
    //        lineThicknessLabel->setObjectName("lineThicknessLabel");

    //        gridLayout_3->addWidget(lineThicknessLabel, 14, 1, 1, 1);

    //        label = new QLabel(CentralLAyout);
    //        label->setObjectName("label");

    //        gridLayout_3->addWidget(label, 6, 1, 1, 1);

    //        centerObjView = new QPushButton(CentralLAyout);
    //        centerObjView->setObjectName("centerObjView");

    //        gridLayout_3->addWidget(centerObjView, 2, 0, 1, 2);

    //        label_10 = new QLabel(CentralLAyout);
    //        label_10->setObjectName("label_10");

    //        gridLayout_3->addWidget(label_10, 9, 1, 1, 1);

    //        label_3 = new QLabel(CentralLAyout);
    //        label_3->setObjectName("label_3");

    //        gridLayout_3->addWidget(label_3, 1, 1, 1, 1);

    //        scrollingSpeed = new QLineEdit(CentralLAyout);
    //        scrollingSpeed->setObjectName("scrollingSpeed");
    //        scrollingSpeed->setMaximumSize(QSize(100, 16777215));

    //        gridLayout_3->addWidget(scrollingSpeed, 1, 0, 1, 1);

    //        lineThicknessEdit = new QLineEdit(CentralLAyout);
    //        lineThicknessEdit->setObjectName("lineThicknessEdit");
    //        lineThicknessEdit->setMaximumSize(QSize(100, 16777215));

    //        gridLayout_3->addWidget(lineThicknessEdit, 14, 0, 1, 1);

    //        label_2 = new QLabel(CentralLAyout);
    //        label_2->setObjectName("label_2");

    //        gridLayout_3->addWidget(label_2, 3, 1, 1, 1);

    //        label_5 = new QLabel(CentralLAyout);
    //        label_5->setObjectName("label_5");

    //        gridLayout_3->addWidget(label_5, 4, 1, 1, 1);

    //        label_8 = new QLabel(CentralLAyout);
    //        label_8->setObjectName("label_8");

    //        gridLayout_3->addWidget(label_8, 8, 1, 1, 1);

    //        zShiftLineEdit = new QLineEdit(CentralLAyout);
    //        zShiftLineEdit->setObjectName("zShiftLineEdit");
    //        zShiftLineEdit->setMaximumSize(QSize(100, 16777215));

    //        gridLayout_3->addWidget(zShiftLineEdit, 5, 0, 1, 1);

    //        circleSquareSizeLabel = new QLabel(CentralLAyout);
    //        circleSquareSizeLabel->setObjectName("circleSquareSizeLabel");

    //        gridLayout_3->addWidget(circleSquareSizeLabel, 16, 1, 1, 1);

    //        xRotationLineEdit = new QLineEdit(CentralLAyout);
    //        xRotationLineEdit->setObjectName("xRotationLineEdit");
    //        xRotationLineEdit->setMaximumSize(QSize(100, 16777215));

    //        gridLayout_3->addWidget(xRotationLineEdit, 6, 0, 1, 1);

    //        label_9 = new QLabel(CentralLAyout);
    //        label_9->setObjectName("label_9");

    //        gridLayout_3->addWidget(label_9, 15, 1, 1, 1);

    //        recordGIFButton = new QPushButton(CentralLAyout);
    //        recordGIFButton->setObjectName("recordGIFButton");

    //        gridLayout_3->addWidget(recordGIFButton, 17, 0, 1, 1);


    //        gridLayout_2->addLayout(gridLayout_3, 0, 2, 3, 1);

    //        gridLayout_2->setColumnStretch(0, 1);

    //        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);

    //        View->setCentralWidget(CentralLAyout);
    //        menubar = new QMenuBar(View);
    //        menubar->setObjectName("menubar");
    //        menubar->setGeometry(QRect(0, 0, 1140, 22));
    //        menu = new QMenu(menubar);
    //        menu->setObjectName("menu");
    //        View->setMenuBar(menubar);
    //        statusbar = new QStatusBar(View);
    //        statusbar->setObjectName("statusbar");
    //        View->setStatusBar(statusbar);

    //        menubar->addAction(menu->menuAction());
    //        menu->addAction(openFileButton);
    //        menu->addAction(closeFileButton);
    //        menu->addAction(deleteSettingsButton);
    //        menu->addAction(saveAsImageButton);

    //        RetranslateUi(View);

    //        QMetaObject::connectSlotsByName(View);
    //    } // setupUi



    //    void RetranslateUi(QMainWindow *View)
    //    {
    //        View->setWindowTitle(QCoreApplication::translate("VIewer", "VIewer", nullptr));
    //        openFileButton->setText(QCoreApplication::translate("VIewer", "Open file", nullptr));
    //        closeFileButton->setText(QCoreApplication::translate("VIewer", "Close file", nullptr));
    //        deleteSettingsButton->setText(QCoreApplication::translate("VIewer", "Delete saved settings", nullptr));
    //        saveAsImageButton->setText(QCoreApplication::translate("VIewer", "Save as image", nullptr));
    //        fileNameLabel->setText(QString());
    //        vertexCount->setText(QString());
    //        facesCount->setText(QString());
    //        orthoButton->setText(QCoreApplication::translate("VIewer", "Orthographic", nullptr));
    //        label_7->setText(QCoreApplication::translate("VIewer", "Choose type of line", nullptr));
    //        perspectiveButton->setText(QCoreApplication::translate("VIewer", "Perspective ", nullptr));
    //        displayMethodBox->setItemText(0, QCoreApplication::translate("VIewer", "none", nullptr));
    //        displayMethodBox->setItemText(1, QCoreApplication::translate("VIewer", "circle", nullptr));
    //        displayMethodBox->setItemText(2, QCoreApplication::translate("VIewer", "square", nullptr));

    //        label_6->setText(QCoreApplication::translate("VIewer", "Z-axis shift", nullptr));
    //        lineTypeBox->setItemText(0, QCoreApplication::translate("VIewer", "solid line", nullptr));
    //        lineTypeBox->setItemText(1, QCoreApplication::translate("VIewer", "dashed line", nullptr));

    //        colorButton->setText(QCoreApplication::translate("VIewer", "Line color", nullptr));
    //        vertexColorButton->setText(QCoreApplication::translate("VIewer", "Vertex color", nullptr));
    //        backgroundColorButton->setText(QCoreApplication::translate("VIewer", "Background color", nullptr));
    //        label_4->setText(QCoreApplication::translate("VIewer", "Y-rotation", nullptr));
    //        lineThicknessLabel->setText(QCoreApplication::translate("VIewer", "Line thickness", nullptr));
    //        label->setText(QCoreApplication::translate("VIewer", "X-rotation", nullptr));
    //        centerObjView->setText(QCoreApplication::translate("VIewer", "Center object in viewport", nullptr));
    //        label_10->setText(QCoreApplication::translate("VIewer", "Scale", nullptr));
    //        label_3->setText(QCoreApplication::translate("VIewer", "mouse scrolling speed", nullptr));
    //        label_2->setText(QCoreApplication::translate("VIewer", "X-axis shift", nullptr));
    //        label_5->setText(QCoreApplication::translate("VIewer", "Y-axis shift", nullptr));
    //        label_8->setText(QCoreApplication::translate("VIewer", "Z-rotation", nullptr));
    //        circleSquareSizeLabel->setText(QCoreApplication::translate("VIewer", "TextLabel", nullptr));
    //        label_9->setText(QCoreApplication::translate("VIewer", "Display method", nullptr));
    //        recordGIFButton->setText(QCoreApplication::translate("VIewer", "Record GIF", nullptr));
    //        menu->setTitle(QCoreApplication::translate("VIewer", "File", nullptr));
    //    } // retranslateUi

};

//namespace Ui {
//class View: public Ui_View {};
//} // namespace Ui

//QT_END_NAMESPACE



} //end s21 namespace
#endif // UI_VIEW_H
