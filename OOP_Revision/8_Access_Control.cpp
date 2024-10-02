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

*/

#include<bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Employee; // Forward Declaration
class Tube;
class Car;

/*---------------------------------------------------------------*/

class Tube {
public:
    string color;
    double diameter;

    Tube(string c = "unknown", double d = 0.35) {
        color = c;
        diameter = d;
    }
};

class Car {
private:
    double gas;
    double temp;
    int year;
public:
    string color;
    int speed;
    bool isrunning;
    Employee* driver; // Pointer to Employee to avoid circular dependency
    vector<Tube*> wheel; // "vector of pointers" refers to tube

    //Car(){}
    Car(string c = "unknown", int s = 0, double g = 30.1,
        double t = 0.0, int y = 2001, bool r = false) : color(c), speed(s), gas(g), temp(t), year(y), isrunning(r) {
        
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

    ~Car() {
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

class Employee {
private:
    string FirstName;
    
public:
    string LastName;
    string NID;
    string Address;
    string phone;
    int Age;
    double Salary;
    Car mycar;

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

int main() {
    Car c1("red", 150, 21, 37, 2004, true);
    Car c2("silver", 150, 21, 37, 2004, true);

    Employee emp1("omar", "ayman");

    //cout << c1.wheel[2]->color << endl;

    cout << c1.Get_Tempreture() << endl;
    //cout << c1.Get_Gas() << endl;
    //cout << emp1.Get_First_Name()<< endl;


    return 0;
}

