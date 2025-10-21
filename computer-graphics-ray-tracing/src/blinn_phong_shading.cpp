#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d hit_point = ray.origin + t * ray.direction; // the point getting hit
  Eigen::Vector3d rgb = {0,0,0}; // temp rgb

  Eigen::Vector3d Ka = (objects[hit_id]->material ->ka);
  Eigen::Vector3d Kd = (objects[hit_id]->material -> kd);
  Eigen::Vector3d Ks = (objects[hit_id]->material -> ks);
  double phone = objects[hit_id]->material->phong_exponent;

  for (int i = 0; i < lights.size(); i++) {
    Eigen::Vector3d temp_d; // store direction of shadow_ray
    double temp_max_t; // store max t of shadow ray
    Ray shadow_ray;
    lights[i]->direction(hit_point, temp_d, temp_max_t);
    shadow_ray.origin = hit_point + 1e-6 * n;
    shadow_ray.direction = temp_d;

    //never used
    int temp_hit_id;
    Eigen::Vector3d temp_n;
    //never used

    double temp_t;

    if (!first_hit(shadow_ray,1e-6,objects,temp_hit_id,temp_t,temp_n) || temp_t >= temp_max_t) {
      // if didn't hit anything or exceed light distance, dont ignore cuz its not shadow
      //std::cout << "is not shadow" << std::endl;
      Eigen::Vector3d l = shadow_ray.direction.normalized();
      Eigen::Vector3d v = -ray.direction.normalized();
      Eigen::Vector3d h = (l+v)/(l+v).norm();
      Eigen::Vector3d light_i = lights[i]->I;
      rgb +=  ((Ks.array() * light_i.array()) * std::pow(std::max(0.0,n.dot(h)),phone)).matrix();
      rgb += ((Kd.array() * light_i.array()) * std::max(0.0,n.dot(l))).matrix();
    }
  }
  rgb += (0.1*Ka.array()).matrix();
  return rgb;
  ////////////////////////////////////////////////////////////////////////////
}
