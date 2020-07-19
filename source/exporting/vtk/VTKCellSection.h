//
//  VTKCellSection.h
//  Node-Based Simulator (NBS)
//
//  Created by Ali Jenabidehkordi on 11.07.2020.
//  Copyright © 2020 Ali Jenabidehkordi. All rights reserved.
//

#ifndef VTKCELLSECTION_H
#define VTKCELLSECTION_H

#include "VTKCell.h"
#include "VTKSection.h"
#include <vector>

/**
 * The exporting namespace provides the means to handle exporting simulation data to files.
 */
namespace exporting {

/**
 * The VTKCellSection class provides the means to handle exporting cell-point map to the tempvtk file.
 */
class VTKCellSection: public VTKSection
{
public:

    using Cell = VTKCell;
    using CellIndex = unsigned long;
    using CellType = VTKCell::Type;
    using Size = unsigned long;

    /**
     * @brief The constructor.
     * @param name The name of the parent VTK file (the path to the file included).
     */
    explicit VTKCellSection(const std::string &name);

    /**
     * @brief The constructor.
     * @param path The directory path of the file.
     * @param name The name of the parent VTK file.
     */
    explicit VTKCellSection(const std::string &path, const std::string &name);

    /**
     * @brief Gives the number of cells inside the body.
     */
    Size cellCount() const;

    /**
     * @brief Gives the header of the points section.
     */
    virtual std::string header() const override;

    /**
     * @brief Gives the number of points inside the body.
     */
    Size pointCount() const;

    /**
     * @brief Appends a cell to the section having the index map and the type of the cell.
     * @tparam ITRT An iterative type.
     * @param type The type of the cell.
     * @param pointIndexes The indexes of the point creating the cell.
     * @returns The number of cells currently exist on the body.
     * @throws If the number of point indexes not match with the type of the cell.
     */
    template<typename ITRT>
    CellIndex appendCell(const CellType type, const ITRT & pointIndexes) {
        if (pointIndexes.size() < Cell::minPoints(type))
            throw std::range_error("The cell requires more point indexes.");
        if (pointIndexes.size() > Cell::maxPoints(type))
            throw  std::range_error("The cell requires less point indexes.");

        bodyPtr()->appendCell(pointIndexes.size(), false);
        bodyPtr()->appendRow(pointIndexes, false);
        bodyPtr()->nextRow();
        return bodyPtr()->rowIndex();
    }

};

} // namespace exporting

#endif // VTKCELLSECTION_H
