 /*
Access Control:
        
            Class       package     World   

private     Yes         No          NO
public      Yes         Yes         Yes
defult      Yes         Yes         No

==> private attributes -> can be accessed only using member function of same class
                              or friend fuction 

geter : read private attributes;
seter : set  private attributes;
seter : for convention help to validate data & 
            or constraints that should also be applied when the object is initialized.
            
==> for Convention : make all attribute private and make setter and geter ass you want


==> key word "const" after member function ensure that the function 
    will not modify any member variables of the object (except those marked as mutable).

==> Constant References: When passed as arguments, 
        it ensures the function does not modify the referenced value.
*/

#include<bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*-----------------Forwared_Declaration------------------------*/
class Employee;
class Tube;
class Auto ;
class Bus;
class Car;

/*--------------------------------------------------------------*/
class Tube {
private:
    string color;
    double diameter;
public:

    Tube(string c = "unknown", double d = 0.35) {
        color = c;
        diameter = d;
    }
    string getColor() { 
        return color; 
    }
    void setColor(string& c) { 
        color = c; 
    }
    double getDiameter() const { 
        return diameter; 
    }
    void setDiameter(double d) { 
        diameter = d; 
    }
};

class Employee {
private:
    string FirstName;
    string LastName;
    string NID;
    string Address;
    string phone;
    int Age;
    double Salary;
    Car* mycar;   // Pointer to Employee to avoid circular dependency
public:
    
    Employee(string FN = "unknown", string LN = "unknown", string ID = "3030",
             string ad = "TOR", string num = "012", int age = 22, double s = 15000.500) {
        
        Set_First_Name(FN);
        this->LastName = LN;
        this->NID = ID;
        this->Address = ad;
        this->phone = num;
        this->Age = age;
        this->Salary = s;
    };
    void Set_First_Name(string str){
        if(str.length() < 21){
            transform(str.begin(), str.end(), str.begin(), 
                    [](unsigned char c){ return toupper(c); });
            FirstName = str;
        }
    }
    
    double Get_Raise(double percent) {
        this->Salary += percent * Salary;
        return Salary;
    }
};

class Auto 
{
private:
    double gas;
    double temp;
    int year;
    string color;
    int speed;
    bool isrunning;
    Employee* driver; 
    vector<Tube*> wheel; // "vector of pointers" refers to tube
public:
    Auto(); 
    Auto(string c = "unknown", int s = 0, double g = 30.1,
        double t = 0.0, int y = 2001, bool r = false) :
         color(c), speed(s), gas(g), temp(t), year(y), isrunning(r) {
        
        //this();  

        this->wheel.resize(4);
        this->wheel[0] = new Tube("mint_green", 0.33);
        this->wheel[1] = new Tube("mint_green", 0.33);
        this->wheel[2] = new Tube("black", 0.33); // Corrected color spelling
        this->wheel[3] = new Tube("black", 0.33);

        this->Turn_On(); // Start the car if there's gas
    }
    int Get_Year(){
        return year;
    }
    double Get_Tempreture(){
        return temp;
    }
    void Set_Gas(double Gas){
        this->gas -= (0.2 * Gas);
    }

    ~Auto() {
        for (auto wheel_ptr : wheel) {
            delete wheel_ptr; // Free allocated memory
        }
    }

    bool Turn_On() {
        if (gas <= 0) {
            cout << "Not enough gas to turn on the car.\n";
            return false;
        }
        this->isrunning = true;
        this->gas -= 1;
        this->temp += 1;

        this->Set_Gas(gas); 
        return isrunning;
    }

    void Turn_Off() {
        this->isrunning = false;
    }

    void Accelerate() {
        if (isrunning) {
            this->gas -= 1;
            this->speed += 1;
        }
    }

    void Brake() {
        if (isrunning) {
            this->speed -= 1;
        }
    }
    
};

class Bus : public Auto {
private:
    int passengerCapacity;
public:
    // using Auto::Auto;
    Bus(string color = "unknown", int s = 0, double g = 30.1,
        double t = 0.0, int y = 2001, bool r = false, int capacity = 50)
        : Auto(color, s, g, t, y, r), passengerCapacity(capacity) {}

    int getPassengerCapacity() const { return passengerCapacity; }
    void setPassengerCapacity(int capacity) { passengerCapacity = capacity; }

    void boardPassengers(int num) {
        if (num <= passengerCapacity) {
            cout << "Boarding " << num << " passengers." << endl;
        } else {
            cout << "Not enough capacity for " << num << " passengers." << endl;
        }
    }
};

class Car : public Auto{
private:
    bool safari;
public:
    // using Auto::Auto;
    Car(string color="unknown", int speed=0, double gas=30.1,
        double temp=0.0, int year=2001, bool run=false, bool safari=true):
        Auto(color, speed, gas, temp, year, run), safari(safari){};

    bool isSafari(){ 
        return safari; 
    }
    void setSafari(bool value) { 
        safari = value; 
    }
    
};

int main() {
    Car c1;

    cout << c1.Get_Year() << endl;

    return 0;
}

