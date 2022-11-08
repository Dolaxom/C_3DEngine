#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtEvents>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void start();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_visualizeb_clicked();
    void display_error(QString result, QString errtext);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
