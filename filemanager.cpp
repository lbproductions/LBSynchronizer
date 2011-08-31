#include "filemanager.h"

#include "fileinfo.h"

#include <QDebug>

FileManager::FileManager(const QString& path, QObject *parent) :
    QObject(parent),
    m_path(path)
{
}

FileManager::~FileManager()
{
    foreach(FileInfo* info, m_fileInfos.values())
    {
        delete info;
    }
}

void FileManager::makeRelativePath(QString& path)
{
    if(path.startsWith(m_path.absolutePath()))
    {
        path.remove(m_path.absolutePath());
    }
}

FileInfo* FileManager::fileInfo(const QString& path)
{
    QString file = path;
    makeRelativePath(file);

    if(!m_fileInfos.contains(file))
    {
        FileInfo* info = new FileInfo(file);
        m_fileInfos.insert(file, info);
    }

    return m_fileInfos.value(file);
}

void FileManager::compareTo(FileManager* other)
{
    qDebug() << "--- Comparing" << m_path.absolutePath() << "to" << other->m_path.absolutePath() << "---";
    compareTo(other, QString(""));
    qDebug() << "--- Finished ---" << endl;
}

void FileManager::compareTo(FileManager* other, const QString& path)
{
    qDebug() << "Comparing" << path;

    QStringList entryList = QDir(m_path.absolutePath()+path).entryList(QDir::AllEntries | QDir::NoDotAndDotDot);
    QDir otherDir(other->m_path.absolutePath()+path);

    foreach(QString file, otherDir.entryList(QDir::AllEntries | QDir::NoDotAndDotDot))
    {
        if(entryList.contains(file))
        {
            qDebug() << path + "/" + file << "synchronized.";
            fileInfo(path + "/" + file)->setStatus(FileInfo::Synchronized);
        }
        else
        {
            //TODO: Passendes file suchen
            qDebug() << path + "/" + file << "missing here.";
            fileInfo(path + "/" + file)->setStatus(FileInfo::MissingHere);
        }

        if(QFileInfo(m_path.absolutePath()+path + "/" + file).isDir())
        {
            compareTo(other,path + "/" + file);
        }
    }

    FileInfo* info = 0;
    foreach(QString file, entryList)
    {
        info = fileInfo(path + "/" + file);
        if(info->status() == FileInfo::Unknown)
        {
            qDebug() << path + "/" + file << "missing there.";
            info->setStatus(FileInfo::MissingThere);
        }
    }
}
