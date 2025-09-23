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
  if (num_recursive_calls == 10) {
    return true;
  }
  int hit_id;
  double  t;
  Eigen::Vector3d  n;
  if (first_hit(ray, min_t, objects,hit_id, t, n)) {
    Eigen::Vector3d temp_rgb = rgb + blinn_phong_shading(ray,hit_id,t,n,objects,lights);
    Ray mirror_ray;
    mirror_ray.origin = ray.origin;
    mirror_ray.direction = reflect(ray.direction, n);
    rgb = temp_rgb;
    if (raycolor(mirror_ray, min_t, objects, lights, num_recursive_calls + 1, rgb)) {
      return true;
    }
  }
  if (num_recursive_calls == 0) { // if ray hits nothing with no reflection
    return false;
  }
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
