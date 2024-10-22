cmake_minimum_required(VERSION 3.5)

project(GAINABLE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(test 
main.cpp 
mainwindow.cpp 
BB_DS18B20.cpp 
sondes.cpp 
thread.cpp 
vitesseventilateur.cpp 
gainable.cpp 
relais.cpp 
gpioPin.cpp 
dispcons.cpp 
modifcons.cpp
configini.cpp 
)

target_link_libraries(test Qt5::Widgets 
gpiod 
pthread
)
