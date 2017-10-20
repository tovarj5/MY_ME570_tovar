#ifndef XMLSHAPESREADER_H
#define XMLSHAPESREADER_H
#include <QIODevice>
#include <QXmlStreamReader>
#include <QString>
//#include "linkedlist.h"


class Shape;

class XmlShapesReader
{

public:
    //XmlShapesReader(LinkedList *linkedlist);
    XmlShapesReader(std::list<Shape*> *linkedlist);
    bool read(QIODevice *device);
    QString errorString() const;

//signals:
//    void on_empty_input(QString name, QString property, double &value);
//    void signal_likedList_changed(Shape *editShape);

protected:
    QXmlStreamReader mReader;
    //LinkedList* mLinkedList;
    std::list<Shape*> *mLinkedList;
    struct Vector3
    {
        double mX{-1};
        double mY{-1};
        double mZ{-1};
    };

    void read_shapes();
    void read_shape();
    void read_box(int id, Shape *&shape); //Reads in the height, width, and depth for a box. if empty property is 1
    void read_cone(int id, Shape *&shape); //Reads in the height, X & Y Radius for a cone. If empty, property is 0
    void read_ellipsoid(int id, Shape *&shape); //Reads in the X, Y, Z Radius for an ellipsoid. If empty, property is 0
    void read_id(int &id);//Reads id number from file. if empty, property is null.
    void read_color(Vector3 &color);
    void read_xyz(Vector3 &vec);



};

#endif // XMLSHAPESREADER_H
