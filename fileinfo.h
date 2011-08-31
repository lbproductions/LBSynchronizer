#ifndef FILEINFO_H
#define FILEINFO_H

#include <QFileInfo>
#include <QObject>

class FileInfo : public QObject, public QFileInfo
{
    Q_OBJECT
public:
    explicit FileInfo(const QString& file);

    enum Status {
        Unknown,
        MissingHere,
        MissingThere,
        Same,
        Synchronized,
        ContainsUnsynchronized
    };


    void setStatus(Status status);
    Status status() const;

    QString statusString() const;

    QString sameFileName() const;
    void setSameFileName(const QString& file);

    Qt::CheckState checkState() const;
    void setCheckState(Qt::CheckState checkState);

private:
    Status m_status;
    QString m_statusString;
    QString m_sameFileName;
    Qt::CheckState m_checkState;
};

#endif // FILEINFO_H
