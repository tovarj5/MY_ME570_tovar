#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include "xmlshapesreader.h"
#include "xmlshapeswriter.h"
#include "shape.h"
#include <QFile>
#include "box.h"
#include "Cone.h"
#include "Ellipsoid.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mLinkedList = new std::list<Shape*>;

   //connect(ui->MainWindow.actionExit(),signals(MainWindow.),slots(MainWindow.on_emptyInput()));
    connect(ui->actionExit,SIGNAL(triggered(bool)),SLOT(close()));
    //connect(Shape, SIGNAL(on_emptyInput(QString,double&)),SLOT(on_emptyInput(QString,double&)));
   //connect(sender,SIGNAL(signal_changed_linkedList(Shape*)),this,SLOT(on_changed_linkedList(Shape*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox *msgbox = new QMessageBox;

    QString message{"Assignment - 4 - FunWithShape \nCreated by: Jacob Tovar \nUniversity: BYU"};
    //(*msgbox).text() = message;
    msgbox->setText(message);
    (*msgbox).show();
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog *browse = new QFileDialog;
    QString selectedFile = browse->getOpenFileName(this,tr("Open File"),"/home",tr("Xml (*.xml)"));
//    ReadXmlLocation = selectedFile;
//    QString outputText  = "";
//    QStringList addressList = selectedFile.split("/");
//    QString fileName = addressList.last();
//    ui->outputDockPlainText->appendPlainText(fileName);

    if (selectedFile != NULL)
    {
        //This code came from the last assignment
        QFile file(selectedFile);
        if(!file.open(QFile::ReadOnly | QFile::Text))
        {
            ui->outputDockPlainText->appendPlainText("Cannot read file - " + (selectedFile.split("/")).last() + file.errorString());
           //return false;
        }
        else
        {
            //std::list<Shape*> linkedList{NULL};
            //Notify user what file is being read.
            QString startText = "Reading File - " + selectedFile;
            ui->outputDockPlainText->appendPlainText(startText);
                    XmlShapesReader shape_reader(mLinkedList);

                    if (!shape_reader.read(&file))
                    {
                        QMessageBox *msgbox = new QMessageBox;
                        QString message{"Parse error in file\nPlease review Xml File\n " + shape_reader.errorString()};
                        msgbox->setText(message);
                        ui->outputDockPlainText->appendPlainText( "Parse error in file. Please review Xml File\n " + shape_reader.errorString());
                        msgbox->show();
                    }
                    if (mLinkedList!= nullptr && mLinkedList->size() >0)
                    {
                       ui->outputDockPlainText->appendPlainText( QString::number(mLinkedList->size()));
                        for(Shape *s: *mLinkedList)     //for(int s=0;s<size;s++)
                        {
                            ui->outputDockPlainText->appendPlainText( s->print());
                            QString ListItem = "Id: " + QString::number(s->get_id()) + "\t Shape: ...";
                            ui->ListListWidget->addItem(ListItem);
                            ui->lineEdit_Id_2->setText(QString::number((mLinkedList->size())+1));
                            //Shape* shape{nullptr};
                            //mLinkedList->get_at(s,shape);
                            //shape->print();
                        }
                            ui->outputDockPlainText->appendPlainText("- - - - - - - - End of File - - - - - - - - - \n");
                    }
        }
    }

}

void MainWindow::on_actionSave_triggered()
{
    //Use the workingFile to try and open the file. If not able throw and error on the Output Dock.
    QFile file(workingFile);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        ui->outputDockPlainText->appendPlainText( "Cannot Save file");// << file.errorString().data();
    }
    //Create a xmlWriter and wrtie the file.
    XmlShapesWriter shape_writer(mLinkedList);
    shape_writer.write(&file);
    ui->outputDockPlainText->appendPlainText("Wrote file" + (workingFile.split("/")).last());
}

void MainWindow::on_actionSave_As_triggered()
{
    //Open file dialog for the user to select the location and name for the saved XML document
    QFileDialog *saveDialog = new QFileDialog;
    QString saveFile = saveDialog->getSaveFileName(this,tr("Save File"), "/home", tr("Xml (*.xml)"));

//    QFileDialog *browse = new QFileDialog;
//    QString selectedFile = browse->getOpenFileName(this,tr("Save File"),"/home",tr("Xml (*.xml)"));
//    QString outputText  = "";
    //QStringList addressList = saveFile.split("/");
    //QString fileName = addressList.last();
    //ui->outputDockPlainText->appendPlainText(fileName);

    QFile file(saveFile);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        ui->outputDockPlainText->appendPlainText( "Cannot Write file");// << file.errorString().data();
    }
    //Create a XmlWriter and write the file. Notify user when done
    XmlShapesWriter shape_writer(mLinkedList);
    shape_writer.write(&file);
    ui->outputDockPlainText->appendPlainText("Wrote new file" + (saveFile.split("/")).last());
}

void MainWindow::on_actionExit_triggered()
{
   //close();
}

