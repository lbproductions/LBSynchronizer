#include "dirmodel.h"

#include <QDebug>

DirModel::DirModel(QObject *parent) :
    QFileSystemModel(parent),
    m_columnCount(QFileSystemModel::columnCount())
{
}

int DirModel::columnCount(const QModelIndex &parent) const
{
    return QFileSystemModel::columnCount(parent) + 1;
}

int DirModel::originalColumnCount(const QModelIndex& parent) const
{
    return QFileSystemModel::columnCount(parent);
}

QVariant DirModel::data(const QModelIndex &index, int role) const
{
    if(index.column() < m_columnCount)
    {
        return QFileSystemModel::data(index,role);
    }

    int column = index.column() - m_columnCount;

    if(role == Qt::DisplayRole)
    {
        switch(column)
        {
        case Status:
            return fileInfo(index)->status;
        case Test:
            return fileInfo(index)->status;
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

DirModel::FileInfo* DirModel::fileInfo(const QModelIndex &index) const
{
    return static_cast<FileInfo*>(index.internalPointer());
}

QModelIndex DirModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row,column,parent))
    {
        return QModelIndex();
    }
    if(column < m_columnCount)
    {
        return QFileSystemModel::index(row,column,parent);
    }

    FileInfo* info = 0;

    if(column == m_columnCount)
    {
        qDebug()<< "test";
        info = new FileInfo(parent);
    }
    if(column > m_columnCount)
    {
        info = fileInfo(index(row,m_columnCount,parent));
    }

    return createIndex(row,column,info);
}

QModelIndex DirModel::parent(const QModelIndex &child) const
{
    if(child.column() < m_columnCount)
    {
        return QFileSystemModel::parent(child);
    }

    return fileInfo(child)->parent;
}

QModelIndex DirModel::index(const QString & path, int column) const
{
    return QFileSystemModel::index(path,column);
}

DirModel::FileInfo::FileInfo(const QModelIndex& parentIndex, QObject* parent) :
    QObject(parent),
    status(tr("Unknown")),
    parent(parentIndex)
{
}
