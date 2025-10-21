#include "Sphere.h"

#include "first_hit.h"
#include "Ray.h"
#include <iostream>

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  const Eigen::Vector3d & e = ray.origin;
  const Eigen::Vector3d & d = ray.direction;
  const Eigen::Vector3d & c = center;
  double r = radius;
  double A = d.dot(d);
  double B = 2.0*d.dot((e - c));
  double C = (e-c).dot(e-c) - (r*r);

  double discriminant = B*B - (4.0*A*C);
  if (discriminant < 0) {
    return false;
  }else if (discriminant == 0){ // only one sol
    double temp_t = -B/(2.0*A);
    if (temp_t >= min_t) {
      t = temp_t;
      n = (e + d * t - c)/r;
      return true;
    }
    return false;
  }else if (discriminant > 0) {
    double t1 = (-B + std::sqrt(discriminant))/(2.0*A);
    double t2 = (-B - std::sqrt(discriminant))/(2.0*A);
    if (t1 < min_t && t2 < min_t) {
      return false;
    }else if (t1 < min_t && t2 >= min_t) {
      t = t2;
      //std::cout << "t in circle " << t << std::endl;
      n = (e + d * t - c)/r; // e+ d*t = q , q-p is normal
      return true;
    }else if (t1 >= min_t && t2 < min_t) {
      t = t1;
      //std::cout << "t in circle " << t << std::endl;
      n = (e + d * t - c)/r;  // e+ d*t = q , q-p is normal
      return true;
    } else if (t1 >= min_t && t2 >= min_t) {
      t = std::min(t1, t2);
      //std::cout << "t in circle " << t << std::endl;
      n = (e + d * t - c)/r;  // e+ d*t = q , q-p is normal
      return true;
    }else if (t1 > min_t && t2 > min_t && t2 < t1) {
      t = t1;
      //std::cout << "t in circle " << t << std::endl;
      n = (e + d * t - c)/r;// e+ d*t = q , q-p is normal
      return true;
    }
    return false;
  }
  return false;
  // reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection.html
  ////////////////////////////////////////////////////////////////////////////
}

