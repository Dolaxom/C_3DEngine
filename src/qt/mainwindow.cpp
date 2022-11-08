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
    display_error("", "no model chosen");

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
      //ui->meshd->setFocus();
      result = true;
    } else {
      ui->camera->grabKeyboard();
    }
  }

  QObject::eventFilter(watched, event);
  return result;
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

