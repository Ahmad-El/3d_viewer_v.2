#ifndef OPENGLGRAPHICS_H
#define OPENGLGRAPHICS_H

#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "../controller/controller.h"

#define RGB_MIN 1
#define RGB_MAX 255

class OpenGLGraphics : public QOpenGLWidget, public QOpenGLFunctions {
 public:
  OpenGLGraphics(QWidget *parent);
  ~OpenGLGraphics();

  QColor backgroundColor;
  QString filename;
  bool perpectiveMode;
  QColor lineColor, dotColor;
  bool dotObj, squareObj;
  bool lineObj, dashObj;
  float lineWidth;
  float dotSize;
  float gapSize;
  QJsonObject configObject;
  s21::Controller &controller = *s21::Controller::GetConnection();
  s21::Geometry *object;
  float xRot, yRot, zRot;
  QPoint mPos;

 public slots:
  void SetFileName();
  void ChangeBack();
  void ChangeViewMode();
  void WriteToJsonFile();
  void ReadFromJsonFile();
  void InitialSettings();
  void LoadConfigSettings();
  void SaveConfigSettings();

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private slots:
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void QColorToRGB(const QColor &color, float &r, float &g, float &b) const;
  float NormalizeColorValue(float val, float min, float max) const;
  void DrawObj();
  void DrawObjDot(int i);
  void DrawObjLine(int i);
};

#endif  // OPENGLGRAPHICS_H
