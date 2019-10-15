#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;

template < class T >
class Vector {
protected:
    T _x, _y, _z;
public:
    Vector(T x, T y, T z);
    Vector( ); // Default constructor

    T get_x() const;
    T get_y() const;
    T get_z() const;

    void set_x(const T &x);
    void set_y(const T &y);
    void set_z(const T &z);

    template < class V >
    friend ostream& operator<< (ostream&, const Vector < V > &); // теперь выводить в консоль можно без геттеров, потому что мы подружили оператор с классом Vector

    Vector <T> operator+(const Vector<T>&) const;// на запись а=а+б будет ругаться, мы же не можем менять а, внутри скобок рядом с поинт можно не писать переменную
    Vector <T> &operator +=(const Vector<T>& b);
    Vector <T> operator-(const Vector<T>&) const;
    Vector <T> &operator -=(const Vector<T>&);
    Vector <T> operator*(const T &h) const;// а можно и написать переменную - не важно пока что
    double operator*(const Vector<T>&) const; // СКАЛЯРНОЕ
    Vector <T> operator^(const Vector<T>&) const; //векторное

    T abs();
};

// Перегружаем логический оператор == вне класса //public static //https://professorweb.ru/my/csharp/charp_theory/level6/6_5.php //https://ru.stackoverflow.com/questions/491054/%D0%9F%D0%B5%D1%80%D0%B5%D0%B3%D1%80%D1%83%D0%B7%D0%BA%D0%B0-%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80%D0%B0
template < class T >
bool operator== (Vector<T>& obj1, Vector<T>& obj2)
{
    if ( ((obj1.get_x() - obj2.get_x()) < 1E-9) && (obj1.get_y() - obj2.get_y() < 1E-9) && (obj1.get_z() - obj2.get_z() <1E-9) )
        return true;
    else return false;
}

template < class T >
Vector < T > ::Vector() {
    _x=0;
    _y=0;
    _z=0;
}

template < class T >
T Vector<T>::get_x() const {
    return _x;
}

template < class T >
T Vector<T>::get_y() const {
    return _y;
}

template < class T >
T Vector<T>::get_z() const {
    return _z;
}

template < class T >
void Vector<T>::set_x(const T& x) {
    _x = x;
}

template < class T >
void Vector<T>::set_y(const T& y) {
    _y = y;
}

template < class T >
void Vector<T>::set_z(const T& z) {
    _z = z;
}

template < class T >
Vector<T>::Vector(T x, T y, T z) {
    _x = x;
    _y = y;
    _z = z;
}

template < class T >
ostream& operator<< (ostream& os, const Vector<T>& p){
    os << "(" << p._x << ";" << p._y << ";" << p._z << ")";
    return os;
}



//Vector::Vector(double x, double y, double z) {
//_x =x;
// //this->x = x вместо подчёркиваний можем использовать указатель this/ this это указатель на используемый в данный текущий момент элемент класса
//_y =y;
//_z =z;
//};
// //Vector::Vector ():x(x), y(y) {}; //альтернативный способ

template < class T >
Vector<T> Vector<T>::operator+(const Vector<T> &b) const{  // ф-ция типа поинт использует оператор из типа поинт, который применяется к объекту из класса поинт
Vector c(0.0, 0.0, 0.0);
c._x = this->_x + b._x;// применяем ф-цию сет из класса поинт для объекта с из класса поинт, с и в тут локальные переменные, то есть вообще не важно как их назвать, значения в них придут из мэйна при вызове фции
c._y = this->_y + b._y;
c._z = this->_z + b._z;
return c;
}

template < class T >
Vector<T>& Vector<T>::operator+=(const Vector<T>& b) {
   this = this + b;
   return this;
}

template < class T >
Vector<T> Vector<T>::operator-(const Vector<T> &b) const{
Vector c(0.0, 0.0, 0.0);
c._x = this->_x - b._x;
c._y = this->_y - b._y;
c._z = this->_z - b._z;
return c;
}

template < class T >
Vector<T>& Vector<T>::operator-=(const Vector<T>& b) {
   this = this - b;
   return this;
}

template < class T >
Vector<T> Vector<T>::operator*(const T &h) const{
Vector<T> c;
    c._x = this->_x * h;
    c._y = this->_y * h;
    c._z = this->_z * h;
return c;
}

template < class T >
double Vector<T>::operator *(const Vector<T> &b) const{
     return this->_x*b._x + this->_y*b._y + this->_z*b._z;
}

template < class T >
Vector<T> Vector<T>::operator ^(const Vector<T> &b) const{
        Vector<T> c;
        c._x = this->_y*b._z - this->_z*b._y;
        c._y = this->_z*b._x - this->_x*b._z;
        c._z = this->_x*b._y - this->_y*b._x;

         return c;
}

template < class T >
T Vector<T>::abs() {
    return sqrt( _x*_x + _y*_y + _z*_z);
}

/*int main(){
    double x,y;
    cout<<"Input coordinates:"<<endl;
    cin>>x>>y;
    Point a=Point(x,y);
    cout<<"Your point is: "<<a<<endl;
    return 0;
}
*/

#endif // VECTOR3D_H
