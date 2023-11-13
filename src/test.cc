#include <gtest/gtest.h>

#include <vector>

#include "controller/controller.h"
#include "model/facade/facade.h"

using std::vector;

s21::Controller &controller = *s21::Controller::GetConnection();

TEST(simple_cube, move) {
  s21::Geometry *info;
  info = controller.ParserOfString("object/simple_cube.obj");
  EXPECT_EQ(info->vertices_count, 8);
  EXPECT_EQ(info->facets_count, 12);
  vector<double> arr;
  for (int i = 0; i < info->vertices_count * 3; i++) {
    arr.push_back(info->vertices[i]);
  }
  controller.MoveToX(1);
  controller.MoveToY(1);
  controller.MoveToZ(1);
  for (int i = 0; i < info->vertices_count * 3 - 2; i++) {
    EXPECT_TRUE(fabs((arr[i] + 1) - info->vertices[i]) < 0.00001);
  }
}

TEST(simple_cube, rotate_x) {
  s21::Geometry *info;
  info = controller.ParserOfString("object/simple_cube.obj");
  EXPECT_EQ(info->vertices_count, 8);
  EXPECT_EQ(info->facets_count, 12);
  vector<double> arr;
  for (int i = 0; i < info->vertices_count * 3; i++) {
    arr.push_back(info->vertices[i]);
  }
  controller.RotateToX(-2);
  controller.RotateToX(2);
  for (int i = 0; i < info->vertices_count * 3 - 2; i++) {
    EXPECT_TRUE(fabs(arr[i] - info->vertices[i]) < 0.00001);
  }
}

TEST(simple_cube, rotate_y) {
  s21::Geometry *info;
  info = controller.ParserOfString("object/simple_cube.obj");
  EXPECT_EQ(info->vertices_count, 8);
  EXPECT_EQ(info->facets_count, 12);
  vector<double> arr;
  for (int i = 0; i < info->vertices_count * 3; i++) {
    arr.push_back(info->vertices[i]);
  }
  controller.RotateToY(-2);
  controller.RotateToY(2);
  for (int i = 0; i < info->vertices_count * 3 - 2; i++) {
    EXPECT_TRUE(fabs(arr[i] - info->vertices[i]) < 0.00001);
  }
}

TEST(simple_cube, rotate_z) {
  s21::Geometry *info;
  info = controller.ParserOfString("object/simple_cube.obj");
  EXPECT_EQ(info->vertices_count, 8);
  EXPECT_EQ(info->facets_count, 12);
  vector<double> arr;
  for (int i = 0; i < info->vertices_count * 3; i++) {
    arr.push_back(info->vertices[i]);
  }
  controller.RotateToZ(-2);
  controller.RotateToZ(2);
  for (int i = 0; i < info->vertices_count * 3 - 2; i++) {
    EXPECT_TRUE(fabs(arr[i] - info->vertices[i]) < 0.00001);
  }
}
TEST(simple_cube, scale) {
  s21::Geometry *info;
  info = controller.ParserOfString("object/simple_cube.obj");
  EXPECT_EQ(info->vertices_count, 8);
  EXPECT_EQ(info->facets_count, 12);
  vector<double> arr;
  for (int i = 0; i < info->vertices_count * 3; i++) {
    arr.push_back(info->vertices[i]);
  }
  controller.Scale(5);
  for (int i = 0; i < info->vertices_count * 3 - 2; i++) {
    EXPECT_TRUE(fabs((arr[i] * 5) - info->vertices[i]) < 0.00001);
  }
}

TEST(teddy, info_file) {
  s21::Geometry *info;
  info = controller.ParserOfString("object/teddy.obj");
  EXPECT_EQ(info->vertices_count, 1598);
  EXPECT_EQ(info->facets_count, 3192);
}

TEST(simple_cube, class_check) {
  s21::Geometry *info;
  info = controller.ParserOfString("object/simple_cube.obj");

  s21::Figure figure;
  figure.SetCountPolygons(info->facets_count);
  figure.SetCountVertexes(info->vertices_count);
  vector<double> vertex;
  for (int i = 0; i < figure.GetCountVertexes() * 3; i++) {
    vertex.push_back(info->vertices[i]);
  }
  vector<int> facets;
  for (int i = 0; i < figure.GetCountPolygons() * 6; i++) {
    vertex.push_back(info->facets[i]);
  }
  figure.SetFacets(facets);
  figure.SetVertexes(vertex);

  EXPECT_EQ(figure.GetCountVertexes(), 8);
  EXPECT_EQ(figure.GetCountPolygons(), 12);
  controller.MoveToX(1);
  controller.MoveToY(1);
  controller.MoveToZ(1);
  for (int i = 0; i < figure.GetCountVertexes() * 3; i++) {
    EXPECT_TRUE(fabs(figure.GetVertexes()[i] - info->vertices[i] + 1) <
                0.000001);
  }
  for (size_t i = 0; i < figure.GetFacets().size(); i++) {
    EXPECT_TRUE(fabs(figure.GetFacets()[i] - info->facets[i]) < 0.000001);
  }
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
