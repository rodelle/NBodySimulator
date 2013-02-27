#ifndef LADIA_CSS342_COLLISION_H
#define LADIA_CSS342_COLLISION_H

#include <vector>
#include "movingsphere.h"
#include "polynomial.h"

//Namespace holding common functions useful for collsion detection
//currently limited to collisions between spheres
namespace COLLISION {
  //return: true if the two spheres are overlapping or touching
  bool isOverlapping(const Sphere&, const Sphere&);

  //return: the distance between two spheres using the distance formula
  //  d = sqrt( (xi2 - xi1)^2 )
  double distance(const Vector3&, const Vector3&);

 
  // Returns a vector containing the times at which two moving spheres will
  // collide. This function solves the quadratic equation created by using the
  // distance formula to detect collisions. 
  // The size of the returned vector will represent how many times the spheres
  // collide with each other. 
  // A size of 0 mean the spheres will never collide. A size of 1 means the 
  // spheres will glance each other. A size of 2 means the glance each other 
  // twice as they move through each other.
  std::vector<double> calculateCollisionTimes(
    const MovingSphere&, const MovingSphere&); 
}

#endif