//Rodelle Ladia Jr.BOUNDARYSIZE
//CSSE 342, Winter 2013 
//Lab 4

//gets rid of assertions
//#define NDEBUG

#include <cassert>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/foreach.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include "../nbodysimulator.h"
#include "tablelogger.h"

#include "display.h"
#include "test.h"

using std::string;

typedef NBodySimulator::Body Body;
typedef NBodySimulator::BodyList BodyList;



// uses the information from the file to add bodies to the list of bodies
// returns false if there was an error opening the file
bool createBodiesFromFile(BodyList &, std::ifstream &);

//uses string stream to convert a number to a string
template<typename T>
string numberToString(T);

void NBodySimulatorTestSuite::Test() 
{
  Display display(1000,1000);
  
  std::ifstream file(kFileName);
  
  NBodySimulator simulation;

  NBodySimulator::BodyList bodies;

  typedef Display::Point Point;
  std::vector<Display::Point> points;

  // add the bodies to the simulation
  if(!createBodiesFromFile(bodies, file)) { 
    std::cerr << "File was not successfully opened.\n";
  }
  file.close();

  for(int i = 0; i < 50000; ++i) {
    
    if(i % 250 == 0) { // once a second
      points.clear();
      BOOST_FOREACH(Body b, bodies) {
        int x = static_cast<int>(b->getCenter().x());
        int y = static_cast<int>(b->getCenter().y());
        points.push_back(Point(x, y));
      }
      display.Draw(points);
    } 
    simulation.Simulate(&bodies, 0.01);
  }
}

// uses the information from the file to add bodies to the simulation
bool createBodiesFromFile(BodyList &bodies, std::ifstream &file)
{
  if(!file.is_open())
   return false; //file was not able to be read

  do { //read rest of bodies
    int x, y, z, r, vx, vy, vz;

    file >> x >> y >> z >> r >> vx >> vy >> vz;

    if(file.fail())
       break;
    
    NBodySimulator::Body body(new SimulatedBody(
      Vector3(x, y, z), 
      r, 
      Vector3(vx, vy, vz), 
      Vector3(0,0,0),
      r*50));
    bodies.push_back(body);
  } while(file.good());
  
  return true;
}

//uses string stream to convert a number to a string
template<typename T>
string numberToString(T number) 
{
  std::ostringstream ss;
  ss << number;
  return ss.str();
}