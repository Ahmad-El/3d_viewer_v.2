#ifndef CPP4_3DVIEWER_V2_0_SRC_MODEL_PARSER_PARSER_H_
#define CPP4_3DVIEWER_V2_0_SRC_MODEL_PARSER_PARSER_H_

#include <string.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "../figure/figure.h"

typedef std::pair<int, int> Pairs;

namespace s21 {

struct Geometry {
  int vertices_count;
  int facets_count;
  int facets_max_size;
  double* vertices;
  int* facets;
  double x_min;
  double x_max;
  double y_min;
  double y_max;
  double z_min;
  double z_max;
};

class Parser {
 public:
  Parser();
  Geometry* ParserOfString(const std::string& file_name, Figure& figure);
  double* GetVertexArray();
  int GetSize();

 private:
  Geometry data;
  std::vector<double> vertexes_;
  std::vector<int> facets_;
  int count_vertexes_;
  int count_polygons_;
  void GetMinMax();
  void NormalizeObject();

  void Clear();
  std::vector<double> ParserStringFromFile(std::string& string_from_file);
  bool Check(std::string& string_from_file, char type);
  void ParserOfVertexes(std::string& string_from_file);
  void ParserOfFacets(std::string& string_from_file);
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_SRC_MODEL_PARSER_PARSER_H_