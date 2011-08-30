#include "mainwindow.h"

#include "tablewidget.h"

#include <QVBoxLayout>
#include <QDirModel>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget;
    QLayout* centralLayout = new QVBoxLayout;
    centralLayout->setContentsMargins(0,0,0,0);
    centralWidget->setLayout(centralLayout);

    QSplitter* splitter = new QSplitter;

    m_tableWidgetLeft = new DirView;
    m_tableWidgetRight = new DirView;

    splitter->addWidget(m_tableWidgetLeft);
    splitter->addWidget(m_tableWidgetRight);

    centralLayout->addWidget(splitter);

    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}
