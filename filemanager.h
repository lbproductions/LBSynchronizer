#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QMap>
#include <QDir>

class FileInfo;

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(const QString& path, QObject *parent = 0);
    ~FileManager();

    FileInfo* fileInfo(const QString& file);

    void compareTo(FileManager* other);

signals:
    void fileAdded(FileInfo* info);

private:
    QDir m_path;
    QMap<QString, FileInfo*> m_fileInfos;

    bool compareTo(FileManager* other, const QString& path);

    QString findSameFileHere(FileManager* other, const QString& path, const QString& file);
    QString findSameFileThere(FileManager* other, const QString& path, const QString& file);

    void makeRelativePath(QString& absolutePath);
};

#endif // FILEMANAGER_H
