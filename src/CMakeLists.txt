find_package(GSL REQUIRED)
FILE(GLOB srcs ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_library(lbcdt SHARED ${srcs})
target_link_libraries(lbcdt GSL::gsl GSL::gslcblas)
