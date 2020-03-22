cmake_minimum_required(VERSION 3.0)

add_executable (demo main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_library(lsm9ds1 LSM9DS1.cpp)
link_directories(${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(demo lsm9ds1 rt)

find_package(iir)
target_link_libraries(demo iir::iir)

find_package(Threads REQUIRED)
target_link_libraries(demo Threads::Threads)

include_directories(/usr/local/include)
link_directories(/usr/lib/arm-linux-gnueabihf /usr/lib/arm-linux-gnueabihf)
target_link_libraries(demo xdo wiringPi)


