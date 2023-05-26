add_subdirectory(lib/googletest)

set(gtest_SOURCE_DIR lib/googletest/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(..)

set(TEST_EXEC_NAME tests_run)
add_executable(tests modbus_client_test.cpp modbus_client_test_samples.cpp)
target_link_libraries(tests gtest gtest_main)

target_link_libraries(tests /home/alexeykozlovsky/Documents/Career/Dialtek/components/sources/libmodbus/build-linux-Debug/liblibmodbus.so)
