#ifndef CPP4_3DVIEWER_V2_0_SRC_CONTROLLER_CONTROLLER_H_
#define CPP4_3DVIEWER_V2_0_SRC_CONTROLLER_CONTROLLER_H_

#include "../model/facade/facade.h"

namespace s21 {
class Controller {
 public:
  Controller(const Controller&) = delete;
  void operator=(const Controller&) = delete;

  static Controller* GetConnection() {
    if (controller == nullptr) controller = new Controller();
    return controller;
  }
  Geometry* ParserOfString(const std::string& file_name);
  void RotateToX(double angle);
  void RotateToY(double angle);
  void RotateToZ(double angle);

  void MoveToX(double angle);
  void MoveToY(double angle);
  void MoveToZ(double angle);

  void Scale(double angle);

 private:
  Facade facade_;
  Controller() {}
  static Controller* controller;
};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_0_SRC_CONTROLLER_CONTROLLER_H_
