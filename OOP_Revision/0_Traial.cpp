/*

==> override : what if all vehicles accelerate same way {gas -= 1} exept Cars {gas -= 3};
==> we should use "virtual" befor the function in base class to allow to be overriden 
==> we should use "override" after function definetion in derived class to be overrided

--> override : Method overriding allows a subclass to provide a specific implementation of a method 
                that is already defined in its superclass. This is used to achieve runtime polymorphism.

--> override : is resolved at runtime, enabling dynamic method dispatch, (dynamic binding).


--> overload : Method overloading allows a class to have more than one method with the same name,
                 but with different parameters,  This is used to increase the readability of the program 
                 and to perform a similar function in different ways. 

--> overload : Overloading is resolved at compile time,  (static binding).

==> setting Vehicle constructor ptotected 
        _The constructor can only be called from within the class itself and its derived classes.

        _Direct instantiation of the Vehicle class is not possible from outside the class hierarchy. 
            _This means you can't create an instance of Vehicle directly; 
            -you can only create instances of classes derived from Vehicle.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*-----------------Forward Declarations------------------------*/

class Employee;
class Tube;
class Vehicle;
class Motor;
class Auto;
class Bus;
class Car;

/*--------------------------------------------------------------*/

class Employee {
private:
    string name;
    int age;
    string id;
public:
    Employee(string str){cout <<  "Employee With String....\n";}
    Employee() {cout <<"Employee Is Starting...\n";}
    Employee(const string& name, int age, const string& id) : name(name), age(age), id(id) {}

    // Getters
    string getName() const { return name; }
    int getAge() const { return age; }
    string getId() const { return id; }

    // Setters
    void setName(const string& name) { this->name = name; }
    void setAge(int age) { this->age = age; }
    void setId(const string& id) { this->id = id; }
};

class Tube {
private:
    double size;
    string color;
public:
    Tube(double size, const string& color) : size(size), color(color) {}

    // Getters
    double getSize() const { return size; }
    string getColor() const { return color; }

    // Setters
    void setSize(double size) { this->size = size; }
    void setColor(const string& color) { this->color = color; }
};

class Vehicle {
private:
    double gas;
    double temp;
    int year;
    string color;
    int speed;
    bool isRunning;
    Employee driver;
    //Employee* driver;
    vector<Tube> wheels;
    //vector<Tube*> wheel;
protected:
    Vehicle(string str){cout <<  "Vehicle With String....\n";}
    Vehicle(){cout <<  "Vehicle Is Starting....\n";}

    // Protected constructor to be used by derived classes
    Vehicle(double gas, double temp, int year, const string& color, int speed, 
        bool isRunning, int numWheels, const Employee& driver)
        : gas(gas), temp(temp), year(year), color(color), speed(speed), 
            isRunning(isRunning), driver(driver), wheels(numWheels, Tube(16.0, "Black")) {}

public:

    //virtual ~Vehicle() {} // Virtual destructor for proper cleanup of derived classes

    // Getters
    double getGas() const { return gas; }
    double getTemp() const { return temp; }
    int getYear() const { return year; }
    string getColor() const { return color; }
    int getSpeed() const { return speed; }
    bool getIsRunning() const { return isRunning; }
    Employee getDriver() const { return driver; }
    vector<Tube> getWheels() const { return wheels; }

    // Setters
    void setGas(double gas) { this->gas = gas; }
    void setTemp(double temp) { this->temp = temp; }
    void setYear(int year) { this->year = year; }
    void setColor(const string& color) { this->color = color; }
    void setSpeed(int speed) { this->speed = speed; }
    void setIsRunning(bool isRunning) { this->isRunning = isRunning; }
    void setDriver(const Employee& driver) { this->driver = driver; }
    void setWheels(const vector<Tube>& wheels) { this->wheels = wheels; }
    
    // Virtual functions to be overridden by derived classes
    virtual void start() {
        if (!isRunning) {
            isRunning = true;
            cout << "Vehicle started." << endl;
        } else {
            cout << "Vehicle is already running." << endl;
        }
    }

    virtual void stop() {
        if (isRunning) {
            isRunning = false;
            cout << "Vehicle stopped." << endl;
        } else {
            cout << "Vehicle is already stopped." << endl;
        }
    }

    virtual void accelerate(int amount) {
        speed += amount;
        cout << "Vehicle accelerated to " << speed << " km/h." << endl;
    }

    virtual void brake(int amount) {
        speed -= amount;
        if (speed < 0) {speed = 0;}
        cout << "Vehicle slowed down to " << speed << " km/h." << endl;
    }
};

class Motor : public Vehicle {
public:
    Motor(double gas, double temp, int year, const string& color, int speed, 
        bool isRunning, const Employee& driver)
        : Vehicle(gas, temp, year, color, speed, isRunning, 2, driver) {}

    void start() override {
        cout << "Motor starting..." << endl;
        Vehicle::start();
    }

    void stop() override {
        cout << "Motor stopping..." << endl;
        Vehicle::stop();
    }

    void accelerate(int amount) override {
        cout << "Motor accelerating..." << endl;
        Vehicle::accelerate(amount);
    }

    void brake(int amount) override {
        cout << "Motor braking..." << endl;
        Vehicle::brake(amount);
    }
};

class Auto : public Vehicle {
private:
    int Numdoors;
public:
    Auto(string str){cout <<  "Auto With String....\n";}
    Auto(){cout << "Auto Is Starting....\n";}

    Auto(double gas, double temp, int year, const string& color,
         int speed, bool isRunning, int numWheels, const Employee& driver, int doors)
        : Vehicle(gas, temp, year, color, speed, isRunning, numWheels, driver){}

    void setdoors(const int numdoors) {this->Numdoors = numdoors;}

    int getdoors() const {return Numdoors;}

    void start() override {
        cout << "Auto starting..." << endl;
        Vehicle::start();
    }

    void stop() override {
        cout << "Auto stopping..." << endl;
        Vehicle::stop();
    }

    void accelerate(int amount) override {
        cout << "Auto accelerating..." << endl;
        Vehicle::accelerate(amount);
    }

    void brake(int amount) override {
        cout << "Auto braking..." << endl;
        Vehicle::brake(amount);
    }
};

class Bus : public Auto {
private:
    int Numdoors;
    //string str;
public:
    Bus(string str): Auto(str){
        cout <<  "Bus With String....\n";
        //this->(str);
    }
    Bus(){cout <<  "Bus Is Starting....\n";}


    Bus(double gas, double temp, int year, const string& color, 
        int speed, bool isRunning, const Employee& driver, int doors)
        : Auto(gas, temp, year, color, speed, isRunning, 6, driver, doors) {}
    
    void accelerate(int amount) override{
        cout << "Car accelerating..." << endl;
        Auto::accelerate(amount);
    }
};

class Car : public Auto {
private:
    int doors;
public:
    Car(double gas, double temp, int year, const string& color, 
        int speed, bool isRunning, const Employee& driver, int doors)
        : Auto(gas, temp, year, color, speed, isRunning, 4, driver, doors) {}
};

int main() {
    
    Employee driver("John Doe", 35, "E12345");
    Bus bus(50, 90, 2023, "Yellow", 0, false, driver, 2);

    Bus bs("omar");  // calling bus constructor with string and its perants will call defauld constructors 

    return 0;
}
