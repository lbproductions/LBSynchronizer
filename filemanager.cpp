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
            QString otherFile = findSameFileHere(other,path,file);
            if(!otherFile.isNull())
            {
                qDebug() << path + "/" + otherFile << "same as" << file;
                fileInfo(path + "/" + otherFile)->setSameFileName(file);
                fileInfo(path + "/" + otherFile)->setStatus(FileInfo::Same);
            }
            else
            {
                qDebug() << path + "/" + file << "missing here.";
                fileInfo(path + "/" + file)->setStatus(FileInfo::MissingHere);
            }
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
            QString otherFile = findSameFileThere(other,path,file);
            if(!otherFile.isNull())
            {
                qDebug() << path + "/" + file << "same as" << otherFile;
                info->setSameFileName(otherFile);
                info->setStatus(FileInfo::Same);
            }
            else
            {
                qDebug() << path + "/" + file << "missing there.";
                info->setStatus(FileInfo::MissingThere);
            }
        }
    }
}

QString FileManager::findSameFileHere(FileManager* other, const QString& path, const QString& file)
{
    if(QFileInfo(other->m_path.absolutePath()+path + "/" + file).isDir())
    {
        return QString();
    }

    QFileInfo otherInfo(other->m_path.absolutePath()+path+"/"+file);
    QDir dir(m_path.absolutePath()+path);
    foreach(QString hereFile, dir.entryList(QDir::AllEntries | QDir::NoDotAndDotDot))
    {
        QFileInfo hereInfo(m_path.absolutePath()+path+"/"+hereFile);
        if(hereInfo.size() == otherInfo.size())
        {
            return hereFile;
        }
    }

    return QString();
}

QString FileManager::findSameFileThere(FileManager* other, const QString& path, const QString& file)
{
    if(QFileInfo(m_path.absolutePath()+path + "/" + file).isDir())
    {
        return QString();
    }

    QFileInfo hereInfo(m_path.absolutePath()+path+"/"+file);
    QDir dir(other->m_path.absolutePath()+path);
    foreach(QString otherFile, dir.entryList(QDir::AllEntries | QDir::NoDotAndDotDot))
    {
        QFileInfo otherInfo(other->m_path.absolutePath()+path+"/"+otherFile);
        if(hereInfo.size() == otherInfo.size())
        {
            return otherFile;
        }
    }

    return QString();
}
