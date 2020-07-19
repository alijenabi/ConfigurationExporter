//
//  File_examples.cpp
//  Relation-Based Simulator (RBS)
//
//  Created by Ali Jenabidehkordi on 12.07.2020.
//  Copyright © 2020 Ali Jenabidehkordi. All rights reserved.
//

#include "exporting/VTK.h"
#include <cmath>
#include <vector>
#include <time.h>
#include <iostream>

using namespace exporting::vtk;
using namespace std;

double random(double dmin, double dmax)
{
    double d = (double)rand() / RAND_MAX;
    return dmin + d * (dmax - dmin);
}

Point randomPoint(double boxDim){
    return {
        random(-boxDim, boxDim),
        random(-boxDim, boxDim),
        random(-boxDim, boxDim)
    };
}

double distanceToCSCenter(const Point & point) {
    return sqrt(pow(point[0], 2) + pow(point[1], 2) + pow(point[2], 2));
}

using Second = double;
Second timeIntervalSince(const clock_t start) {
    return Second(clock() - start) / CLOCKS_PER_SEC;
}

void wait(const Second seconds) {
    cout << "Wait for " << seconds << " seconds." << endl;
    const auto startingTime = clock();
    int privious = 0;
    while ((clock() - startingTime) / CLOCKS_PER_SEC < seconds) {
        const int time_in_seconds = timeIntervalSince(startingTime);
        if (privious != time_in_seconds) {
            privious = time_in_seconds;
            cout << "." << flush;
            if (time_in_seconds % 10 == 0)
                cout << " " << to_string(int(time_in_seconds)) << "s" << endl;
        }
    }
    cout << endl;
}

void next(unsigned long & value) {
    cout << to_string(value) << ") ";
    value += 1;
}

/**
 * @brief Presents the examples on how to work with exporting::File.
 * @note Examples are suitable for clang compiler. Running them suing other compilers may require modification.
 * @note Examples are suitable for mac file-system. Running them on other operating systems may require modification.
 * @return EXIT_SUCCESS if all examples are build successfuly, EXIT_FAILURE otherwise.
 */
