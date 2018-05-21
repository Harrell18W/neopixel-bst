#ifndef TREE_CONTROLLER_H
#define TREE_CONTROLLER_H

#include <QMainWindow>

//colors
enum Color {RED = 31, GREEN = 32, BLUE = 34};

//data structure types
enum Type {AVL, BST, HEAP, MAX_HEAP, MIN_HEAP};

//heap types
enum HeapType {MIN, MAX};

//operations
enum Operation {INSERT, DELETE, CLEAR, SWITCH};

namespace Ui {
class tree_controller;
}

class tree_controller : public QMainWindow
{
    Q_OBJECT

public:
    explicit tree_controller(QWidget *parent = 0);
    ~tree_controller();
    void addLog(char *msg);
    char *qstringToCharPtr(QString qstring);
    enum Color getCurrentColor();
    enum Type getCurrentType();
    void setCurrentType(enum Type type);
    enum Type getSelectedType();
    char *typeToString(enum Type type);

private slots:
    void on_typePushButton_clicked();

private:
    Ui::tree_controller *ui;
};

#endif // TREE_CONTROLLER_H
