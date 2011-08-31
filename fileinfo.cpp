#include "fileinfo.h"

FileInfo::FileInfo(const QString& file) :
    QFileInfo(file),
    m_status(Unknown),
    m_statusString(tr("<Unknown>"))
{
}

FileInfo::Status FileInfo::status() const
{
    return m_status;
}

void FileInfo::setStatus(Status status)
{
    m_status = status;

    switch(status)
    {
    case MissingHere:
        m_statusString = tr("<Missing here>");
        break;
    case MissingThere:
        m_statusString = tr("<Missing there>");
        break;
    case Same:
        m_statusString = tr("<Same as %1>").arg(m_sameFileName);
        break;
    case Synchronized:
        m_statusString = tr("<Synchronized>");
        break;
    case ContainsUnsynchronized:
        m_statusString = tr("<Unsynchronized>");
        break;
    default:
    case Unknown:
        m_statusString = tr("<Unknown>");
        break;
    }
}

QString FileInfo::statusString() const
{
    return m_statusString;
}


QString FileInfo::sameFileName() const
{
    return m_sameFileName;
}

void FileInfo::setSameFileName(const QString& file)
{
    m_sameFileName = file;
}
