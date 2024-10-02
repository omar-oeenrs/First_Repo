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

#include<algorithm>
#include<iostream>
#include<vector>
#include<string>
#include<set>
using namespace std;

// Forward declarations
class College;
class Department;
class Course;
class Professor;
class Student;

// --------------- Student Class ---------------
class Student
{
public:
      string firstname ;
      string lastname;
      string phone;
      string address;
      int age;
      Department* department;
      vector<Course*> courses;

      Student(string fn="Unknown", string ln="Unknown", 
                  string pn="012", string add="TOR", 
                        int age=21, Department* dpt = nullptr) :
                        firstname(fn), lastname(ln), phone(pn), 
                        address(add), age(age), department(dpt){};

      string Full_Name(){
            return firstname + " " + lastname;
      }
      //bool Is_Assigned(){}

      void Report(){
        cout << "Student Name: " << Full_Name() << endl;
        cout << "Age: " << age << endl;
        cout << "Phone: " << phone << endl;
        cout << "Address: " << address << endl;
        //cout << "Department: " << (department ? department->name : "Not assigned") << endl;
        cout << "Enrolled Courses: ";
        for (const auto& course : courses) {
            cout << course->name << " ";
        }
        cout << endl;
    }
};

// --------------- Professor Class ---------------
class Professor
{
public:
      string firstname ;
      string lastname;
      string phone;
      string address;
      double salary;
      vector<Course*> courses;

      Professor(string fn="Unknown", string ln="Unknown", 
                  string pn="010", string add="ZAG", double d=15000.5):
                        firstname(fn), lastname(ln), phone(pn),
                         address(add), salary(d) {};

      double Get_Raise(double percent){
            salary = salary + salary*percent;
            return salary;
      }
      string Full_Name(){
            return firstname + " " + lastname;
      }
      vector<Course*>& Get_Courses(){
            return courses;
      }
      void Report(){
        cout << "Professor Name: " << Full_Name() << endl;
        cout << "Phone: " << phone << endl;
        cout << "Address: " << address << endl;
        cout << "Salary: $" << salary << endl;
        cout << "Courses: \n\t";
        for (const auto& course : courses) {
            cout << course->name << " ";
        }
        cout << endl;
    }
};


// --------------- Course Class ---------------
class Course
{
public:
      string name;
      string description;
      int max_number_of_students;
      int number_of_lectures;
      vector<Student*> students;
      Professor* professor;
      Department* department;

      Course(string name="Unknown", 
            string desc="non-subject", int maxst=50, int maxlc=15, 
               Department* dpt = nullptr):
                  name(name), description(desc), max_number_of_students(maxst),
                  number_of_lectures(maxlc), professor(nullptr),department(dpt){};

      int Number_Of_Students(){
            return students.size();
      }
      bool Is_Assigned(){
            return professor != nullptr;
      }
      bool Assign_Professor(Professor* p){
            if (!Is_Assigned()) {
                  professor = p;
                  p->courses.push_back(this);
                  return true;
            }
            cout << "This Course is already assigned to professor\n";
            return false;
      }
      void Unassign_Professor(){
            if (professor == nullptr) {
                  return;
            }
            // Remove this course from the professor's list of courses
            auto courses = professor->Get_Courses();
            auto pos = find(courses.begin(), courses.end(), this);

            if (pos != courses.end()) {
                  courses.erase(pos);
            }
            // Unassign the professor from this course
            professor = nullptr;
      }
      string Professor_Name(){
            if(Is_Assigned()){
                  return professor->Full_Name();
            }
            return "This Course Is Still Unassigned\n";
      }
      bool Is_Full(){
            return students.size() == max_number_of_students;
      }
      bool Enroll(Student* st){
            if((!Is_Full()) && (st->department == department)){
                  students.push_back(st);
                  st->courses.push_back(this);
                  return true;
            }
            return false;
      }
      void Withdrow(Student* st){
            auto pos = find(students.begin(), students.end(), st);
            if(pos != students.end()){
                  students.erase(pos);
            }
            auto pos2 = find(st->courses.begin(), st->courses.end(), this);
            if(pos2 != st->courses.end()){
                  st->courses.erase(pos2);
            }
      }
      void Report(){
        cout << "Course Name: " << name << endl;
        cout << "Description: " << description << endl;
        cout << "Max Number of Students: " << max_number_of_students << endl;
        cout << "Number of Lectures: " << number_of_lectures << endl;
        cout << "Professor: " << Professor_Name() << endl;
        cout << "Enrolled Students: ";
        for (const auto& student : students) {
            cout << student->Full_Name() << " ";
        }
        cout << endl;
    }
};

// --------------- Department Class ---------------

class Department
{
public:
      string name;
      string description;
      int max_number_of_students;
      vector<Course*> courses;
      vector<Student*> students;
      vector<Professor*> professors;

      Department(string name="Unknown", 
                  string desc="new department", int maxst=500):
                  name(name), description(desc), max_number_of_students(maxst){};
      
