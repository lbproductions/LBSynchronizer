#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class DirView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    DirView* m_tableWidgetLeft;
    DirView* m_tableWidgetRight;
};

#endif // MAINWINDOW_H
