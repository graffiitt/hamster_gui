cmake_minimum_required(VERSION 3.0.2)
project(rviz_widget_custom)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  rviz
)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${catkin_INCLUDE_DIRS})


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

file(GLOB CPPFILE
"*.cpp")

message("Adding ${PROJECT_NAME} CPP files: " )
foreach(source ${CPPFILE})
    message("  - " ${source})
endforeach(source)


file(GLOB HFILE
"*.h")

message("Adding ${PROJECT_NAME} H files: " )
foreach(source ${HFILE})
    message("  - " ${source})
endforeach(source)


file(GLOB UIFILE
"*.ui")

message("Adding ${PROJECT_NAME} UI files: " )
foreach(source ${UIFILE})
    message("  - " ${source})
endforeach(source)


message("buliding ${PROJECT_NAME} node: ")

add_library(
  ${PROJECT_NAME} SHARED
    ${CPPFILE}
    ${HFILE}
    ${UIFILE}
    )

target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} Qt5::Widgets)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})


project(run_rviz_widget)

add_executable(
    ${PROJECT_NAME}
    main.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE ${catkin_LIBRARIES} Qt5::Widgets rviz_widget_custom)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
