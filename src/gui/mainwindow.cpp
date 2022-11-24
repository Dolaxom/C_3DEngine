#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  start();

  qApp->installEventFilter(this);
  connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)), this, SLOT(focusChanged(QWidget*,QWidget*)), Qt::QueuedConnection);
  connect(ui->projections, SIGNAL(valueChanged(int)), this, SLOT(on_projections_valueChanged()), Qt::QueuedConnection);
  connect(ui->bgcolors, SIGNAL(valueChanged(int)), this, SLOT(on_bgcolors_valueChanged()), Qt::QueuedConnection);
  connect(ui->vertcolors, SIGNAL(valueChanged(int)), this, SLOT(on_vertcolors_valueChanged()), Qt::QueuedConnection);
  connect(ui->edgecolors, SIGNAL(valueChanged(int)), this, SLOT(on_edgecolors_valueChanged()), Qt::QueuedConnection);
  connect(ui->vertstyles, SIGNAL(valueChanged(int)), this, SLOT(on_vertstyles_valueChanged()), Qt::QueuedConnection);
  connect(ui->edgestyles, SIGNAL(valueChanged(int)), this, SLOT(on_edgestyles_valueChanged()), Qt::QueuedConnection);
}

MainWindow::~MainWindow() { delete ui; }

// PUBLIC SLOTS

void MainWindow::focusChanged(QWidget *old, QWidget *now) {
  QSpinBox *check_now = qobject_cast<QSpinBox *>(now);

  if (check_now) {
    QLineEdit *spinedit = check_now->findChild<QLineEdit*>();

    if (spinedit) {
        spinedit->setReadOnly(true);
        spinedit->deselect();
    }
  }
}

// PROTECTED

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
  bool result = false;

//  if (event->type() == QEvent::MouseMove) {
//    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
//    mouseMoveEvent(mouseEvent);
//  } else
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return) {
      result = process_enterkey();
    } else if (keyEvent->key() == Qt::Key_Alt) {
      result = process_altkey();
    } else if (keyEvent->key() == Qt::Key_Escape) {
      result = process_escapekey();
    } else if (keyEvent->key() == Qt::Key_F11) {
      result = process_fkey();
    }
  } else if (event->type() == QEvent::Resize) {
    view->resizeGL(ui->camera->width(), ui->camera->height());
  }

  QObject::eventFilter(watched, event);
  return result;
}

// PRIVATE SLOTS

void MainWindow::on_redrawb_clicked() {
  bool error = true;

  finalize_input_fields();
  error = check_values();

  if (!error) {
    update_openglwidget();

    if (view->getErrcode() != 0) {
        display_error("error when parsing mesh: " + ui->meshpathedit->text(), -2);
        update_info_labels(get_filename(ui->meshpathedit->text()), "0", "0");
    } else {
        display_error("", 0);
        update_info_labels(get_filename(ui->meshpathedit->text()),
                           QString::number(view->getPointsCount()),
                           QString::number(view->getPolygonsCount()));
    }
  } else {
    display_error("incorrect meshpath or input value(s); unable to proceed", -2);
  }
}

void MainWindow::on_screenb_clicked() {
  // take a screenshot
  qDebug() << "screen";
}

void MainWindow::on_gifb_clicked() {
  // record a gif
  qDebug() << "gif";
}

void MainWindow::on_autorotationc_clicked(bool checked) {
  ui->autorotationc->setChecked(checked);
}

void MainWindow::on_meshpathb_clicked() {
    QString fileName = QFileDialog::getOpenFileName(NULL, "open:", last_dirpath, "OBJ files (*.obj)");

    if (!fileName.isNull()) {
        last_dirpath = get_filedir(fileName);
        ui->meshpathedit->setText(fileName);
        on_redrawb_clicked();
    }
}

void MainWindow::on_projections_valueChanged()
{
    ui->projections->findChild<QLineEdit*>()->deselect();
    update_spinbox(ui->projections, "", "_" + projections.at(ui->projections->value()));
}

void MainWindow::on_bgcolors_valueChanged()
{
    ui->bgcolors->findChild<QLineEdit*>()->deselect();
    update_spinbox(ui->bgcolors, "", "_" + colors.at(ui->bgcolors->value()));
}

