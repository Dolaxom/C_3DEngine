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

public slots:
    void focusChanged(QWidget* old, QWidget* now);

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_visualizeb_clicked();    
    void on_screenb_clicked();
    void on_gifb_clicked();
    //void on_persc_clicked(bool checked);
    //void on_orthc_clicked(bool checked);
    void on_autorotationc_clicked(bool checked);

private:
    void process_enterkey();
    void cycle_focus();
    void create_info_labels();
    void update_info_values(QString filename, QString n_vertices, QString n_edges);
    void display_error(QString result, QString message);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
