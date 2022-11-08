#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  qApp->installEventFilter(this);
}

MainWindow::~MainWindow() { delete ui; }

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
  bool result = false;

  ui->camera->releaseKeyboard();

  if (event->type() == QEvent::KeyPress) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return) {
      // result = true;
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
  return result;
}

void MainWindow::on_leftb_pressed() {}

void MainWindow::on_upb_pressed() {}

void MainWindow::on_rightb_pressed() {}

void MainWindow::on_downb_pressed() {}

void MainWindow::on_autoc_clicked(bool checked) {}

void MainWindow::on_autoc_stateChanged(int arg1) {}

void MainWindow::on_meshd_activated(int index) {}

void MainWindow::on_meshd_currentIndexChanged(int index) {}

void MainWindow::on_meshd_currentTextChanged(const QString &arg1) {}

void MainWindow::on_showb_clicked()
{

}

