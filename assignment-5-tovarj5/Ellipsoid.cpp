///-------------------------------------------
// Author: Jacob Tovar
// Date: 9/28/17
// Assignment: 3 - Linked-Lists with Pointers
//--------------------------------------------
#include "Ellipsoid.h"


Ellipsoid::Ellipsoid(int id) :Shape(id)
{

}
void Ellipsoid::get_size(double &rx, double &ry, double &rz)
{
    rx = mradx;
    ry = mrady;
    rz = mradz;
}
void Ellipsoid::set_size(double rx, double ry, double rz)
{
    mradx = rx;
    mrady = ry;
    mradz = rz;
}
QString Ellipsoid::print()
{
    QString output;
    output = "Ellipsoid ID: " + QString::number(mid) + "\n"
            + "Translation: \n\tX:" + QString::number(mtx) + " \n\tX: " + QString::number(mty) + "\n\tZ: " + QString::number(mtz) + "\n"
            + "Rotations: \n\tX:" + QString::number(mrx) + " \n\tY: " + QString::number(mry) + " \n\tZ: " + QString::number(mrz) + "\n"
            + "Scales: \n\tX:" + QString::number(msx) + " \n\tY: " + QString::number(msy) + " \n\tZ: " + QString::number(msz) + "\n"
            + "Color \n\tR: " + QString::number(mred) + " \n\tG: " + QString::number(mgreen) + " \n\tB: " + QString::number(mblue) + "\n"
            + "Size: \n\tRadiusX: " + QString::number(mradx) + " \n\tRadiusY: " + QString::number(mrady) + " \n\tRadiusZ: " + QString::number(mradz)
            + "\n";

//    std::cout << "Ellipsoid ID: " << mid << std::endl;
//    std::cout << "Translations: " << mtx << " " << mty << " " << mtz << std::endl;
//    std::cout << "Roatations: " << mrx << " " << mry << " " << mrz << std::endl;
//    std::cout << "Scales: " << msx << " " << msy << " " << msz << std::endl;
//    std::cout << "Color: Red: " << mred << " Green: " << mgreen << " Blue: " << mblue  << std::endl;
//    std::cout << "RadiusX: " << mradx << ", RadiusY: " << mrady << ", RadiusZ:" << mradz << std::endl <<std::endl;

    return output;
}