void MainWindow::print(QString output)
{
    QString message = "Hello World!";

    QPlainTextEdit *outputTextBox =  ui->outputDockPlainText;

    outputTextBox->setPlainText(message);
}

void MainWindow::clear_window()
{
    ui->outputDockPlainText->clear();
}

void MainWindow::close()
{
    ui->outputDockPlainText->appendPlainText("close functoin.");
    QCoreApplication::quit();
}

void MainWindow::on_emptyInput(QString XmlProperty, double &xmlValue)
{
    bool ok;
    //Code to get text input from the user. Useful reference Don't delete
//     QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
//                                          tr("User name:"), QLineEdit::Normal,
//                                          QDir::home().dirName(), &ok);
    //Get numeric input from the user.
    double value = QInputDialog::getDouble(this,tr("Missing Xml Property!"),
                                           tr("Your file is missing a property\nPlease enter a valid value of property:"),0,0,10000,5,&ok);

    //If user hit ok use the value from the user.
    if (ok)
         ui->outputDockPlainText->appendPlainText(QString::number(value));

}

void MainWindow::add_shape_to_UIlist(Shape *s)
{
    QString ListItem = "Id: " + QString::number(s->get_id()) + "\t Shape: ???";
    ui->ListListWidget->addItem(ListItem);
}


void MainWindow::on_addShapeButton_2_clicked()
{
    //Create the message box with text notification incase there is a incorrect property
    QMessageBox *msgbox = new QMessageBox;
    QString message{"Missing property!\n Please enter all properties and add shape."};
    msgbox->setText(message);
    //(*msgbox).show();

    //Add the values of the current property to the new shape.
    double x,y,z;
    bool valid{true};
    int id = ui->lineEdit_Id_2->text().toInt();
    if(id >0)
    {
        //Create string to add to the  Listwidget.
        QString ListItem = "Id: " + QString::number(id) + "\t Shape: ";

        //If we are talking about the dimensions, find out what type of shape we are creating.
        if(ui->boxRadioButton_2->isChecked())
        {
            Box *newBox = new Box(id);
            double h = ui->lineEdit_DimX->text().toDouble();
            double w = ui->lineEdit_DimY->text().toDouble();
            double d = ui->lineEdit_DimZ->text().toDouble();
            if(h==0 || w==0 || d==0)
            {
                //double value = QInputDialog::getDouble(this,tr("Missing Shape Property!"),
                //tr("You have not entered a property.\nPlease enter a valid value of property:"),0,0,10000,5,&ok);
                valid = false;
                (*msgbox).show();
            }
            else
            {
                newBox->set_size(h,w,d);
                newShape = newBox;
                ListItem.append("Box");
                //valid = true;
            }
        }
        else if (ui->coneRadioButton_2->isChecked())
        {
            Cone *newCone = new Cone(id);
            double h = ui->lineEdit_DimX->text().toDouble();
            double radX = ui->lineEdit_DimY->text().toDouble();
            double radY = ui->lineEdit_DimZ->text().toDouble();
            if(h==0 || radX==0 || radY==0)
            {
                //double value = QInputDialog::getDouble(this,tr("Missing Shape Property!"),
                //tr("You have not entered a property.\nPlease enter a valid value of property:"),0,0,10000,5,&ok);
                valid = false;
                (*msgbox).show();
            }
            else
            {
                newCone->set_size(h,radX,radY);
                newShape = newCone;
                ListItem.append("Cone");
            }
        }
        else if (ui->ellipsoidRadioButton_2->isChecked())
        {
            Ellipsoid *newEllipsoid = new Ellipsoid(id);
            double radX = ui->lineEdit_DimX->text().toDouble();
            double radY = ui->lineEdit_DimY->text().toDouble();
            double radZ = ui->lineEdit_DimZ->text().toDouble();
            if(radX==0 || radY==0 || radZ==0)
            {
                //double value = QInputDialog::getDouble(this,tr("Missing Shape Property!"),
                //tr("You have not entered a property.\nPlease enter a valid value of property:"),0,0,10000,5,&ok);
                valid = false;
                (*msgbox).show();
            }
            else
            {
                newEllipsoid->set_size(radX,radY,radZ);
                newShape = newEllipsoid;
                ListItem.append("Ellipsoid");
            }
        }

        //Get and Set color properties
        double r = ui->lineEdit_ColorX->text().toDouble();
        double g = ui->lineEdit_ColorY->text().toDouble();
        double b = ui->lineEdit_ColorZ->text().toDouble();
        if(r==0 || g==0 || b==0)
        {
            //double value = QInputDialog::getDouble(this,tr("Missing Shape Property!"),
            //tr("You have not entered a property.\nPlease enter a valid value of property:"),0,0,10000,5,&ok);
            valid = false;
            (*msgbox).show();
        }
        else
            newShape->set_color(r,g,b);

        //Get Translation values from GUI and set them in the newShape
        x = ui->lineEdit_TranX->text().toDouble();
        y = ui->lineEdit_TranY->text().toDouble();
        z = ui->lineEdit_TranZ->text().toDouble();
        if(x==0 || y==0 || z==0)
        {
            //double value = QInputDialog::getDouble(this,tr("Missing Shape Property!"),
            //tr("You have not entered a property.\nPlease enter a valid value of property:"),0,0,10000,5,&ok);
            valid = false;
            (*msgbox).show();
        }
        else
            newShape->set_translation(x,y,z);

        //Get and set Rotation values from the GUI into the newShape
        x = ui->lineEdit_RotX->text().toDouble();
        y = ui->lineEdit_RotY->text().toDouble();
        z = ui->lineEdit_RotZ->text().toDouble();
        if(x==0 || y==0 || z==0)
        {
            //double value = QInputDialog::getDouble(this,tr("Missing Shape Property!"),
            //tr("You have not entered a property.\nPlease enter a valid value of property:") 0,0,10000,5,&ok);
            valid = false;
            (*msgbox).show();
        }
        else
            newShape->set_rotation(x,y,z);

        //Get and set Scale
        x = ui->lineEdit_ScaleX->text().toDouble();
        y = ui->lineEdit_ScaleY->text().toDouble();
        z = ui->lineEdit_ScaleZ->text().toDouble();
        if(x==0 || y==0 || z==0)
        {
            //double value = QInputDialog::getDouble(this,tr("Missing Shape Property!"),
            //tr("You have not entered a property.\nPlease enter a valid value of property:"),0,0,10000,5,&ok);
            valid = false;
            (*msgbox).show();
        }
        else
            newShape->set_scale(x,y,z);

        if (valid)
        {
            //Add the shape to the linked list and output the info to the user
            mLinkedList->push_back(newShape);
            ui->outputDockPlainText->appendPlainText(newShape->print());

            //Create a new listWidget item with the shape information.
            ui->ListListWidget->addItem(ListItem);
            ui->ListListWidget->repaint();
            ui->ListListWidget->update();

            //Increment the shapes id for usability
            ui->lineEdit_Id_2->setText(QString::number(id+1));
        }
    }
}

