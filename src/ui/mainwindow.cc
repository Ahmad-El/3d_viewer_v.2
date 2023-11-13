#include "mainwindow.h"

#include "openglgraphics.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setlocale(LC_NUMERIC, "C");
  InitConfig();
  QFileInfo file_info(ui->widget->filename);
  FileInfoFilling(file_info);
  ui->dotSize->setValue(ui->widget->dotSize);
  ui->lineWidthValue->setValue(ui->widget->lineWidth);
  ui->lineGapValue->setValue(ui->widget->gapSize);

  animation_ = new QMovie(":/new/prefix1/icons/cube_1.gif");
  ui->gif_display->setMovie(animation_);
  ui->gif_display->setVisible(true);
  ui->gif_display->raise();
  animation_->start();
}

MainWindow::~MainWindow() {
  ui->gif_display->setVisible(false);
  animation_->stop();
  delete animation_;
  delete ui;
}

void MainWindow::InitConfig() {
  QString style = QString(
      "background-color: transparent; color: #1affbc; border-style: solid; "
      "border-width: 1px; border-color: #1affbc; border-radius: 10px; ");
  ui->pushButton_3->setStyleSheet(style);
  style = QString(
      "background-color: transparent; color: #ff55d9; border-style: solid; "
      "border-width: 1px; border-color: #ff55d9; border-radius: 10px; ");
  ui->pushButton_lineColor->setStyleSheet(style);
  ui->pushButton_dotColor->setStyleSheet(style);

  ui->scale_move->setRange(1, 9);
  ui->scale_move->setSingleStep(1);
  ui->scale_move->setValue(1);
}
void MainWindow::on_pushButton_3_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  if (color.isValid()) {
    ui->widget->makeCurrent();
    ui->widget->backgroundColor = color;
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_openFile_clicked() {
  QString file = QFileDialog::getOpenFileName(this, "Выбрать файл для открытия",
                                              0, "Text Files (*.obj)");
  if (file.isEmpty()) {
    qDebug() << "Empty file";
  } else {
    ui->widget->filename = file;
    ui->widget->SetFileName();
    ui->widget->update();
    QFileInfo file_info(file);
    FileInfoFilling(file_info);
  }
}

void MainWindow::on_minus_x_clicked() {
  double value = ui->x_rotate_value->value() * (-1);
  ui->widget->controller.RotateToX(value);
  ui->widget->update();
}

void MainWindow::on_plus_x_clicked() {
  double value = ui->x_rotate_value->value();
  ui->widget->controller.RotateToX(value);
  ui->widget->update();
}

void MainWindow::on_minus_y_clicked() {
  double value = ui->y_rotate_value->value() * (-1);
  ui->widget->controller.RotateToY(value);
  ui->widget->update();
}

void MainWindow::on_plus_y_clicked() {
  double value = ui->y_rotate_value->value();
  ui->widget->controller.RotateToY(value);
  ui->widget->update();
}

void MainWindow::on_minus_z_clicked() {
  double value = ui->z_rotate_value->value() * (-1);
  ui->widget->controller.RotateToZ(value);
  ui->widget->update();
}

void MainWindow::on_plus_z_clicked() {
  double value = ui->z_rotate_value->value();
  ui->widget->controller.RotateToZ(value);
  ui->widget->update();
}

void MainWindow::on_move_x_minus_clicked() {
  double value = ui->x_move_value->value() * (-1);
  ui->widget->controller.MoveToX(value);
  ui->widget->update();
}

void MainWindow::on_move_x_plus_clicked() {
  double value = ui->x_move_value->value();
  ui->widget->controller.MoveToX(value);
  ui->widget->update();
}

void MainWindow::on_move_y_minus_clicked() {
  double value = ui->y_move_value->value() * (-1);
  ui->widget->controller.MoveToY(value);
  ui->widget->update();
}

void MainWindow::on_move_y_plus_clicked() {
  double value = ui->y_move_value->value();
  ui->widget->controller.MoveToY(value);
  ui->widget->update();
}

void MainWindow::on_move_z_minus_clicked() {
  double value = ui->z_move_value->value() * (-1);
  ui->widget->controller.MoveToZ(value);
  ui->widget->update();
}

void MainWindow::on_move_z_plus_clicked() {
  double value = ui->z_move_value->value();
  ui->widget->controller.MoveToZ(value);
  ui->widget->update();
}

void MainWindow::on_scale_down_clicked() {
  double value = (10 - ui->scale_move->value()) / 10.0;
  ui->widget->controller.Scale(value);
  ui->widget->update();
}

void MainWindow::on_scale_up_clicked() {
  double value = (10 - ui->scale_move->value()) / 10.0;
  ui->widget->controller.Scale(1.0 / value);
  ui->widget->update();
}

void MainWindow::on_perpective_mode_clicked() {
  if (ui->widget->perpectiveMode == false) {
    ui->widget->perpectiveMode = true;
    ui->widget->update();
  }
}

void MainWindow::on_paralel_mode_clicked() {
  if (ui->widget->perpectiveMode == true) {
    ui->widget->perpectiveMode = false;
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_lineColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  if (color.isValid()) {
    ui->widget->lineColor = color;
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_clicked() {
  ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_move_clicked() { ui->stackedWidget->setCurrentIndex(1); }

void MainWindow::on_rotate_clicked() { ui->stackedWidget->setCurrentIndex(2); }

void MainWindow::on_pushButton_6_clicked() {
  ui->widget->dashObj = false;
  ui->widget->lineObj = false;
  ui->widget->update();
}

void MainWindow::on_pushButton_5_clicked() {
  if (ui->widget->lineObj == false) {
    ui->widget->lineObj = true;
    ui->widget->dashObj = false;
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_4_clicked() {
  if (ui->widget->dashObj == false) {
    ui->widget->dashObj = true;
    ui->widget->lineObj = false;
    ui->widget->update();
  }
}

void MainWindow::on_line_2_clicked() { ui->stackedWidget->setCurrentIndex(3); }

void MainWindow::on_pushButtonWidth_clicked() {
  ui->widget->lineWidth = ui->lineWidthValue->value();
  ui->widget->update();
}

void MainWindow::on_pushButton_noDot_clicked() {
  ui->widget->dotObj = false;
  ui->widget->squareObj = false;
  ui->widget->update();
}

void MainWindow::on_pushButton_dot_clicked() {
  if (ui->widget->dotObj == false) {
    ui->widget->dotObj = true;
    ui->widget->squareObj = false;
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_dotSquare_clicked() {
  if (ui->widget->squareObj == false) {
    ui->widget->squareObj = true;
    ui->widget->dotObj = false;
    ui->widget->update();
  }
}

void MainWindow::on_dot_clicked() { ui->stackedWidget->setCurrentIndex(4); }

void MainWindow::on_pushButton_dotColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  if (color.isValid()) {
    ui->widget->dotColor = color;
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_dotSize_clicked() {
  ui->widget->dotSize = ui->dotSize->value();
  ui->widget->update();
}

void MainWindow::on_pushButton_bmpSave_clicked() {
  QString filePath = QFileDialog::getSaveFileName(nullptr, "Save Screenshot",
                                                  "", "BMP Files (*.bmp)");
  QPixmap screenshot(ui->widget->size());
  ui->widget->render(&screenshot);
  screenshot.save(filePath, "BMP");
}

void MainWindow::on_pushButton_takeJpeg_clicked() {
  QString filePath = QFileDialog::getSaveFileName(nullptr, "Save Screenshot",
                                                  "", "JPEG Files (*.jpeg)");
  QPixmap screenshot(ui->widget->size());
  ui->widget->render(&screenshot);
  screenshot.save(filePath, "JPEG");
}

void MainWindow::on_pushButtonLineGap_clicked() {
  ui->widget->gapSize = ui->lineGapValue->value();
  ui->widget->update();
}

void MainWindow::FileInfoFilling(QFileInfo file_info) {
  QString filename = file_info.fileName();
  QString filepath = file_info.absolutePath();
  QString filesize = QString::number(file_info.size() / 1000.0);
  QString v_count = QString::number(ui->widget->object->vertices_count);
  QString f_count = QString::number(ui->widget->object->facets_count);
  QString e_count = QString::number(EdgesCounting());
  ui->textEdit->setText(
      "filename: " + filename + "\nfilepath: " + filepath +
      "/\n\nfilesize: " + filesize + " kb\n\nvertices count: " + v_count +
      "\nedges count: " + e_count + "\nfacets count: " + f_count);
}

int MainWindow::EdgesCounting() {
  return (ui->widget->object->facets_count * 3) / 2;
}

void MainWindow::on_settings_clicked() {
  ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::StartTimer() {
  gif_ = new QGifImage(QSize(640, 480));
  timer_gif_ = new QTimer(this);
  connect(timer_gif_, &QTimer::timeout, this, &MainWindow::RecordGif);
  timer_gif_->start(100);
  frame_ = 0;
}

void MainWindow::RecordGif() {
  if (frame_ < 50) {
    const QRect rect(0, 0, 640, 480);
    QPixmap pixmap = ui->widget->grab(rect);
    QImage myImage = pixmap.toImage();
    frame_++;
    gif_->addFrame(myImage, 100);  // цифра это задержка
  } else {
    timer_gif_->stop();
    gif_->save(p_file_);
    p_file_->close();
    delete p_file_;
    delete gif_;
    QMessageBox::about(this, "status", "GIF saved");
  }
}

void MainWindow::on_pushButton_save_gif_clicked() {
  QString filename = QFileDialog::getSaveFileName(this, "Сохранить GIF",
                                                  QDir::homePath(), "*.gif");
  p_file_ = new QFile(filename);
  if (p_file_->open(QIODevice::WriteOnly)) {
    StartTimer();
  } else {
    qDebug() << "Error occured";
  }
}

void MainWindow::on_pushButton_7_clicked() {
  QString temp_file = ui->widget->filename;
  ui->widget->InitialSettings();
  ui->widget->filename = temp_file;
  ui->widget->update();
}
