#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class DirView;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionCompare_triggered();

private:
    Ui::MainWindow *ui;

    DirView* m_leftView;
    DirView* m_rightView;
};

#endif // MAINWINDOW_H
