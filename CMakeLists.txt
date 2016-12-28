cmake_minimum_required(VERSION 3.6)
project(ex3_tm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)


set(SOURCE_FILES main.cpp Algorithm.cpp Algorithm.h Bfs.cpp Bfs.h Bfs_Test.cpp Driver.cpp Driver.h Driver_Test.cpp Logic.cpp Logic.h Logic_Test.cpp LuxTaxiFactory.cpp LuxTaxiFactory.h LuxTaxiFactory_Test.cpp LuxuryTaxi.cpp LuxuryTaxi.h Management.cpp Management.h Map.cpp Map.h MapFactory.cpp MapFactory.h Map_Factory_Test.cpp Map_Tesr.cpp Passenger.cpp Passenger.h Passenger_test.cpp Point.cpp Point.h Point_Test.cpp Searchable.cpp Searchable.h Square.cpp Square.h Square_Test.cpp StandardTaxi.cpp StandardTaxi.h StndTaxiFactory.cpp StndTaxiFactory.h Taxi.cpp Taxi.h TaxiCenter.cpp TaxiCenter.h Taxi_Center_Test.cpp Trip.cpp Trip.h Trip_Test.cpp Validate_Interface.cpp Validate_Interface.h VirtualTaxiFactory.cpp VirtualTaxiFactory.h Management_Test.cpp Socket.cpp Socket.h Udp.cpp Udp.h)
add_executable(ex3_tm ${SOURCE_FILES})
target_link_libraries(ex3_tm gtest gtest_main)
target_link_libraries(ex3_tm ${Boost_LIBRARIES})
