#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  // Use a list as a queue to store pairs of nodes to check
  std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>> queue;
  std::shared_ptr<Object> nodeA;
  std::shared_ptr<Object> nodeB;
  // Start with the root nodes
  queue.push_back(std::make_pair(rootA, rootB));

  while (!queue.empty()) {
    nodeA = queue.front().first;
    nodeB = queue.front().second;
    queue.pop_front();

    // Check if nodes are valid before proceeding
    if (!nodeA || !nodeB) {
      continue;
    }

    // Check if both nodes are leaves (primitive objects)
    if (!box_box_intersect(nodeA->box, nodeB->box)) {
      continue;
    } // cuz not doing so is too slow and leads stack overflow
    if (std::dynamic_pointer_cast<AABBTree>(nodeA) == nullptr && std::dynamic_pointer_cast<AABBTree>(nodeB) == nullptr) {
      // Both are leaves, add to the result
      leaf_pairs.push_back(std::make_pair(nodeA, nodeB));
    } else if (std::dynamic_pointer_cast<AABBTree>(nodeA) == nullptr) { // nodeA is leaf, nodeB is AABBTree
      std::shared_ptr<AABBTree> treeB = std::dynamic_pointer_cast<AABBTree>(nodeB);
      // Check if children exist before pushing them
      if (treeB->left) queue.push_back(std::make_pair(nodeA, treeB->left));
      if (treeB->right) queue.push_back(std::make_pair(nodeA, treeB->right));
    } else if (std::dynamic_pointer_cast<AABBTree>(nodeB) == nullptr) {// nodeB is leaf, nodeA is AABBTree
      std::shared_ptr<AABBTree> treeA = std::dynamic_pointer_cast<AABBTree>(nodeA);
      // Check if children exist before pushing them
      if (treeA->left) queue.push_back(std::make_pair(treeA->left, nodeB));
      if (treeA->right) queue.push_back(std::make_pair(treeA->right, nodeB));
    } else { // Both are AABBTrees
      std::shared_ptr<AABBTree> treeA = std::dynamic_pointer_cast<AABBTree>(nodeA);
      std::shared_ptr<AABBTree> treeB = std::dynamic_pointer_cast<AABBTree>(nodeB);

      // Check if children exist before pushing them
      if (treeA->left && treeB->left) queue.push_back(std::make_pair(treeA->left, treeB->left));
      if (treeA->left && treeB->right) queue.push_back(std::make_pair(treeA->left, treeB->right));
      if (treeA->right && treeB->left) queue.push_back(std::make_pair(treeA->right, treeB->left));
      if (treeA->right && treeB->right) queue.push_back(std::make_pair(treeA->right, treeB->right));
    }
  }
}
