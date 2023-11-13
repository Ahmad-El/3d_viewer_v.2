#include "facade.h"

namespace s21 {

void Facade::RotateX(double angle) {
  int size = parser_.GetSize();
  if (size < 3) return;
  affine_.SetStragegy(new s21::RotateByOx());
  affine_.Move(parser_.GetVertexArray(), size, angle);
}

void Facade::RotateY(double angle) {
  int size = parser_.GetSize();
  if (size < 3) return;
  affine_.SetStragegy(new s21::RotateByOy());
  affine_.Move(parser_.GetVertexArray(), size, angle);
}

void Facade::RotateZ(double angle) {
  int size = parser_.GetSize();
  if (size < 3) return;
  affine_.SetStragegy(new s21::RotateByOz());
  affine_.Move(parser_.GetVertexArray(), size, angle);
}

void Facade::MoveToX(double angle) {
  int size = parser_.GetSize();
  if (size < 3) return;
  affine_.SetStragegy(new s21::MoveX());
  affine_.Move(parser_.GetVertexArray(), size, angle);
}

void Facade::MoveToY(double angle) {
  int size = parser_.GetSize();
  if (size < 3) return;
  affine_.SetStragegy(new s21::MoveY());
  affine_.Move(parser_.GetVertexArray(), size, angle);
}

void Facade::MoveToZ(double angle) {
  int size = parser_.GetSize();
  if (size < 3) return;
  affine_.SetStragegy(new s21::MoveZ());
  affine_.Move(parser_.GetVertexArray(), size, angle);
}

void Facade::Zoom(double angle) {
  int size = parser_.GetSize();
  if (size < 3) return;
  affine_.SetStragegy(new s21::ScaleModel());
  affine_.Move(parser_.GetVertexArray(), size, angle);
}

Geometry* Facade::ParserOfString(const std::string& file_name) {
  return parser_.ParserOfString(file_name, figure_);
}

void Facade::Clear() { figure_.Clear(); }

int Facade::GetCountVertexes() const { return figure_.GetCountVertexes(); }
int Facade::GetCountPolygons() const { return figure_.GetCountPolygons(); }

void Facade::SetVertexes(std::vector<double>& vertexes) {
  figure_.SetVertexes(vertexes);
}
void Facade::SetFacets(std::vector<int>& facets) { figure_.SetFacets(facets); }
void Facade::SetCountVertexes(int count_vertexes) {
  figure_.SetCountVertexes(count_vertexes);
}
void Facade::SetCountPolygons(int count_polygons) {
  figure_.SetCountPolygons(count_polygons);
}
}  // namespace s21
