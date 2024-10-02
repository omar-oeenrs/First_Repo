 /*
this-> : is used for convention that we access current Object;

==> this-> : gives more reusability of code
                  _ we can make more one constructur with different parameters

this->wheel[0] = new Tube("mint_green", 0.33);
            dynamically allocates memory for a Tube object and 
            calls its constructor with the provided arguments

this->wheel[2]->color = "blake";
            is a pointer to an object, and -> is used to access the color 
            property of the object that wheel[2] points to.*
*/


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
public:
    string color;
    int speed;
    double gas;
    double temp;
    int year;
    bool isrunning;
    Employee* driver; // Pointer to Employee to avoid circular dependency
    vector<Employee*> passenger; // "vector of references" refers to employee
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
public:
    string FirstName;
    string LastName;
    string NID;
    string Address;
    string phone;
    int Age;
    double Salary;
    Car mycar;

    Employee(string FN = "unknown", string LN = "unknown", string ID = "3030",
             string ad = "TOR", string num = "012", int age = 22, double s = 15000.500) {
        this->FirstName = FN;
        this->LastName = LN;
        this->NID = ID;
        this->Address = ad;
        this->phone = num;
        this->Age = age;
        this->Salary = s;
    };

    double Get_Raise(double percent) {
        this->Salary += percent * Salary;
        return Salary;
    }
};

int main() {
    Car c1("red", 150, 5.3, 37, 2004, true);
    Car c2("silver", 150, 5.3, 37, 2004, true);

    Employee emp1("omar", "ayman");

    cout << c1.wheel[2]->color << endl;

    return 0;
}

