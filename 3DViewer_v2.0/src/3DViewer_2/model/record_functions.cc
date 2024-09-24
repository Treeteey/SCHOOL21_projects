#include "3rdparty/qtgifimage/src/gifimage/qgifimage.h"
#include "../view/ui_view.h"
#include "../view/view.h"



// Функция SaveImage
// Сохраняет текущее изображение из OpenGL виджета в файл с использованием диалогового окна для выбора имени файла и формата.
void s21::View::SaveImage() {
    // Get the size of the OpenGL widget
    QSize widget_size_ = ui_->widget_->size();

    // Create a QImage to render the OpenGL content
    QImage image(widget_size_, QImage::Format_RGB32);
    image.fill(Qt::white);  // Fill the image with a background color if needed

    // Create a QPainter to render the OpenGL content onto the QImage
    QPainter painter(&image);
    ui_->widget_->render(&painter);

    // Open a file dialog to choose the location and name of the image file
    QString save_file_path_ =
        QFileDialog::getSaveFileName(this, "Save Image", QDir::homePath(),
                                     "JPEG Files (*.jpg);;BMP Files (*.bmp)");

    if (!globalData_.filepath_.isEmpty()) {
        // Determine the format based on the file extension
        QString file_extension_ = QFileInfo(save_file_path_).suffix().toLower();
        QByteArray format_;

        if (file_extension_ == "jpg" || file_extension_ == "jpeg") {
            format_ = "JPEG";
        } else if (file_extension_ == "bmp") {
            format_ = "BMP";
        } else {
            // Default to JPEG if the extension is not recognized
            format_ = "JPEG";
            save_file_path_ += ".jpg";  // Append ".jpg" to the file path
        }

        // Save the QImage to the chosen file path and format
        image.save(save_file_path_, format_);
    }
}


//}
// Функция OnRecordGIFButtonClicked
// Обрабатывает нажатие кнопки для начала записи GIF. Открывает диалоговое окно для сохранения GIF файла и инициализирует процесс записи.
void s21::View::OnRecordGIFButtonClicked() {
    if (!globalData_.filepath_.isEmpty() && !globalData_.gif_recording_) {
        globalData_.gif_filename_ = QFileDialog::getSaveFileName(
            this, tr("Save screenshot"), "",
            tr("GIF screenshot (*.gif);;GIF screenshot(*.gif)"));
        if (globalData_.gif_filename_ != "") {
            globalData_.gif_recording_ = true;
            gif_images_ = new QGifImage;
            gif_images_->setDefaultDelay(10);
            timer_->setInterval(100);
            timer_->start();
            QColor temp_color_;
            controller_->ControllerCalcStyleSheetForButton(ui_->record_gif_button_, temp_color_, QColor(255, 0, 0), "temp");
        }
    }
}


// Функция MakeGIF
// Добавляет кадры к GIF и сохраняет его после завершения записи.
// Останавливает запись после достижения определенного количества кадров.
void s21::View::MakeGIF() {
    QImage image = ui_->widget_->grabFramebuffer();
    QImage scaled_image = image.scaled(ui_->widget_->size());
    gif_images_->addFrame(scaled_image);
    if (globalData_.images_count_ >= 50) {
        timer_->stop();
        gif_images_->save(globalData_.gif_filename_);
        globalData_.images_count_ = 0;
        delete gif_images_;
        globalData_.gif_recording_ = false;
        QColor temp_color_;
        controller_->ControllerCalcStyleSheetForButton(ui_->record_gif_button_, temp_color_, QColor(255, 255, 255), "temp");
    } else {
        globalData_.images_count_++;
    }
}
