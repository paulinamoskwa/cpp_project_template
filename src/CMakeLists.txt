# Get all the source files
file(GLOB_RECURSE SOURCES "*.cpp")

# Add library target (if there are libraries in src)
add_library(MyProjectLib ${SOURCES})
