#ifndef DIRMODEL_H
#define DIRMODEL_H

#include <QFileSystemModel>

class DirModel : public QFileSystemModel
{
    Q_OBJECT
public:
    explicit DirModel(QObject *parent = 0);

    enum Columns {
        Status,
        Test
    };

    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex index(const QString & path, int column = 0 ) const;

    QModelIndex parent(const QModelIndex &child) const;

private:
    class FileInfo : public QObject
    {
    public:
        FileInfo(const QModelIndex& parentIndex, QObject* parent = 0);

        QString status;

        QModelIndex parent;
    };

    FileInfo* fileInfo(const QModelIndex &index) const;

    int m_columnCount;
    int originalColumnCount(const QModelIndex& index) const;
    QMap<QModelIndex, FileInfo*> m_fileInfos;
};

#endif // DIRMODEL_H
