#ifndef XMLSHAPESWRITER_H
#define XMLSHAPESWRITER_H
#include <QIODevice>
#include <QXmlStreamWriter>
#include <QObject>

class Shape;
class Box;
class Cone;
class Ellipsoid;


class XmlShapesWriter
{
public:
//    XmlShapesWriter(LinkedList *linkedlist);
    XmlShapesWriter(std::list<Shape*> *linkedlist);
    void write(QIODevice *device);

protected:
    QXmlStreamWriter mWriter;

    //LinkedList* mLinkedList;
    std::list<Shape*> *mLinkedList;

    struct Vector3
    {
        double mX{0};
        double mY{0};
        double mZ{0};
    };

    void write_shapes();
    void write_shape(Shape *shape);
    void write_id(int id);
    void write_xyz(Vector3 &vec);
    void write_color(Vector3 &color);
    void write_box(Box *box);
    void write_cone(Cone *cone);
    void write_ellipsoid(Ellipsoid *ellipsoid);
};

#endif // XMLSHAPESWRITER_H
