#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "shape.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    std::list<Shape*> *mLinkedList;
    void on_emptyInput(QString XmlProperty, double &xmlValue);
    void add_shape_to_UIlist(Shape *s);

private slots:
    void on_actionAbout_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionExit_triggered();

    void print(QString output);

    void clear_window();

    void close();

    void on_addShapeButton_2_clicked();

    void on_boxRadioButton_2_toggled(bool checked);

    void on_coneRadioButton_2_toggled(bool checked);

    void on_ellipsoidRadioButton_2_toggled(bool checked);

    void on_clearButton_2_clicked();

    void on_actionOpen_Create_Shape_Dialog_triggered();

    void on_actionOpen_Output_Dock_triggered();

    //void on_changed_linkedList(Shape *editShape);

    void on_DeleteShapePushButton_clicked();

private:
    Ui::MainWindow *ui;
    //QString ReadXmlLocation{""};
    Shape *newShape{nullptr};
    QString workingFile{""};
//    bool read_xml(const QString& fileName,std::list<Shape*> *linked_list);
};

#endif // MAINWINDOW_H
