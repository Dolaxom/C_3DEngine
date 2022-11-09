#include "mainwindow.h"

#include "./ui_mainwindow.h"

QLabel *filenamel = NULL;
QLabel *filenamel_value = NULL;
QLabel *verticesl = NULL;
QLabel *verticesl_value = NULL;
QLabel *edgesl = NULL;
QLabel *edgesl_value = NULL;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  qApp->installEventFilter(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::start() {
    create_info_labels();
    ui->camera->setFocus();

    ui->errl->setStyleSheet("color: grey;");
    display_error("N/A", "no model chosen for display.");

    // set style sheet for buttons
}

void MainWindow::focusChanged(QWidget* old, QWidget* now)
{
    QCheckBox *check_old = qobject_cast<QCheckBox*>(old);
    QCheckBox *check_now = qobject_cast<QCheckBox*>(now);

    if (check_old) {
        check_old->setStyleSheet("QCheckBox {border: 0px solid royalblue; border-radius: 2px;}");
    }
    if (check_now) {
        check_now->setStyleSheet("QCheckBox {border: 1px solid royalblue; border-radius: 2px;}");
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
  bool result = false;

  ui->camera->releaseKeyboard();

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
    } else {
      ui->camera->grabKeyboard();
    }
  }

  QObject::eventFilter(watched, event);
  return result;
}

void MainWindow::process_enterkey() {
//    if (ui->persc->hasFocus()) {
//        on_persc_clicked(!ui->persc->checkState());
//    } else if (ui->orthc->hasFocus()) {
//        on_orthc_clicked(!ui->orthc->checkState());
//    }
    //else
    if (ui->autorotationc->hasFocus()) {
        on_autorotationc_clicked(!ui->autorotationc->checkState());
    } else {
        on_visualizeb_clicked();
    }
}

void MainWindow::cycle_focus() {
    if (ui->meshd->hasFocus()) {
        ui->sxedit->setFocus();
    } else if (ui->sxedit->hasFocus()) {
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
        ui->ryedit->setFocus();
    } else if (ui->ryedit->hasFocus()) {
        ui->rzedit->setFocus();
    } else if (ui->rzedit->hasFocus()) {
        ui->autorotationc->setFocus();
    } else if (ui->autorotationc->hasFocus()) {
        ui->camera->setFocus();
        //
    } else {
        ui->meshd->setFocus();
    }
}

void MainWindow::on_visualizeb_clicked() {
    bool error = false;

    if (!error) {
        ui->resultl->setStyleSheet("color: green;");
        display_error("SUCCESS", "");
    } else {
        ui->resultl->setStyleSheet("color: red;");
        display_error("ERROR", "errortext errortext errortext");
    }
}

void MainWindow::on_screenb_clicked()
{
    // make a screenshot
}


void MainWindow::on_gifb_clicked()
{
    // record a gif
}

//void MainWindow::on_persc_clicked(bool checked)
//{
//    ui->persc->setChecked(checked);
//    ui->orthc->setChecked(!checked);
//}

//void MainWindow::on_orthc_clicked(bool checked)
//{
//    ui->orthc->setChecked(checked);
//    ui->persc->setChecked(!checked);
//}

void MainWindow::on_autorotationc_clicked(bool checked)
{
    ui->autorotationc->setChecked(checked);
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
    edgesl_value->setGeometry(pos_x + width, pos_y + upd_y + upd_y, width, height);

    filenamel->setText("filename: ");
    verticesl->setText("vertices: ");
    edgesl->setText("edges: ");
    update_info_values("n/a", "0", "0");
}

void MainWindow::update_info_values(QString filename, QString n_vertices, QString n_edges) {
    filenamel_value->setAlignment(Qt::AlignRight);
    verticesl_value->setAlignment(Qt::AlignRight);
    edgesl_value->setAlignment(Qt::AlignRight);

    filenamel_value->setText(filename);
    verticesl_value->setText(n_vertices);
    edgesl_value->setText(n_edges);
}

void MainWindow::display_error(QString result, QString message) {
    ui->errl->setText(message);
    ui->resultl->setText(result);
}

