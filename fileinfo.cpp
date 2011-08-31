#include "fileinfo.h"

FileInfo::FileInfo(const QString& file) :
    QFileInfo(file),
    m_status(Unknown),
    m_statusString(tr("<Unknown>")),
    m_checkState(Qt::Checked)
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
        m_checkState = Qt::Checked;
        break;
    case MissingThere:
        m_statusString = tr("<Missing there>");
        m_checkState = Qt::Unchecked;
        break;
    case Same:
        m_statusString = tr("<Same as %1>").arg(m_sameFileName);
        m_checkState = Qt::Unchecked;
        break;
    case Synchronized:
        m_statusString = tr("<Synchronized>");
        m_checkState = Qt::Checked;
        break;
    case ContainsUnsynchronized:
        m_statusString = tr("<Unsynchronized>");
        m_checkState = Qt::Unchecked;
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

Qt::CheckState FileInfo::checkState() const
{
    return m_checkState;
}

void FileInfo::setCheckState(Qt::CheckState checkState)
{
    m_checkState = checkState;
}
