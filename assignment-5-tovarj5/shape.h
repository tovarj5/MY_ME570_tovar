///-------------------------------------------
// Author: Jacob Tovar
// Date: 9/28/17
// Assignment: 3 - Linked-Lists with Pointers
//--------------------------------------------
#include <string>
#include <iostream>
#include <QString>
#include <QObject>


#ifndef SHAPE_H
#define SHAPE_H

class Shape : public QObject
{
    Q_OBJECT

public:
    Shape(int id);

    int get_id();
    void set_id(int id);

    //All of the get / set functions are the same and take in the parameters and assign them.
    //Get takes in null parameters by reference and fills them.
    void set_translation(double tx,double ty, double tz);
    void get_translation(double &tx,double &ty, double &tz);

    void set_rotation(double rx,double ry, double rz);
    void get_rotation(double &rx,double &ry, double &rz);

    void set_scale(double sx,double sy, double sz);
    void get_scale(double &sx,double &sy, double&sz);

    void set_color(double r,double g, double b);
    void get_color(double &r,double &g, double &b);

    //void check_values(double cx,double cy,double cz,bool &valid);//QString property_name); //,int num);
    void set_missing_value(double &mx, double &my,double &mz);
    bool check_values(double cx,double cy,double cz);

    virtual QString print()=0;

//signals:
//    void on_emptyInput(QString xmlProperty, double &xmlValue);

protected:
    //All shapes have the following things in common: An id. A color.
    //A set of translations in the x, y and z directions. A set of rotations about the x axis, y axis and z axis.
    //A set of scale factors in the x, y and z directions.
    int mid{0};
    std::string shape_color{0};
    double mtx{0},mty{0},mtz{0};
    double mrx{0},mry{0},mrz{0};
    double msx{0},msy{0},msz{0};
    double mred{0},mgreen{0},mblue{0};
    double cx{0},cy{0},cz{0};
    double mx{0},my{0},mz{0};
    int num{0};

};

#endif // SHAPE_H
