
add_executable(squares_of_sorted_array squares_of_sorted_array.cpp)
target_compile_options(squares_of_sorted_array PRIVATE -Wno-deprecated -Wno-weak-vtables -Wno-global-constructors -Wno-unused-member-function)
