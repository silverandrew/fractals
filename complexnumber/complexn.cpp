//method definitions for complexn.cpp, includes a couple of nonmember functions that are friends of the class

#include "complexn.h" //complex.cpp

double Complex::real() const{ //return real part of complex number
  return a;
}

double Complex::img() const{ //return imaginary part of complex number
  return b;
}

double Complex::rho() const{
  return sqrt(a*a + b*b); //returns |z| = |a^2 + b^2|, should be positive
  }

double Complex::theta() const{ //tan theta = a/b, so theta = arctan (a/b) if a and b > 0. if a and b < 0, then want tan theta + pi.
  if(a >= 0 || b >= 0){ //normal case
    return atan(a/b);
  }
  else{ //a <= 0 and b <= 0, then we are looking at arctan shifted by pi - the minus sign was lost by division
return atan(a/b + M_PI); //M_PI is 3.14159
}
}

//x = rcostheta, y = rsintheta
Complex Complex::complexFromPolar(double mag, double angle) const{ //takes a rho and theta and creats a complex number
  Complex c; //create new complex number
  c.a = mag*cos(angle);
  c.b = mag*sin(angle);
  return c; //returns the new complex number
}

Complex& Complex::operator+(Complex& c) const{
auto fc = std::make_shared<Complex>(); //make a shared pointer to a new complex number
 fc->a = a + c.a;
 fc->b = b + c.b;
 return *fc; //return the new complex number
}
Complex& Complex::operator-(Complex& c) const{
  auto fc = std::make_shared<Complex>(); //make a shared pointer to a new complex number
 fc->a = a - c.a;
 fc->b = b - c.b;
 return *fc; //return the new complex number
}
Complex& Complex::operator*(Complex& c) const{
    auto fc = std::make_shared<Complex>(); //make a shared pointer to a new complex number
  fc->a = a*c.a - b*c.b;
  fc->b = b*c.a + a*c.b;
 return *fc; //return the new complex number
}

Complex& Complex::operator/(Complex& c){ //not const because returning *this
 double num = 0;
  double denom = c.a*c.a + c.b*c.b;
  double af;

  if(denom != 0){ //division by 0 is impossible
    num = a*c.a + b*c.b; //calculate numerator of a
  af = num/denom;
  }
  else{ //trying to divide by 0
    throw std::runtime_error("Cannot divide by 0");
    //std::cout << "cannot divide by 0" << std::endl; bad to have a print statement
    // return *this; //returns the complex number this was called on, the division is impossible
  }
  //std::cout << "current num" << num << std::endl;
  //std::cout << "cura" << a << std::endl;
  //std::cout << "curb" << b << std::endl;
 num = (b*c.a) - (a*c.b);
 //std::cout << "current num" << num << std::endl;
 double bf = num/denom;
 auto fc = std::make_shared<Complex>(); //make a shared pointer to a new complex number
 fc->a = af;
 fc->b = bf;
 return *fc; //return the new complex number
    }

void Complex::operator+=(Complex& c){ //x1 + x2, y1 + y2
  a += c.a;
  b += c.b;
}


void Complex::operator-=(Complex& c){ //x1 - x2, y1 - y2
  a -= c.a;
  b -= c.b;
}

void Complex::operator*=(Complex& c){ //(x1, y1)*(x2, y2) = (x1x2 - y1y2, y1x2 + x1y2) -> Brown/Churchill
  double af = a*c.a - b*c.b;
  double bf = b*c.a + a*c.b;
  a = af;
  b = bf;
}

void Complex::operator/=(Complex& c){ //see Brown and Churchill
  double num = 0;
  double denom = c.a*c.a + c.b*c.b;
  double af;
  if(denom != 0){ //division by 0 is impossible
    num = a*c.a + b*c.b; //calculate numerator of a
  af = num/denom;
  }
  else{ //attempting to divide by 0
    //std::cout << "cannot divide by 0" << std::endl;
    //throw std::runtime_error("cannot divide by 0");
    throw std::runtime_error("Cannot divide by 0");
    // return; //do nothing, operation not possible
  }
  //std::cout << "current num" << num << std::endl;
  //std::cout << "cura" << a << std::endl;
  //std::cout << "curb" << b << std::endl;
 num = (b*c.a) - (a*c.b);
 //std::cout << "current num" << num << std::endl;
 b = num/denom;
 a = af;
}

bool Complex::operator==(Complex& c) const{ //complex numbers are equal iff their real part and imaginary parts are real
  return (a == c.a && b == c.b); //if both a, bs are equal, then the whole thing is equal
}

bool Complex::operator!=(Complex& c) const{
      return !(a == c.a && b == c.b); //! the above
    }

