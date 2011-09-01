#include "tablewidget.h"

#include "dirmodel.h"
#include "filtermodel.h"

#include <QTreeView>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>

DirView::DirView(QWidget *parent) :
    QWidget(parent),
    m_treeView(new QTreeView),
    m_buttonChoose(new QPushButton(tr("Choose..."))),
    m_lineEditFolder(new QLineEdit),
    m_model(new DirModel(this)),
    m_filterModel(0)
{
    m_treeView->setAlternatingRowColors(true);
    m_treeView->setFont(QFont("Lucida Grande",12));
    m_treeView->setFrameStyle(QFrame::NoFrame);
    m_treeView->setAttribute(Qt::WA_MacShowFocusRect, false);
    m_treeView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_treeView->setSelectionMode(QAbstractItemView::SingleSelection);

    m_treeView->setUniformRowHeights(true);
    m_treeView->setSortingEnabled(true);
    m_treeView->setHeaderHidden(false);

    m_filterModel = new FilterModel(m_model,this);
    m_treeView->setModel(m_filterModel);

    QHBoxLayout* folderChooserLayout = new QHBoxLayout;
    QWidget* folderChooserWidget = new QWidget;
    folderChooserWidget->setLayout(folderChooserLayout);

    QLabel* labelFolder = new QLabel(tr("Folder:"));
    folderChooserLayout->addWidget(labelFolder);
    folderChooserLayout->addWidget(m_lineEditFolder);
    folderChooserLayout->addWidget(m_buttonChoose);

    QVBoxLayout* l = new QVBoxLayout;
    l->setContentsMargins(0,0,0,0);
    l->addWidget(folderChooserWidget);
    l->addWidget(m_treeView);
    setLayout(l);

    connect(m_buttonChoose,SIGNAL(clicked()),this,SLOT(chooseDir()));
    connect(m_lineEditFolder,SIGNAL(returnPressed()),this,SLOT(setPathFromLineEdit()));

    this->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    this->updateGeometry();
}

FileManager* DirView::fileManager() const
{
    return m_model->fileManager();
}

FilterModel* DirView::filterModel() const
{
    return m_filterModel;
}

void DirView::setPath(const QString &path)
{
    m_model->setRootPath(path);
    m_treeView->setRootIndex(m_filterModel->mapFromSource(m_model->index(path)));
    m_lineEditFolder->setText(path);
}

void DirView::chooseDir()
{
    QFileDialog dialog(this);
    dialog.setDirectory(m_model->rootDirectory());
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setModal(true);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setOption(QFileDialog::ShowDirsOnly);
    dialog.setModal(true);

    dialog.exec();
    QStringList list = dialog.selectedFiles();
    if(!list.isEmpty())
    {
        QString path = list.at(0);
        setPath(path);
    }
}

QString DirView::path() const
{
    return m_lineEditFolder->text();
}

void DirView::setPathFromLineEdit()
{
    QDir dir(m_lineEditFolder->text());

    if(dir.exists())
    {
        setPath(dir.absolutePath());
    }
}
