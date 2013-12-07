//Test program for complex number using catch. This assumes that the math library works, i.e. all the trig functions like arctan are correct. I verified that M_PI returns 3.14...

#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "complexn.h"

TEST_CASE( "Check the math library stuff", "[complexnumber]"){
  REQUIRE( ( M_PI >= 3.14 && M_PI <= 3.146 ) == true);
  //std::cout << "pi is " << M_PI << std::endl; //pi from the math library
  REQUIRE( cos(0) == 1 );
  REQUIRE( sin(0) == 0 );
  REQUIRE( cos(M_PI) == -1 );
  REQUIRE( ( sin(M_PI) >= -.00009 && sin(M_PI) <= .00009 ) == true ); //passed on OS X Mavericks, 64 bit
  //REQUIRE( sin(M_PI) == 0 ); it is not "exactly" 0 due to precision issues
  REQUIRE( atan(0) == 0 );
}

TEST_CASE( "Create a complex number with real = 0, img = 0 )", "[complexnumber]"){
  Complex* c = new Complex();
  REQUIRE( c->real() == 0 );
  REQUIRE( c->img() == 0 );
  delete c; //deconstructor implicit
}

TEST_CASE( "Create a complex number with real = int, img = 0 )", "[complexnumber]"){
  Complex* c = new Complex(5);
  REQUIRE( c->real() == 5 );
  REQUIRE( c->img() == 0 );
  delete c; //deconstructor implicit
}

TEST_CASE( "Create a complex number with real = int1, img = int2 )", "[complexnumber]"){
  Complex* c = new Complex(1, 2);
  REQUIRE( c->real() == 1 );
  REQUIRE( c->img() == 2 );
  delete c; //deconstructor implicit
}

TEST_CASE( "Create a complex number with real = double, img = 0 )", "[complexnumber]"){
  Complex* c = new Complex(4.3);
  REQUIRE( c->real() == 4.3 );
  REQUIRE( c->img() == 0 );
  delete c; //deconstructor implicit
} 

TEST_CASE( "Copy constructor", "[complexnumber]"){
  Complex* c1 = new Complex(1.5); //complex number with a = 1.5, b = 0
  Complex* c2 = new Complex(*c1); //complex number with a = 1.5, b= 0
  REQUIRE( c2->real() == 1.5 );
   REQUIRE( c2->img() == 0 );
   delete c1;
   delete c2;
}

TEST_CASE ( "Move constructor", "[complexnumber]"){
  Complex* c1 = new Complex(1, 2); //a = 1, b = 2
  Complex* c2 = new Complex((std::move(*c1))); //std::move generates an Rvalue which is passed as the argument for the move constructor
 REQUIRE( c2->real() == 1 );
   REQUIRE( c2->img() == 2 );
   delete c1;
   delete c2;
}

TEST_CASE ( "Get magnitude and angle of imaginary number where a, b >=0", "[complexnumber]"){
  Complex* c1 = new Complex(0, 2);

  SECTION("Magnitude check"){
  REQUIRE( c1->rho() == 2 ); // sqrt (0^2 + 2^2) == 2
  }
  SECTION("Angle check"){
  REQUIRE( c1->theta() == atan(c1->real() / c1->img()));
  }
	   delete c1;
}

TEST_CASE ( "Get magnitude and angle of imaginary number where a, b <0", "[complexnumber]"){
  Complex* c1 = new Complex(-5, -1);
  SECTION ("Magnitude check"){
  REQUIRE( c1 -> rho() == sqrt(26) ); // sqrt (25 + 1) == sqrt(26)
  }
  SECTION("Angle check"){
  REQUIRE( c1 -> theta() == atan(c1->real()/c1->img() + M_PI));
  }
  delete c1;
}

TEST_CASE( "Get complex number from rho, theta", "[complexnumber]"){
  Complex* b = new Complex(); //need to create a new complex number to use complexfrompolar
  Complex* c = new Complex(b->complexFromPolar(9, M_PI)); //using the copy constructor
  REQUIRE( c->real() == -9 ); //cos(180) == -1
  REQUIRE( c->img() == 9*sin(M_PI) ); //sin(180) == 0 was causing issues, so switched to how the math library handles this
  delete b;
  delete c;
}

