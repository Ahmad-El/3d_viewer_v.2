#ifndef CPP4_3DViewer_v2_AFFINE_AFFINE_H_
#define CPP4_3DViewer_v2_AFFINE_AFFINE_H_
#include <cmath>
#include <vector>

namespace s21 {

class Interface {
 public:
  virtual ~Interface() {}
  virtual void MoveObj(double *vertex, int n, double angle) = 0;
};

class Affine {
 public:
  Affine(){};
  Affine(Interface *interface) : interface_(interface) {}
  ~Affine() { delete interface_; }
  void SetStragegy(Interface *interface) { interface_ = interface; }
  void Move(double *vertex, int n, double angle) {
    interface_->MoveObj(vertex, n, angle);
    delete interface_;
  }

 private:
  Interface *interface_;
};

class RotateByOx : public Interface {
 public:
  void MoveObj(double *vertex, int n, double angle) override {
    for (int i = 0; i < n - 2; i += 3) {
      int y = i + 1, z = i + 2;
      double temp_y = vertex[y];
      double temp_z = vertex[z];
      vertex[y] = cos(angle) * temp_y - sin(angle) * temp_z;
      vertex[z] = sin(angle) * temp_y + cos(angle) * temp_z;
    }
  }
};

class RotateByOy : public Interface {
 public:
  void MoveObj(double *vertex, int n, double angle) override {
    for (int i = 0; i < n; i += 3) {
      int x = i, z = i + 2;
      double temp_x = vertex[x];
      double temp_z = vertex[z];
      vertex[x] = cos(angle) * temp_x + sin(angle) * temp_z;
      vertex[z] = -sin(angle) * temp_x + cos(angle) * temp_z;
    }
  }
};

class RotateByOz : public Interface {
 public:
  void MoveObj(double *vertex, int n, double angle) override {
    for (int i = 0; i < n; i += 3) {
      int x = i, y = i + 1;
      double temp_x = vertex[x];
      double temp_y = vertex[y];
      vertex[x] = cos(angle) * temp_x - sin(angle) * temp_y;
      vertex[y] = sin(angle) * temp_x + cos(angle) * temp_y;
    }
  }
};

class MoveX : public Interface {
 public:
  void MoveObj(double *vertex, int n, double angle) override {
    for (int i = 0; i < n; i += 3) {
      vertex[i] += angle;
    }
  }
};

class MoveY : public Interface {
 public:
  void MoveObj(double *vertex, int n, double angle) override {
    for (int i = 0; i < n; i += 3) {
      int y = i + 1;
      vertex[y] += angle;
    }
  }
};

class MoveZ : public Interface {
 public:
  void MoveObj(double *vertex, int n, double angle) override {
    for (int i = 0; i < n; i += 3) {
      int z = i + 2;
      vertex[z] += angle;
    }
  }
};

class ScaleModel : public Interface {
 public:
  void MoveObj(double *vertex, int n, double angle) override {
    if (!angle) return;
    for (int i = 0; i < n; i += 3) {
      int x = i, y = i + 1, z = i + 2;
      vertex[x] *= angle;
      vertex[y] *= angle;
      vertex[z] *= angle;
    }
  }
};

}  // namespace s21
#endif  // CPP4_3DViewer_v2_AFFINE_AFFINE_H_
