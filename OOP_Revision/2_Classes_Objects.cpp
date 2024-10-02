/*
==> Class is a catalog which contains all properties ==> DNA of humans
==> Objects is an instance of the class which contain all properties in this class ==> man
==> Attribute is The characteristic that "distinguishes" one person from another
==> Function or Method is the characteristic or function "shared" between people


>> we will descuss this on a car as an example.

==> Class     : car
==> Object    : instance of car
==> functions :
            {
               Turn_On
               Turn_Of
               Accelerate
               Break
            }

==> Attributes :
            {
               Speed
               Gas
               Temprateure
               Color
               Year
               Is_Running
            }
*/
 
#include<bits/stdc++.h>
#include <iostream>
#include <string>
using namespace std;

class Car
{
private:
      /*
      string color;
      int speed;
      double gas;
      double temp;
      int year;
      dool isrunning;
      */
public:
      string color;
      int speed;
      double gas;
      double temp;
      int year;
      bool isrunning;
      // Default Constructor
      Car() : color("Unknown"), speed(0), gas(10.0), temp(0.0), year(2020), isrunning(false) {}

      // Parameterized Constructor
      Car(const string& color, int speed, double gas, double temp, int year, bool isrunning)
        : color(color), speed(speed), gas(gas), temp(temp), year(year), isrunning(isrunning) {}

      //~Car();
      
      bool Turn_On(){
            if (gas <= 0) {
                  cout << "Not enough gas to turn on the car.\n";
                  return false;
            }
            isrunning = true;
            gas -= 1;
            temp += 1;

            return isrunning;
      }
      void Turn_Of(){
            isrunning = false;
      }
      void Accelerate(){
            if(isrunning){
                  gas -= 1;
                  speed += 1;
            }
      }
      void breke(){
            if(isrunning){
                  speed -= 1;
            }
      }
};

int main() 
{
      Car c1("Blake", 0, 10.0, 0.0, 2020, false);

      bool c = c1.Turn_On();
      //cout << c1.color << endl;  //"will print if color is a public attribute"
      cout << c1.gas << endl;




      return 0;
}



