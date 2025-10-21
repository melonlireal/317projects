#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  if (num_recursive_calls >= 5) {
    return false;
  }
  rgb = Eigen::Vector3d(0, 0, 0);
  int hit_id;
  double  t;
  Eigen::Vector3d  n;
  if (first_hit(ray, min_t, objects,hit_id, t, n)) { // if it hits sth
    Eigen::Vector3d Km = objects[hit_id]->material->km;
    rgb += blinn_phong_shading(ray,hit_id,t,n,objects,lights);
    Ray mirror_ray;
    mirror_ray.origin = ray.origin + t * ray.direction + 1e-6 * n; //prevent commom shading
    mirror_ray.direction = reflect(ray.direction, n);
    Eigen::Vector3d temp_rgb;
    if (raycolor(mirror_ray, 1e-6, objects, lights, num_recursive_calls + 1, temp_rgb)) { //if relection also hits sth
      rgb = rgb +  (Km.array() * temp_rgb.array()).matrix();
    }
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
