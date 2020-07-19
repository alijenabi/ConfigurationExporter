//
//  TextFile.cpp
//  Relation-Based Simulator (RBS)
//
//  Created by Ali Jenabidehkordi on 16.04.18.
//  Copyright © 2020 Ali Jenabidehkordi. All rights reserved.
//

#include "TextFile.h"

namespace exporting {

using SingleFile = file_system::SingleFile;

TextFile::TextFile(const std::string &name, const std::string &extension)
    : SingleFile(name, extension)
{
}

TextFile::TextFile(const std::string &path, const std::string &name, const std::string &extension)
    : SingleFile(path, name, extension)
{
}

TextFile::CharCount TextFile::append(const char *c_str) {
    if(!isOpen())
        open(false);
    return std::fputs(c_str, filePtr());
}

TextFile::CharCount TextFile::append(const std::string &str)
{
    return append(str.c_str());
}

bool TextFile::appendFileContent(const std::string &filePath) {
    unsigned long addedChars = 0;
    char buffer[1024];
    auto otherFile = fopen(filePath.c_str(), "r");
    if (!isOpen())
        open(false);
    if (otherFile)
        while (std::fgets(buffer, sizeof(buffer), otherFile))
            addedChars += std::fputs(buffer, filePtr());
    return addedChars;
}

bool TextFile::nextLine()
{
    return static_cast<bool>(append("\n"));
}

} // namespace exporting
