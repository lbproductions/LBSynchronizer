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

    void on_actionAll_files_triggered();

    void on_actionSynchronized_triggered();

    void on_actionUnsynchronized_triggered();

    void on_actionMissing_triggered();

    void on_actionRenamed_triggered();

    void on_actionUse_left_filenames_triggered();

    void on_actionUse_right_filenames_triggered();

private:
    Ui::MainWindow *ui;

    DirView* m_leftView;
    DirView* m_rightView;
};

#endif // MAINWINDOW_H
