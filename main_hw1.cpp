#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <cmath>
#include <memory>
#include <utility>
#include "functions_hw1.h"

// Ben Cutuli
// AERSP 424 HW 1

int main()
{
	//Question 1
	{
		// Define variables 
		double W;
		double W_m;
		int FS_occupants;
		double FS_total_W = 0.0;
		double FS_mom_arm;
		int RS_occupants;
		double RS_total_W = 0.0;
		double RS_mom_arm;
		int gals_fuel;
		double W_fuel;
		double FT_mom_arm;
		double W_bags;
		double bags_mom_arm;

		std::cout << "------ Question 1 ------" << std::endl;
		std::cout << "Airplane Empty Weight (Pounds): ";
		std::cin >> W;
		std::cout << "Airplane Empty Weight Moment (Pounds-Inches): ";
		std::cin >> W_m;
		std::cout << "Number of Front Seat Occupants: ";
		std::cin >> FS_occupants;
		for (int i = 0; i < FS_occupants; i++) // Loops through to get every front seat occupants' weight
		{
			double W_FS_occupants = 0.0;
			std::cout << "Weight of Front Seat Occupant " << (i + 1) << " (Pounds): ";
			std::cin >> W_FS_occupants;

			if (W_FS_occupants <= 0)
			{
				std::cout << "Weight must be greater than 0 pounds. \n";
				return 1;
			}
			FS_total_W += W_FS_occupants;
		}
		std::cout << "Front Seat Moment Arm (Inches): ";
		std::cin >> FS_mom_arm;
		double FS_m = FS_mom_arm * FS_total_W;

		std::cout << "Number of Rear Seat Occupants: ";
		std::cin >> RS_occupants;
		for (int i = 0; i < RS_occupants; i++) // Loops through to get every rear seat occupants' weight
		{
			double W_RS_occupants = 0.0;
			std::cout << "Weight of Rear Seat Occupant " << (i + 1) << " (Pounds): ";
			std::cin >> W_RS_occupants;

			if (W_RS_occupants <= 0)
			{
				std::cout << "Weight must be greater than 0 pounds. \n";
				return 1;
			}
			RS_total_W += W_RS_occupants;
		}
		std::cout << "Rear Seat Moment Arm (Inches): ";
		std::cin >> RS_mom_arm;
		double RS_m = RS_mom_arm * RS_total_W;

		std::cout << "Number of Gallons of Usable Fuel (Gallons): ";
		std::cin >> gals_fuel;
		std::cout << "Usable Fuel Weights Per Gallon (Pounds): ";
		std::cin >> W_fuel;

		double W_fuel_total = 0.0;
		W_fuel_total = gals_fuel * W_fuel;

		std::cout << "Fuel Tank Moment Arm (Inches): ";
		std::cin >> FT_mom_arm;
		double FT_m = FT_mom_arm * W_fuel_total;

		std::cout << "Baggage Weight (Pounds): ";
		std::cin >> W_bags;
		std::cout << "Baggage Moment Arm (Inches): ";
		std::cin >> bags_mom_arm;
		double bags_m = bags_mom_arm * W_bags;

		// Call functions to calculate gross weight and CG location
		double W_gross = gross_weight(W, FS_total_W, RS_total_W, W_fuel_total, W_bags);
		double CG = CG_(W_m, FS_m, RS_m, FT_m, bags_m, W_gross);

		std::cout << "\nAircraft Total Gross Weight = " << W_gross << " Pounds \n";
		std::cout << "Aircraft CG Location = " << CG << " Inches \n";

		// Define weight and CG limits
		double W_max = 2950;
		double CG_forward_lim = 82.1;
		double CG_aft_lim = 84.7;
		double W_fuel_init = W_fuel_total;

		if (W_gross > W_max)
		{
			std::cout << "\nAircraft exceeds maximum allowable weight. \n";
		}
		if (CG < CG_forward_lim || CG > CG_aft_lim)
		{
			std::cout << "\nAircraft is outside of CG limits. \n";
		}

		bool sol = false; // While loop to drain or add fuel to bring aircraft into limits
		while (W_gross >= W_max || (CG < CG_forward_lim || CG > CG_aft_lim)) // Checks for every condition
		{
			if (CG < CG_forward_lim)
			{
				W_fuel_total -= 0.01;
				FT_m = FT_mom_arm * W_fuel_total;
				W_gross = gross_weight(W, FS_total_W, RS_total_W, W_fuel_total, W_bags);
				CG = CG_(W_m, FS_m, RS_m, FT_m, bags_m, W_gross);
				if (W_fuel_total < 0)
				{
					sol = false;
					break;
				}
			}
			if (CG > CG_aft_lim)
			{
				if (W_gross >= W_max)
				{
					sol = false;
					break;
				}
				W_fuel_total += 0.01;
				FT_m = FT_mom_arm * W_fuel_total;
				W_gross = gross_weight(W, FS_total_W, RS_total_W, W_fuel_total, W_bags);
				CG = CG_(W_m, FS_m, RS_m, FT_m, bags_m, W_gross);
			}
		}
		if (W_gross <= W_max && CG >= CG_forward_lim && CG <= CG_aft_lim)
		{
			sol = true;
		}

		// Calculate how much fuel needs drained or added
		double fuel_dump = W_fuel_init - W_fuel_total;
		std::cout << "\n--------------------------------------------------------\n";

		if (fuel_dump > 0)
		{
			std::cout << "\nNeed to drain " << std::fixed << std::setprecision(2) << fuel_dump << " pounds or "
				<< std::fixed << std::setprecision(2) << fuel_dump / W_fuel << " gallons of fuel. \n";
		}
		else
		{
			std::cout << "\nNeed to add " << std::fixed << std::setprecision(2) << (fuel_dump * -1) << " pounds or "
				<< std::fixed << std::setprecision(2) << fuel_dump / W_fuel << " gallons of fuel. \n";
		}
		std::cout << "\nAircraft New Total Gross Weight = " << std::fixed << std::setprecision(2) << W_gross << " Pounds \n";
		std::cout << "Aircraft New CG Location = " << std::fixed << std::setprecision(2) << CG << " Inches \n";
		
		std::cout << "------ End of Question 1 ------" << std::endl;
	}


	// Questions 2 - 5
	{
		std::cout << "\n------ Questions 2 - 5 ------" << std::endl;
		// Instance for Plane class object
		Plane plane("SCE", "PHL");

		// Setting the speed of the airplane
		double speed = 450; // mph
		plane.set_vel(speed);

		// Timestep and number of iterations
		int timestep = 15; // seconds
		int max_iterations = 1500;

		// Perform iterations until deconstructor deletes "Plane" object
		for (int i = 0; i < max_iterations; ++i)
		{
			if (i == 0)
			{
				std::cout << "Time: " << (i) * timestep << " seconds, Position: " << plane.get_pos() << " miles." << std::endl;
				max_iterations = max_iterations - 1;
			}
			plane.operate(timestep);
			std::cout << "Time: " << (i+1) * timestep << " seconds, Position: " << plane.get_pos() << " miles." << std::endl;
		}
	}
	std::cout << "------ End of Questions 2 - 5 ------" << std::endl;


	// Questions 6 - 7
	{
		std::cout << "\n------ Questions 6 and 7 ------" << std::endl;
		// Instance for Plane and Pilot objects
		std::shared_ptr<Plane> planePtr = std::make_shared<Plane>("SCE", "PHL");
		std::shared_ptr<Pilot> pilot1 = std::make_shared<Pilot>("Alpha", planePtr);
		std::shared_ptr<Pilot> pilot2 = std::make_shared<Pilot>("Bravo", planePtr);

		// Set speed of the airplane
		double speed = 450; // mph
		planePtr->set_vel(speed);

		// Set timestep and maximum number of iterations
		int timestep = 15; // seconds
		int max_iterations = 1500;

		// Start simulation
		std::shared_ptr<Pilot> currentPilot = pilot1;
		std::shared_ptr<Pilot> currentCoPilot = pilot2;

		std::cout << "Plane Created at " << planePtr.get() << std::endl;

		// Print initial pilot information
		std::cout << "Pilot " << currentPilot->get_name() << " with certificate number " << currentPilot.get() << " is in control of a plane: " << currentPilot->myPlane.get() << std::endl;
		std::cout << "Pilot " << currentCoPilot->get_name() << " with certificate number " << currentCoPilot.get() << " is in control of a plane: " << "0000000000000000" << std::endl;

		for (int i = 0; i < max_iterations; ++i)
		{
			// Take off, fly, and land
			currentPilot->myPlane->operate(timestep);

			if (currentPilot->myPlane->get_at_SCE())
			{
				std::cout << "\nThe plane " << currentPilot->myPlane.get() << " is at SCE" << std::endl;
				// Switch pilot
				if (currentPilot->get_name() == "Alpha")
				{
					currentPilot = pilot2;
					currentCoPilot = pilot1;
				}
				else if (currentPilot->get_name() == "Bravo")
				{
					currentPilot = pilot1;
					currentCoPilot = pilot2;
				}
				std::cout << "Pilot " << currentPilot->get_name() << " with certificate number " << currentPilot.get() << " is in control of a plane: " << currentPilot->myPlane.get() << std::endl;
				std::cout << "Pilot " << currentCoPilot->get_name() << " with certificate number " << currentCoPilot.get() << " is in control of a plane: " << "0000000000000000" << std::endl;
			}
		}
	}
	std::cout << "------ End of Questions 6 - 7 ------" << std::endl;


	// Question 8 - Using an old CPP style pointer
	{
		std::cout << "\n------ Question 8 ------" << std::endl;
		// Instantiate Plane and Pilot objects
		Plane* planePtr_old = new Plane("SCE", "PHL");
		Pilot* pilot1 = new Pilot("Alpha", planePtr_old);
		Pilot* pilot2 = new Pilot("Bravo", planePtr_old);

		// Set speed of the airplane
		double speed = 450; // mph
		planePtr_old->set_vel(speed);

		// Set timestep and maximum number of iterations
		int timestep = 15; // seconds
		int max_iterations = 1500;

		// Start simulation
		Pilot* currentPilot = pilot1;
		Pilot* currentCoPilot = pilot2;

		std::cout << "Plane Created at " << planePtr_old << std::endl;

		// Print initial pilot information
		std::cout << "Pilot " << currentPilot->get_name() << " with certificate number " << currentPilot << " is in control of a plane: " << currentPilot->myPlane_old << std::endl;
		std::cout << "Pilot " << currentCoPilot->get_name() << " with certificate number " << currentCoPilot << " is in control of a plane: " << "0000000000000000" << std::endl;

		for (int i = 0; i < max_iterations; ++i)
		{
			// Take off, fly, and land
			currentPilot->myPlane_old->operate(timestep);

			if (currentPilot->myPlane_old->get_at_SCE())
			{
				std::cout << "\nThe plane " << currentPilot->myPlane_old << " is at SCE" << std::endl;
				// Switch pilot
				if (currentPilot->get_name() == "Alpha")
				{
					currentPilot = pilot2;
					currentCoPilot = pilot1;
				}
				else if (currentPilot->get_name() == "Bravo")
				{
					currentPilot = pilot1;
					currentCoPilot = pilot2;
				}
				std::cout << "Pilot " << currentPilot->get_name() << " with certificate number " << currentPilot << " is in control of a plane: " << currentPilot->myPlane_old << std::endl;
				std::cout << "Pilot " << currentCoPilot->get_name() << " with certificate number " << currentCoPilot << " is in control of a plane: " << "0000000000000000" << std::endl;
			}
		}
		// Destroy pilot and plane objects
		delete pilot1;
		delete pilot2;
		delete planePtr_old;
		std::cout << "------ End of Question 8 ------" << std::endl;
	}

	return 0;
}