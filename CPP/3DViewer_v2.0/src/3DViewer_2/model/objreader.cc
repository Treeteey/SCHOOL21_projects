#include "my_functions.h"

#include <iostream>
#include <fstream>
#include <sstream>

// Конструктор класса OBJReader
// Инициализирует объект, устанавливая начальное состояние переменных.
s21::OBJReader::OBJReader(){
  is_good_objfile_ = true;
  objreader_coords_.clear();
  objreader_faces_.clear();
  normals_.clear();
  tex_coords_.clear();
}

// Функция LoadOBJ
// Загружает данные из OBJ файла, парсит вершины, текстурные координаты, нормали и грани.
// Возвращает true, если файл загружен и распознан корректно, иначе возвращает false.
bool s21::OBJReader::LoadOBJ(const std::string &path)
{
    this->is_good_objfile_ = true;
  std::ifstream obj_file_(path);
    if (!obj_file_.is_open()) {
        std::cerr << "File not found!" << std::endl;
        this->is_good_objfile_ = false;
    }
    std::string line;
    std::vector<std::string> tokens;
    std::vector<long> face_;

    //so std::stof saves float instead of int
    std::locale::global(std::locale("C"));

    while (this->is_good_objfile_ == true && std::getline(obj_file_, line)) {
        tokens = SplitString(line, ' ');
        if (!tokens.empty()) {
            if (tokens[0] == "v") {
                if (tokens.size() == 4) {
                    this->objreader_coords_.emplace_back(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
                    continue;
                } else {
                    this->is_good_objfile_ = false;
                    std::cerr << "wrong vertex line: " << line << std::endl;
                }
            } else if (tokens[0] == "vt") {
                this->tex_coords_.emplace_back(std::stof(tokens[1]), std::stof(tokens[2]));
                continue;
            } else if (tokens[0] == "vn") {
                this->normals_.emplace_back(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
                continue;
            } else if (tokens[0] == "f") {
                std::vector<std::string> parts;
                for (size_t i = 1; i < tokens.size(); i++) {
                    parts = SplitString(tokens[i], '/');
                    if (!parts.empty()) {
                        face_.push_back(std::stol(parts[0]) - 1);  // Extract the vertex index
                    }
                    parts.clear();
                }
                this->objreader_faces_.push_back(face_);
                face_.clear();
            } // end "f" line
        }  // end "if(!tokens.empty())"
    }  // end while loop
  obj_file_.close();
  CheckObj();
  if(this->is_good_objfile_ == false){
    this->objreader_coords_.clear();
    this->objreader_faces_.clear();
  }
  return this->is_good_objfile_;
}



// Функция SplitString
// Разделяет строку на подстроки по указанному разделителю и возвращает их в виде вектора строк.
std::vector<std::string> s21::OBJReader::SplitString(const std::string str, char delim){
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string token;
  while(std::getline(ss, token, delim)){
      if(!token.empty())
        tokens.push_back(token);
  }
  return tokens;
}

// Функция PrintInfo
// Выводит информацию о загруженных координатах и гранях в консоль. Проверяет валидность данных перед выводом.
void s21::OBJReader::PrintInfo(){
  CheckObj();
  if(is_good_objfile_){
    std::cout << "coords:" << objreader_coords_.size() << std::endl;
    for(auto i : objreader_coords_){
      std::cout << i.x << " " << i.y << " " << i.z << std::endl;
    }
    std::cout << std::endl;
    std::cout << "faces:" << objreader_faces_.size() << std::endl;
    for(auto &i : objreader_faces_){
        for(const auto j : i){
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
  }
}

// Функция CheckObj
// Проверяет валидность OBJ файла путем сравнения индексов вершин в гранях с размером списка координат.
// Если файл некорректен, функция устанавливает флаг is_good_objfile_ в false.
void s21::OBJReader::CheckObj(){
    std::pair<long,long> p = FindMaxMinValueInFaces();
  if(static_cast<long>(objreader_coords_.size()) < p.first + 1 ){
    is_good_objfile_ = false;
    std::cout << "coords size" << objreader_coords_.size() << std::endl;
    std::cout << "wrong face data" << std::endl;
  }
  if(p.second < 0){
      is_good_objfile_ = false;
      std::cout << "wrong face data - negative vertex index!" << std::endl;
  }
}

// Функция FindMaxMinValueInFaces
// Находит и возвращает максимальное и минимальное значение индексов вершин среди всех граней в OBJ файле.
std::pair<long, long> s21::OBJReader::FindMaxMinValueInFaces() {
  long maxVal = -std::numeric_limits<long>::max(); // Initialize to minimum possible int value
  long minVal = std::numeric_limits<long>::max(); // Initialize to maxinun possible int value
  for (const std::vector<long>& face_ : objreader_faces_) {
    for (long val : face_) {
      if (val > maxVal) {
        maxVal = val;
      }
      if(val < minVal) minVal = val;
    }
  }
  std::cout << "max vertex: " << maxVal+1;
  return std::make_pair(maxVal, minVal);
}
