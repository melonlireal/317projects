#include "AABBTree.h"
#include "insert_box_into_box.h"

#include <iostream>

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  //std::cout << "building AABB tree" << std::endl;
  if (objects.size() == 0) {
    this->left = NULL;
    this->right = NULL;
    return;
  }else if (objects.size() == 1) {
    this->left = objects[0];
    this->right = NULL;
    insert_box_into_box(objects[0]->box, this->box);
    return;
  }else if (objects.size() == 2) {
    this->left = objects[0];
    this->right = objects[1];
    insert_box_into_box(objects[0]->box, this->box);
    insert_box_into_box(objects[1]->box, this->box);
    return;
  }
  for (const auto& obj : objects) {
    insert_box_into_box(obj->box, this->box);
  }
  int which_max = 0; // index on which axis is max axis
  double max_axis =   box.max_corner(0) - box.min_corner(0);

  if (box.max_corner(1) - box.min_corner(1) > max_axis) {
    which_max = 1;
    max_axis = box.max_corner(1) - box.min_corner(1);
  }
  if (box.max_corner(2) - box.min_corner(2) > max_axis) {
    which_max = 2;
    max_axis = box.max_corner(2) - box.min_corner(2);
  }
  double midpoint = box.min_corner(which_max) + max_axis / 2.0;

  std::vector<std::shared_ptr<Object>> left_box;
  std::vector<std::shared_ptr<Object>> right_box;

  for (int i = 0; i < objects.size(); i++) {
    if (objects[i]->box.center()[which_max] < midpoint) {
      left_box.push_back(objects[i]);
    } else {
      right_box.push_back(objects[i]);
    }
  }

  //because for some reason left/right can be empty so now I have to manually bring one
  //back so code dont crash
  if (left_box.empty()) {
    left_box.push_back(right_box.back());
    right_box.pop_back();
  } else if (right_box.empty()) {
    right_box.push_back(left_box.back());
    left_box.pop_back();
  }

  this->left = std::make_shared<AABBTree>(left_box, depth + 1);
  this->right = std::make_shared<AABBTree>(right_box, depth + 1);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
}