TEST_CASE( "arithmetic operators", "[complexnumber]"){
  Complex c1(1, 1);
  Complex c2(2, 2);

SECTION( "+ operator" ) {
  Complex c3( c1 + c2);
  REQUIRE( c3.real() == 3 );
  REQUIRE( c3.img() == 3 );
    }

SECTION( "- operator" ) {
  Complex c3( c1 - c2);
  REQUIRE( c3.real() == -1 );
  REQUIRE( c3.img() == -1 );
    }

SECTION( "* operator" ) {
  Complex c3( c1*c2);
 REQUIRE( c3.real() == 2 - 2);
  REQUIRE ( c3.img() == 2 + 2 );
    }
SECTION( "/ operator" ) {
  Complex c3 ( c1/c2 );
  REQUIRE( c3.real() == .5 );
  REQUIRE( c3.img() == 0 );
    }
SECTION( "+= operator" ) {
  c1 += c2;
  REQUIRE( c1.real() == 3 );
  REQUIRE( c1.img() == 3 );
    }
SECTION( "-= operator" ) {
  c1 -= c2;
  REQUIRE( c1.real() == -1 );
        REQUIRE( c1.img() == -1);
    }
SECTION( "*= operator" ) {
  c1 *= c2;
  REQUIRE( c1.real() == 2 - 2);
  REQUIRE ( c1.img() == 2 + 2 );
    }
SECTION( "/= operator" ) {
  // std:: cout << c1.real() << std::endl;
  //std::cout << c1.img() << std::endl;
  //std::cout << c2.real() << std::endl;
  //std::cout << c2.img() << std::endl;
  c1 /= c2;
  //std:: cout << c1.real() << std::endl;
  //std::cout << c1.img() << std::endl;
  //std::cout << c2.real() << std::endl;
  //std::cout << c2.img() << std::endl;
  REQUIRE( c1.real() == .5 ); // 2+2/4+4 = 1/2
  REQUIRE( c1.img() == 0 ); // 2-2 / 4+4 
    }

}

//division by 0 is not defined, so throw exceptions
TEST_CASE( "Division by 0", "[complexnumber]"){
  Complex c1(1, 1);
  Complex c2; //default constructor, c2.a = 0, c2.b = 0. i.e. 0^2 + 0^2 = 0 in the denominator for any division
  REQUIRE( c2.real() == 0 );
  REQUIRE ( c2.img() == 0);
  SECTION(" /= operator"){
    REQUIRE_THROWS(c1 /= c2); //require an exception be thrown
}
SECTION(" / operator"){
  REQUIRE_THROWS(Complex c3(c1 / c2)); //uses c1 as an initializer for c3, throws exception because division by 0 is undefined so c3 cannot be initialized
  }
}

TEST_CASE( "comparison operators, c1 == c2", "[complexnumber]"){
  Complex c1(1, 1);
  Complex c2(1, 1);
  SECTION("== operator"){
    REQUIRE( ( c1 == c2 ) == true );
  }
  SECTION("!= operator"){
    REQUIRE( ( c1 != c2 ) == false );
  }
  SECTION("< operator"){
    REQUIRE( ( c1 < c2 ) == false );
  }
  SECTION("<= operator"){
    REQUIRE ( ( c1 <= c2 ) == true );
  }
  SECTION("> operator"){
    REQUIRE( ( c1 > c2 ) == false );
  }
  SECTION(">= operator"){
    REQUIRE ( ( c1 >= c2 ) == true );
  }

}

TEST_CASE( "comparison operators, c1 > c2", "[complexnumber]"){
  Complex c1(2, 2);
  Complex c2(1, 1);
   SECTION("== operator"){
    REQUIRE( ( c1 == c2 ) == false );
  }
  SECTION("!= operator"){
    REQUIRE( ( c1 != c2 ) == true );
  }
  SECTION("< operator"){
    REQUIRE( ( c1 < c2 ) == false );
  }
  SECTION("<= operator"){
    REQUIRE ( ( c1 <= c2 ) == false );
  }
  SECTION("> operator"){
    REQUIRE( ( c1 > c2 ) == true );
  }
  SECTION(">= operator"){
    REQUIRE ( ( c1 >= c2 ) == true );
  }
}

