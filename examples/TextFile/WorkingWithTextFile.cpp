//
//  TextFile_examples.cpp
//  Relation-Based Simulator (RBS)
//
//  Created by Ali Jenabidehkordi on 06.07.2020.
//  Copyright © 2020 Ali Jenabidehkordi. All rights reserved.
//
//  @brief Presenting

#include "exporting/TextFile.h"
#include "exporting/TextFileSeries.h"
#include <time.h>
#include <iostream>

using namespace exporting;
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
    const double wating = 20; // seconds
    const string desktopPath = " /Users/" + home + "/Desktop/";
    const unsigned long numberOfChars = 10000;

    auto startingTime = clock();

    auto textFile = TextFile(desktopPath , "SingeFileTest", "txt");
    cout << "Creating a file \"" << textFile.fullName(false)
         << "\" on \"" << textFile.directory() << "\" path." << endl;

    textFile.open(true);
    if (textFile.isOpen()) {
        cout << "The file is created in " << timeIntervalSince(startingTime) << " seconds." << endl;

        wait(wating);
        startingTime = clock();
        cout << "Appending " << to_string(numberOfChars) << " characters to the file in one step." << endl;
        std::srand(std::time(nullptr)); // use current time as seed for random generator
        for(unsigned long nc = 0; nc < numberOfChars; nc++) {
            textFile.append(std::string(1,char(std::rand()%256)));
        }
        cout << "The file content is ready in " << timeIntervalSince(startingTime) << " seconds." << endl;

        wait(wating);
        startingTime = clock();
        textFile.cleanContent();
        cout << "Removed the content of the file in " << timeIntervalSince(startingTime) << " seconds." << endl;

        wait(wating);
        startingTime = clock();
        cout << "Appending " << to_string(numberOfChars) << " characters to the file, saving it after each append." << endl;
        textFile.open(false);
        for(unsigned long nc = 0; nc < numberOfChars; nc++) {
            textFile.append(std::string(1,char(std::rand()%256)));
            textFile.save();
        }
        cout << "The file content is ready in " << timeIntervalSince(startingTime) << " seconds." << endl;

        wait(wating);
        startingTime = clock();
        cout << "Removing the file." << endl;
        if (textFile.remove()) {
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
    auto fileSeries = TextFileSeries(documentsPath , "FileSeriesTest", "tst", 100);
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
    startingTime = clock();
    cout << "Appending " << to_string(numberOfChars) << " characters to each of the files in the series in one step." << endl;
    for(int itr = 0; itr < 100; itr++)
        for(unsigned long nc = 0; nc < numberOfChars; nc++)
            fileSeries.at(itr).append(std::string(1,char(std::rand()%256)));
    cout << "The files' contents are ready in " << timeIntervalSince(startingTime) << " seconds." << endl;

    wait(wating);
    startingTime = clock();
    for(int itr = 0; itr < 100; itr++)
        fileSeries.at(itr).cleanContent();
    cout << "Cleared the contents of the files in " << timeIntervalSince(startingTime) << " seconds." << endl;

    wait(wating);
    startingTime = clock();
    cout << "Appending " << to_string(numberOfChars) << " characters to the file series, saving them after each append." << endl;
    for(int itr = 0; itr < 100; itr++){
        if (!fileSeries.at(itr).isOpen())
            fileSeries.at(itr).open(false);
        for(unsigned long nc = 0; nc < numberOfChars; nc++) {
            fileSeries.at(itr).append(std::string(1,char(std::rand()%256)));
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
