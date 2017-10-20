///-------------------------------------------
// Author: Jacob Tovar
// Date: 9/28/17
// Assignment: 3 - Linked-Lists with Pointers
//--------------------------------------------
#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "Shape.h"

class Ellipsoid : public Shape
{
public:
    Ellipsoid(int id);

    void set_size(double rx, double ry, double rz);
    void get_size(double &rx, double &ry, double &rz);

    //Prints the shape properties and the unique Ellipsoid properties.
    QString print();

protected:
    double mradx{0}, mrady{0}, mradz{0};
};

#endif // ELLIPSOID_H
