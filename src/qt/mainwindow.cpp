#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  qApp->installEventFilter(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::start() {
    ui->errl->setStyleSheet("color: grey;");

    // set style sheet for buttons
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
      on_visualizeb_clicked();
      result = true;
    } else if (keyEvent->key() == Qt::Key_Alt) {
      // result = true;
    } else if (keyEvent->key() == Qt::Key_Escape) {
      close();
      result = true;
    } else if (keyEvent->key() == Qt::Key_Control) {
      ui->meshd->setFocus();
      result = true;
    } else {
      ui->camera->grabKeyboard();
    }
  }

  QObject::eventFilter(watched, event);
  return result;
}

void MainWindow::on_leftb_pressed() {
    // rotate left
}

void MainWindow::on_upb_pressed() {
    // rotate up
}

void MainWindow::on_rightb_pressed() {
    // rotate right
}

void MainWindow::on_downb_pressed() {
    // rotate down
}

void MainWindow::on_autoc_clicked(bool checked) {
    // auto rotation
}

void MainWindow::on_autoc_stateChanged(int arg1) {
    //
}

void MainWindow::on_meshd_activated(int index) {
    //
}

void MainWindow::on_meshd_currentIndexChanged(int index) {
    //
}

void MainWindow::on_meshd_currentTextChanged(const QString &arg1) {
    //
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

void MainWindow::display_error(QString result, QString errtext) {
    ui->errl->setText(errtext);
    ui->resultl->setText(result);
}