int main() {

    using Counter = unsigned long;

    const string home = "<yourComputeName>";
    const string desktopPath = " /Users/" + home + "/Desktop/";

    cout << "\n =======================================================================\n";
    cout << " ===========================< Point Cluster >===========================\n";
    cout << " =======================================================================\n" << endl;

    const Counter numberOfPoints = 1000000;
    Counter step = 1;
    next(step);
    cout << "Creating a cluster of points (continaing " << to_string(numberOfPoints)
         << " points), in a cube centered at the center of the global coordinate system and dimension of "
         << to_string(10) << "m^3." << endl;

    std::srand(std::time(nullptr)); // Use current time as seed for random generator

    vector<Point> points;
    points.reserve(numberOfPoints);
    for(Counter pNum = 0; pNum < numberOfPoints; pNum++)
        points.push_back(randomPoint(5));

    next(step);
    auto pointClusterFile = File(desktopPath , "point-cluster", "vtk");
    pointClusterFile.setDataTitle("An example of creating a point cluster with scalar attributes on the points.");
    cout << "Creating the file \"" << pointClusterFile.fullName(false)
         << "\"\n\t at \"" << pointClusterFile.directory() << "\" path." << endl;

    next(step);
    auto startingTime = clock();
    for(Counter cell = 0; cell < numberOfPoints; cell++)
        pointClusterFile.appendCell(Cell::Vertex, {points[cell]});
    cout << to_string(numberOfPoints) << " Vertexes are appended to the VTK file in "
         << timeIntervalSince(startingTime) << " seconds." << endl;

    next(step);
    startingTime = clock();
    cout << "Computing the distance of the points to the center of the coordinate system ";
    vector<double> distances;
    distances.reserve(numberOfPoints);
    for(Counter pNum = 0; pNum < numberOfPoints; pNum++)
        distances.emplace_back(distanceToCSCenter(points[pNum]));
    cout << " is done in " << timeIntervalSince(startingTime) << " seconds." << endl;

    next(step);
    startingTime = clock();
    cout << "Appending the distance attribute to the VTK file ";
    pointClusterFile["distance_double"].setSource(AttSource::Point);
    pointClusterFile["distance_double"].setAttributeType(AttType::Scalar);
    pointClusterFile["distance_double"].appendAttribute(distances);
    cout << " is done in " << timeIntervalSince(startingTime) << " seconds." << endl;

    next(step);
    startingTime = clock();
    cout << "Converting the distances from double to float ";
    vector<float> fdistances;
    fdistances.reserve(numberOfPoints);
    for(Counter pNum = 0; pNum < numberOfPoints; pNum++)
        fdistances.emplace_back(static_cast<float>(distances[pNum]));
    distances.clear();
    cout << " is done in " << timeIntervalSince(startingTime) << " seconds." << endl;

    next(step);
    startingTime = clock();
    cout << "Appending the float distance attribute to the VTK file ";
    pointClusterFile["distance_float"].setSource(AttSource::Cell);
    pointClusterFile["distance_float"].setAttributeType(AttType::Scalar);
    pointClusterFile["distance_float"].appendAttribute(fdistances);
    cout << " is done in " << timeIntervalSince(startingTime) << " seconds." << endl;

    next(step);
    startingTime = clock();
    cout << "Converting the distances from float to int ";
    vector<int> idistances;
    idistances.reserve(numberOfPoints);
    for(Counter pNum = 0; pNum < numberOfPoints; pNum++)
        idistances.emplace_back(static_cast<int>(fdistances[pNum]));
    fdistances.clear();
    cout << " is done in " << timeIntervalSince(startingTime) << " seconds." << endl;

    next(step);
    startingTime = clock();
    cout << "Appending the float distance attribute to the VTK file ";
    pointClusterFile["distance_int"].setSource(AttSource::Point);
    pointClusterFile["distance_int"].setAttributeType(AttType::Scalar);
    pointClusterFile["distance_int"].appendAttribute(idistances);
    cout << " is done in " << timeIntervalSince(startingTime) << " seconds." << endl;

    next(step);
    startingTime = clock();
    pointClusterFile.assemble();
    cout << "Assembled the VTK file in " << timeIntervalSince(startingTime) << " seconds." << endl;
    cout << endl;

    cout << "\n =======================================================================\n";
    cout << " =============================< All Cells >=============================\n";
    cout << " =======================================================================\n" << endl;

    step = 1;
    next(step);
    startingTime = clock();
    auto vtkSeries = FileSeries(desktopPath, "all_cells", "vtk", 20);
    cout << "Creating series of the files starting at \"" << vtkSeries.fullName(0, false)
         << "\"\n\t at \"" << vtkSeries.directory() << "\" path." << endl;

    points = {
        {0, 0, 0}, // The origin => vertex
        {2, 0, 0},      {2, 2, 0},      {0, 2, 0},   {0, 0, 2},     {2, 0, 2},      {2, 2, 2},          {0, 2, 2}, // => cube vertixes
        {2.1, 0.2, 0},  {2, 2, -0.2},   {0, 2, 0.1}, {0, 0, 1.8},   {2, 0.1, 2.3},  {2.5, 2.5, 2.5},    {-0.3, 2, 2} // => hexahedron vertixes
    };

    startingTime = clock();
    vtkSeries.at(0).appendCell(Cell::Vertex, {points[0]});
    vtkSeries.at(1).appendCell(Cell::PolyVertex, {points[0], points[3], points[9], points[5], points[11], points[12], points[7], points[14]});
    vtkSeries.at(2).appendCell(Cell::Line, {points[0], points[7]});
    vtkSeries.at(3).appendCell(Cell::PolyLine, {points[0], points[3], points[9], points[5], points[11], points[12], points[7], points[14]});
    vtkSeries.at(4).appendCell(Cell::Triangle, {points[0], points[14], points[12]});
    vtkSeries.at(5).appendCell(Cell::TriangleStrip, {points[0], points[14], points[12], points[13], points[3], points[9]});
    vtkSeries.at(6).appendCell(Cell::Polygon, {points[0], points[10], points[7], points[4]});
    vtkSeries.at(7).appendCell(Cell::Pixel, {points[0], points[1], points[3], points[2]});
    vtkSeries.at(8).appendCell(Cell::Quad,  {points[0], points[8], points[9], points[10]});
    vtkSeries.at(9).appendCell(Cell::Tetra, {points[0], points[1], points[3], points[13]});
    vtkSeries.at(10).appendCell(Cell::Voxel, {points[0], points[1], points[3], points[2], points[4], points[5], points[7], points[6]});

    vtkSeries.at(11).appendCell(Cell::Hexahedron, {points[0], points[8], points[9], points[10], points[11], points[12], points[13], points[14]});
    vtkSeries.at(12).appendCell(Cell::Wedge, {points[0], points[1], points[11], points[10], points[9], points[7],});
    vtkSeries.at(13).appendCell(Cell::Pyramid, {points[0], points[1], points[2], points[3], points[13]});
    next(step);
    cout << "Appending all cells to the VTK files in " << timeIntervalSince(startingTime) << " seconds." << endl;

    next(step);
    startingTime = clock();
    for (int itr = 0; itr < 14; itr++)
        vtkSeries.at(itr).assemble(true);
    cout << "Assembled the VTK files in " << timeIntervalSince(startingTime) << " seconds." << endl;
    cout << endl;

    return EXIT_SUCCESS;
}
