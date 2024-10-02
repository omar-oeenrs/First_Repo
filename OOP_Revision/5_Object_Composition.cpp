 /*

Composition : models a "has-a" relationship between objects. 
                It allows one class (the "composite" or "container" class) 
                to contain objects of another class (the "component" class) 
                as part of its state.

==> Composition involve a relationship called "has-a"
                Car "has-a" Employees.

==> we use dirver in Car to compose an Employee in Car.
==> and so on passenger & wheel
*/


#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Employee; // Forward Declaration
class Car;
class Tube;

class Tube
{
public:
    string color;
    double dimeter;

    Tube(string c = "unknowen", double d = 0.35){
        color = c;
        dimeter = d;
    }
};
 
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
    vector<Employee*> passenger; // "vector of references" refers to employee
    vector<Tube*> wheel;         // "vector of references" refers to tube
    
    Car(string c = "unknowen", int s = 0, double g = 30.1, double t = 0.0, 
                int y = 2001, bool r = false, int siz = 4) {
        color = c;
        speed = s;
        gas = g;
        year = y;
        temp = t;
        isrunning = r;
        passenger.resize(siz);
        wheel.resize(siz);
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

    //cout << c1.dirver->FirstName << endl;
    //cout << emp.mycar.color << endl;

    string c = "amar";
    for(int i = 0; i < (int)c1.passenger.size(); i++){
        c[0] = (char)'a'+i;
        Employee* e = new Employee();
        e->FirstName = c;
        c1.passenger[i] = e;
    }
    for(int i = 0; i < (int)c1.passenger.size(); i++){
        //cout << c1.passenger[i]->FirstName << endl;
    }
    for(Employee* e : c1.passenger){
        delete e;
    }
    c1.passenger.clear();
    /*
    // this will done without mycar in employee;
    string c = "amar";
    for(int i = 0; i < (int)c1.passenger.size(); i++){
        c[0] = (char)'a'+i;
        Employee e;
        e.FirstName = c;
        c1.passenger[i] = e;
    }
    for(int i = 0; i < (int)c1.passenger.size(); i++){
        cout << c1.passenger[i].FirstName << endl;
    }
    */
    for(int i = 0; i < c1.wheel.size(); i++){
        Tube* w = new Tube();
        if(i%2){
            w->color = "Black";
        }
        else{
            w->color = "Red";
        }
        c1.wheel[i] = w;
    }
    for(int i = 0; i < (int)c1.wheel.size(); i++){
        cout << c1.wheel[i]->color << " " << c1.wheel[i]->dimeter<< endl;
    }
    for(Tube* t : c1.wheel){
        delete t;
    }
    c1.wheel.clear();
    return 0;
}
