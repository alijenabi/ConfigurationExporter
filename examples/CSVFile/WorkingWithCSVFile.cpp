//
//  CSVFile_examples.cpp
//  Relation-Based Simulator (RBS)
//
//  Created by Ali Jenabidehkordi on 11.07.2020.
//  Copyright © 2020 Ali Jenabidehkordi. All rights reserved.
//

#include "exporting/CSV.h"
#include <vector>
#include <time.h>
#include <iostream>

using namespace exporting::csv;
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
 * @brief Presents the examples on how to work with exporting::CSVFile and exporting::CSVFileSeries.
 * @note Examples are suitable for clang compiler. Running them suing other compilers may require modification.
 * @note Examples are suitable for mac file-system. Running them on other operating systems may require modification.
 * @return EXIT_SUCCESS if all examples are build successfuly, EXIT_FAILURE otherwise.
 */
int main() {
    const string home = "<yourComputeName>"; 
    const double wating = 5; // seconds
    const string desktopPath = " /Users/" + home + "/Desktop/";
    const unsigned long numberOfCells = 10000;

    auto startingTime = clock();

    auto csvFile = File(desktopPath , "SingeFileTest", "csv");
    cout << "Creating a file \"" << csvFile.fullName(false)
         << "\" on \"" << csvFile.directory() << "\" path." << endl;

    std::srand(std::time(nullptr)); // use current time as seed for random generator
    csvFile.open(true);
    if (csvFile.isOpen()) {
        cout << "The file is created in " << timeIntervalSince(startingTime) << " seconds." << endl;

        wait(wating);
        startingTime = clock();
        cout << "Adding a 9 column table contining " << to_string(numberOfCells)
             << " characters to the file in one step." << endl;
        csvFile.maxColumn() = 9;
        for(unsigned long nc = 0; nc < numberOfCells; nc++) {
            csvFile.appendCell(std::string(1,char('a' + std::rand()%(256)/(26*2))));
        }
        cout << "The file content is ready in " << timeIntervalSince(startingTime) << " seconds." << endl;

        wait(wating);
        startingTime = clock();
        csvFile.cleanContent();
        cout << "Removed the content of the file in " << timeIntervalSince(startingTime) << " seconds." << endl;

        wait(wating);
        startingTime = clock();
        cout << "Adding a 5 column table contining " << to_string(numberOfCells)
             << " numbers to the file, saving it after each append." << endl;
        csvFile.open(false);
        csvFile.maxColumn() = 5;
        for(unsigned long nc = 0; nc < numberOfCells; nc++) {
            csvFile.appendCell(double(std::rand()/10000), true);
            csvFile.save();
        }
        cout << "The file content is ready in " << timeIntervalSince(startingTime) << " seconds." << endl;

        wait(wating);
        startingTime = clock();
        cout << "Removing the file." << endl;
        if (csvFile.remove()) {
            cout << "The file is removed successfuly in " << timeIntervalSince(startingTime) << " seconds." << endl;
        } else {
            cout << "The file could not be removed." << endl;
            return EXIT_FAILURE;
        }
    } else {
       cout << "The file could not be created." << endl;
       return EXIT_FAILURE;
    }

    cout << endl << "---------------------------------------------------" << endl;

    startingTime = clock();
    const string documentsPath = "/Users/" + home + "/Documents/test/";
    auto fileSeries = FileSeries(documentsPath , "FileSeriesTest", "csv", 100);
    cout << "Creating a file series \"" << fileSeries.basename()
         << "\" on \"" << fileSeries.directory() << "\" path." << endl;
    cout << "Adding 200 files to the series with size of " << fileSeries.maximumSize() << ".";
    for(int itr = 0; itr < 200; itr++)
        if (fileSeries.next().isOpen())
            cout << fileSeries.fullName(fileSeries.highestIndex() ,true) << endl;

    cout << endl << "The files are created in " << timeIntervalSince(startingTime) << " seconds." << endl;

    if(fileSeries.isCreated(0) && fileSeries.isCreated(99))
        cout << "The files between 0 to 99 are created." << endl;
    if(fileSeries.isCreated(100) || fileSeries.isCreated(199))
        cout << "The files between 100 to 199 are creaed." << endl;
    cout << endl;

    wait(wating);
    startingTime = clock();
    cout << "Currently " << to_string(fileSeries.count()) << " files exists on the \"" << fileSeries.directory() << "\" path." << endl;
    cout << "The files are searched in " << timeIntervalSince(startingTime) << " seconds." << endl;

    wait(wating);
    std::vector<int> rowContents;
    for(int itr = 0; itr < int(numberOfCells); itr++)
        rowContents.emplace_back(itr);

    startingTime = clock();
    cout << "Adding a 9 column table contining " << to_string(numberOfCells)
         << " numbers to each of the files in the series in one step." << endl;
    for(int itr = 0; itr < 100; itr++) {
        fileSeries.at(itr).maxColumn() = 9;
        fileSeries.at(itr).appendRow(rowContents);
    }
    cout << "The files' contents are ready in " << timeIntervalSince(startingTime) << " seconds." << endl;

    wait(wating);
    startingTime = clock();
    for(int itr = 0; itr < 100; itr++)
        fileSeries.at(itr).cleanContent();
    cout << "Cleared the contents of the files in " << timeIntervalSince(startingTime) << " seconds." << endl;

    wait(wating);
    startingTime = clock();
    cout << "Adding a 4 column table contining " << to_string(numberOfCells)
         << " numbers to the file series, saving them after each append." << endl;

    for(int itr = 0; itr < 100; itr++){
        if (!fileSeries.at(itr).isOpen())
            fileSeries.at(itr).open(false);
        fileSeries.at(itr).maxColumn() = 4;
        for(unsigned long nc = 0; nc < numberOfCells; nc++) {
            fileSeries.at(itr).appendCell(itr + rowContents[nc], true);
            fileSeries.at(itr).save();
        }
    }
    cout << "The files' contents is ready in " << timeIntervalSince(startingTime) << " seconds." << endl;
    wait(wating);

    cout << "Removing all the files." << endl;
    startingTime = clock();
    cout << to_string(fileSeries.removeAll(true)) << " files are removed successfully." << endl;
    cout << "The files are removed in " << timeIntervalSince(startingTime) << " seconds." << endl;

    return EXIT_SUCCESS;
}
