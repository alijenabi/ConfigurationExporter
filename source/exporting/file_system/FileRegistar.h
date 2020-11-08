//
//  FileRegistar.h
//  Relation-Based Simulator (RBS)
//
//  Created by Ali Jenabidehkordi on 07.11.2020.
//  Copyright © 2020 Ali Jenabidehkordi. All rights reserved.
//

#ifndef FILEREGISTAR_H
#define FILEREGISTAR_H

#include <cstdio>
#include <set>

/**
 * The file_system namespace provides the means to handle files on the operating system file system.
 */
namespace exporting::file_system {

/**
 * @brief The FileRegistar class.
 * @details The file system, due to security reasons, does not allow the software to open files indefinitely.
 *          This class is a singleton that counts the number of opened files and opens a new one if allowed by the operating system.
 */
class FileRegistar
{
public:
    using Size = size_t;
    using FilePtrs = std::set<std::FILE*>;

    /**
     * @brief Provides the current FileRegister.
     */
    static FileRegistar& current();

    /**
     * @brief Whether there is a place left for opening a new file.
     */
    Size canOpen() const;

    /**
     * @brief Opens a file and returns the pointer to it.
     * @param filename The name of the file
     * @param mode The access mode same as std::fopen mode.
     */
    std::FILE* open(const char* filename, const char* mode);

    /**
     * @brief Closes the file streaming.
     * @param stream The file stream to close
     * @return True, if successful, false otherwise.
     */
    bool close(std::FILE* stream);

private:

    /**
     * @brief Constroctor.
     * @note This is private since the file registar is a Singleton.
     */
    FileRegistar();

    /**
     * @brief Copy Constroctor.
     * @note This is private since copying file registar should only be handled here;
     *        otherwise, the file registar will not be a Singleton.
     */
    FileRegistar(const FileRegistar& other);

    /**
     * @brief Assignment Operation.
     * @note This is private since assiging file registar systems should only be handled here;
     *        otherwise, the file registar will not be a Singleton.
     */
    FileRegistar& operator =(FileRegistar&);

    /**
     * @brief Gives the maximum possible open files allowed by the operating system.\
     */
    constexpr Size maxAllowed() const;

    FilePtrs p_files; // The files that are opens with this registar.

};

}

#endif // FILEREGISTAR_H
