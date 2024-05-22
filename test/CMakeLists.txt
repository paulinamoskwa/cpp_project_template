# Enable testing
enable_testing()

# Add subdirectory
add_subdirectory(googletest)

# Add include directories for GoogleTest
include_directories(googletest/include)

# Get all the test source files from the test directory and its subdirectories
file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Add the test executable
add_executable(MyProjectTests ${TEST_SOURCES})

# Link the test executable with the GoogleTest libraries and the project library
target_link_libraries(MyProjectTests PRIVATE GTest::gtest GTest::gtest_main MyProjectLib)
target_include_directories(MyProjectTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src)

# Discover and add tests
include(GoogleTest)
gtest_discover_tests(MyProjectTests)