void MainWindow::on_boxRadioButton_2_toggled(bool checked)
{
    if(checked)
    {
        ui->label_sizeX->setText(QString("Height:"));
        ui->label_sizeY->setText(QString("Width:"));
        ui->label_sizeZ->setText(QString("Depth:"));
    }
}

void MainWindow::on_coneRadioButton_2_toggled(bool checked)
{
    if(checked)
    {
        ui->label_sizeX->setText(QString("Height:"));
        ui->label_sizeY->setText(QString("Radius X:"));
        ui->label_sizeZ->setText(QString("Radius Y:"));
    }
}

void MainWindow::on_ellipsoidRadioButton_2_toggled(bool checked)
{
    if(checked)
    {
        ui->label_sizeX->setText(QString("Radius X:"));
        ui->label_sizeY->setText(QString("Radius Y:"));
        ui->label_sizeZ->setText(QString("Radius Z:"));
    }
}

void MainWindow::on_clearButton_2_clicked()
{
    ui->lineEdit_Id_2->setText(QString(""));

    ui->lineEdit_ColorX->setText(QString(""));
    ui->lineEdit_ColorY->setText(QString(""));
    ui->lineEdit_ColorZ->setText(QString(""));

    ui->lineEdit_DimX->setText(QString(""));
    ui->lineEdit_DimY->setText(QString(""));
    ui->lineEdit_DimZ->setText(QString(""));

    ui->lineEdit_TranX->setText(QString(""));
    ui->lineEdit_TranY->setText(QString(""));
    ui->lineEdit_TranZ->setText(QString(""));

    ui->lineEdit_RotX->setText(QString(""));
    ui->lineEdit_RotY->setText(QString(""));
    ui->lineEdit_RotZ->setText(QString(""));

    ui->lineEdit_ScaleX->setText(QString(""));
    ui->lineEdit_ScaleY->setText(QString(""));
    ui->lineEdit_ScaleZ->setText(QString(""));

    //ui->addShapeButton_2->setDisabled(true);
}

void MainWindow::on_actionOpen_Create_Shape_Dialog_triggered()
{
    //ui->creatShapeDockWidget = new QDockWidget;
    ui->creatShapeDockWidget->show();

}

void MainWindow::on_actionOpen_Output_Dock_triggered()
{
    //ui->outputDockPlainText = new QDockWidget;
    ui->outputDockWidget->show();
}

void MainWindow::on_DeleteShapePushButton_clicked()
{
    //ui->ListListWidget->selectedItems();
    QList <QListWidgetItem*> slist {ui->ListListWidget->selectedItems()};
    QMessageBox *msgbox = new QMessageBox;
    QString text{slist.first()->text()};
    msgbox->setText(text);
    msgbox->show();

//    for (QString item : shapeslist)
//    {
//        QStringList list = item.split("|");

//        for(Shape *s :mLinkedList)
//        {
//            if (s->get_id() == list.last())
//            {

//            }
//        }
//    }
}
