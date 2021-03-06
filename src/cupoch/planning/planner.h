#pragma once
#include "cupoch/geometry/graph.h"
#include <vector>

namespace cupoch {
namespace planning {

typedef std::vector<Eigen::Vector3f> Path;

class PlannerBase {
public:
    PlannerBase() {};
    virtual ~PlannerBase() {};
    virtual PlannerBase &AddObstacle(const std::shared_ptr<geometry::Geometry>& obstacle);
    virtual std::shared_ptr<Path> FindPath(const Eigen::Vector3f& start, const Eigen::Vector3f& goal) const = 0;
public:
    std::vector<std::shared_ptr<geometry::Geometry>> obstacles_;
};

class SimplePlanner : public PlannerBase {
public:
    SimplePlanner(float object_radius = 0.1);
    SimplePlanner(const geometry::Graph& graph, float object_radius = 0.1);
    ~SimplePlanner();

    SimplePlanner &UpdateGraph();
    std::shared_ptr<Path> FindPath(const Eigen::Vector3f& start, const Eigen::Vector3f& goal) const;
public:
    geometry::Graph graph_;

    float object_radius_;
    float max_edge_distance_ = 1.0;
};

}
}