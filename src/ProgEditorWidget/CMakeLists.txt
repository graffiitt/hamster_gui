cmake_minimum_required(VERSION 3.0.2)
project(ProgEditorWidget)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

include_directories(${catkin_INCLUDE_DIRS})




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
qt5_add_translation(TSFILE ProgEditorWidget_en_US.ts ProgEditorWidget_ru_RU.ts)
#qt5_create_translation(TSFILE ${CMAKE_SOURCE_DIR} )

message("buliding ${PROJECT_NAME} node: ")

add_library(
    ${PROJECT_NAME} SHARED
    ${CPPFILE}
    ${HFILE}
    ${UIFILE}
    ${QRCFILE}
    ${TSFILE}
     )

target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} Qt5::Widgets JSONmodule ICommand IOWidget)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})


project(run_editor_widget)

add_executable(
    ${PROJECT_NAME}
    main.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE ${catkin_LIBRARIES} Qt5::Widgets ProgEditorWidget)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
