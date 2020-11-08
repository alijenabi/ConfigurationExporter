//
//  SingleFile.cpp
//  Relation-Based Simulator (RBS)
//
//  Created by Ali Jenabidehkordi on 28.06.2020.
//  Copyright © 2020 Ali Jenabidehkordi. All rights reserved.
//

#include "FileRegistar.h"
#include "SingleFile.h"

namespace exporting::file_system {

SingleFile::SingleFile(const std::string &name, const std::string &extension)
    : BaseFile(name, extension)
    , p_file{nullptr}
{
}

SingleFile::SingleFile(const std::string &path,
                       const std::string &name,
                       const std::string &extension)
    : SingleFile(path + name, extension)
{
}

SingleFile::~SingleFile()
{
    close();
}

bool SingleFile::isOpen() const
{
    return static_cast<bool>(p_file);
}

bool SingleFile::save() {
    if (isOpen()) {
        std::fflush(p_file);
        return true;
    }
    return false;
}

void SingleFile::close()
{
    if(isOpen()) {
        std::fflush(p_file);
        FileRegistar::current().close(p_file);
        p_file = nullptr;
    }
}

void SingleFile::open(const bool override)
{
    const auto option = (override)? "w" : "a";
    p_file = FileRegistar::current().open(fullName(true).c_str(), option);
}

bool SingleFile::cleanContent() noexcept
{
    try {
        close();
        open(true);
        close();
        return true;
    } catch (...) {
    }
    return false;
}

bool SingleFile::remove()
{
    close();
    return BaseFile::remove();
}

const SingleFile::file_ptr &SingleFile::filePtr() const {
    return p_file;
}

} // namespace file_system

