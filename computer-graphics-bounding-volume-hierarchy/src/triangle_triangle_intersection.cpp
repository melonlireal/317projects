#include "triangle_triangle_intersection.h"
#include <Eigen/Geometry>
#include <iostream>
bool same_side(
    const Eigen::RowVector3d& p1,
    const Eigen::RowVector3d& p2,
    const Eigen::RowVector3d& a,
    const Eigen::RowVector3d& b,
    const Eigen::RowVector3d& c)
{
    Eigen::Vector3d ba = b - a;
    Eigen::Vector3d ca = c - a;
    Eigen::Vector3d p1a = p1 - a;
    Eigen::Vector3d p2a = p2 - a;

    Eigen::Vector3d normal = ba.cross(ca);

    double dot1 = normal.dot(p1a);
    double dot2 = normal.dot(p2a);

    return (dot1 * dot2) >= 0;
}

bool triangle_triangle_intersection(
    const Eigen::RowVector3d& A0,
    const Eigen::RowVector3d& A1,
    const Eigen::RowVector3d& A2,
    const Eigen::RowVector3d& B0,
    const Eigen::RowVector3d& B1,
    const Eigen::RowVector3d& B2)
{
    ////////////////////////////////////////////////////////////////////////////
    // More complete triangle-triangle intersection test

    // Check if all vertices of B are on same side of A's plane
    Eigen::Vector3d A_edge1 = A1 - A0;
    Eigen::Vector3d A_edge2 = A2 - A0;
    Eigen::Vector3d A_normal = A_edge1.cross(A_edge2);

    double B0_dist = A_normal.dot(B0 - A0);
    double B1_dist = A_normal.dot(B1 - A0);
    double B2_dist = A_normal.dot(B2 - A0);

    if ((B0_dist > 0 && B1_dist > 0 && B2_dist > 0) ||
        (B0_dist < 0 && B1_dist < 0 && B2_dist < 0)) {
        return false;
    }

    //check if all vertices of A are on same side of B's plane
    Eigen::Vector3d B_edge1 = B1 - B0;
    Eigen::Vector3d B_edge2 = B2 - B0;
    Eigen::Vector3d B_normal = B_edge1.cross(B_edge2);

    double A0_dist = B_normal.dot(A0 - B0);
    double A1_dist = B_normal.dot(A1 - B0);
    double A2_dist = B_normal.dot(A2 - B0);

    if ((A0_dist > 0 && A1_dist > 0 && A2_dist > 0) ||
        (A0_dist < 0 && A1_dist < 0 && A2_dist < 0)) {
        return false;
    }

    // Test edges of A against edges of B
    Eigen::Vector3d edgesA[3] = {A_edge1, A2 - A1, A0 - A2};
    Eigen::Vector3d edgesB[3] = {B_edge1, B2 - B1, B0 - B2};

    // Test all combinations of edges
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Eigen::Vector3d axis = edgesA[i].cross(edgesB[j]);
            if (axis.squaredNorm() < 1e-10) continue; // Skip parallel edges
            auto project_triangle = [&axis](const Eigen::RowVector3d& v0,
                const Eigen::RowVector3d& v1, const Eigen::RowVector3d& v2)
                -> std::pair<double, double> {
                double p0 = axis.dot(v0);
                double p1 = axis.dot(v1);
                double p2 = axis.dot(v2);
                return {std::min({p0, p1, p2}), std::max({p0, p1, p2})};
            };

            auto [minA, maxA] = project_triangle(A0, A1, A2);
            auto [minB, maxB] = project_triangle(B0, B1, B2);

            if (maxA < minB || maxB < minA) {
                return false; // Separating axis found
            }
        }
    }
    return true;
    ////////////////////////////////////////////////////////////////////////////
}

