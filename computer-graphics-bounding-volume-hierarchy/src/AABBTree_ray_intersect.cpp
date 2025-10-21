#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
    ////////////////////////////////////////////////////////////////////////////
    // Replace with your code here:
    double temp_t;
    double temp_t2;
    std::shared_ptr<Object> temp_desc;
    std::shared_ptr<Object> temp_desc2;
    if (!ray_intersect_box(ray, box, min_t, max_t)) {
      return false;
    }
    // ray MUST intersects with current box
    if (num_leaves == 0) { // if nothing
      return false;
    }else if (num_leaves == 1) { // leaf reached
      if (left->ray_intersect(ray, min_t, max_t, t, descendant)) {
        if (!descendant) {
          descendant = left;
        }
        return true;
      }
      return false;
    }

    if (ray_intersect_box(ray, this->left->box, min_t, max_t) &&\
      !ray_intersect_box(ray, this->right->box, min_t, max_t)) { // if only left hit
        if (this->left->ray_intersect(ray, min_t, max_t, temp_t, temp_desc)) {  // ADDED: Check if actually hit object
          t = temp_t;
          if (temp_desc) {
            descendant = temp_desc;
          } else {
            descendant = left;
          }
          return true;
        }
        return false;
    }else if (!ray_intersect_box(ray, this->left->box, min_t, max_t) &&\
      ray_intersect_box(ray, this->right->box, min_t, max_t)) { // if only right hit
        if (this->right->ray_intersect(ray, min_t, max_t, temp_t2, temp_desc2)) {  // ADDED: Check if actually hit object
          t = temp_t2;
          if (temp_desc2) {
            descendant = temp_desc2;
          } else {
            descendant = right;
          }
          return true;
        }
        return false;
    }else if (ray_intersect_box(ray, this->left->box, min_t, max_t) &&\
      ray_intersect_box(ray, this->right->box, min_t, max_t)) { // if both hit
        bool left_hit = this->left->ray_intersect(ray, min_t, max_t, temp_t, temp_desc);
        bool right_hit = this->right->ray_intersect(ray, min_t, max_t, temp_t2, temp_desc2);
      if (left_hit && right_hit) {
        if (temp_t < temp_t2) {
          t = temp_t;
          if (temp_desc) {
            descendant = temp_desc;
          } else {
            descendant = left;
          }
        } else {
          t = temp_t2;
          if (temp_desc2) {
            descendant = temp_desc2;
          } else {
            descendant = right;
          }
        }
        return true;
      } else if (left_hit) {
        t = temp_t;
        if (temp_desc) {
          descendant = temp_desc;
        } else {
          descendant = left;
        }
        return true;
      } else if (right_hit) {
        t = temp_t2;
        if (temp_desc2) {
          descendant = temp_desc2;
        } else {
          descendant = right;
        }
        return true;
      }
    }
    return false;
  ////////////////////////////////////////////////////////////////////////////
}