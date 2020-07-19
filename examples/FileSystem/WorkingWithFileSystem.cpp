//
//  file_system_examples.cpp
//  Relation-Based Simulator (RBS)
//
//  Created by Ali Jenabidehkordi on 28.06.2020.
//  Copyright © 2020 Ali Jenabidehkordi. All rights reserved.
//
//  @brief Presenting the application and speed of the file_system classes (namely, SingleFile and FileSeries).

#include "exporting/file_system/FileSeries.h"
#include "exporting/file_system/FileSeries.h"
#include <time.h>
#include <iostream>

using namespace exporting::file_system;
using namespace std;

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
 * @brief Presents the examples on how to work with exporting::file_system.
 * @note Examples are suitable for clang compiler. Running them suing other compilers may require modification.
 * @note Examples are suitable for mac file-system. Running them on other operating systems may require modification.
 * @return EXIT_SUCCESS if all examples are build successfuly, EXIT_FAILURE otherwise.
 */
int main()
{
    const string home = "<yourComputeName>";
    const double wating = 10; // seconds
    const string desktopPath = " /Users/" + home + "/Desktop/";

    auto startingTime = clock();
    auto singleFile = SingleFile(desktopPath , "SingeFileTest", "tst");
    cout << "Creating a file \"" << singleFile.fullName(false) << "\" on \"" << singleFile.directory() << "\" path." << endl;
    singleFile.open(true);
    if (singleFile.isOpen()) {
        cout << "The file is created in " << timeIntervalSince(startingTime) << " seconds." << endl;

        wait(wating);

        startingTime = clock();
        cout << "Removing the file." << endl;
        if (singleFile.remove()) {
            cout << "The file is removed successfuly in " << timeIntervalSince(startingTime) << " seconds." << endl;
        } else {
            cout << "The file could not be removed." << endl;
            return EXIT_FAILURE;
        }
    } else {
       cout << "The is file could not be created." << endl;
       return EXIT_FAILURE;
    }

    cout << "---------------------------------------------------" << endl;

    startingTime = clock();
    const string documentsPath = "/Users/" + home + "/Documents/test/";
    auto fileSeries = FileSeries<SingleFile>(documentsPath , "FileSeriesTest", "tst", 100);
    cout << "Creating a file series \"" << fileSeries.basename() << "\" on \"" << fileSeries.directory() << "\" path." << endl;
    cout << "Adding 200 files to the series with size of " << fileSeries.maximumSize() << ".";
    for(int itr = 0; itr < 200; itr++)
       if (fileSeries.next().isOpen())
        cout << fileSeries.fullName(fileSeries.highestIndex() ,true) << endl;
    cout << endl;
    cout << "The files are created in " << timeIntervalSince(startingTime) << " seconds." << endl;


    if(fileSeries.isCreated(0) && fileSeries.isCreated(99))
        cout << "The files between 0 to 99 are created." << endl;
    if(fileSeries.isCreated(100) || fileSeries.isCreated(199))
        cout << "The files between 100 to 199 are creaed." << endl;
    cout << endl;

    wait(wating);

    startingTime = clock();
    cout << "Currently " << to_string(fileSeries.count()) << " files exists on the \"" << fileSeries.directory() << "\" path." << endl;
    cout << "The files are searched in " << timeIntervalSince(startingTime) << " seconds." << endl;

    cout << "Removing the files." << endl;
    startingTime = clock();
    cout << to_string(fileSeries.removeAll(true)) << " files are removed successfully." << endl;
    cout << "The files are removed in " << timeIntervalSince(startingTime) << " seconds." << endl;

    return EXIT_SUCCESS;
}
