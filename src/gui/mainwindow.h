#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QtEvents>

#include "./ui_mainwindow.h"
#include "openglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 public slots:
  void focusChanged(QWidget *old, QWidget *now);

 protected:
  bool eventFilter(QObject *watched, QEvent *event);

 private slots:
  void on_redrawb_clicked();
  void on_screenb_clicked();
  void on_gifb_clicked();
  void on_autorotationc_clicked(bool checked);
  void on_meshpathb_clicked();
  void on_projections_valueChanged();
  void on_bgcolors_valueChanged();
  void on_vertcolors_valueChanged();
  void on_edgecolors_valueChanged();
  void on_vertstyles_valueChanged();
  void on_edgestyles_valueChanged();

private:
  void start();
  void init_meshpath();
  void init_spinboxes();
  void create_info_labels();
  void update_info_labels(QString filename, QString n_vertices,
                          QString n_edges);
  void update_spinbox(QSpinBox *spinbox, QString prefix, QString suffix);
  void update_lineedit(QLineEdit *widget, QString add);
  void update_openglwidget();
  void finalize_input_fields();
  void finalize_lineedit(QWidget *widget);
  bool check_values();
  bool is_valid_mesh();
  bool is_valid_textvalue(QString text);
  void display_error(QString message, bool noerror);
  QString get_filedir(QString fullpath);
  QString get_filename(QString fullpath);
  bool process_altkey();
  bool process_fkey();
  bool process_enterkey();
  bool process_escapekey();

  QStringList projections = {"perspective", "orthogonal"};
  QStringList colors = {"black", "white", "grey", "red", "blue", "green", "yellow", "pink"};
  QStringList vert_styles = {"solid", "dashed"};
  QStringList edge_styles = {"none", "circle", "square"};
  QString def_dirpath = "../../materials/raw";
  QString last_dirpath = NULL;
  QLabel *filenamel = NULL;
  QLabel *filenamel_value = NULL;
  QLabel *verticesl = NULL;
  QLabel *verticesl_value = NULL;
  QLabel *edgesl = NULL;
  QLabel *edgesl_value = NULL;
  OpenGLWidget *view = NULL;

  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
