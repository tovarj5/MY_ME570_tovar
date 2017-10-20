cmake_minimum_required(VERSION 3.4)
project(ShapesGraphics)


FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5Gui)
FIND_PACKAGE( OpenSceneGraph REQUIRED COMPONENTS osgDB osgGA osgUtil osgViewer osgText )

INCLUDE_DIRECTORIES( ${OPENSCENEGRAPH_INCLUDE_DIRS} )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)


SET(MYSOURCE
    osgwidget.h
    osgwidget.cpp
	shape.h
	shape.cpp
	box.h
	box.cpp
	Cone.h
	Cone.cpp
	Ellipsoid.h
	Ellipsoid.cpp
	main.cpp
	mainwindow.h
	mainwindow.cpp
	mainwindow.ui
	shapesoutputwindow.h
	shapesoutputwindow.cpp
	xmlshapesreader.h
	xmlshapesreader.cpp
	xmlshapeswriter.h
	xmlshapeswriter.cpp
    )
add_executable(${PROJECT_NAME}
    ${MYSOURCE}
    )


target_link_libraries(${PROJECT_NAME}
    ${OPENSCENEGRAPH_LIBRARIES}	
    Qt5::Widgets
    Qt5::Gui
)
