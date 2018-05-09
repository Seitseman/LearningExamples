#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QtWidgets/QWidget>

class CustomTableModel;
class TableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TableWidget(QWidget *parent = nullptr);

private:
    CustomTableModel *mModel = nullptr;
};

#endif // TABLEWIDGET_H
