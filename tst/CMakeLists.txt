find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories (${PROJECT_SOURCE_DIR}/include
 ${Boost_INCLUDE_DIRS}
 )
add_definitions (-DBOOST_TEST_DYN_LINK)
find_package(iir)
add_executable (Test Filt_tst.cpp)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
target_link_libraries (Test
 iir
 Filter
 ${Boost_FILESYSTEM_LIBRARY}
${Boost_SYSTEM_LIBRARY}
${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
 )
add_test (NAME FilterTest COMMAND Test)

find_package(Threads REQUIRED)
add_executable (ClickTest Click_tst.cpp)
target_link_libraries (ClickTest
 Mouse
 wiringPi
 xdo
 Threads::Threads
)