void MainWindow::on_vertcolors_valueChanged()
{
    ui->vertcolors->findChild<QLineEdit*>()->deselect();
    update_spinbox(ui->vertcolors, "", "_" + colors.at(ui->vertcolors->value()));
}

void MainWindow::on_edgecolors_valueChanged()
{
    ui->edgecolors->findChild<QLineEdit*>()->deselect();
    update_spinbox(ui->edgecolors, "", "_" + colors.at(ui->edgecolors->value()));
}

void MainWindow::on_vertstyles_valueChanged()
{
    ui->vertstyles->findChild<QLineEdit*>()->deselect();
    update_spinbox(ui->vertstyles, "", "_" + vert_styles.at(ui->vertstyles->value()));
}

void MainWindow::on_edgestyles_valueChanged()
{
    ui->edgestyles->findChild<QLineEdit*>()->deselect();
    update_spinbox(ui->edgestyles, "", "_" + edge_styles.at(ui->edgestyles->value()));
}

// PRIVATE

void MainWindow::start() {
  view = new OpenGLWidget(ui->camera);

  ui->errl->setStyleSheet("color: grey;");
  ui->errl->setText("");
  ui->resultl->setText("");

  init_meshpath();
  init_spinboxes();
  create_info_labels();

  ui->camera->setFocus();
}

void MainWindow::init_meshpath() {
    QDir def(def_dirpath);
    ui->meshpathedit->setPlaceholderText("(none)");

    if (!def.exists()) {
        last_dirpath = ".";
        display_error("failure when trying to navigate to the default location of the materials folder; "
                      "meshpath has been reset to point to the application directory.", 1);
    } else {
        last_dirpath = def_dirpath;
    }
}

void MainWindow::init_spinboxes() {
    ui->projections->setMaximum(projections.count() - 1);
    ui->bgcolors->setMaximum(colors.count() - 1);
    ui->vertcolors->setMaximum(colors.count() - 1);
    ui->edgecolors->setMaximum(colors.count() - 1);
    ui->vertstyles->setMaximum(vert_styles.count() - 1);
    ui->edgestyles->setMaximum(edge_styles.count() - 1);

    ui->vertcolors->setValue(1);
    ui->edgecolors->setValue(1);
    ui->edgesizes->setValue(0.01);

    on_projections_valueChanged();
    on_bgcolors_valueChanged();
    on_vertcolors_valueChanged();
    on_edgecolors_valueChanged();
    on_vertstyles_valueChanged();
    on_edgestyles_valueChanged();
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
  filenamel_value->setMinimumWidth(filename.length() * 10 + 10);
  filenamel_value->setMaximumWidth(filename.length() * 10 + 10);

  filenamel_value->setText(filename);
  verticesl_value->setText(n_vertices);
  edgesl_value->setText(n_edges);
}

void MainWindow::update_spinbox(QSpinBox *spinbox, QString prefix, QString suffix) {
    spinbox->setPrefix(prefix);
    spinbox->setSuffix(suffix);
}

void MainWindow::update_lineedit(QLineEdit *widget, QString add) {
  widget->setText(widget->text() + add);
  widget->setAlignment(Qt::AlignRight);
}

