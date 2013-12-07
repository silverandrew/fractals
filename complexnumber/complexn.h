//following rules in Complex Variables and Applications by Churchill-Brown, 8th edition

//x = rcos(theta), y = rsin(theta)

#ifndef _COMPLEXN_H_
#define _COMPLEXN_H_

#include <iostream> //generic I/O, other stuff
#include <math.h> //trig functions, PI
#include <memory> //shared pointers
#include <string> //using std::string
#include <sstream> //for converting double/int to string
#include <stdexcept> //for exceptions, "just in case"

class Complex { // numbers of the form z = a + bi
  double a; //real part
  double b; //imaginary part

 public:
  Complex () : a(0), b(0){} //default constructor
  Complex (double r) : a(r), b(0){}
  Complex (int r) : a(r), b(0){}
  Complex (int r, int i) : a(r), b(i){}
  Complex(Complex&& s) noexcept : a(s.a), b(s.b){ //move constructor, no resources to free
    // std::cout << "move constructor" << std::endl; is called during the program
}
 Complex(Complex& c) : a(c.a), b(c.b){} //copy constructor
  Complex& operator+(Complex& c) const;
  Complex& operator-(Complex& c) const;
  Complex& operator*(Complex& c) const;
  Complex& operator/(Complex& c);
  void operator+=(Complex& c);
  void operator-=(Complex& c);
  void operator*=(Complex& c);
  void operator/=(Complex& c);
  bool operator==(Complex& c) const;
  bool operator!=(Complex& c) const;
  bool operator>(Complex& c) const;
  bool operator<(Complex& c) const;
  bool operator>=(Complex& c) const;
  bool operator<=(Complex& c) const;
  double real() const; //return real part of complex number
  double img() const; //return imaginary part of complex number
  double rho() const; //returns |z|, distance from origin
  double theta() const; //returns angle wrt positive x axis in radians
  std::string string() const; //return a + bi or a - bi
  std::string stringCart() const; //return (real,img)
  std::string stringPolar() const; //return (rho,theta)
  Complex complexFromPolar(double mag, double angle) const; //creats a complex number given r and theta
  friend std::ostream &operator<<(std::ostream &os, const Complex& c);
  friend std::istream &operator>>(std::istream &is, Complex& c);

};

#endif
