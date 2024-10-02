 /*

Referance Object : what if you want to know the if employee x has a car and its color.

Forward Declaration :  informs the compiler of 
                        its existence before providing its complete definition.


--> Car is a non-primitive data type then we can initialize a variable from it

==> we used previous property to add an attribute with kind of Car to an employee
==> we use Forward Declaration to Resolving Circular Dependencies

*/


#include<iostream>
#include<string>
using namespace std;

class Employee; // Forward Declaration

class Car
{
private:
public:
    string color;
    int speed;
    double gas;
    double temp;
    int year;
    bool isrunning;
    Employee* dirver; // Pointer to Employee to avoid circular dependency

    /*
    Car(string color = "unknowen", int speed=0, double gas=30, double temp=31, int year=2013, bool isrunning=false)
      : color(color), speed(speed), gas(gas),
        temp(temp), year(year), isrunning(isrunning) driver(nullptr) {}

    */
    Car(string c = "unknowen", int s = 0, double g = 30.1, double t = 0.0, int y = 2001, bool r = false) {
        color = c;
        speed = s;
        gas = g;
        year = y;
        temp = t;
        isrunning = r;
    }
    bool Turn_On() {
        if (gas <= 0) {
            cout << "Not enough gas to turn on the car.\n";
            return false;
        }
        isrunning = true;
        gas -= 1;
        temp += 1;

        return isrunning;
    }
    void Turn_Of() {
        isrunning = false;
    }
    void Accelerate() {
        if (isrunning) {
            gas -= 1;
            speed += 1;
        }
    }
    void breke() {
        if (isrunning) {
            speed -= 1;
        }
    }
};

class Employee
{
private:

public:
    string FirstName;
    string LastName;
    string NID;
    string Address;
    string phone;
    int Age;
    double Salary;
    Car mycar;
    /*
    Employee(string FN, string LN, string ID, string ad, string num, int age, double s, const Car& car)
      : FirstName(FN), LastName(LN), NID(ID), Address(ad), phone(num), Age(age), Salary(s), mycar(car) {}
    */

    Employee(string FN="unknowen", string LN="unknowen", string ID="3030", 
                  string ad="TOR", string num="012", int age=22, double s=15000.500) {
        FirstName = FN;
        LastName = LN;
        NID = ID;
        Address = ad;
        phone = num;
        Age = age;
        Salary = s;
    };

    double Get_Raise(double percent) {
        Salary = Salary + percent * Salary;
        return Salary;
    }

};

int main()
{
    Car c1("Blue", 150, 10.5, 31.9);
    Employee emp("omar", "ayman", "3030", "TOR", "012", 22, 15000.500);

    emp.mycar = c1;
    c1.dirver = &emp;

    cout << c1.dirver->FirstName << endl;
    cout << emp.mycar.color << endl;
    return 0;
}
