cmake_minimum_required(VERSION 3.0)
#version requirement

add_executable (demo main.cpp)
#executable file named as "demo" compilied from "main.cpp"

include_directories(${PROJECT_SOURCE_DIR}/include)
#include the header directory "../include"

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the executable output path as "../bin"

add_library(lsm9ds1 LSM9DS1.cpp Filter.cpp)
#creat libray "lsm9ds1" based on "LSM9DS1.cpp" and "Filter.cpp"

link_directories(${PROJECT_SOURCE_DIR}/lib)
#add directory "../lib" as the path of libries need to be linked.
#(lem9ds1 is under it)

target_link_libraries(demo lsm9ds1 rt)
#Link library "lsn8ds1" to "demo"

find_package(iir)
target_link_libraries(demo iir::iir)
#find and link library "iir" to "demo"

find_package(Threads REQUIRED)
target_link_libraries(demo Threads::Threads)
#find and link library "threads" (pthread) to "demo"

include_directories(/usr/local/include)
#include the header dircetory "/usr/local/include" 
#(wiringPi and xdo are under it)
link_directories(/usr/lib/arm-linux-gnueabihf /usr/lib/arm-linux-gnueabihf)
#add the library dircetory "/usr/lib/arm-linux-gnueabihf /usr/lib/arm-linux-gnueabihf"
#as the path of libries need to be linked.
#(wiringPi and xdo are under it)

target_link_libraries(demo xdo wiringPi)
#find and link libraries "xdo" and "wiringPi" to "demo"
