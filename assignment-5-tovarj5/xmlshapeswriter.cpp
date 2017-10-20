#include "xmlshapeswriter.h"
#include "box.h"
#include "shape.h"
#include "Cone.h"
#include "Ellipsoid.h"
#include <QObject>

XmlShapesWriter::XmlShapesWriter(std::list <Shape*> * linkedlist):
    mLinkedList{linkedlist}
{

}
void XmlShapesWriter::write(QIODevice *device)
{
    mWriter.setDevice(device);

    mWriter.setAutoFormatting(true);
    mWriter.writeStartDocument();

    write_shapes();

    mWriter.writeEndDocument();

}

void XmlShapesWriter::write_shapes()
{
    mWriter.writeStartElement("shapes");

//    for(int s=0;s<mLinkedList->size();s++)
    for(Shape* shape : *mLinkedList)
    //for (int s=0;s<mLinkedList->size();s++)
    {
        //Shape* shape{nullptr};
        //mLinkedList->get_at(s,shape);
        //shape = mLinkedList->;
        write_shape(shape);
    }

    mWriter.writeEndElement(); // shapes
}
void XmlShapesWriter::write_shape(Shape *shape)
{
    mWriter.writeStartElement("shape");

    int id{0};
    Vector3 translation;
    Vector3 rotation;
    Vector3 scale;
    Vector3 color;

    id=shape->get_id();
    shape->get_translation(translation.mX,translation.mY,translation.mZ);
    shape->get_rotation(rotation.mX,rotation.mY,rotation.mZ);
    shape->get_scale(scale.mX,scale.mY,scale.mZ);
    shape->get_color(color.mX,color.mY,color.mZ); //mX == red, mY == green, mZ == blue


    write_id(id);

    mWriter.writeStartElement("translation");
    write_xyz(translation);
    mWriter.writeEndElement();


    mWriter.writeStartElement("rotation");
    write_xyz(rotation);
    mWriter.writeEndElement();


    mWriter.writeStartElement("scale");
    write_xyz(scale);
    mWriter.writeEndElement();

    mWriter.writeStartElement("color");
    write_color(color);
    mWriter.writeEndElement();


    Box* box=dynamic_cast<Box*>(shape);
    if(box)
    {
        write_box(box);
    }
    Cone *cone = dynamic_cast<Cone*>(shape);
    if(cone)
    {
        write_cone(cone);
    }
    Ellipsoid *ellipse = dynamic_cast<Ellipsoid*>(shape);
    if(ellipse)
    {
        write_ellipsoid(ellipse);
    }

    mWriter.writeEndElement();//shape
}
void XmlShapesWriter::write_box( Box *box)
{
    double height{0};
    double width{0};
    double depth{0};

    box->get_size(height,width,depth);

    mWriter.writeStartElement("box");

    mWriter.writeTextElement("height", QString::number(height));
    mWriter.writeTextElement("width", QString::number(width));
    mWriter.writeTextElement("depth", QString::number(depth));
    mWriter.writeEndElement();//box
}

void XmlShapesWriter::write_cone(Cone *cone)
{
    double height{0}, radx{0}, rady{0};
    cone->get_size(height,radx,rady);

    mWriter.writeStartElement("cone");

    mWriter.writeTextElement("height", QString::number(height));
    mWriter.writeTextElement("x", QString::number(radx));
    mWriter.writeTextElement("y", QString::number(rady));
    mWriter.writeEndElement();//cone
}

void XmlShapesWriter::write_ellipsoid(Ellipsoid *ellipsoid)
{
    double rx{0},ry{0},rz{0};
    ellipsoid->get_size(rx,ry,rz);

    mWriter.writeStartElement("ellipsoid");
    mWriter.writeStartElement("radius");

    mWriter.writeTextElement("x", QString::number(rx));
    mWriter.writeTextElement("y", QString::number(ry));
    mWriter.writeTextElement("z", QString::number(rz));
    mWriter.writeEndElement();//radius
    mWriter.writeEndElement();//ellipsoid
}
void XmlShapesWriter::write_id(int id)
{
    mWriter.writeTextElement("id", QString::number(id));
}
void XmlShapesWriter::write_color(Vector3 &color)
{
    mWriter.writeTextElement("r",QString::number(color.mX));
    mWriter.writeTextElement("g",QString::number(color.mY));
    mWriter.writeTextElement("b",QString::number(color.mZ));
}
void XmlShapesWriter::write_xyz(Vector3 &vec)
{
    mWriter.writeTextElement("x", QString::number(vec.mX));
    mWriter.writeTextElement("y", QString::number(vec.mY));
    mWriter.writeTextElement("z", QString::number(vec.mZ));
}
