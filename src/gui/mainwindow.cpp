#include "mainwindow.h"

QLabel *filenamel = NULL;
QLabel *filenamel_value = NULL;
QLabel *verticesl = NULL;
QLabel *verticesl_value = NULL;
QLabel *edgesl = NULL;
QLabel *edgesl_value = NULL;
OpenGLWidget *view = NULL;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  qApp->installEventFilter(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::start() {
  view = new OpenGLWidget(ui->camera);

  ui->errl->setStyleSheet("color: grey;");
  ui->errl->setText("");
  ui->resultl->setText("");

  init_meshpath();
  init_dropdowns();
  create_info_labels();

  ui->camera->setFocus();
}

void MainWindow::focusChanged(QWidget *old, QWidget *now) {
  QCheckBox *check_old = qobject_cast<QCheckBox *>(old);
  QCheckBox *check_now = qobject_cast<QCheckBox *>(now);

  if (check_old) {
    check_old->setStyleSheet(
        "QCheckBox {border: 0px solid royalblue; border-radius: 2px;}");
  }
  if (check_now) {
    check_now->setStyleSheet(
        "QCheckBox {border: 1px solid royalblue; border-radius: 2px;}");
  }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
  bool result = false;

  if (event->type() == QEvent::MouseMove) {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    mouseMoveEvent(mouseEvent);
  } else if (event->type() == QEvent::KeyPress) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return) {
      process_enterkey();
      result = true;
    } else if (keyEvent->key() == Qt::Key_Alt) {
      ui->camera->setFocus();
    } else if (keyEvent->key() == Qt::Key_Escape) {
      close();
      result = true;
    } else if (keyEvent->key() == Qt::Key_Control) {
      cycle_focus();
      result = true;
    } else if (keyEvent->key() == Qt::Key_Tab) {
      set_fullscreen();
      result = true;
    } else if (keyEvent->key() == Qt::Key_Space) {
      if (ui->projectiond->currentIndex() == 0) {
          ui->projectiond->setCurrentIndex(1);
      } else {
          ui->projectiond->setCurrentIndex(0);
      }
      on_visualizeb_clicked();
      result = true;
    }
  } else if (event->type() == QEvent::Resize) {
    view->resizeGL(ui->camera->width(), ui->camera->height());
  }

  QObject::eventFilter(watched, event);
  return result;
}

void MainWindow::cycle_focus() {
  // this is horrible and needs a rewrite

  if (ui->meshpathedit->hasFocus()) {
      ui->meshd->setFocus();
  } else if (ui->meshd->hasFocus()) {
      ui->projectiond->setFocus();
  } else if (ui->projectiond->hasFocus()) {
      ui->sxedit->setFocus();
  }
  else if (ui->sxedit->hasFocus()) {
    ui->syedit->setFocus();
  } else if (ui->syedit->hasFocus()) {
    ui->szedit->setFocus();
  } else if (ui->szedit->hasFocus()) {
    ui->pxedit->setFocus();
  } else if (ui->pxedit->hasFocus()) {
    ui->pyedit->setFocus();
  } else if (ui->pyedit->hasFocus()) {
    ui->pzedit->setFocus();
  } else if (ui->pzedit->hasFocus()) {
    ui->rxedit->setFocus();
  } else if (ui->rxedit->hasFocus()) {
    ui->autorotationc->setFocus();
  } else if (ui->autorotationc->hasFocus()) {
    ui->ryedit->setFocus();
  } else if (ui->ryedit->hasFocus()) {
    ui->rzedit->setFocus();
  } else if (ui->rzedit->hasFocus()) {
    ui->camera->setFocus();
    //
  } else {
    ui->meshpathedit->setFocus();
  }
}


void MainWindow::set_fullscreen() {
  if (this->isFullScreen()) {
    showNormal();
  } else {
    showFullScreen();
  }
}

void MainWindow::process_enterkey() {
  if (ui->autorotationc->hasFocus()) {
    on_autorotationc_clicked(!ui->autorotationc->checkState());
  } else if (ui->meshpathedit->hasFocus()) {
    on_meshpathedit_editingFinished();
  } else if (ui->meshd->hasFocus()) {
      //
  } else if (ui->projectiond->hasFocus()) {
      //
  } else if (ui->bgcolord->hasFocus()) {
      //
  } else if (ui->edgecolord->hasFocus()) {
      //
  } else if (ui->vertcolord->hasFocus()) {
      //
  } else if (ui->edgestyled->hasFocus()) {
      //
  } else if (ui->vertstyled->hasFocus()) {
      //
  } else if (ui->edgesizes->hasFocus()) {
      //
  } else if (ui->vertsizes->hasFocus()) {
      //
  }
  else {
    on_visualizeb_clicked();
  }
}

void MainWindow::on_visualizeb_clicked() {
  bool error = false;

  finalize_input_fields();
  error = check_values();

  if (!error) {
    update_openglwidget();
    if (view->getErrcode() != 0) {
        display_error("error when parsing mesh.", false);
    } else {
        display_error("", true);
    }
  } else {
    display_error("incorrect input value(s); unable to proceed", false);
  }
}

void MainWindow::on_screenb_clicked() {
  // take a screenshot
}

void MainWindow::on_gifb_clicked() {
  // record a gif
}

void MainWindow::on_autorotationc_clicked(bool checked) {
  ui->autorotationc->setChecked(checked);
}

void MainWindow::on_meshpathedit_editingFinished()
{
    QDir newpath(ui->meshpathedit->text());
    update_meshfields(newpath);
}

