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

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_leftb_pressed();

    void on_upb_pressed();

    void on_rightb_pressed();

    void on_downb_pressed();

    void on_autoc_clicked(bool checked);

    void on_autoc_stateChanged(int arg1);

    void on_meshd_activated(int index);

    void on_meshd_currentIndexChanged(int index);

    void on_meshd_currentTextChanged(const QString &arg1);

    void on_showb_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
