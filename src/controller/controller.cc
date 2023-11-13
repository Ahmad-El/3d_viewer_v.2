#include "controller.h"

namespace s21 {
Geometry* Controller::ParserOfString(const std::string& file_name) {
  facade_.Clear();
  return facade_.ParserOfString(file_name);
}

void Controller::RotateToX(double angle) { facade_.RotateX(angle); }
void Controller::RotateToY(double angle) { facade_.RotateY(angle); }
void Controller::RotateToZ(double angle) { facade_.RotateZ(angle); }

void Controller::MoveToX(double angle) { facade_.MoveToX(angle); }
void Controller::MoveToY(double angle) { facade_.MoveToY(angle); }
void Controller::MoveToZ(double angle) { facade_.MoveToZ(angle); }

void Controller::Scale(double angle) { facade_.Zoom(angle); }
Controller* Controller::controller = nullptr;

}  // namespace s21
