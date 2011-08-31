#ifndef FILTERMODEL_H
#define FILTERMODEL_H

#include <QSortFilterProxyModel>

class DirModel;

class FilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit FilterModel(DirModel* model, QObject *parent = 0);

    enum Filter {
        AllFiles,
        Synchronized,
        Unsynchronized,
        Missing,
        Renamed
    };

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

    void setFilter(Filter filter);

private:
    Filter m_filter;
    DirModel* m_model;

};

#endif // FILTERMODEL_H
