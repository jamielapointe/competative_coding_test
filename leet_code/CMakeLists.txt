
# include_directories(GoogleTest)
# include_directories(GoogleMock)
include_directories(${GOOGLEMOCK_INCLUDE})
include_directories(${GOOGLETEST_INCLUDE})
link_libraries(GTest::gtest_main)
# link_libraries(GMock::gmock_main)

add_subdirectory(data_structures_and_algorithms)
add_subdirectory(leet_75)
add_subdirectory(programming_skills)
