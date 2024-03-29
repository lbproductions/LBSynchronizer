#ifndef DIRMODEL_H
#define DIRMODEL_H

#include <QFileSystemModel>

class FileManager;
class FileInfo;
class DirView;

class DirModel : public QFileSystemModel
{
    Q_OBJECT
public:
    explicit DirModel(DirView* view);

    enum Columns {
        Status,
        Test
    };

    int columnCount(const QModelIndex &parent) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void setRootPath(const QString &path);

    FileManager* fileManager() const;

    QFileInfo fileInfo(const QModelIndex& index) const;
    FileInfo* fileInfo(int row, const QModelIndex &parent) const;

//    QModelIndex index(int row, int column, const QModelIndex &parent) const;
//    QModelIndex index(const QString & path, int column = 0 ) const;

//    QModelIndex parent(const QModelIndex &child) const;

private:
    int m_columnCount;
    FileManager* m_fileManager;
    DirView* m_view;
};

#endif // DIRMODEL_H
