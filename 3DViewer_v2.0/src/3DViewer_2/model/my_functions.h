#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H


#include <string>
#include <vector>

#include <cmath>

namespace s21{

    struct GlobalData;

    struct Vector3D{
        Vector3D(float x_, float y_, float z_) : x(x_), y(y_), z(z_){}
        float x,y,z;

        Vector3D& operator+=(const Vector3D& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vector3D& operator*=(float mult_by_number_) {
            x *= mult_by_number_;
            y *= mult_by_number_;
            z *= mult_by_number_;
            return *this;
        }

        Vector3D& operator/=(float div_by_number_) {
            x /= div_by_number_;
            y /= div_by_number_;
            z /= div_by_number_;
            return *this;
        }
    };

    struct Vector2D{
        Vector2D(float x_, float y_) : x(x_), y(y_){}
        float x,y;
    };


    class OBJReader{
    public:
        OBJReader();
        bool LoadOBJ(const std::string &path);
        void PrintInfo();

        std::vector<Vector2D> tex_coords_;
        std::vector<Vector3D> normals_;
        std::vector<Vector3D> objreader_coords_;
        std::vector<std::vector<long>> objreader_faces_;
        bool is_good_objfile_;
    private:
        std::pair<long, long> FindMaxMinValueInFaces();
        std::vector<std::string> SplitString(const std::string str, char delim);
        void CheckObj();
    };

    class ShiftRotationScale
    {
    public:
        ShiftRotationScale();

        float x_shift_, y_shift_, z_shift_;
        float x_rotate_, y_rotate_, z_rotate_;
        float max_x_, max_y_, max_z_, min_x_, min_y_, min_z_;
        float center_x_, center_y_, center_z_;
        float scale_;

        void ShiftObject(std::vector<Vector3D>& coords, float x_shift_new_,
                         float y_shift_new_, float z_shift_new_);
        void RotateObject(std::vector<Vector3D>& coords, float x_rotate_new_,
                          float y_rotate_new_, float z_rotate_new_);
        void ScaleObject(std::vector<Vector3D>& coords, float new_scale);
        void FindObjectCenter(std::vector<Vector3D>& coords);
        void FindMinMax(std::vector<Vector3D>& coords);
        void ClearData();

    private:
        void ShiftObjectByDelta(std::vector<Vector3D>& coords, float x_delta,
                                float y_delta, float z_delta);


    };
}



#endif // MY_FUNCTIONS_H
