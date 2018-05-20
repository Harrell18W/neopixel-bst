#include "tree_controller.h"
#include "ui_tree_controller.h"

tree_controller::tree_controller(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tree_controller)
{
    ui->setupUi(this);
}

tree_controller::~tree_controller()
{
    delete ui;
}
