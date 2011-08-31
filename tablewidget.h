#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QDir>

class QTreeView;
class QPushButton;
class QLineEdit;

class DirModel;
class FileManager;
class FilterModel;

class DirView : public QWidget
{
    Q_OBJECT
public:
    explicit DirView(QWidget *parent = 0);

    FileManager* fileManager() const;

    FilterModel* filterModel() const;

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
    FilterModel* m_filterModel;
};

#endif // TABLEWIDGET_H
