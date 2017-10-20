#ifndef SHAPESOUTPUTWINDOW_H
#define SHAPESOUTPUTWINDOW_H

#include <QMainWindow>

namespace Ui {
class ShapesOutputWindow;
}

class ShapesOutputWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShapesOutputWindow(QWidget *parent = 0);
    ~ShapesOutputWindow();
    void print(QString outputMessage);
    void clear_window();

private:
    Ui::ShapesOutputWindow *ui;
};

#endif // SHAPESOUTPUTWINDOW_H
