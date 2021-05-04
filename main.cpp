//-----------------------------------------------------------------------
// File: WDCA.cpp
// Summary: Calculated weight distribution on Airbus A380-800
// Version: 1.0
// Owner: Emil Willersjö Nyfelt
//-----------------------------------------------------------------------
// Log: 2015-11-18 Created file. /Emil
//-----------------------------------------------------------------------

#include <iostream>
    using std::cout;
    using std::cin;
    using std::endl;
#include <iomanip>
    using std::setprecision;
    using std::fixed;
#include <ctime>
    using std::time;

int main()
{
    srand((unsigned)time(NULL));
    
    cout << "Weight Distribution Calculator (WDC)" << endl << endl;
    cout << "FLIGHT INFORMATION" << endl;
    cout << "Operator:            British Airways" << endl;
    cout << "Equipment:           Airbus A380-800" << endl;
    cout << "Route:               London (LHR) - Singapore (SIN)" << endl;
    cout << "Flight Nr:           BA11" << endl;
    cout << "Duration:            12h 50m" << endl;
    cout << "Distance:            10850 km" << endl << endl;
    
    cout << "PAYLOAD INFORMATION" << endl;
    cout << "Crew:                 22 pers" << endl;
    cout << "Max PAX:             469 pers" << endl;
    cout << "Max cargo:            89.2 t" << endl;
    cout << "Max fuel:            258.8 t" << endl;
    cout << "Max take of weight:  575.0 t" << endl << endl;
    
    double const crew = 22;
    double const dryWeight = 276800;
    double const distance = 10850;
    double const fuelConsumption = 20.6;
    double const fuel = distance * fuelConsumption;
    
    double lgFrontDry = dryWeight * 0.1;
    double lgMiddleLeftDry = dryWeight * 0.2;
    double lgMiddleRightDry = dryWeight * 0.2;
    double lgRearLeftDry = dryWeight * 0.25;
    double lgRearRightDry = dryWeight * 0.25;
    
    double gravityXa = (-lgMiddleLeftDry*6.5 -lgRearLeftDry*3.5 + lgRearRightDry*3.5 + lgMiddleRightDry*6.5)/dryWeight;
    
    double gravityYa = (lgFrontDry*22 + ((lgMiddleLeftDry + lgMiddleRightDry)*2) - ((lgRearLeftDry + lgRearRightDry)*5))/dryWeight;
    
    double pax, cargo = 0;
    cout << "Enter number of passengers: ";
    cin >> pax;
    
    cout << "Enter weight of cargo [kg]: ";
    cin >> cargo;
    
    double payLoadWeight = (crew*100) + (pax*100) + cargo + fuel;
    
    double lgFront = payLoadWeight * 0.1;
    double lgMiddleLeft = payLoadWeight * 0.2;
    double lgMiddleRight = payLoadWeight * 0.2;
    double lgRearLeft = payLoadWeight * 0.25;
    double lgRearRight = payLoadWeight * 0.25;
    
    double randNumF = (double)rand() / RAND_MAX;
    randNumF = -0.04 + randNumF * 0.08;
    
    double randNumM = (double)rand() / RAND_MAX;
    randNumM = -0.04 + randNumM * 0.08;
    
    double randNumR = (double)rand() / RAND_MAX;
    randNumR = -0.04 + randNumR * 0.08;
    
    double lgFrontOld = lgFront;
    lgFront = lgFront + (lgFront * randNumF);
    double lgFrontDiff = lgFront - lgFrontOld;
    lgFront = lgFront + lgFrontDry;
    
    lgMiddleLeft = lgMiddleLeft - (lgMiddleLeft*randNumM) - (lgFrontDiff/4) + lgMiddleLeftDry;
    lgMiddleRight = lgMiddleRight + (lgMiddleRight*randNumM) - (lgFrontDiff/4) + lgMiddleRightDry;
    
    lgRearLeft = lgRearLeft - (lgRearLeft*randNumR) - (lgFrontDiff/4) + lgRearLeftDry;
    lgRearRight = lgRearRight + (lgRearRight*randNumR)- (lgFrontDiff/4) + lgRearRightDry;
    
    double totalWeight = lgFront + lgMiddleLeft + lgMiddleRight + lgRearLeft + lgRearRight;
    
    cout << "\nFuel loaded: " << fuel/1000 << " t" << endl;
    
    cout << "\n\nTOTAL AIRCRAFT WEIGHT DISTRIBUTION" << endl;
    cout << "Front:         " << setprecision(2) << fixed << lgFront/1000 << " t" << endl;
    cout << "Middle Left:  " << setprecision(2) << fixed << lgMiddleLeft/1000 << " t" << endl;
    cout << "Middle Right: " << setprecision(2) << fixed << lgMiddleRight/1000 << " t" << endl;
    cout << "Rear Left:    " << setprecision(2) << fixed << lgRearLeft/1000 << " t" << endl;
    cout << "Rear Right:   " << setprecision(2) << fixed << lgRearRight/1000 << " t" << endl << endl;
    cout << "Total weight: " << setprecision(2) << fixed << totalWeight/1000 << " t" << endl << endl;
    
    if (pax > 469)
    {
        cout << "\nWARNING! TOO MANY PASSENGERS!" << endl;
        cout << "Maximum PAX: 469" << endl << endl;
    }
    
    if (totalWeight >575000)
    {
        cout << "\nWARNING! AIRCRAFT OVERWEIGHT!" << endl;
        cout << "Maximum take of weight: 575.0 t" << endl << endl;
    }
    
    if (cargo > 89200)
    {
        cout << "\nWARNING! TOO MUCH CARGO LOADED!" << endl;
        cout << "Maximum cargo weight: 89.2 t" << endl << endl;
    }
    
    double gravityXb = (-lgMiddleLeft*6.5 -lgRearLeft*3.5 + lgRearRight*3.5 + lgMiddleRight*6.5)/totalWeight;
    
    double gravityYb = (lgFront*22 + ((lgMiddleLeft + lgMiddleRight)*2) - ((lgRearLeft + lgRearRight)*5))/totalWeight;
    
    double gravityShiftX = gravityXa - gravityXb;
    double gravityShiftY = gravityYa - gravityYb;
    
    cout << "\nSHIFTED CENTRE OF GRAVITY AFTER LOADING" << endl;
    cout << "X-direction: " << setprecision(2) << fixed << gravityShiftX << " m";
    if (gravityShiftX < 0.005 && gravityShiftX > -0.005)
        cout << " (centered)";
    else if (gravityShiftX < 0)
        cout << " (left)";
    else if (gravityShiftX > 0)
        cout << " (right)";
    
    cout << "\nY-direction: " << setprecision(2) << fixed << gravityShiftY << " m";
    if (gravityShiftY < 0.005 && gravityShiftY > -0.005)
        cout << " (centered)" << endl << endl;;
    if (gravityShiftY < 0)
        cout << " (rear)" << endl << endl;
    else if (gravityShiftY > 0)
        cout << " (front)" << endl << endl;
    
    return 0;
}