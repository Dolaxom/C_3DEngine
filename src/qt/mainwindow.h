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
    void create_info_labels();
    void update_info_values(QString filename, QString n_vertices, QString n_edges);
    void display_error(QString result, QString message);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
