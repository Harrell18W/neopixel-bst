#ifndef TREE_CONTROLLER_H
#define TREE_CONTROLLER_H

#include <QMainWindow>

namespace Ui {
class tree_controller;
}

class tree_controller : public QMainWindow
{
    Q_OBJECT

public:
    explicit tree_controller(QWidget *parent = 0);
    ~tree_controller();

private:
    Ui::tree_controller *ui;
};

#endif // TREE_CONTROLLER_H