void MainWindow::update_openglwidget() {
    convert_to_rgb(ui->bgcolors->value(), bg_rgb);
    convert_to_rgb(ui->vertcolors->value(), vert_rgb);
    convert_to_rgb(ui->edgecolors->value(), edge_rgb);

    view->setPosition(ui->pxedit->text().toFloat(), ui->pyedit->text().toFloat(), ui->pzedit->text().toFloat());
    view->setRotation(ui->rxedit->text().toFloat(), ui->ryedit->text().toFloat(), ui->rzedit->text().toFloat());
    view->setScale(ui->sxedit->text().toFloat(), ui->syedit->text().toFloat(), ui->szedit->text().toFloat());
    view->setProjection(ui->projections->value());
    view->setColors(bg_rgb, vert_rgb, edge_rgb);
    view->setStyles(ui->vertstyles->value(), ui->edgestyles->value());
    view->setSizes(ui->vertsizes->value(), ui->edgesizes->value());
    view->setMeshpath(ui->meshpathedit->text());
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
    QFile finmesh(ui->meshpathedit->text());

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

void MainWindow::display_error(QString message, int errtype) {
  if (errtype == 0) {
      ui->resultl->setStyleSheet("color: green;");
      ui->resultl->setText("SUCCESS");
  } else if (errtype == 1) {
      ui->resultl->setStyleSheet("color: yellow;");
      ui->resultl->setText("WARNING");
  } else {
      ui->resultl->setStyleSheet("color: red;");
      ui->resultl->setText("ERROR");
  }
  ui->errl->setText(message);
}

QString MainWindow::get_filedir(QString fullpath) {
    QFileInfo fileInfo;
    fileInfo.setFile(fullpath);
    return fileInfo.absolutePath();
}

QString MainWindow::get_filename(QString fullpath) {
    QString fileName;
    QFileInfo fileInfo;

    fileInfo.setFile(fullpath);

    if (fileInfo.completeSuffix().isEmpty()) {
        fileName = fileInfo.completeBaseName();
    } else {
        fileName = fileInfo.completeBaseName() + "." + fileInfo.completeSuffix();
    }
    return fileName;
}

void MainWindow::convert_to_rgb(int index, float *rgb) {
    if (rgb) {
        switch (index) {
        case 0:     // black
            rgb[0] = 0, rgb[1] = 0, rgb[2] = 0;
            break;
        case 1:     // white
            rgb[0] = 1, rgb[1] = 1, rgb[2] = 1;
            break;
        case 2:     // grey
            rgb[0] = 0.5, rgb[1] = 0.5, rgb[2] = 0.5;
            break;
        case 3:     // red
            rgb[0] = 1, rgb[1] = 0, rgb[2] = 0;
            break;
        case 4:     // blue
            rgb[0] = 0, rgb[1] = 0, rgb[2] = 1;
            break;
        case 5:     // green
            rgb[0] = 0, rgb[1] = 1, rgb[2] = 0;
            break;
        case 6:     // yellow
            rgb[0] = 1, rgb[1] = 1, rgb[2] = 0;
            break;
        case 7:     // purple
            rgb[0] = 1, rgb[1] = 0, rgb[2] = 1;
            break;
        default:
            break;
        }
    }
}

bool MainWindow::process_altkey() {
    ui->camera->setFocus();
    return true;
}

bool MainWindow::process_fkey() {
    if (this->isFullScreen()) {
      showNormal();
    } else {
      showFullScreen();
    }
    return true;
}

bool MainWindow::process_enterkey() {
  if (ui->autorotationc->hasFocus()) {
    on_autorotationc_clicked(!ui->autorotationc->checkState());
  } else if (ui->gifb->hasFocus()) {
    on_gifb_clicked();
  } else if (ui->screenb->hasFocus()) {
    on_screenb_clicked();
  } else if (ui->meshpathb->hasFocus()) {
    on_meshpathb_clicked();
  } else {
    on_redrawb_clicked();
  }
  return true;
}

bool MainWindow::process_escapekey() {
    close();
    return true;
}

void MainWindow::read_settings() {
    QSettings settings("C_3DEngine");
}

void MainWindow::write_settings() {
    QSettings settings("C_3DEngine");

    settings.setValue("windowsize", this->geometry());
    settings.setValue("fullscreen", this->isFullScreen());

    settings.setValue("meshpath", ui->meshpathedit->text());
    settings.setValue("last_dirpath", last_dirpath);
    settings.setValue("projection", ui->projections->value());
    settings.setValue("pos_x", ui->pxedit->text());
    settings.setValue("pos_y", ui->pyedit->text());
    settings.setValue("pos_z", ui->pzedit->text());
    settings.setValue("rot_x", ui->rxedit->text());
    settings.setValue("rot_y", ui->ryedit->text());
    settings.setValue("rot_z", ui->rzedit->text());
    settings.setValue("scale_x", ui->sxedit->text());
    settings.setValue("scale_y", ui->syedit->text());
    settings.setValue("scale_z", ui->szedit->text());
    settings.setValue("bg_color", ui->bgcolors->value());
    settings.setValue("vert_color", ui->vertcolors->value());
    settings.setValue("edge_color", ui->edgecolors->value());
    settings.setValue("vert_style", ui->vertstyles->value());
    settings.setValue("edge_style", ui->edgestyles->value());
    settings.setValue("vert_size", ui->vertsizes->value());
    settings.setValue("edge_size", ui->edgesizes->value());
}
