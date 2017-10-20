#include "box.h"
//#include <iostream>
Box::Box(int id) : Shape(id)
{

}
void Box::get_size(double &height, double &width, double &depth)
{
height = mheight;
width = mwidth;
depth = mdepth;
}

void Box::set_size(double height, double width, double depth)
{
mheight = height;
mwidth = width;
mdepth = depth;
}

//This function should print, to std::cout,
//all of the Shape and Box data : shape type, id, translations, rotations, scales, color, height, width and depth.
QString Box::print()
{
    QString test;
    test.number(mtx);

    QString output{""};
    output.append("Box ID: ").append(QString::number(mid)).append("\n");
    output.append("Translations: \n\tX: ").append(QString::number(mtx)).append(" \n\tY: ").append(QString::number(mty)).append(" \n\tZ: ").append(QString::number(mtz)).append("\n");
    output.append("Rotations: \n\tX: ").append(QString::number(mrx)).append(" \n\tY: ").append(QString::number(mry)).append(" \n\tZ: ").append(QString::number(mrz)).append("\n");
    output.append("Scales: \n\tX: ").append(QString::number(msx)).append(" \n\tY: ").append(QString::number(msy)).append(" \n\tZ: ").append(QString::number(msz)).append("\n");
    output.append("Color: \n\tRed: ").append(QString::number(mred)).append(" \n\tGreen: ").append(QString::number(mgreen)).append(" \n\tBlue: ").append(QString::number(mblue)).append("\n");
    output.append("Size: \n\tHeight: ").append(QString::number(mheight)).append(" \n\tWidth: ").append(QString::number(mwidth)).append(" \n\tDepth: ").append(QString::number(mdepth)).append("\n");


return output;
//std::cout << "Box ID: " << mid << std::endl;
//std::cout << "Translations: " << mtx << " " << mty << " " << mtz << std::endl;
//std::cout << "Rotations: " << mrx << " " << mry << " " << mrz << std::endl;
//std::cout << "Scales: " << msx << " " << msy << " " << msz << std::endl;
//std::cout << "Color: Red: " << mred << " Green: " << mgreen << " Blue: " << mblue  << std::endl;
//std::cout << "Height, Width, Depth " << mheight << " " << mwidth << " " << mdepth << std::endl <<std::endl;

}

