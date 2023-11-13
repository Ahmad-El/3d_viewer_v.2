#ifndef CPP4_3DVIEWER_V2_0_SRC_MODEL_FIGURE_FIGURE_H_
#define CPP4_3DVIEWER_V2_0_SRC_MODEL_FIGURE_FIGURE_H_

#include <vector>

namespace s21 {
class Figure {
 public:
  Figure();
  void Clear();

  const std::vector<double>& GetVertexes();
  const std::vector<int>& GetFacets();
  int GetCountVertexes() const;
  int GetCountPolygons() const;

  void SetVertexes(std::vector<double>& vertexes);
  void SetFacets(std::vector<int>& facets);
  void SetCountVertexes(int count_vertexes);
  void SetCountPolygons(int count_polygons);

 private:
  std::vector<double> vertexes_;
  std::vector<int> facets_;
  int count_vertexes_;
  int count_polygons_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_SRC_MODEL_FIGURE_FIGURE_H_