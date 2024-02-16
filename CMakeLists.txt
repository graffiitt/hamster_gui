cmake_minimum_required(VERSION  3.0.2)

project(hamster_gui)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTORCC ON)
set(QRCFILE ../../resource/resource.qrc)


add_subdirectory(src/CommunicateWidget)
add_subdirectory(src/ExectutorWidget)
add_subdirectory(src/ICommand)
add_subdirectory(src/IOwidget)
add_subdirectory(src/JSONmodule)
add_subdirectory(src/mainWindow)
add_subdirectory(src/ProgEditorWidget)
add_subdirectory(src/RegisterWidget)
add_subdirectory(src/stateWidget)
add_subdirectory(src/moveEngine)