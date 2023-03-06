add_library(sudoku sudoku.cpp)
target_include_directories(sudoku PUBLIC ../include)

# require at least c++11
target_compile_features(sudoku PUBLIC cxx_std_11)
