//
//  SingleFile.h
//  Relation-Based Simulator (RBS)
//
//  Created by Ali Jenabidehkordi on 28.06.2020.
//  Copyright © 2020 Ali Jenabidehkordi. All rights reserved.
//

#ifndef SINGLEFILE_H
#define SINGLEFILE_H

#include "BaseFile.h"

/**
 * The file_system namespace provides the means to handle files on the operating system file system.
 */
namespace exporting::file_system {

/**
 * @brief The SingleFile class provides the mean to handel a single file on the operating system file system.
 * @note This is a format free file, meaning there is no mean to write or append to the file.
 * @note The class is not default constructable.
 * @note The class is not copiable or moveable.
 */
class SingleFile: public BaseFile
{
public:

    static constexpr auto seperator = std::filesystem::path::preferred_separator;

    /**
     * @brief The constructor.
     * @param name The name of the file (the path to the file included).
     * @param extension The extention of the file without the dot(.).
     */
    explicit SingleFile(const std::string &name,
                        const std::string &extension);

    /**
     * @brief The constructor.
     * @param path The directory path of the file.
     * @param name The name of the file.
     * @param extension The extention of the file without the dot(.).
     */
    explicit SingleFile(const std::string &path,
                        const std::string &name,
                        const std::string &extension);

    /**
     * @brief The constructor.
     */
     ~SingleFile();

    /**
     * @brief Gives true if the file is open, false otherwise.
     */
    bool isOpen() const;

    /**
     * @brief Closes the file and removes the pointer to it.
     */
    void close();

    /**
     * @brief Opens the file and creates a pointer to it.
     * @note The file will be created if it is not exists.
     * @param override If true, it will override the file incase it exsists, and appends if false.
     */
    void open(const bool override);

    /**
     * @brief Removes the content of the file.
     * @note The fill will be closed afterward.
     * @return True if successful, false otherwise.
     */
    bool cleanContent() noexcept;

    /**
     * @brief Removes the file without move it to bin/trash directory.
     * @return True if successful, false otherwise.
     */
    bool remove();

    /**
     * @brief Flushes the file but keeps it open!
     * @return True if successful, false otherwise.
     */
    bool save();

protected:

    using file_ptr = FILE *;

    const file_ptr & filePtr() const;

private:

   file_ptr p_file;     // The file pointer.

};

} // namespace file_system

#endif // SINGLEFILE_H
