#pragma once
#include <vector>
#include<iostream>
#include<Eigen/Eigen>
using namespace std;
using namespace Eigen;

namespace PolygonalLibrary{

struct PolygonalMesh{

    //Cell0D
    int NumberCell0D = 0;
    vector<unsigned int> idCell0D = {};
    vector<Vector2d> CoordinatesCell0Ds;
    map<unsigned int, list<unsigned int>> Cell0DMarkers = {};

    //Cell1D
    int NumberCell1D = 0;
    vector<unsigned int> idCell1D = {};
    vector<Vector2d> VerticesCell1D = {};
    map<unsigned int, list<unsigned int>> Cell1DMarkers = {};

    //Cell2D
    unsigned  int NumberCell2D = 0;
    unsigned  int NumberVertices2D = 0;
    unsigned  int NumberEdges2D = 0;
    vector<unsigned int> idCell2D = {};
    map<unsigned int, list<unsigned int>> Cell2DMarkers = {};
    vector<vector<unsigned int>> VerticesCell2D = {};
    vector<vector<unsigned int>> EdgesCell2D = {};
    double tol = 10* numeric_limits<double>::epsilon();


};
}
