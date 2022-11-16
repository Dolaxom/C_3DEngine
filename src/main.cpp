#include <QApplication>

#include "gui/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;

  // qDebug() << a.applicationDirPath();
  QObject::connect(&a, SIGNAL(focusChanged(QWidget *, QWidget *)), &w,
                   SLOT(focusChanged(QWidget *, QWidget *)));
  w.start();
  w.show();
  return a.exec();
}