bool Complex::operator<(Complex& c) const{
  return ( rho() < c.rho() || ( ( rho() == c.rho() ) && ( theta() < c.theta() ) ) );
}

bool Complex::operator>(Complex& c) const{
  return ( rho() > c.rho() || ( ( rho() == c.rho() ) && ( theta() > c.theta() ) ) );
}

bool Complex::operator<=(Complex& c) const{
  return ( rho() < c.rho() || ( ( rho() == c.rho() ) && ( theta() < c.theta() ) ) || (a == c.a && b == c.b) );
}

bool Complex::operator>=(Complex& c) const{
  return ( rho() > c.rho() || ( ( rho() == c.rho() ) && ( theta() > c.theta() ) ) || (a == c.a && b == c.b) );
}

//convert a and b to strings, and output " a + bi " - requires converting ints to strings, reversing these strings to get the correct order, and concat with the results. Alternative methods include using a vector which has push_front/prepend, or improving the algorithm for grabbing digits. Using an sstream for conversion here, because it works with both ints and doubles
std::string Complex::string() const{ //returns a + bi, if b = 0 it returns a + 0i
  std::string cn = "";
std::ostringstream osa;
std::ostringstream osb;
 osa << a; //read in a
 cn += osa.str(); //concat a to the beginning of the output string
    osb << b; //send b into ostringstream
  if( b >= 0 ){ //b is positive
    cn += " + ";
cn += osb.str();
  }
  else{ //b < 0, want a minus sign and need to eliminate the existing - sign in front of the b term
    cn += " - ";
    cn += osb.str().substr(1); //convert the ostringstream into a string and skip past the minus sign at index 0 by making a substring from that point
  }
 cn += " i"; //concat i, padding at the front per assignment specifications
 return cn; //return the output string of a + bi

 //old method for converting integers to strings with mod operation, modulus doesn't work for doubles
  /* std::string cn = ""; //final string output
  std::string x = ""; //string that will hold a (in reverse order)
  std::string y = ""; //string that will hold b (in reverse order)
  std::string flipped = ""; //the string that is the flipped string after the for loop
  for( int n = a; n != 0; n/=10 ){ //while the number is not equal to 0, divide it by 10 repeatedly
    x.push_back( ( n % 10 ) + '0' ); //perform mod operation repeatedly to grab the last digit, append to X
  }
  //after this is done the number a is in the reverse order, so reverse it
  for ( std::string::reverse_iterator itb = x.rbegin(); itb != x.rend(); ++itb ) { //create the forward integer string from the reversed integer string
    flipped += *itb; //concat the character
}
  cn += flipped; //concat the flipped number a to the output string
  if( b >= 0 ){ //b is positive
    cn += " + ";
  }
  else{ //b < 0, want a minus sign
    cn += " - ";
  }
  //do the same for b
  for( int n = b; n != 0; n/=10 ){ //while the number is not equal to 0, divide it by 10 repeatedly
    y.push_back( ( n % 10 ) + '0' ); //perform mod operation repeatedly to grab the last digit
  }
  flipped = ""; //change the flipped string to empty again
  for ( std::string::reverse_iterator itb = y.rbegin(); itb != y.rend(); ++itb ) { //create the forward integer string from the reversed integer string
    flipped += *itb; //concat the character
}
  cn += flipped; //concat the b in the correct order
  cn += "i"; //add i
  return cn; */

}

std::string Complex::stringCart() const{ //returns (real,img)
  std::string output = "";
  output += "(";
std::ostringstream osa;
std::ostringstream osb;
 osa << a; //read in a
 output += osa.str(); //concat a to the beginning of the output string
 output += ",";
    osb << b; //send b into ostringstream
    output += osb.str(); //concat b to the output string
    output += ")";
    return output;
}

std::string Complex::stringPolar() const{ //returns (rho,theta)
  std::string output = "";
std::ostringstream osa;
std::ostringstream osb;
  output += "(";
  osa << rho(); //read in rho
  output += osa.str(); //concat rho to the output string
  output += ",";
  osb << theta(); //read in theta
  output += osb.str(); //concat theta to the output string
    output += ")";
    return output;
}

std::ostream &operator<<(std::ostream &os, const Complex& c){ //allows for std::cout shenanigans
  os << c.string();
return os;
}

std::istream &operator>>(std::istream &is, Complex& c){ //expects form a + b i OR a - b i
  char sign; //grabs the + or - sign
  char letter; //grabs the letter "i" at the end
  is >> c.a >> sign >> c.b >> letter; //skips whitespaces
  if(sign == '-' ){
    c.b *= -1; //change b to a negative value
  } 
  if (!is){ //input did not succeed, go to default state of 0 + 0i
    c.a = 0;
    c.b = 0;
    std::cout << "stream extraction from istream failed, set to default state" << std::endl;
  }
return is;
}


