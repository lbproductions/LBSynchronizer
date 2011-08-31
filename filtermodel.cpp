#include "filtermodel.h"

#include "dirmodel.h"
#include "fileinfo.h"

#include <QDebug>

FilterModel::FilterModel(DirModel* model, QObject *parent) :
    QSortFilterProxyModel(parent),
    m_filter(AllFiles),
    m_model(model)
{
    setSourceModel(m_model);
}

bool FilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    FileInfo* info = m_model->fileInfo(sourceRow, sourceParent);

    if(m_model->rootPath().startsWith(info->absoluteFilePath()) || info->absoluteFilePath() == QDir::currentPath())
    {
        return true;
    }

    if(info->status() == FileInfo::ContainsUnsynchronized)
    {
        return true;
    }

    switch(m_filter)
    {
    case Synchronized:
        return info->status() == FileInfo::Synchronized;
        break;
    case Unsynchronized:
        return info->status() == FileInfo::Same || info->status() == FileInfo::MissingHere || info->status() == FileInfo::MissingThere;
        break;
    case Missing:
        return info->status() == FileInfo::MissingHere || info->status() == FileInfo::MissingThere;
        break;
    case Renamed:
        return info->status() == FileInfo::Same;
        break;
    default:
    case AllFiles:
        return true;
        break;
    }

    return true;
}


void FilterModel::setFilter(Filter filter)
{
    m_filter = filter;
    invalidateFilter();
}
