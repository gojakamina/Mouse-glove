cmake_minimum_required(VERSION 3.0)

add_executable (demo main.cpp)
target_link_libraries(demo lsm9ds1 rt)
target_include_directories(demo PRIVATE ..)

find_package(iir)
target_link_libraries(demo iir::iir)

find_package(Threads REQUIRED)
target_link_libraries(demo Threads::Threads)

include_directories(/usr/local/include)

link_directories(/usr/lib/arm-linux-gnueabihf /usr/lib/arm-linux-gnueabihf)
target_link_libraries(demo xdo wiringPi)
