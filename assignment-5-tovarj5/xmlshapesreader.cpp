#include "xmlshapesreader.h"
#include <QString>
#include "shape.h"
#include "box.h"
#include "Cone.h"
#include "Ellipsoid.h"
#include "mainwindow.h"

XmlShapesReader::XmlShapesReader(std::list <Shape*> *linkedlist):
    mLinkedList{linkedlist}
{
//    mLinkedList.push_back(linkedlist);
    //connect(this,SIGNAL(XmlShapesReader.on_likedList_changed(Shape *editShape)),MainWindow,SLOT(MainWindow))
}
QString XmlShapesReader::errorString() const
{
    return QObject::tr("%1\nLine %2, column %3")
            .arg(mReader.errorString())
            .arg(mReader.lineNumber())
            .arg(mReader.columnNumber());
}

bool XmlShapesReader::read(QIODevice *device)
{
    mReader.setDevice(device);

    if (mReader.readNextStartElement()) {
        if (mReader.name() == "shapes")
            read_shapes();
        else
            mReader.raiseError(QObject::tr("Not a Shapes file"));
    }
    return !mReader.error();
}

void XmlShapesReader::read_shapes()
{
    int written_shapes{0};
    while(mReader.readNextStartElement())
    {
        if(mReader.name() == "shape")
        {
            written_shapes++;
            read_shape();
        }
        else
            mReader.raiseError(QString("No Shape!!")); //mReader.skipCurrentElement();
    }
}

void XmlShapesReader::read_shape()
{
    int id{-1};
    Vector3 color;
    Vector3 translation;
    Vector3 rotation;
    Vector3 scale;

    Shape* shape{nullptr};

    while (mReader.readNextStartElement())
    {
        //Check for any type of listed properties in the xml file.
        if (mReader.name() == "id")
            read_id(id);
        else if(mReader.name() == "color")
            read_color(color);
        else if (mReader.name() == "translation")
            read_xyz(translation);
        else if (mReader.name() == "rotation")
            read_xyz(rotation);
        else if (mReader.name() == "scale")
            read_xyz(scale);
        else if (mReader.name() == "box" && shape==nullptr)
            read_box(id,shape);
        else if (mReader.name()=="cone" && shape==nullptr)
            read_cone(id,shape);
        else if (mReader.name()=="ellipsoid" && shape==nullptr)
            read_ellipsoid(id,shape);
        else
            mReader.skipCurrentElement();
    }
    //Set the aquired properties into the shape class, then add the shape to the linked-list.
    if(shape!=nullptr)
    {
        //int invalid{-1};
        bool valid_values{true};
        if(shape->get_id() >=0)
        {

            if (shape->check_values(color.mX,color.mY,color.mZ))//valid_values,invalid);
                shape->set_color(color.mX,color.mY,color.mZ);
            else
            {
                mReader.raiseError(QObject::tr("Corruption in file.\n Color value missing."));
                valid_values = false;
            }

            if (shape->check_values(translation.mX,translation.mY,translation.mZ))
                shape->set_translation(translation.mX,translation.mY,translation.mZ);
            else
            {
                mReader.raiseError(QObject::tr("Corruption in file.\n Translation value missing."));
                valid_values = false;
            }

            if (shape->check_values(rotation.mX,rotation.mY,rotation.mZ))
                shape->set_rotation(rotation.mX,rotation.mY,rotation.mZ);
            else
            {
                mReader.raiseError(QObject::tr("Corruption in file. Rotation value missing."));
                valid_values = false;
            }

            if (shape->check_values(scale.mX,scale.mY,scale.mZ))
                shape->set_scale(scale.mX,scale.mY,scale.mZ);
            else
            {
                mReader.raiseError(QObject::tr("Corruption in file. Scale value missing."));
                valid_values = false;
            }

            if(valid_values)
            {
                mLinkedList->push_back(shape);
                //FIND WAY TO ADD ITEM TO THE LISTWIDGET!!!!!!

//                MainWindow *window = MainWindow::;
//                window->add_shape_to_UIlist(shape);
            }
        }
        else
            mReader.raiseError(QObject::tr("Corruption in file. \nMissing ID"));
    }


}
//Read the id from the XML file.
void XmlShapesReader::read_id(int &id)
{
    if (mReader.name() == "id")
        id=mReader.readElementText().toInt();
}
void XmlShapesReader::read_color(Vector3 &color)
{

    while(mReader.readNextStartElement())
    {
        if (mReader.name() == "red")
        {
                color.mX = mReader.readElementText().toDouble();        
        }
        else if(mReader.name() == "green")
        {
                color.mY = mReader.readElementText().toDouble();
        }
        else if(mReader.name() == "blue")
        {
                color.mZ = mReader.readElementText().toDouble();
        }
        else
            mReader.skipCurrentElement();
    }

}
void XmlShapesReader::read_xyz(Vector3 &vec)
{
    vec.mX=-1;
    vec.mY=-1;
    vec.mZ=-1;

    while(mReader.readNextStartElement())
    {
        if(mReader.name() == "x")
        {
            vec.mX = mReader.readElementText().toDouble();
        }
        else if(mReader.name() == "y")
        {
            vec.mY = mReader.readElementText().toDouble();
        }
        else if(mReader.name() == "z")
        {
            vec.mZ = mReader.readElementText().toDouble();
        }
        else
            mReader.skipCurrentElement();
    }
}
void XmlShapesReader::read_box(int id,Shape *&shape)
{
    //Create new box with initialized properties, then fill in with values from the file.
    Box* box = new Box(id);
    double height{-1};
    double width{-1};
    double depth{-1};

    while(mReader.readNextStartElement())
    {
        if(mReader.name() == "height")
        {
            height = mReader.readElementText().toDouble();
        }
        else if(mReader.name() == "width")
        {
            width = mReader.readElementText().toDouble();
        }
        else if(mReader.name() == "depth")
        {
            depth = mReader.readElementText().toDouble();
        }
        else
            mReader.skipCurrentElement();
    }

    box->set_size(height,width,depth);

    shape=box;
}

void XmlShapesReader::read_cone(int id, Shape *&shape)
{
    Cone *cone = new Cone(id);
    double height{-1}, rx{-1}, ry{-1};

    //Read through file and get basic properties
    while (mReader.readNextStartElement())
    {
        if(mReader.name() == "height")
        {
            height = mReader.readElementText().toDouble();
        }
        else if (mReader.name() == "radiusX")
        {
            rx = mReader.readElementText().toDouble();
        }
        else if (mReader.name() == "radiusY")
        {
            ry = mReader.readElementText().toDouble();
        }
        else
            mReader.skipCurrentElement();

    }
    //Set properties of new cone
    cone->set_size(height,rx,ry);

    shape = cone;
}

void XmlShapesReader::read_ellipsoid(int id, Shape *&shape)
{
    Ellipsoid *ellipse = new Ellipsoid(id);
    double rx{-1}, ry{-1}, rz{-1};
    Vector3 xyz_ellipsoid;
    mReader.readNextStartElement();

    while(mReader.readNextStartElement())//ERROR HERE I NEED TO GO DOWN ONE MORE LEVEL TO READ
    {

        if(mReader.name()=="x")
        {
            rx = mReader.readElementText().toDouble();
        }
        else if(mReader.name() =="y")
        {
            ry = mReader.readElementText().toDouble();
        }
        else if (mReader.name() == "z")
        {
            rz = mReader.readElementText().toDouble();
        }
        else
            mReader.skipCurrentElement();

    }
    //Set properties of the new Ellipsoid
    ellipse->set_size(rx,ry,rz);

    shape = ellipse;
}
