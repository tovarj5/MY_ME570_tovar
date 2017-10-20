#ifndef BOX_H
#define BOX_H

#include "Shape.h"

class Box : public Shape
{
public:
    Box(int id);

    void set_size(double height,double width, double depth);
    void get_size(double &height,double &width, double &depth);

    //Prints the shape properties and the unique Box properties.
    QString print();

protected:
    double mheight{0},mwidth{0},mdepth{0};


};

#endif // BOX_H
