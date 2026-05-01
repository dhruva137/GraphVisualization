cmake_minimum_required(VERSION 3.24)
project(GraphVisualization VERSION 2.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(GRAPHVIZ_BUILD_APP "Build SFML desktop app" ON)
option(GRAPHVIZ_BUILD_TESTS "Build unit tests" ON)

if (GRAPHVIZ_BUILD_APP)
    set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
    find_package(SFML REQUIRED system window graphics)

    add_executable(GraphVisualization
        src/main.cpp
    )

    target_include_directories(GraphVisualization PRIVATE src)
    target_link_libraries(GraphVisualization PRIVATE ${SFML_LIBRARIES})

    if (SFML_INCLUDE_DIR)
        target_include_directories(GraphVisualization PRIVATE ${SFML_INCLUDE_DIR})
    endif()

    target_compile_definitions(GraphVisualization PRIVATE
        GRAPHVIZ_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
        GRAPHVIZ_VERSION_MINOR=${PROJECT_VERSION_MINOR}
        GRAPHVIZ_VERSION_PATCH=${PROJECT_VERSION_PATCH}
    )

    file(COPY Resources DESTINATION ${CMAKE_BINARY_DIR})

    if(WIN32 AND SFML_INCLUDE_DIR)
        file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
        file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    endif()
endif()

if (GRAPHVIZ_BUILD_TESTS)
    enable_testing()

    add_executable(GraphVisualizationTests
        tests/test_runtime_ingestion_bridge.cpp
    )

    target_include_directories(GraphVisualizationTests PRIVATE src)

    add_test(NAME runtime_ingestion_bridge COMMAND GraphVisualizationTests)
endif()
