#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QDir>

class QTreeView;
class QPushButton;
class QLineEdit;

class DirModel;
class FileManager;

class DirView : public QWidget
{
    Q_OBJECT
public:
    explicit DirView(QWidget *parent = 0);

    FileManager* fileManager();

    QString path() const;

public slots:
    void setPath(const QString& path);
    void chooseDir();
    void setPathFromLineEdit();

private:
    QTreeView* m_treeView;
    QPushButton* m_buttonChoose;
    QLineEdit* m_lineEditFolder;
    DirModel* m_model;
};

#endif // TABLEWIDGET_H
