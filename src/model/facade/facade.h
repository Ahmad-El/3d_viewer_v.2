#ifndef CPP4_3DVIEWER_V2_0_SRC_FACADE_FACADE_H_
#define CPP4_3DVIEWER_V2_0_SRC_FACADE_FACADE_H_

#include <string.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "../affine/affine.h"
#include "../parser/parser.h"

namespace s21 {
class Facade {
 public:
  Geometry* ParserOfString(const std::string& file_name);
  void Clear();
  void RotateX(double angle);
  void RotateY(double angle);
  void RotateZ(double angle);
  void MoveToX(double angle);
  void MoveToY(double angle);
  void MoveToZ(double angle);
  void Zoom(double angle);
  int GetCountVertexes() const;
  int GetCountPolygons() const;
  void SetVertexes(std::vector<double>& vertexes);
  void SetFacets(std::vector<int>& facets);
  void SetCountVertexes(int count_vertexes);
  void SetCountPolygons(int count_polygons);

 private:
  Parser parser_;
  Figure figure_;
  Affine affine_;
};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_0_SRC_FACADE_FACADE_H_
