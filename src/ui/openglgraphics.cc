#include "openglgraphics.h"

#include <QCoreApplication>
OpenGLGraphics::OpenGLGraphics(QWidget *parent) : QOpenGLWidget(parent) {
  setlocale(LC_NUMERIC, "C");
  QString projectPath = QCoreApplication::applicationDirPath();
  if (QFile::exists(projectPath + "/config.json")) {
    ReadFromJsonFile();
    LoadConfigSettings();
  } else {
    InitialSettings();
  }
  SetFileName();
}

void OpenGLGraphics::WriteToJsonFile() {
  QJsonDocument jsonDoc(configObject);
  QString projectPath = QCoreApplication::applicationDirPath();
  QFile file(projectPath + "/config.json");
  file.open(QIODevice::WriteOnly | QIODevice::Truncate);
  file.write(jsonDoc.toJson());
  file.close();
}

void OpenGLGraphics::ReadFromJsonFile() {
  QString projectPath = QCoreApplication::applicationDirPath();
  QFile configFile(projectPath + "/config.json");
  configFile.open(QIODevice::ReadOnly);
  QByteArray configData = configFile.readAll();
  QJsonParseError parseError;
  QJsonDocument jsonDoc = QJsonDocument::fromJson(configData, &parseError);
  configObject = jsonDoc.object();
  configFile.close();
}

void OpenGLGraphics::LoadConfigSettings() {
  backgroundColor = configObject["backgroundColor"].toString();
  filename = configObject["filename"].toString();
  perpectiveMode = configObject["perpectiveMode"].toBool();
  lineColor = configObject["lineColor"].toString();
  dotColor = configObject["dotColor"].toString();
  dotObj = configObject["dotObj"].toBool();
  lineObj = configObject["lineObj"].toBool();
  squareObj = configObject["squareObj"].toBool();
  dashObj = configObject["dashObj"].toBool();
  lineWidth = static_cast<float>(configObject["lineWidth"].toDouble());
  dotSize = static_cast<float>(configObject["dotSize"].toDouble());
  gapSize = static_cast<float>(configObject["gapSize"].toDouble());
}
void OpenGLGraphics::SaveConfigSettings() {
  configObject["backgroundColor"] = backgroundColor.name(QColor::HexArgb);
  configObject["filename"] = filename;
  configObject["perpectiveMode"] = perpectiveMode;
  configObject["lineColor"] = lineColor.name(QColor::HexArgb);
  configObject["dotColor"] = dotColor.name(QColor::HexArgb);
  configObject["dotObj"] = dotObj;
  configObject["lineObj"] = lineObj;
  configObject["squareObj"] = squareObj;
  configObject["dashObj"] = dashObj;
  configObject["lineWidth"] = lineWidth;
  configObject["dotSize"] = dotSize;
  configObject["gapSize"] = gapSize;
}

void OpenGLGraphics::InitialSettings() {
  backgroundColor = Qt::black;
  filename = "";
  perpectiveMode = false;
  lineColor = Qt::white;
  dotColor = Qt::white;
  dotObj = true;
  lineObj = true;
  squareObj = false;
  dashObj = false;
  lineWidth = 1.0f;
  dotSize = 1.0f;
  gapSize = 1.0f;
}

OpenGLGraphics::~OpenGLGraphics() {
  SaveConfigSettings();
  WriteToJsonFile();
}

void OpenGLGraphics::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void OpenGLGraphics::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void OpenGLGraphics::paintGL() {
  ChangeViewMode();
  ChangeBack();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  float far = fmax(fabs(object->z_max), fabs(object->z_min)) +
              fmax(fabs(object->y_max), fabs(object->y_min));
  if (far < 5) {
    far = 5;
  }
  glTranslated(0, 0, -far);
  glRotated(xRot, 1, 0, 0);
  glRotated(yRot, 0, 1, 0);
  DrawObj();
}

void OpenGLGraphics::DrawObj() {
  if (dotObj || squareObj) {
    float r, g, b;
    QColorToRGB(dotColor, r, g, b);
    glColor3f(r, g, b);
    DrawObjDot(0);
  }
  if (lineObj || dashObj) {
    float r, g, b;
    QColorToRGB(lineColor, r, g, b);
    glColor3f(r, g, b);
    DrawObjLine(0);
  }
}

void OpenGLGraphics::DrawObjDot(int ii) {
  int size = object->vertices_count * 3;
  glPointSize(dotSize);
  if (dotObj) glEnable(GL_POINT_SMOOTH);
  glBegin(GL_POINTS);
  for (int i = 0; i < size - 2; i += 3) {
    int x = i, y = i + 1, z = i + 2;
    double x_value = object->vertices[x];
    double y_value = object->vertices[y];
    double z_value = object->vertices[z];
    glVertex3d(x_value, y_value, z_value);
  }
  glEnd();
  glDisable(GL_POINT_SMOOTH);
}

void OpenGLGraphics::DrawObjLine(int ii) {
  glLineWidth(lineWidth);
  if (dashObj) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(gapSize, 0xAAAA);  // if 1 Pattern: 1010 1010 1010 1010
  }
  int size = object->facets_max_size;
  glVertexPointer(3, GL_DOUBLE, 0, object->vertices);
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawElements(GL_LINES, size, GL_UNSIGNED_INT, object->facets);
  glDisableClientState(GL_VERTEX_ARRAY);

  glDisable(GL_LINE_STIPPLE);
}

void OpenGLGraphics::QColorToRGB(const QColor &color, float &r, float &g,
                                 float &b) const {
  int red = color.red();
  int green = color.green();
  int blue = color.blue();
  r = NormalizeColorValue(red, RGB_MIN, RGB_MAX);
  g = NormalizeColorValue(green, RGB_MIN, RGB_MAX);
  b = NormalizeColorValue(blue, RGB_MIN, RGB_MAX);
}

float OpenGLGraphics::NormalizeColorValue(float val, float min,
                                          float max) const {
  return (val - min) / (max - min);
}

void OpenGLGraphics::ChangeBack() {
  float r, g, b, a = 1;
  QColorToRGB(backgroundColor, r, g, b);
  glClearColor(r, g, b, a);
}

void OpenGLGraphics::ChangeViewMode() {
  if (perpectiveMode == false) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, 1, 9999999);
    float value = 0.5 / object->y_max;
    glScalef(value, value, 1.0f);
  } else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 9999999);
  }
}

void OpenGLGraphics::SetFileName() {
  std::string file = filename.toStdString();
  object = controller.ParserOfString(file);
}

void OpenGLGraphics::mousePressEvent(QMouseEvent *mo) { mPos = mo->pos(); }
void OpenGLGraphics::mouseMoveEvent(QMouseEvent *mo) {
  xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}