TEST_CASE( "comparison operators, c1 < c2", "[complexnumber]"){
  Complex c1(1, 1);
  Complex c2(3, 3);
   SECTION("== operator"){
    REQUIRE( ( c1 == c2 ) == false );
  }
  SECTION("!= operator"){
    REQUIRE( ( c1 != c2 ) == true );
  }
  SECTION("< operator"){
    REQUIRE( ( c1 < c2 ) == true );
  }
  SECTION("<= operator"){
    REQUIRE ( ( c1 <= c2 ) == true );
  }
  SECTION("> operator"){
    REQUIRE( ( c1 > c2 ) == false );
  }
  SECTION(">= operator"){
    REQUIRE ( ( c1 >= c2 ) == false );
  }
}
TEST_CASE( "return a + bi as a string, b > 0, integers", "[complexnumber]"){
  Complex c(-1000, 50896);
  SECTION( "string()"){
  REQUIRE( c.string() == "-1000 + 50896 i" );
  }
  SECTION("stringCart()"){
    REQUIRE( c.stringCart() == "(-1000,50896)" );
  }
  SECTION("stringPolar()"){
    //std::cout << "expressed as a String in polar coordinates case 1 is " << c.stringPolar() << std::endl;
    REQUIRE( c.stringPolar() == "(50905.8,-0.0196454)");// obviously the print statement gave this answer! but since rho and theta already work by previous test case and the sstream works in the above cases, we were just checking to see that it formatted correctly
  }
  SECTION("<<"){
    std::ostringstream os; //create an ostringstream
    os << c;
    REQUIRE( os.str() == "-1000 + 50896 i" );
      // std::cout << "test of stream insertion into ostream " << c << std::endl;
  }
}
TEST_CASE( "return a + bi as a string, b = 0, double", "[complexnumber]"){
  Complex c(12.57);
  SECTION("string()"){
  REQUIRE( c.string() == "12.57 + 0 i" );
  }
   SECTION("stringCart()"){
    REQUIRE( c.stringCart() == "(12.57,0)" );
  }
  SECTION("stringPolar()"){
    // std::cout << "expressed as a String in polar coordinates case 2 is " << c.stringPolar() << std::endl;
    REQUIRE( c.stringPolar() == "(12.57,1.5708)");// obviously the print statement gave this answer! but since rho and theta already work by previous test case and the sstream works in the above sections, we were just checking to see that it formatted correctly
  }
  SECTION("<<"){
    std::ostringstream os; //create an ostringstream
    os << c;
    REQUIRE( os.str() == "12.57 + 0 i" );
    //std::cout << "test of stream insertion into ostream " << c << std::endl;
  }
}
TEST_CASE( "return a + bi as a string, b < 0, integers", "[complexnumber]"){
  Complex c(9416, -1044);
  SECTION("string()"){
  REQUIRE( c.string() == "9416 - 1044 i" );
}
  SECTION("stringCart()"){
    REQUIRE( c.stringCart() == "(9416,-1044)" );
  }
  SECTION("stringPolar()"){
    //std::cout << "expressed as a String in polar coordinates case 3 is " << c.stringPolar() << std::endl;
    REQUIRE( c.stringPolar() == "(9473.7,-1.46037)"); // obviously the print statement gave this answer! but since rho and theta already work by previous test case and the sstream works in the above sections, we were just checking to see that it formatted correctly
  }
  SECTION("<<"){
    std::ostringstream os; //create an ostringstream
    os << c;
    REQUIRE( os.str() == "9416 - 1044 i" );
    //std::cout << "test of stream insertion into ostream " << c << std::endl;
  }
}

TEST_CASE("Stream extraction from istream using std::cin", "[complexnumber]"){
  Complex c; //new complex # a = b = 0
  // std::istringstream is;

  SECTION("b > 0"){
    // std::cout << "enter 100 + 5 i to test case 1 stream extraction from istream" << std::endl;
    std::istringstream is("100 + 5 i"); //create the std::cin replacement
    is >> c;
    //std::cin >> c; //enter as 100 + 5 i
  REQUIRE( c.real() == 100 );
  REQUIRE( c.img() == 5 );
  }
  SECTION("b < 0"){
    //std::cout << "enter 100 - 5 i to test case 2 stream extraction from istream" << std::endl;
    //std::cin >> c; //enter as 100 - 5 i
   std::istringstream is("100 - 5 i"); //create the std::cin replacement
    is >> c;
  REQUIRE( c.real() == 100 );
  REQUIRE( c.img() == -5 );
  }
  SECTION("b == 0"){
    //std::cout << "enter 100 + 0 i to test case 3 stream extraction from istream" << std::endl;
    //std::cin >> c; //enter as 100 + 0 i or 100 - 0 i
   std::istringstream is("100 + 0 i"); //create the std::cin replacement
    is >> c;
  REQUIRE( c.real() == 100 );
  REQUIRE( c.img() == 0 );
  }
}	  

	   
	   