      int Number_Of_Course(){
            return courses.size();
      }
      int Number_Of_Professors(){
            return professors.size();
      }
      int Number_Of_Students(){
            return students.size();
      }
      bool Is_Full(){
            return students.size() == max_number_of_students;
      }
      Course* Find_Course(string Course_Name){
            for(Course* c : courses){
                  if(c->name == Course_Name){
                        return c;
                  }
            }
            return nullptr;
      }
      bool Enroll(Student* s) {
        if (!Is_Full()) {
            students.push_back(s);
            s->department = this;
            return true;
        }
        return false;
    }
    void Add_Course(Course* course) {
        auto pos = find(courses.begin(), courses.end(), course);
        if (pos == courses.end()) {
            courses.push_back(course);
            course->department = this;
        }
    }
    void Add_Professor(Professor* professor) {
        auto pos = find(professors.begin(), professors.end(), professor);
        if (pos == professors.end()) {
            professors.push_back(professor);
        }
    }
    void Remove_Student(Student* s) {
        auto pos = find(students.begin(), students.end(), s);
        if (pos != students.end()) {
            students.erase(pos);
        }
    }
    void Report(){
        cout << "Department Name: " << name << endl;
        cout << "Description: " << description << endl;
        cout << "Max Number of Students: " << max_number_of_students << endl;
        cout << "Number of Courses: " << Number_Of_Course() << endl;
        cout << "Number of Professors: " << Number_Of_Professors() << endl;
        cout << "Number of Students: " << Number_Of_Students() << endl;
        cout << "Courses: \n\t";
        for (auto& course : courses) {
            cout << course->name << endl;
        }
        cout << endl;
        cout << "Professors: \n\t";
        for (auto& professor : professors) {
            cout << professor->Full_Name() << endl;
        }
        cout << endl;
        cout << "Students: \n\t";
          for (auto& student : students) {
              cout << student->Full_Name() << endl;
        }
        cout << endl;
    }
};


// --------------- College Class ---------------
class College
{
private:
public:
      vector<Department*> departments;
      vector<Course*> courses;
      vector<Professor*> professors;
      vector<Student*> students;
      College();

      int Number_Of_Departments(){
            return departments.size();
      }
      int Number_Of_Courses(){
            return courses.size();
      }
      int Number_Of_Professors(){
            return professors.size();
      }
      int Number_Of_Students(){
            return students.size();
      }

      Department* Find_Department(string dept_name){
            for(Department* dept : departments){
                  if(dept->name == dept_name){
                        return dept;
                  }
            }
            return nullptr;
      }
      Course* Find_Course(string course_name){
            for(Course* crs : courses){
                  if(crs->name == course_name){
                        return crs;
                  }
            }
            return nullptr;
      } 
      Professor* Find_Professor(string professor_name){
            for(Professor* prof : professors){
                  if(prof->Full_Name() == professor_name){
                        return prof;
                  }
            }
            return nullptr;
      }
      Student* Find_Student(string student_name){
            for(Student* stud : students){
                  if(stud->Full_Name() == student_name){
                        return stud;
                  }
            }
            return nullptr;
      }
      void Add_Department(Department* dept){
            auto search = find(departments.begin(), departments.end(), dept);
            if(search == departments.end()){
                  departments.push_back(dept);
            }
      }
      void Add_Course(Course* crs){
            auto search = find(courses.begin(), courses.end(),crs);
            if(search == courses.end()){
                  courses.push_back(crs);
            }
      }
      void Add_Professor(Professor* prof){
            auto search = find(professors.begin(), professors.end(), prof);
            if(search == professors.end()){
                  professors.push_back(prof);
            }
      }
      void Add_Student(Student* stnd){
            auto search = find(students.begin(), students.end(), stnd);
            if(search == students.end()){
                  students.push_back(stnd);
            }
      }
      void Report(){
          cout << "College Report: \n\t";
          cout << "Number of Departments: " << Number_Of_Departments() << endl;
          cout << "Number of Courses: " << Number_Of_Courses() << endl;
          cout << "Number of Professors: " << Number_Of_Professors() << endl;
          cout << "Number of Students: " << Number_Of_Students() << endl;
          cout << "Departments: \n\t";
          for (auto& dept : departments) {
              cout << dept->name << endl;
          }
          cout << endl;
          cout << "Courses: \n\t";
          for (auto& course : courses) {
              cout << course->name << endl;
          }
          cout << endl;
          cout << "Professors: \n\t";
          for (auto& professor : professors) {
              cout << professor->Full_Name() << endl;
          }
          cout << endl;
          cout << "Students: \n\t";
          for (auto& student : students) {
              cout << student->Full_Name() << endl;
          }
          cout << endl;
      }
};

// --------------- Main Function ---------------
int main()
{
    Department dp1("CS", "Computer_Science");
    Department dp2("IT", "Information_Technology");

    Professor prof("Omar", "Ayman");
    
    Course c1("Introduction");
    Course c2("OOP");
    Course c3("Algorithms");

    
   c1.Assign_Professor(&prof);
   c2.Assign_Professor(&prof);
   c3.Assign_Professor(&prof);
   
   dp1.Add_Course(&c1);
   dp1.Add_Course(&c2);
   dp2.Add_Course(&c3);

    // Report before unassigning
    cout << "Before unassigning:" << endl;
    for (int i = 0; i < prof.courses.size(); i++) {
        prof.courses[i]->Report();
    }

    c2.Unassign_Professor();
    cout <<"\n\n-----------------------------------------------\n\n";

    
    for (int i = 0; i < prof.courses.size(); i++) {
        //prof.courses[i]->Report();
        
        if (prof.courses[i]->professor == &prof) {
            prof.courses[i]->Report();
        }
    }
    cout << endl << endl;
    
    cout << c1.Professor_Name() << endl;
    cout << c2.Professor_Name() << endl;
    cout << endl << endl;

    Student st1("ali", "omar", "MeetHamal", "010", 10, &dp1);
    Student st2("abdo", "beshry", "belbais", "010", 23, &dp1);
    Student st3("nada", "emad", "MeetHamal", "011", 22, &dp2);

    c1.Enroll(&st1);
    c1.Enroll(&st2);
    c1.Enroll(&st3);

    for(int i = 0; i < c1.students.size(); i++){
      c1.students[i]->Report();
    }
    cout <<"-----------------------------------------------\n";
    c1.Withdrow(&st2);

    for(int i = 0; i < c1.students.size(); i++){
      c1.students[i]->Report();
    }
    cout <<"\n-----------------------------------------------\n";
}


