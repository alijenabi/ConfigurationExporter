//
//  VTKFile_examples.cpp
//  Relation-Based Simulator (RBS)
//
//  Created by Ali Jenabidehkordi on 12.07.2020.
//  Copyright © 2020 Ali Jenabidehkordi. All rights reserved.
//

//#include "exporting/VTKFile.h"
//#include "exporting/CSVFileSeries.h"
#include "exporting/VTKFile.h"
#include <vector>
#include <time.h>
#include <iostream>

using namespace exporting;
using namespace std;


double random(double dmin, double dmax)
{
    double d = (double)rand() / RAND_MAX;
    return dmin + d * (dmax - dmin);
}

using Point = VTKFile::Point;
Point randomPoint(double boxDim){
    return {
        random(-boxDim, boxDim),
        random(-boxDim, boxDim),
        random(-boxDim, boxDim)
    };
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

/**
 * @brief Presents the examples on how to work with exporting::VTKFile and VTKFielSeries.
 * @note Examples are suitable for clang compiler. Running them suing other compilers may require modification.
 * @note Examples are suitable for mac file-system. Running them on other operating systems may require modification.
 * @return EXIT_SUCCESS if all examples are build successfuly, EXIT_FAILURE otherwise.
 */
int main() {

    const string home = "<yourComputeName>";
    const double wating = 30; // seconds
    const string desktopPath = " /Users/" + home + "/Desktop/";
    const int numberOfPoints = 1000000;
    const double simulationBoxDimention = 10;

    cout << "Creating a point array continaing " << to_string(numberOfPoints)
         << " points, in a box centerd at the center of global coordinate system and dimension of "
         << to_string(simulationBoxDimention) << "m." << endl;
    std::srand(std::time(nullptr)); // Use current time as seed for random generator
    vector<VTKFile::Point> points;
    points.reserve(numberOfPoints);
    for(int pNum = 0; pNum < numberOfPoints; pNum++) {
        points.push_back(randomPoint(simulationBoxDimention));
    }

    auto vtkFile = VTKFile(desktopPath , "SingeFileTest", "vtk");
    cout << "Creating a file \"" << vtkFile.fullName(false)
         << "\" on \"" << vtkFile.directory() << "\" path." << endl;

    // ==============< exporting single cell types meny times >==============
    // -------------------------------------------------------------<< vertex

    auto startingTime = clock();
    cout << "Exporting " << to_string(numberOfPoints) << " VTKCell::Vertex to the file.";
    for(int cell = 0; cell < numberOfPoints; cell++)
        vtkFile.appendCell(VTKCell::Vertex, {points[cell]});
    cout << " Done in " << timeIntervalSince(startingTime) << " seconds." << endl;
    startingTime = clock();
    vtkFile.assemble();
    cout << "Assembled the VTK file in " << timeIntervalSince(startingTime) << " seconds." << endl;
    wait(wating);
    startingTime = clock();
    vtkFile.cleanContent();
    cout << "Content cleared in " << timeIntervalSince(startingTime) << " seconds." << endl << endl;

    // ---------------------------------------------------------<< PolyVertex
    startingTime = clock();
    cout << "Exporting 1 VTKCell::PolyVertex with " << to_string(numberOfPoints) << " points to the file.";
    vtkFile.appendCell(VTKCell::PolyVertex, points);
    cout << " Done in " << timeIntervalSince(startingTime) << " seconds." << endl;
    startingTime = clock();
    vtkFile.assemble();
    cout << "Assembled the VTK file in " << timeIntervalSince(startingTime) << " seconds." << endl;
    wait(wating);
    startingTime = clock();
    vtkFile.cleanContent();
    cout << "Content cleared in " << timeIntervalSince(startingTime) << " seconds." << endl << endl;

    // ---------------------------------------------------------------<< line
    startingTime = clock();
    cout << "Exporting " << to_string(numberOfPoints / 2) << " VTKCell::Line with " << to_string(numberOfPoints) << " points to the file.";
    for(int cell = 0; cell < numberOfPoints - 1; cell+=2)
        vtkFile.appendCell(VTKCell::Line, {points[cell], points[cell +1]});
    cout << " Done in " << timeIntervalSince(startingTime) << " seconds." << endl;
    startingTime = clock();
    vtkFile.assemble();
    cout << "Assembled the VTK file in " << timeIntervalSince(startingTime) << " seconds." << endl;
    wait(wating);
    startingTime = clock();
    vtkFile.cleanContent();
    cout << "Content cleared in " << timeIntervalSince(startingTime) << " seconds." << endl << endl;

    // -----------------------------------------------------------<< polyline
    startingTime = clock();
    cout << "Exporting 1 VTKCell::PolyLine with " << to_string(numberOfPoints) << " points to the file.";
    vtkFile.appendCell(VTKCell::PolyLine, points);
    cout << " Done in " << timeIntervalSince(startingTime) << " seconds." << endl;
    startingTime = clock();
    vtkFile.assemble();
    cout << "Assembled the VTK file in " << timeIntervalSince(startingTime) << " seconds." << endl;
    wait(wating);
    startingTime = clock();
    vtkFile.cleanContent();
    cout << "Content cleared in " << timeIntervalSince(startingTime) << " seconds." << endl << endl;

    // -----------------------------------------------------------<< triangle
    startingTime = clock();
    cout << "Exporting " << to_string(numberOfPoints / 3) << " VTKCell::Triangle with " << to_string(numberOfPoints) << " points to the file.";
    for(int cell = 0; cell < numberOfPoints - 3; cell += 3)
        vtkFile.appendCell(VTKCell::Triangle, {points[cell], points[cell + 1], points[cell + 2]});
    cout << " Done in " << timeIntervalSince(startingTime) << " seconds." << endl;
    startingTime = clock();
    vtkFile.assemble();
    cout << "Assembled the VTK file in " << timeIntervalSince(startingTime) << " seconds." << endl;
    wait(wating);
    startingTime = clock();
    vtkFile.cleanContent();
    cout << "Content cleared in " << timeIntervalSince(startingTime) << " seconds." << endl << endl;

    // -----------------------------------------------------<< triangle strip
    startingTime = clock();
    cout << "Exporting 1 VTKCell::TriangleStrip with " << to_string(numberOfPoints) << " points to the file.";
    vtkFile.appendCell(VTKCell::TriangleStrip, points);
    cout << " Done in " << timeIntervalSince(startingTime) << " seconds." << endl;
    startingTime = clock();
    vtkFile.assemble();
    cout << "Assembled the VTK file in " << timeIntervalSince(startingTime) << " seconds." << endl;
    wait(wating);
    startingTime = clock();
    vtkFile.cleanContent();
    cout << "Content cleared in " << timeIntervalSince(startingTime) << " seconds." << endl << endl;

    // ------------------------------------------------------------<< polygon
    startingTime = clock();
    cout << "Exporting 1 VTKCell::Polygon with " << to_string(numberOfPoints) << " points to the file.";
    vtkFile.appendCell(VTKCell::Polygon, points);
    cout << " Done in " << timeIntervalSince(startingTime) << " seconds." << endl;
    startingTime = clock();
    vtkFile.assemble();
    cout << "Assembled the VTK file in " << timeIntervalSince(startingTime) << " seconds." << endl;
    wait(wating);
    startingTime = clock();
    vtkFile.cleanContent();
    cout << "Content cleared in " << timeIntervalSince(startingTime) << " seconds." << endl << endl;

    // ---------------------------------------------------------------<< quad
    startingTime = clock();
    cout << "Exporting " << to_string(numberOfPoints / 4) << " VTKCell::Quad with " << to_string(numberOfPoints) << " points to the file.";
    for(int cell = 0; cell < numberOfPoints - 3; cell += 4)
        vtkFile.appendCell(VTKCell::Quad, {points[cell], points[cell + 1], points[cell + 2], points[cell + 3]});
    cout << " Done in " << timeIntervalSince(startingTime) << " seconds." << endl;
    startingTime = clock();
    vtkFile.assemble();
    cout << "Assembled the VTK file in " << timeIntervalSince(startingTime) << " seconds." << endl;
    wait(wating);
    startingTime = clock();
    vtkFile.cleanContent();
    cout << "Content cleared in " << timeIntervalSince(startingTime) << " seconds." << endl << endl;

    // --------------------------------------------------------------<< tetra
    startingTime = clock();
    cout << "Exporting " << to_string(numberOfPoints / 4) << " VTKCell::Tetra with " << to_string(numberOfPoints) << " points to the file.";
    for(int cell = 0; cell < numberOfPoints - 3; cell += 4)
        vtkFile.appendCell(VTKCell::Tetra, {points[cell], points[cell + 1], points[cell + 2], points[cell + 3]});
    cout << " Done in " << timeIntervalSince(startingTime) << " seconds." << endl;
    startingTime = clock();
    vtkFile.assemble();
    cout << "Assembled the VTK file in " << timeIntervalSince(startingTime) << " seconds." << endl;
    wait(wating);
    startingTime = clock();
    vtkFile.cleanContent();
    cout << "Content cleared in " << timeIntervalSince(startingTime) << " seconds." << endl << endl;

    // ---------------------------------------------------------<< hexahedron
    startingTime = clock();
    cout << "Exporting " << to_string(numberOfPoints / 8) << " VTKCell::Hexahedron with " << to_string(numberOfPoints) << " points to the file.";
    for(int cell = 0; cell < numberOfPoints - 7; cell += 8)
        vtkFile.appendCell(VTKCell::Hexahedron, {points[cell], points[cell + 1], points[cell + 2], points[cell + 3],
                                                 points[cell + 4], points[cell + 5], points[cell + 6], points[cell + 7]});
    cout << " Done in " << timeIntervalSince(startingTime) << " seconds." << endl;
    startingTime = clock();
    vtkFile.assemble();
    cout << "Assembled the VTK file in " << timeIntervalSince(startingTime) << " seconds." << endl;
    wait(wating);
    startingTime = clock();
    vtkFile.cleanContent();
    cout << "Content cleared in " << timeIntervalSince(startingTime) << " seconds." << endl << endl;

    // --------------------------------------------------------------<< Wedge
    startingTime = clock();
    cout << "Exporting " << to_string(numberOfPoints / 6) << " VTKCell::Wedge with " << to_string(numberOfPoints) << " points to the file.";
    for(int cell = 0; cell < numberOfPoints - 5; cell += 6)
        vtkFile.appendCell(VTKCell::Wedge, {points[cell], points[cell + 1],
                                            points[cell + 2], points[cell + 3],
                                            points[cell + 4], points[cell + 5]});
    cout << " Done in " << timeIntervalSince(startingTime) << " seconds." << endl;
    startingTime = clock();
    vtkFile.assemble();
    cout << "Assembled the VTK file in " << timeIntervalSince(startingTime) << " seconds." << endl;
    wait(wating);
    startingTime = clock();
    vtkFile.cleanContent();
    cout << "Content cleared in " << timeIntervalSince(startingTime) << " seconds." << endl << endl;

    // ------------------------------------------------------------<< pyramid
    startingTime = clock();
    cout << "Exporting " << to_string(numberOfPoints / 8) << " VTKCell::Pyramid with " << to_string(numberOfPoints) << " points to the file.";
    for(int cell = 0; cell < numberOfPoints - 4; cell += 5)
        vtkFile.appendCell(VTKCell::Pyramid, {points[cell], points[cell + 1],
                                              points[cell + 2], points[cell + 3],
                                              points[cell + 4]});
    cout << " Done in " << timeIntervalSince(startingTime) << " seconds." << endl;
    startingTime = clock();
    vtkFile.assemble();
    cout << "Assembled the VTK file in " << timeIntervalSince(startingTime) << " seconds." << endl;
    wait(wating);
    startingTime = clock();
    vtkFile.remove();
    cout << "Removed the file in " << timeIntervalSince(startingTime) << " seconds." << endl << endl;

    return EXIT_SUCCESS;
}
