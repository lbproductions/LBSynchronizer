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

private:
    Status m_status;
    QString m_statusString;
    QString m_sameFileName;
};

#endif // FILEINFO_H
