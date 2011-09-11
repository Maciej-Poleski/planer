find_package(Boost 1.46.1 REQUIRED unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS} ../src)
add_definitions(-DBOOST_TEST_DYN_LINK)

set(TEST_SOURCES calendar_test.cxx)

add_executable(test ${TEST_SOURCES} main.cxx)
target_link_libraries(test ${QT_LIBRARIES} ${Boost_LIBRARIES} PlanerCore)
