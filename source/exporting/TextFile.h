//
//  TextFile.h
//  Relation-Based Simulator (RBS)
//
//  Created by Ali Jenabidehkordi on 16.04.18.
//  Copyright © 2020 Ali Jenabidehkordi. All rights reserved.
//

#ifndef TEXTFILES_H
#define TEXTFILES_H

#include "file_system/SingleFile.h"
#include <iomanip>
#include <sstream>

/**
 * The exporting namespace provides the means to handle exporting simulation data to files.
 */
namespace exporting {

/**
 * @brief The TextFile class provides the means to handle exporting data to a text file.
 * @note The class is not default constructable.
 * @note The class is not copiable or moveable.
 */
class TextFile:public file_system::SingleFile
{
public:

    using CharCount = int;

    /**
     * @brief The constructor.
     * @param name The name of the file (the path to the file included).
     * @param extension The extention of the file without the dot(.).
     */
    explicit TextFile(const std::string &name, const std::string &extension = "txt");

    /**
     * @brief The constructor.
     * @param path The directory path of the file.
     * @param name The name of the file (the path to the file included).
     * @param extension The extention of the file without the dot(.).
     */
    explicit TextFile(const std::string &path,
                       const std::string &name,
                       const std::string &extension);

    /**
     * @brief Appends a c_string to the file.
     * @param c_str The c string.
     * @return The number of characters successfully added to the file.
     */
    CharCount append(const char * c_str);

    /**
    * @brief Append a string to the text file.
    * @param text The string to append
    * @return The number of characters successfully added to the file.
    */
    CharCount append(const std::string & text);

    /**
     * @brief Appends a number to the text file.
     * @tparam N The number type.
     * @param number The number.
     * @param scientific Whether print the number with schientific notation or not.
     * @param precision The number of char after dot(.) to print.
     * @return The number of characters successfully added to the file.
     */
    template<typename N>
    CharCount appendNumber(const N number, bool scientific = false, int precision = -1){
        const auto type = (scientific) ? "e" : "f";
        const unsigned int defaultPrecision = (typeid(N) == typeid(double)) ? 14 : ((typeid (N) == typeid(float)) ? 6: 0);
        const unsigned int finalPercision = (precision < 0) ? defaultPrecision : precision;
        const auto str = "%." + std::to_string(finalPercision) + type;

        if(!isOpen())
            open(false);
        return std::fprintf(filePtr(), str.c_str(), static_cast<double>(number));
    }

    /**
     * @brief Appends a custom object to the text file.
     * @tparam DATA The custom type.
     * @param object The custom object.
     * @return The number of characters successfully added to the file.
     */
    template<typename DATA>
    CharCount appendCustom(const DATA object){
        std::ostringstream osContent{std::ostringstream::ate};
        osContent << object;
        return append(osContent.str().c_str());
    }

    /**
     * @brief Appends the content of the given file.
     * @param filePath The complete path to the other file.
     * @return True, if successful, false otherwise.
     */
    bool appendFileContent(const std::string & filePath);

    /**
     * @brief Gos to a new line.
     * @return True, if successful, false otherwise.
     */
    bool nextLine();

};

} // namespace exporting

#endif // TEXTFILES_H
