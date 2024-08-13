cmake_minimum_required(VERSION 3.22)

project(xmlParser)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    #Linux-specific code or configuration here
    message(STATUS "Configuring for Linux")
    set(CXX_STANDARD 23)

    # set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra")
    # set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -ggdb -g -DTRACY_ENABLE")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -ggdb -g")
    # set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -ggdb -g -DRENDER_FRONT_TO_BACK")

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../debug)

    add_executable(${PROJECT_NAME}
        # src/main.cpp
        # src/protobuf.cpp
        src/xml.cpp
        src/Utility.cpp
        )
    
    # target_precompile_headers(${PROJECT_NAME} PUBLIC src/pch/pch.hpp)

    target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
    
    # Needed for absolute include paths
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

    # target_link_libraries(${PROJECT_NAME} )

# If the operating system is not recognized
else()
    message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
endif()