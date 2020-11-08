//
//  FileRegistar.h
//  Relation-Based Simulator (RBS)
//
//  Created by Ali Jenabidehkordi on 07.11.2020.
//  Copyright © 2020 Ali Jenabidehkordi. All rights reserved.
//

#include "FileRegistar.h"

namespace exporting::file_system {

FileRegistar &FileRegistar::current() {
    static FileRegistar singleRegistar;
    return singleRegistar;
}

FileRegistar::Size FileRegistar::canOpen() const {
    return maxAllowed() - p_files.size();
}

std::FILE *FileRegistar::open(const char *filename, const char *mode){
    while(!canOpen()){ /* Wait untill there is a place available. */ }
    const auto ptr = std::fopen(filename, mode);
    p_files.insert(ptr);
    return ptr;
}

bool FileRegistar::close(std::FILE *stream){
    if (std::fclose(stream) == 0) {
        p_files.erase(stream);
        return true;
    }
    return false;
}

FileRegistar::FileRegistar()
    : p_files{}
{}

FileRegistar::FileRegistar(const FileRegistar &other) = default;
FileRegistar& FileRegistar::operator =(FileRegistar&) = default;

constexpr FileRegistar::Size FileRegistar::maxAllowed() const {
    return FOPEN_MAX;
}

} // namespace exporting::file_system
