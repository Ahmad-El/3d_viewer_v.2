#include "parser.h"

namespace s21 {

Parser::Parser() : count_vertexes_(0), count_polygons_(0) {}

Geometry* Parser::ParserOfString(const std::string& file_name, Figure& figure) {
  std::ifstream file(file_name);
  Clear();
  size_t last_dot = file_name.find_last_of('.');
  if (file.is_open() && file_name.substr(last_dot) == ".obj") {
    std::string string_from_file;
    while (std::getline(file, string_from_file)) {
      if (Check(string_from_file, 'v')) {
        ParserOfVertexes(string_from_file);
      } else if (Check(string_from_file, 'f')) {
        ParserOfFacets(string_from_file);
      }
    }
  }
  figure.Clear();
  figure.SetFacets(facets_);
  figure.SetVertexes(vertexes_);
  figure.SetCountPolygons(count_polygons_);
  figure.SetCountVertexes(count_vertexes_);
  data.vertices_count = count_vertexes_;
  data.vertices = vertexes_.data();
  data.facets = facets_.data();
  data.facets_max_size = facets_.size();
  data.facets_count = count_polygons_;
  if (this->GetSize() > 2) {
    GetMinMax();
    NormalizeObject();
  }

  return &data;
}

double* Parser::GetVertexArray() { return data.vertices; }

int Parser::GetSize() { return this->vertexes_.size(); }

void Parser::Clear() {
  vertexes_.clear();
  facets_.clear();
  count_vertexes_ = 0;
  count_polygons_ = 0;
}

bool Parser::Check(std::string& string_from_file, char type) {
  bool flag = false;
  while (!string_from_file.empty() && isspace(string_from_file.front())) {
    string_from_file.erase(string_from_file.begin());
  }
  if (!string_from_file.empty() && string_from_file.front() == type &&
      isspace(string_from_file.at(1))) {
    string_from_file.erase(string_from_file.begin());
    flag = true;
  }
  return flag;
}

void Parser::ParserOfVertexes(std::string& string_from_file) {
  std::vector<double> vect = ParserStringFromFile(string_from_file);
  for (size_t i = 0; i < 3; ++i) {
    vertexes_.push_back(vect.at(i));
  }
  count_vertexes_++;
}

std::vector<double> Parser::ParserStringFromFile(
    std::string& string_from_file) {
  std::vector<double> numbers;
  while (!string_from_file.empty()) {
    while (!string_from_file.empty() && isspace(string_from_file.at(0))) {
      string_from_file.erase(string_from_file.begin());
    }
    std::string number;
    number = string_from_file.substr(0, string_from_file.find_first_of(' '));
    if (!number.empty()) numbers.push_back(std::stod(number));
    string_from_file.erase(0, number.size());
  }
  return numbers;
}

void Parser::ParserOfFacets(std::string& string_from_file) {
  int facet = 0;
  std::vector<double> vect = ParserStringFromFile(string_from_file);
  vect.at(0) >= 0 ? facet = -1 : facet = count_vertexes_;
  facets_.push_back(vect.at(0) + facet);
  for (size_t i = 1; i < vect.size(); i++) {
    facets_.push_back(vect.at(i) + facet);
    facets_.push_back(vect.at(i) + facet);
  }
  facets_.push_back(vect.at(0) + facet);
  count_polygons_++;
}
void Parser::GetMinMax() {
  if (vertexes_.size() < 3) return;
  data.x_max = data.x_min = vertexes_[0];
  data.y_max = data.y_min = vertexes_[1];
  data.z_max = data.z_min = vertexes_[2];
  for (size_t i = 0; i < vertexes_.size() - 2; i += 3) {
    int x = i, y = i + 1, z = i + 2;
    if (vertexes_[x] > data.x_max)
      data.x_max = vertexes_[x];
    else if (vertexes_[x] < data.x_min)
      data.x_min = vertexes_[x];
    if (vertexes_[y] > data.y_max)
      data.y_max = vertexes_[y];
    else if (vertexes_[y] < data.y_min)
      data.y_min = vertexes_[y];
    if (vertexes_[z] > data.z_max)
      data.z_max = vertexes_[z];
    else if (vertexes_[z] < data.z_min)
      data.z_min = vertexes_[z];
  }
}

void Parser::NormalizeObject() {
  double center_x = (data.x_max + data.x_min) / 2;
  double center_y = (data.y_max + data.y_min) / 2;
  double center_z = (data.z_max + data.z_min) / 2;
  int size = data.vertices_count * 3;
  for (int i = 0; i < size - 2; i += 3) {
    int x = i, y = i + 1, z = i + 2;
    data.vertices[x] -= center_x;
    data.vertices[y] -= center_y;
    data.vertices[z] -= center_z;
  }
  data.x_max -= center_x;
  data.x_min -= center_x;
  data.z_max -= center_z;
  data.z_min -= center_z;
  data.y_max -= center_y;
  data.y_min -= center_y;
}
}  // namespace s21
