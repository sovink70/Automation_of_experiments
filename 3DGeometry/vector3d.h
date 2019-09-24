#ifndef VECTOR3D_H
#define VECTOR3D_H

//#include <math.h>
#include <cstdlib>
#include <iostream>

#include <cmath>

using namespace std;

class Vector {
protected:
    double _x, _y, _z;
public:
    Vector(double x, double y, double z);

//    double get_x() const;
//    double get_y() const;
//    double get_z() const;

//    void set_x(double x);
//    void set_y(double y);
//    void set_z(double z);

    friend ostream& operator<< (ostream &, const Vector&); // теперь можно без геттеров, потому что мы подружили оператор с классом Vector

    Vector operator+(const Vector&) const;// на запись а=а+б будет ругаться, мы же не можем менять а, внутри скобок рядом с поинт можно не писать переменную
    // пишем конст чтоб случайно не поменять значение b, если значение b изменено то будет ошибка
    Vector operator-(const Vector&) const;
    Vector operator*(const double &h) const;// а можно и написать переменную - не важно пока что
  double operator*(const Vector&) const;
  Vector operator^(const Vector&) const;

    float abs();
};


//double Vector::get_x() const {
//    return _x;
//} //;

//double Vector::get_y() const {
//    return _y;
//} //;

//double Vector::get_z() const {
//    return _z;
//} //;

//void Vector::set_x(double x) {
//    _x = x;
//} //;

//void Vector::set_y(double y) {
//    _y = y;
//} //;

//void Vector::set_z(double z) {
//    _z = z;
//} //;

Vector::Vector(double x, double y, double z) {
    _x = x;
    _y = y;
    _z = z;
} //;

ostream& operator<< (ostream& os, const Vector& p){
    os << "(" << p._x << ";" << p._y << p._z << ")";
    return os;
} //;



//Vector::Vector(double x, double y, double z) {
//_x =x;
// //this->x = x вместо подчёркиваний можем использовать указатель this/ this это указатель на используемый в данный текущий момент элемент класса
//_y =y;
//_z =z;
//};
// //Vector::Vector ():x(x), y(y) {}; //альтернативный способ


Vector Vector::operator+(const Vector &b) const{  // ф-ция типа поинт использует оператор из типа поинт, который применяется к объекту из класса поинт
Vector c(0.0, 0.0, 0.0);
c._x = this->_x + b._x;// применяем ф-цию сет из класса поинт для объекта с из класса поинт, с и в тут локальные переменные, то есть вообще не важно как их назвать, значения в них придут из мэйна при вызове фции
c._y = this->_y + b._y;
c._z = this->_z + b._z;
return c;
}

Vector Vector::operator-(const Vector &b) const{
Vector c(0.0, 0.0, 0.0);
c._x = this->_x - b._x;
c._y = this->_y - b._y;
c._z = this->_z - b._z;

return c;
}

//Пасставь везде _

Vector Vector::operator*(const double &h) const{
Vector c(0.0, 0.0, 0.0);
    c._x = this->_x * h;
    c._y = this->_y * h;
    c._z = this->_z * h;
return c;
}


double Vector::operator *(const Vector &b) const{
     return this->_x*b._x + this->_y*b._y + this->_z*b._z;
}

Vector Vector::operator ^(const Vector &b) const{
        Vector  c(0.0, 0.0, 0.0);
        c._x = this->_y*b._z - this->_z*b._y;
        c._y = this->_z*b._x - this->_x*b._z;
        c._z = this->_x*b._y - this->_y*b._x;

         return c;
}

#endif // VECTOR3D_H
