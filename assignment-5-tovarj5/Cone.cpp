///-------------------------------------------
// Author: Jacob Tovar
// Date: 9/28/17
// Assignment: 3 - Linked-Lists with Pointers
//--------------------------------------------
#include "Cone.h"

Cone::Cone(int id) : Shape(id)
{

}
void Cone::get_size(double &height, double &rx, double &ry)
{
    height = mheight;
    rx = mradx;
    ry = mrady;
}
void Cone::set_size(double height, double rx, double ry)
{
    mheight = height;
    mradx = rx;
    mrady = ry;
}
QString Cone::print()
{
    QString output;
    output = "Cone ID: " + QString::number(mid) + "\n"
            + "Translation: \n\tX: " + QString::number(mtx) + " \n\tY:" + QString::number(mty) + " \n\tZ:" + QString::number(mtz) + "\n"
            + "Rotations: \n\tX:" + QString::number(mrx) + " \n\tY:" + QString::number(mry) + " \n\tZ:" + QString::number(mrz) + "\n"
            + "Scales: \n\tX:" + QString::number(msx) + " \n\tY:" + QString::number(msy) + " \n\tZ:" + QString::number(msz) + "\n"
            + "Color \n\tR: " + QString::number(mred) + " \n\tG:" + QString::number(mgreen) + " \n\tB:" + QString::number(mblue) + "\n"
            + "Size: \n\tHeight: " + QString::number(mheight) + " \n\tRadiusX: " + QString::number(mradx) + "\n\tRadiusY: " + QString::number(mrady) + "\n";

//    std::cout << "Cone ID: " << mid << std::endl;
//    std::cout << "Translations: " << mtx << " " << mty << " " << mtz << std::endl;
//    std::cout << "Roatations: " << mrx << " " << mry << " " << mrz << std::endl;
//    std::cout << "Scales: " << msx << " " << msy << " " << msz << std::endl;
//    std::cout << "Color: Red: " << mred << " Green: " << mgreen << " Blue: " << mblue  << std::endl;
//    std::cout << "Height: " << mheight << ", RadiusX: " << mradx << ", RadiusY: " << mrady << std::endl <<std::endl;

    return output;
}
