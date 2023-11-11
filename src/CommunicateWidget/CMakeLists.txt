cmake_minimum_required(VERSION 3.0.2)
project(CommunicateWidget)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(${catkin_INCLUDE_DIRS})

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS SerialPort)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES qt_template
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  # ${CMAKE_CURRENT__BYNARY_DIR}
)

file(GLOB CPPFILE "*.cpp")

message("Adding ${PROJECT_NAME} CPP files: " )
foreach(source ${CPPFILE})
    message("  - " ${source})
endforeach(source)


file(GLOB HFILE "*.h")

message("Adding ${PROJECT_NAME} H files: " )
foreach(source ${HFILE})
    message("  - " ${source})
endforeach(source)


file(GLOB UIFILE "*.ui")

message("Adding ${PROJECT_NAME} UI files: " )
foreach(source ${UIFILE})
    message("  - " ${source})
endforeach(source)

set(QRCFILE ../../resource/resource.qrc)

message("buliding ${PROJECT_NAME} node: ")

add_library(
    ${PROJECT_NAME} SHARED
    ${CPPFILE}
    ${HFILE}
    ${UIFILE}
    ${QRCFILE}
    )

target_link_libraries(${PROJECT_NAME} PRIVATE ${catkin_LIBRARIES} Qt5::Widgets Qt5::SerialPort stateWidget)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})


project(run_serial_widget)

add_executable(
    ${PROJECT_NAME}
    main.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE ${catkin_LIBRARIES} Qt5::Widgets Qt5::SerialPort  CommunicateWidget)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
