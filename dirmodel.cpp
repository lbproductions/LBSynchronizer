#include "dirmodel.h"

#include "filemanager.h"
#include "fileinfo.h"
#include "tablewidget.h"

#include <QDebug>

DirModel::DirModel(DirView *view) :
    QFileSystemModel(view),
    m_columnCount(QFileSystemModel::columnCount()),
    m_fileManager(new FileManager(rootPath(),this)),
    m_view(view)
{
}

void DirModel::setRootPath(const QString &path)
{
    QFileSystemModel::setRootPath(path);
    if(m_fileManager)
    {
        m_fileManager->deleteLater();
    }

    m_fileManager = new FileManager(path, this);
}

int DirModel::columnCount(const QModelIndex &parent) const
{
    return QFileSystemModel::columnCount(parent) + 2;
}

FileManager* DirModel::fileManager() const
{
    return m_fileManager;
}

QFileInfo DirModel::fileInfo(const QModelIndex& index) const
{
    return QFileSystemModel::fileInfo(index);
}

FileInfo* DirModel::fileInfo(int row, const QModelIndex &parent) const
{
    QString file = fileInfo(this->index(row,0,parent)).absoluteFilePath();
    return m_fileManager->fileInfo(file);
}

Qt::ItemFlags DirModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QFileSystemModel::flags(index);

    if(index.isValid())
    {
        return flags | Qt::ItemIsUserCheckable;
    }

    return flags;
}

bool DirModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::CheckStateRole && index.isValid())
    {
        QString file = fileInfo(index).absoluteFilePath();
        FileInfo* info = m_fileManager->fileInfo(file);

        if(info->status() != FileInfo::Synchronized)
        {
            info->setCheckState(static_cast<Qt::CheckState>(value.toInt()));
            if(hasChildren(index))
            {
                for(int i = 0; i < columnCount(index); ++i)
                {
                    setData(index.child(i,0),value,role);
                }
            }
            emit dataChanged(index,index);
            return true;
        }
    }

    return false;
}

QVariant DirModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::CheckStateRole && index.column() == 0)
    {
        QString file = fileInfo(index).absoluteFilePath();
        FileInfo* info = m_fileManager->fileInfo(file);
        return info->checkState();
    }

    if(index.column() < m_columnCount)
    {
        return QFileSystemModel::data(index,role);
    }

    int column = index.column() - m_columnCount;

    QString file = fileInfo(this->index(index.row(),0,index.parent())).absoluteFilePath();
    FileInfo* info = m_fileManager->fileInfo(file);

    if(role == Qt::DisplayRole)
    {
        switch(column)
        {
        case Status:
            return info->statusString();
        }
    }

    return QVariant();
}

QVariant DirModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(section < m_columnCount || orientation != Qt::Horizontal)
    {
        return QFileSystemModel::headerData(section,orientation,role);
    }

    int column = section - m_columnCount;

    if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch(column)
        {
        case Status:
            return tr("Status");
        case Test:
            return tr("Test");
        }
    }

    return QVariant();
}
