///-------------------------------------------
// Author: Jacob Tovar
// Date: 9/28/17
// Assignment: 3 - Linked-Lists with Pointers
//--------------------------------------------
#ifndef CONE_H
#define CONE_H

#include "Shape.h"
#include <QString>

class Cone: public Shape
{
public:
    Cone(int id);
    void set_size(double height, double rx, double ry);
    void get_size(double &height, double &rx, double &ry);

    //Prints the shape properties and the unique Cone properties.
    QString print();

protected:
    double mheight{0}, mradx{0}, mrady{0};
};

#endif //CONE_H
