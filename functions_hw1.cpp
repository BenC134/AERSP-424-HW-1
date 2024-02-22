#include "functions_hw1.h"
#include <iostream>
#include <iomanip>
#include <math.h>
#include <sstream>
#include <string>
#include <map>
#include <cmath>
#include <memory>
#include <utility>

// Gross Weight function
double gross_weight(double W_, double FS_total_W_, double RS_total_W_, double W_fuel_total_, double W_bags_)
{
	return W_ + FS_total_W_ + RS_total_W_ + W_fuel_total_ + W_bags_;
}

// CG calculation function
double CG_(double W_m_, double FS_m_, double RS_m_, double FT_m_, double bags_m_, double W_gross_)
{
	return (W_m_ + FS_m_ + RS_m_ + FT_m_ + bags_m_) / W_gross_;
}

// Plane class constructor definition
Plane::Plane(const std::string& from, const std::string& to) : pos(0), vel(0), distance(0), at_SCE(false), origin(from), destination(to) 
{
    // Container from Question 2 incorporated into the Plane class
    flights_cont[std::make_pair("SCE", "PHL")] = 160;
    flights_cont[std::make_pair("SCE", "ORD")] = 640;
    flights_cont[std::make_pair("SCE", "EWR")] = 220;
    distance = flights_cont[std::make_pair(from, to)];
    std::cout << "Plane Created at " << this << std::endl;
}

// Destructor definition
Plane::~Plane() 
{
    std::cout << "Plane Destroyed" << std::endl;
}

// Operate function according to flowchart
void Plane::operate(double dt) 
{
    if (dt < 0) dt = 0; // Sets time-related variables to 0
    if (pos < distance)
    {
        pos += vel * dt / 3600;
        at_SCE = false;
    }
    else
    {
        if (destination == "SCE")
        {
            at_SCE = true;
            std::swap(origin, destination);
            pos = 0.0;
        }
        else
        {
            std::swap(origin, destination);
            pos = 0.0;
            at_SCE = false;
        }
    }
}

// Get and Set functions
double Plane::get_pos() const
{
    return pos;
}

std::string Plane::get_origin() const 
{
    return origin;
}

std::string Plane::get_destination() const 
{
    return destination;
}

bool Plane::get_at_SCE() const 
{
    return at_SCE;
}

double Plane::get_vel() const
{
    return vel;
}

void Plane::set_vel(double new_vel)
{
    vel = new_vel;
}

// Pilot class constructor definition
Pilot::Pilot(const std::string& pilotName, std::shared_ptr<Plane> planePtr) : name(pilotName), myPlane(planePtr) // Modern style
{
    std::cout << "Pilot " << name << " with certificate number " << this << " is at the gate, ready to board the plane."<< std::endl;
}

Pilot::Pilot(const std::string& pilotName, Plane* planePtr_old) : name(pilotName), myPlane_old(planePtr_old) // Old style
{
    std::cout << "Pilot " << name << " with certificate number " << this << " is at the gate, ready to board the plane." << std::endl;
}

// Destructor definition
Pilot::~Pilot()
{
    std::cout << "Pilot " << name << " is out of the plane." << std::endl;
}

// Name get function
std::string Pilot::get_name() const 
{
    return name;
}


