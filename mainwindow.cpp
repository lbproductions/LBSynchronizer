#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tablewidget.h"
#include "filemanager.h"

#include <QSplitter>
#include <QSettings>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_leftView(new DirView),
    m_rightView(new DirView)
{
    ui->setupUi(this);

    QSettings settings;

    m_leftView->setPath(settings.value("leftpath",QDesktopServices::storageLocation(QDesktopServices::HomeLocation)).toString());
    m_rightView->setPath(settings.value("rightpath",QDesktopServices::storageLocation(QDesktopServices::HomeLocation)).toString());

    QSplitter* splitter = new QSplitter;
    splitter->addWidget(m_leftView);
    splitter->addWidget(m_rightView);

    setCentralWidget(splitter);
    statusBar()->showMessage(tr("Please choose two foldersand press \"Compare\""));
}

MainWindow::~MainWindow()
{
    QSettings settings;

    settings.setValue("leftpath",m_leftView->path());
    settings.setValue("rightpath",m_rightView->path());

    delete ui;
}

void MainWindow::on_actionCompare_triggered()
{
    statusBar()->showMessage(tr("Comparing left to right..."));
    m_leftView->fileManager()->compareTo(m_rightView->fileManager());
    statusBar()->showMessage(tr("Comparing right to left..."));
    m_rightView->fileManager()->compareTo(m_leftView->fileManager());
    statusBar()->showMessage(tr("Finished"));
}
