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
        Synchronized
    };


    void setStatus(Status status);
    Status status() const;

    QString statusString() const;

private:
    Status m_status;
    QString m_statusString;
};

#endif // FILEINFO_H
