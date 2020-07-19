TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.16

SOURCES += \
    WorkingWithVTKFile.cpp \
    exporting/CSVFile.cpp \
    exporting/TextFile.cpp \
    exporting/VTKFile.cpp \
    exporting/VTKFileSeries.cpp \
    exporting/file_system/BaseFile.cpp \
    exporting/file_system/SingleFile.cpp \
    exporting/vtk/VTKAttributeSection.cpp \
    exporting/vtk/VTKCell.cpp \
    exporting/vtk/VTKCellSection.cpp \
    exporting/vtk/VTKCellTypeSection.cpp \
    exporting/vtk/VTKSection.cpp \
    exporting/vtk/VTKPointSection.cpp

HEADERS += \
    exporting/CSV.h \
    exporting/CSVFile.h \
    exporting/CSVFileSeries.h \
    exporting/TextFile.h \
    exporting/TextFileSeries.h \
    exporting/VTK.h \
    exporting/VTKFile.h \
    exporting/VTKFileSeries.h \
    exporting/file_system/BaseFile.h \
    exporting/file_system/FileSeries.h \
    exporting/file_system/FileSeriesImp.h \
    exporting/file_system/SingleFile.h \
    exporting/vtk/VTKAttributeSection.h \
    exporting/vtk/VTKCell.h \
    exporting/vtk/VTKCellSection.h \
    exporting/vtk/VTKCellTypeSection.h \
    exporting/vtk/VTKSection.h \
    exporting/vtk/VTKPointSection.h