void MainWindow::init_meshpath() {
    QDir def("../../materials/raw");
    update_meshfields(def);

    if (!def.exists()) {
        ui->meshpathedit->setText("");
        ui->meshpathedit->setPlaceholderText("(none)");
        display_error("failure when trying to load the default path variable; set meshpath field manually.", false);
    }
}

void MainWindow::init_dropdowns() {
  QStringList colors = {"black", "white",  "red", "blue",
                        "green", "yellow", "pink"};

//  qDebug() << colors << colors.count();

  ui->projectiond->addItems({"perspective", "orthogonal"});
  ui->bgcolord->addItems(colors);
  ui->vertcolord->addItems(colors);
  ui->edgecolord->addItems(colors);
  ui->vertstyled->addItems({"none", "circle", "square"});
  ui->edgestyled->addItems({"solid", "dashed"});

  // switching between dropdown items crashes the entire program why?
}

void MainWindow::create_info_labels() {
  filenamel = new QLabel(this);
  filenamel_value = new QLabel(this);
  verticesl = new QLabel(this);
  verticesl_value = new QLabel(this);
  edgesl = new QLabel(this);
  edgesl_value = new QLabel(this);

  int pos_x = 15;
  int pos_y = 15;
  int upd_y = 20;
  int height = 20;
  int width = 70;

  filenamel->setGeometry(pos_x, pos_y, width, height);
  filenamel_value->setGeometry(pos_x + width, pos_y, width, height);
  verticesl->setGeometry(pos_x, pos_y + upd_y, width, height);
  verticesl_value->setGeometry(pos_x + width, pos_y + upd_y, width, height);
  edgesl->setGeometry(pos_x, pos_y + upd_y + upd_y, width, height);
  edgesl_value->setGeometry(pos_x + width, pos_y + upd_y + upd_y, width,
                            height);

  filenamel->setText("filename: ");
  verticesl->setText("vertices: ");
  edgesl->setText("edges: ");
  update_info_labels("n/a", "0", "0");
}

void MainWindow::update_info_labels(QString filename, QString n_vertices,
                                    QString n_edges) {
  filenamel_value->setAlignment(Qt::AlignRight);
  verticesl_value->setAlignment(Qt::AlignRight);
  edgesl_value->setAlignment(Qt::AlignRight);

  filenamel_value->setText(filename);
  verticesl_value->setText(n_vertices);
  edgesl_value->setText(n_edges);
}

void MainWindow::update_meshfields(QDir meshpath) {
    if (meshpath.exists()) {
        ui->meshpathedit->setText(meshpath.absolutePath());
        ui->meshd->clear();
        ui->meshd->addItems(meshpath.entryList(QDir::Files));
    } else {
        ui->meshd->clear();
        ui->meshd->addItem("(none)");
    }
}

void MainWindow::update_lineedit(QLineEdit *widget, QString add) {
  widget->setText(widget->text() + add);
  widget->setAlignment(Qt::AlignRight);
}

void MainWindow::update_openglwidget() {
    view->setProjection(ui->projectiond->currentIndex());
    view->setMeshpath(ui->meshpathedit->text() + "/" + ui->meshd->currentText());
    //
    view->update();
}

void MainWindow::finalize_input_fields() {
  finalize_lineedit(ui->sxedit);
  finalize_lineedit(ui->syedit);
  finalize_lineedit(ui->szedit);
  finalize_lineedit(ui->pxedit);
  finalize_lineedit(ui->pyedit);
  finalize_lineedit(ui->pzedit);
  finalize_lineedit(ui->rxedit);
  finalize_lineedit(ui->ryedit);
  finalize_lineedit(ui->rzedit);
  finalize_lineedit(ui->meshpathedit);
}

void MainWindow::finalize_lineedit(QWidget *widget) {
  QLineEdit *ledit = qobject_cast<QLineEdit *>(widget);

  if (ledit) {
    if (ledit->text().isEmpty()) {
      ledit->setText(ledit->placeholderText());
    }
  }
}

bool MainWindow::check_values() {
  bool error = true;

  if (is_valid_textvalue(ui->sxedit->text()) &&
      is_valid_textvalue(ui->syedit->text()) &&
      is_valid_textvalue(ui->szedit->text()) &&
      is_valid_textvalue(ui->pxedit->text()) &&
      is_valid_textvalue(ui->pyedit->text()) &&
      is_valid_textvalue(ui->pzedit->text()) &&
      is_valid_textvalue(ui->rxedit->text()) &&
      is_valid_textvalue(ui->ryedit->text()) &&
      is_valid_textvalue(ui->rzedit->text()) &&
      is_valid_mesh()) {
    error = false;
  }
  return error;
}

bool MainWindow::is_valid_mesh() {
    bool result = false;

    QString finpath = ui->meshpathedit->text() + "/" + ui->meshd->currentText();
    QFile finmesh(finpath);

    if (finmesh.exists()) {
        result = true;
    }
    return result;
}

bool MainWindow::is_valid_textvalue(QString text) {
  bool result = false;

  QChar first = text.front();
  QChar last = text.back();

  if ((first.isNumber() || first == '-') && last.isNumber()) {
    result = true;

    for (int i = 1; i < text.size() - 1; i++) {
      if ((i == 1 && !text[i].isNumber() && first == '-') ||
          (!text[i].isNumber() && text[i] != '.')) {
        result = false;
        break;
      }
    }
  }
  return result;
}

void MainWindow::display_error(QString message, bool noerror) {
  if (noerror) {
      ui->resultl->setStyleSheet("color: green;");
      ui->resultl->setText("SUCCESS");
  } else {
      ui->resultl->setStyleSheet("color: red;");
      ui->resultl->setText("ERROR");
  }
  ui->errl->setText(message);
}

