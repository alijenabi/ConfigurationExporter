# Configuration Exporter

![size](https://img.shields.io/github/repo-size/alijenabi/configuration-exporter)
![license](https://img.shields.io/badge/license-MIT-green)

The `Configuration Exporter` allows `computational enginers` to `export simulation's results to VTK files.`.

The provided code is the export package of my Ph.D. work, which eases the exportation of numerical simulations' configurations to VTK files, where ParaView supports it for post-processing.

## Am I in the right place?

If you answer one of the following questions with NO, then this code probably is no help for you.
* Do you have knowledge of numerical simulations?
* Do you use C++17 for your models?
* Are you searching for a way to reduce your situation's exportation cost in a safe way?

## Why Configuration Exporter?

The Configuration Exporter is not the faster nor the most optimized code for exporting configurations to the VTK format. Configuration Exporter is developed to address the following problems:
* In the world of computational engineering, we always search to reduce the cost of computation. However, the secondary costs like exporting the simulations' results often take a large portion of the resources, which are preferable to be dedicated to running the simulation itself. The Configuration Exporter utilizes a series of temporary files and flushes the simulation result into them immediately as they become available. Thus it allocates resources as minimum as possible during run time.
* To provide better post-processing experience, simulators often use a separate post-processing software. The data will then be stored inside a database or a binary file format. This approach, however, demands that the user wait until the simulation is over. The Configuration Exporter provides the means to export the modeling stages (i.e., configurations) parallel to the simulation. Thus the end-user can start post-processing simulation results in parallel with undergoing analyses. This allows the researcher to stop the simulation if the desired result is achieved or simulation is not propagated as assumed.

## Prerequisites
The code uses some of the `C++17` features, thus a compatible compiler is required.

## Installing
No installation required, simply download or fork the code and start using it.

## Using

1. Include the `Configuration Exporter` to your project by forking this repository.
2. Include the `Configuration Exporter` to your simulation core.
    ```C++
    #include "exporting/VTK.h"
    using namespace exporting::vtk;
    ```

3. Create a `VTKFile`:
    ```C++
    auto pointCluster = File(path , "point-cluster", "vtk");
    ```

    or `VTKFileSeries`:
    ```C++
    auto vtkSeries = FileSeries(desktopPath, "all_cells", "vtk", 20);
    ```

4. Append cells and their point-map to the VTK file,
    ```C++
    for(Counter cell = 0; cell < numberOfPoints; cell++)
        pointClusterFile.appendCell(Cell::Vertex, {points[cell]});
    ```

    or any other `vtd::Cell` to the file series,
    ```C++
    vtkSeries.at(11).appendCell(Cell::Hexahedron, {points[0], points[8], points[9], points[10], points[11], points[12], points[13], points[14]});
    ```

5. Create as many attributes as required. Attributes are extra information in the form of scalar, vector, and tensor that can be applied to either point or cell as the source of that attribute. 
    * first set the source (i.e, `AttSource::Point` or `AttSource::Cell`) of the attribute
    ```C++
    pointCluster["distance_double"].setSource(AttSource::Point);
    ```
    * next set the type of the attribute (`AttType::Scalar`, `AttType::Vector`, or `AttType::Tensor`):
    ```C++
    pointCluster["distance_double"].setAttributeType(AttType::Scalar);
    ```

    * Finally, append the attribute values to the file, keep in mind that the order of the attribute data is the same as the point (if `AttSource::Point` is selected), or cells (if `AttSource::Cell` is selected).
    ```C++
    pointCluster["distance_to_origin"].appendAttribute(distances);
    ```

6. Assemble the files.
    ```C++
    pointCluster.assemble(true);
    ```

    ```C++
    vtkSeries.at(11).assemble(true);
    ```

6. Open the files with ParaView and explore them. 

![Point Cluster](/image/point-cluster.png)
![Points' Distance to the Coordinate System origin in double](/image/distance_double.png)
![Points' Distance to the Coordinate System origin in int](/image/distance_int.png)

## Examples
You can find complete code to create the above example (point cluster) and more in the [`'examples'` directory](/examples) of this repository. 
Note that the [Qt Creator](https://www.qt.io/product/development-tools) is used to provide examples because it is a cross-platform IDE, and QMake provides simple syntax. To run the examples,
* first, on your machine, copy the content of the example directory to the source directory,
* next, open the QtCreator, and under the `Welcome` window, click on `Open` or go to `File>Open File or Project...` in the menu bar.
* next, select the `.pro` file, and click the `Open` button,
* next, select the `Desktop <Qt Version> clang` compiler,  
* the `Qt Creator` will configure a new project named `ConfigurationExporter`
* next, click on the triangle on the right side of the project to open it,
* next, navigate to the `Sources/<ExampleFileName>.cpp` and double click on it.
* next, find the following code and edit it so that `desktopPath` contains your divice absolute desktop path, 
    ```C++
    const string home = "<yourComputeName>";
    const string desktopPath = " /Users/" + home + "/Desktop/";
    ```
* Finally, run the examples by hitting `cmd` + `r` on mac and `ctrl` + `r` on windows and Linux.

## Documentation
The code is well documented using [Doxygen](https://www.doxygen.nl/manual/index.html).  

## Contributing

To contribute to `Configuration Exporter`, follow these steps:

1. Fork this repository. 
2. Create a branch: `git checkout -b '<feature/mycoolfeature>'`.
3. Make your changes and commit them: `git commit -m '<your_commit_message>'`
4. Push to the original branch: `git push origin '<feature/mycoolfeature>'`
5. Create the pull request.

Alternatively see the GitHub documentation on [creating a pull request](https://help.github.com/en/github/collaborating-with-issues-and-pull-requests/creating-a-pull-request).

## License
[MIT](http://opensource.org/licenses/MIT)

Copyright (c) 2020-present, Ali Jenabidehkordi