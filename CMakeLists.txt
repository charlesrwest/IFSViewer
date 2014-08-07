cmake_minimum_required (VERSION 2.8.3)
PROJECT(IFSOperationViewer)

# The version number.
set (My_VERSION_MAJOR 1)
set (My_VERSION_MINOR 0)
set (CMAKE_CXX_FLAGS "-fpermissive") #Deal with IFS functions that are char* rather than const char*

#set path to library
set(IFS_LIBRARY_DIRECTORY $ENV{DYLD_LIBRARY_PATH})
link_directories(/usr/lib/x86_64-linux-gnu)

#Access QT4 package
FIND_PACKAGE(Qt4 REQUIRED)

#Add the QT modules we are going to use
#QT_USE_QTNETWORK QT_USE_QTOPENGL QT_USE_QTSQL QT_USE_QTXML QT_USE_QTSVG QT_USE_QTTEST QT_USE_QTDBUS QT_USE_QTSCRIPT QT_USE_QTWEBKIT QT_USE_QTXMLPATTERNS QT_USE_PHONON
#SET(QT_USE_QTNETWORK TRUE)

#List all of the sources and all the headers
SET(my_SOURCES main.cpp IFSOperationViewer.cpp utilityFunctions.cpp IFSImageLabel.cpp functionDetails.cpp)
SET(my_HEADERS  IFSOperationViewer.h utilityFunctions.h IFSImageLabel.h functionDetails.h)

#List all of the .ui forms and resources that need to be processed
SET(my_FORMS mainWindow.ui)
#SET(my_RESOURCES democracyResources.qrc)

#Set the headers to be processed by moc
QT4_WRAP_CPP(my_HEADERS_MOC ${my_HEADERS})


#Set the UIs and resources to be processed
QT4_WRAP_UI(my_FORMS_HEADERS ${my_FORMS})
#QT4_ADD_RESOURCES(my_RESOURCES_RCC ${my_RESOURCES})

#include QT headers
INCLUDE(${QT_USE_FILE})

#Add QT definitions
ADD_DEFINITIONS(${QT_DEFINITIONS})

#Add the compilation target
ADD_EXECUTABLE(IFSOperationViewer ${my_SOURCES} ${my_HEADERS_MOC} ${my_FORMS_HEADERS} )#${my_RESOURCES_RCC})



#Add all of the generated files to the include
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

#Add libraries
TARGET_LINK_LIBRARIES(IFSOperationViewer ${QT_LIBRARIES} ${IFS_LIBRARY_DIRECTORY}/libifs.a m ${IFS_LIBRARY_DIRECTORY}/libflip.a ${IFS_LIBRARY_DIRECTORY}/libifs.a)

#add the install targets
#install (TARGETS IFSOperationViewer DESTINATION bin)
#install (FILES ${my_HEADERS} ${my_HEADERS_MOC} ${my_FORMS_HEADERS} ${my_RESOURCES_RCC} DESTINATION include)
#install (FILES ${my_HEADERS} ${my_HEADERS_MOC} ${my_FORMS_HEADERS} DESTINATION include)
#install (FILES "${PROJECT_BINARY_DIR}/votingClient.h" DESTINATION include)

# build a CPack driven installer package (Debian package)

# autogenerate dependency information
#set (CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

#include (InstallRequiredSystemLibraries)
#set (CPACK_RESOURCE_FILE_LICENSE  
#     "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
#set (CPACK_PACKAGE_VERSION_MAJOR "${My_VERSION_MAJOR}")
#set (CPACK_PACKAGE_VERSION_MINOR "${My_VERSION_MINOR}")
#SET(CPACK_GENERATOR "DEB")
#SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Charles West") #required
#include (CPack)
