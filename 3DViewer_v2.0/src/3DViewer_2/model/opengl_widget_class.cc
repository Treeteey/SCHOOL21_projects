#include "opengl_widget_class.h"
#include <algorithm>
#include "../controller/controller.h"

//----------------------------- NEW-----------------------------
// Конструктор OpenGLWidgetClass инициализирует виджет OpenGL и загружает глобальные данные.

s21::OpenGLWidgetClass::OpenGLWidgetClass(QWidget *parent)
    : QOpenGLWidget(parent)
    , globalData_(GlobalData::getInstance())
{
}
// Деструктор OpenGLWidgetClass
s21::OpenGLWidgetClass::~OpenGLWidgetClass() {}

// Функция initializeGL() инициализирует функции OpenGL и настраивает начальные параметры,
// такие как цвет фона для корректного отображения объектов.
void s21::OpenGLWidgetClass::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(globalData_.base_background_color_.redF(), globalData_.base_background_color_.greenF(),
                 globalData_.base_background_color_.blueF(), 1);
    glEnable(GL_DEPTH_TEST); // Enable depth testing for z-culling
}

// Функция resizeGL(int w, int h) устанавливает новый размер окна отображения OpenGL
// и корректирует viewport (область отображения) в соответствии с новыми размерами окна.
void s21::OpenGLWidgetClass::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

// Функция paintGL() выполняет основную работу по отрисовке сцены. Она очищает экран,
// настраивает параметры отрисовки, загружает данные вершин, рисует примитивы (линии и точки)
// и, если требуется, настраивает вид точек (круги или квадраты).
void s21::OpenGLWidgetClass::paintGL() {
    glClearColor(globalData_.background_color_.redF(), globalData_.background_color_.greenF(),
                 globalData_.background_color_.blueF(), 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);

    glLineWidth(globalData_.line_width_);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    SetProjection();
    SetLineType();

    glColor3f(globalData_.line_color_.redF(), globalData_.line_color_.greenF(), globalData_.line_color_.blueF());

    std::vector<float> vertexData;
    const auto& coords_ = controller_->GetCoords();
    vertexData.reserve(coords_.size() * 3);
    for (const auto& vertex : coords_) {
        vertexData.push_back(vertex.x);
        vertexData.push_back(vertex.y);
        vertexData.push_back(vertex.z);
    }

    glVertexPointer(3, GL_FLOAT, 0, vertexData.data());
    std::vector<std::vector<long>> faces_ = controller_->GetFaces();
    for (const auto& face : faces_) {
        std::vector<GLuint> indices(face.begin(), face.end());
        glDrawElements(GL_LINE_LOOP, indices.size(), GL_UNSIGNED_INT, indices.data());
    }

    if(globalData_.display_method_ != 0){
        glPointSize(globalData_.circle_square_size_);
        if(globalData_.display_method_ == 1){
            glEnable(GL_POINT_SMOOTH);
        } else {
            glDisable(GL_POINT_SMOOTH);
        }
        glDrawElements(GL_POINTS, vertexData.size(), GL_FLOAT, vertexData.data());
    }

    glDisableClientState(GL_VERTEX_ARRAY);
}

// Функция SetLineType() задает тип линий, которые будут отрисовываться (сплошные или пунктирные).
// Если `line_type_` равен 0, используются сплошные линии; если 1 — включается режим пунктирной линии.
void s21::OpenGLWidgetClass::SetLineType(){
    if(globalData_.line_type_ == 0){
        glDisable(GL_LINE_STIPPLE);
    }else{
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x0F03);
    }
}

// Функция SetProjection() устанавливает проекцию (перспективную или ортографическую)
// для отображения 3D-сцены. В зависимости от соотношения сторон окна и выбора пользователя
// устанавливаются параметры фрустума или ортогонального проецирования.
void s21::OpenGLWidgetClass::SetProjection(){
    float aspect = width() / (float)height();
    if (globalData_.projection_ == 1) {
        if(aspect > 1){
            //doesnt matter if object located far in one axis
            //like x coords between -200 and -190
            //one need to determine volume and point camera at that object
            // when camera moves, glFrustum volume also moves WITH CAMERA
            glFrustum(- globalData_.max_radius_*aspect, globalData_.max_radius_*aspect,
                      - globalData_.max_radius_, globalData_.max_radius_,
                      5*globalData_.max_radius_, 100*globalData_.max_radius_);
            //translate to center of object and move it away to negative z axis
            //REMEMBER: to point camera at object, coords should be center of object in space
            //          BUT WITH NEGATIVE SIGN!!!
            //REMEMBER: camera's z coord should be between zNear and zFar:
            //          10max is between 5max and 100max
            glTranslatef(-globalData_.base_center_x_, -globalData_.base_center_y_, -10*globalData_.max_radius_);

        }else{
            glFrustum(- globalData_.max_radius_, globalData_.max_radius_,
                      - globalData_.max_radius_/aspect, globalData_.max_radius_/aspect,
                      5*globalData_.max_radius_, 100*globalData_.max_radius_);
            glTranslatef(-globalData_.base_center_x_, -globalData_.base_center_y_, -10*globalData_.max_radius_);
        }
    } else {
        //you need exactly locate rectangle at x,y,z space, not just its dimensions!
        if(aspect > 1){
            glOrtho(globalData_.base_center_x_ - globalData_.max_radius_*aspect, globalData_.base_center_x_ + globalData_.max_radius_*aspect,
                    globalData_.base_center_y_ - globalData_.max_radius_, globalData_.base_center_y_ + globalData_.max_radius_,
                    -(globalData_.base_center_z_ - globalData_.max_radius_), -(globalData_.base_center_z_ + globalData_.max_radius_));
        }else{
            glOrtho(globalData_.base_center_x_ - globalData_.max_radius_, globalData_.base_center_x_ + globalData_.max_radius_,
                    globalData_.base_center_y_ - globalData_.max_radius_/aspect, globalData_.base_center_y_ + globalData_.max_radius_/aspect,
                    -(globalData_.base_center_z_ - globalData_.max_radius_), -(globalData_.base_center_z_ + globalData_.max_radius_));
        }
        // по умолчанию будет смотреть в центр прямоугольника определенного в glOrtho() !!! не нужно его смещать
        // glTranslatef(0,0,  globalData_.base_center_z_ - max);
        glTranslatef(0,0,0);
    }
}
