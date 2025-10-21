#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
    typedef std::pair<double, std::shared_ptr<Object>> element;
    std::priority_queue<element, std::vector<element>,
                       std::greater<element>> queue;

    queue.push(std::make_pair(point_box_squared_distance(query, root->box), root));
    double temp_sqrd = std::numeric_limits<double>::infinity();
    std::shared_ptr<Object> temp_descendant = NULL;

    while (!queue.empty()) {
        double current_dist = queue.top().first;
        std::shared_ptr<Object> current = queue.top().second;
        queue.pop();

        // If already found something closer than this node's bounding box, skip

        std::shared_ptr<AABBTree> tree = std::dynamic_pointer_cast<AABBTree>(current);
        if (tree != NULL) {
            if (tree->num_leaves == 1) {
                // This is a leaf - compute actual distance to the object
                double leaf_sqrd;
                std::shared_ptr<Object> leaf_desc;
                if (tree->left && tree->left->point_squared_distance(query, min_sqrd, max_sqrd, leaf_sqrd, leaf_desc)) {
                    if (leaf_sqrd < temp_sqrd) {
                        temp_sqrd = leaf_sqrd;
                        temp_descendant = leaf_desc ? leaf_desc : tree->left;
                    }
                }
                // If point_squared_distance fails, continue searching other nodes
                // Don't return false immediately
            } else {
                // Internal node - add children to queue
                if (tree->left) {
                    double left_dist = point_box_squared_distance(query, tree->left->box);
                    if (left_dist < temp_sqrd) {
                        queue.push(std::make_pair(left_dist, tree->left));
                    }
                }
                if (tree->right) {
                    double right_dist = point_box_squared_distance(query, tree->right->box);
                    if (right_dist < temp_sqrd) {
                        queue.push(std::make_pair(right_dist, tree->right));
                    }
                }
            }
        } else {
            // Leaf object (not AABBTree)
            double obj_sqrd;
            std::shared_ptr<Object> obj_desc;
            if (current->point_squared_distance(query, min_sqrd, max_sqrd, obj_sqrd, obj_desc)) {
                if (obj_sqrd < temp_sqrd) {
                    temp_sqrd = obj_sqrd;
                    temp_descendant = obj_desc ? obj_desc : current;
                }
            }
            // If point_squared_distance fails, continue searching other nodes
        }
    }

    if (temp_sqrd < std::numeric_limits<double>::infinity()) {
        sqrd = temp_sqrd;
        descendant = temp_descendant;
        return true;
    }
    return false;
}
  ////////////////////////////////////////////////////////////////////////////
