#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tablewidget.h"
#include "filemanager.h"
#include "filtermodel.h"

#include <QSplitter>
#include <QSettings>
#include <QDesktopServices>
#include <QActionGroup>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_leftView(new DirView),
    m_rightView(new DirView)
{
    ui->setupUi(this);

    QSettings settings;

    QActionGroup* group = new QActionGroup(this);
    group->addAction(ui->actionAll_files);
    group->addAction(ui->actionSynchronized);
    group->addAction(ui->actionUnsynchronized);
    group->addAction(ui->actionMissing);
    group->addAction(ui->actionRenamed);

    m_leftView->setPath(settings.value("leftpath",QDesktopServices::storageLocation(QDesktopServices::HomeLocation)).toString());
    m_rightView->setPath(settings.value("rightpath",QDesktopServices::storageLocation(QDesktopServices::HomeLocation)).toString());

    QSplitter* splitter = new QSplitter;
    splitter->addWidget(m_leftView);
    splitter->addWidget(m_rightView);

    setCentralWidget(splitter);
    statusBar()->showMessage(tr("Please choose two folders and press \"Compare\""));
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
    statusBar()->showMessage(tr("Finished comparing. You may now synchronize"));
    ui->actionSynchronize->setEnabled(true);
}

void MainWindow::on_actionAll_files_triggered()
{
    m_leftView->filterModel()->setFilter(FilterModel::AllFiles);
    m_rightView->filterModel()->setFilter(FilterModel::AllFiles);
}

void MainWindow::on_actionSynchronized_triggered()
{
    m_leftView->filterModel()->setFilter(FilterModel::Synchronized);
    m_rightView->filterModel()->setFilter(FilterModel::Synchronized);
}

void MainWindow::on_actionUnsynchronized_triggered()
{
    m_leftView->filterModel()->setFilter(FilterModel::Unsynchronized);
    m_rightView->filterModel()->setFilter(FilterModel::Unsynchronized);
}

void MainWindow::on_actionMissing_triggered()
{
    m_leftView->filterModel()->setFilter(FilterModel::Missing);
    m_rightView->filterModel()->setFilter(FilterModel::Missing);
}

void MainWindow::on_actionRenamed_triggered()
{
    m_leftView->filterModel()->setFilter(FilterModel::Renamed);
    m_rightView->filterModel()->setFilter(FilterModel::Renamed);
}
