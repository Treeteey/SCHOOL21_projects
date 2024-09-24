#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QColor>
#include <QColorDialog>
#include <QDoubleValidator>
#include <QLineEdit>
#include <QSettings>
#include <QTimer>

// for recording
#include <QImage>
#include <QPainter>



#include "../controller/controller.h"
#include "../model/opengl_widget_class.h"
#include "../model/3rdparty/qtgifimage/src/gifimage/qgifimage.h"
#include "ui_view.h"


namespace s21 {

    class View : public QMainWindow
    {
        Q_OBJECT

    public:
        View(QWidget *parent = nullptr);
        ~View();

    private slots:
        void OnAxisShiftLineEdited();
        void OnCircleSquareSizeEdited();
        void OnLineThicknessEdited();
        void OnRotationLineEdited();
        void OnScaleLineEdited();

        void OnDisplayMethodBoxActivated(int index_);
        void OnLineTypeBoxActivated();

        void OnOrthoButtonClicked();
        void OnPerspectiveButtonClicked();

        void OnBackgroundColorButtonClicked();
        void OnLineColorButtonClicked();
        void OnVertexColorButtonClicked();

        void ResetButtonColors();  // to default colors
        void SetButtonColors();    // to openGLWidget colors

        void OnRecordGIFButtonClicked();
        void MakeGIF();

        void ChooseFile();
        void OpenFile();
        void CloseFile();

        void SaveSettings();
        void LoadSettings();
        void ClearSettings();

        void ChangeDisplayMethodData(int index_);

    private:
        // Classes
        Controller* controller_;
        s21::UiView *ui_;
        // QSettings *app_settings_;
        QGifImage *gif_images_;
        QTimer *timer_;

        GlobalData& globalData_;

        // Functions
        void SetValidatorsToLineEdits();
        void SetConnectsToSlots();
        void SaveImage();
        void SaveGifFrame();
    };

} //end namespace


#endif // VIEW_H




