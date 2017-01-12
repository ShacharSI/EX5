cmake_minimum_required(VERSION 3.6)
project(ex3_tm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})

#add_subdirectory(lib/googletest-master)
#include_directories(lib/googletest-master/googletest/include)
#include_directories(lib/googletest-master/googlemock/include)


set(SOURCE_FILES Algorithm.cpp Algorithm.h Bfs.cpp Bfs.h Driver.cpp Driver.h Logic.cpp Logic.h
         LuxuryTaxi.cpp LuxuryTaxi.h Management.cpp Management.h
        Map.cpp Map.h MapFactory.cpp MapFactory.h Passenger.cpp Passenger.h Point.cpp Point.h Searchable.cpp
        Searchable.h Square.cpp Square.h StandardTaxi.h StandardTaxi.cpp
        Taxi.cpp Taxi.h TaxiCenter.cpp TaxiCenter.h Trip.cpp Trip.h Validate_Interface.cpp Validate_Interface.h
        Socket.cpp Socket.h Udp.cpp Udp.h Tcp.cpp Tcp.h
        Thread_Runner.cpp Thread_Runner.h Trip_Info.cpp Trip_Info.h BfsInfoMap.cpp BfsInfoMap.h Thread_Class.cpp Thread_Class.h Thread_Manage.cpp Thread_Manage.h Mutex_Locker.cpp Mutex_Locker.h)
add_executable(main.cpp ${SOURCE_FILES} main.cpp)
#add_executable(mainDriver.cpp ${SOURCE_FILES} ManageDriver.cpp ManageDriver.h mainDriver.cpp )
#target_link_libraries(ex3_tm gtest gtest_main)
target_link_libraries(main.cpp ${Boost_LIBRARIES})
#target_link_libraries(mainDriver.cpp ${Boost_LIBRARIES})

