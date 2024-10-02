/*
==> Method is the function inside the class;

==> primitives data types : int , string , double; => first cahr is "small"
==> non-primitives data types : Classe; => first cahr is "Capital"
*/


#include<bits/stdc++.h>
#include<istream>

using namespace std;

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

      Employee(string FN, string LN, string ID, string ad, string num, int age, double s){
            FirstName = FN;
            LastName = LN;
            NID = ID;
            Address = ad;
            phone = num;
            Age = age;
            Salary = s;
      
      };

      //~Employee();

      double Get_Raise(double percent){
            Salary = Salary + percent*Salary;
            return Salary;
      }

};

int main()
{
      Employee emp("omar", "ayman", "30302601284744853", "TOR", "012", 22, 15000.500);

      emp.Get_Raise(0.20);
      cout << emp.Salary << endl;

      return 0;
}

