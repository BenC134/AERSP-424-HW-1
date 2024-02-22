#ifndef hw1_functions
#define hw1_functions

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <memory>

// Question 1 functions
double gross_weight(double W_, double FS_total_W_, double RS_total_W_, double W_fuel_total_, double W_bags_);
double CG_(double W_m_, double FS_m_, double RS_m_, double FT_m_, double bags_m_, double W_gross_);


// Questions 2 - 5 "Plane" class
class Plane 
{
private:
    double pos;
    double vel;
    double distance;
    bool at_SCE;
    std::string origin;
    std::string destination;
    std::map<std::pair<std::string, std::string>, int> flights_cont; // Map type container from Question 2
public:
    Plane(const std::string& from, const std::string& to); // Constructor
    ~Plane(); // Destructor
    void operate(double dt);
    double get_pos() const;
    std::string get_origin() const;
    std::string get_destination() const;
    bool get_at_SCE() const;
    double get_vel() const;
    void set_vel(double new_vel);
};


// Questions 6 - 8 "Pilot" class
// Combined old and new CPP style pointers under the same class structure
class Pilot 
{
private:
    std::string name;
public:
    std::shared_ptr<Plane> myPlane; // Modern CPP style pointer
    Pilot(const std::string& pilotName, std::shared_ptr<Plane> planePtr);
    Plane* myPlane_old; // Old CPP style pointer
    Pilot(const std::string & pilotName, Plane * planePtr_old);
    ~Pilot(); // Destructor
    std::string get_name() const;
};

#endif // !hw1_functions
