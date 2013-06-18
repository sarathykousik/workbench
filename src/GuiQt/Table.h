#ifndef TABLE_H
#define TABLE_H
#include <QColor>
#include <QWidget>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QTableView>

namespace Ui {
class Table;
}

class Table : public QWidget
{
    Q_OBJECT
    
public:
    explicit Table(QWidget *parent = 0);
    ~Table();
    void createModel();
    void populate(std::vector< std::vector <QColor> > &colors);
    QTableView *getTableView();
    const QRect adjustTableSize(
        QTableView* tv,
        const QVBoxLayout* lay);
private:    
    Ui::Table *ui;
    QStandardItemModel *model;
};

#endif // TABLE_H