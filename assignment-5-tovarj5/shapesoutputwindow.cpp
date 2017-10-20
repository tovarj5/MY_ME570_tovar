#include "shapesoutputwindow.h"
#include "ui_shapesoutputwindow.h"

ShapesOutputWindow::ShapesOutputWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShapesOutputWindow)
{
    ui->setupUi(this);
}

ShapesOutputWindow::~ShapesOutputWindow()
{
    delete ui;
}

void ShapesOutputWindow::print(QString outputMessage)
{
    ui->outputPlainText->setPlainText(outputMessage);
}

void ShapesOutputWindow::clear_window()
{
    ui->outputPlainText->clear();
}
