# Create executable
add_executable(6DTeleOp main.cpp aruco.cpp)

# Link against Imath
target_link_libraries(6DTeleOp PRIVATE 
    Imath::Imath
    ${OpenCV_LIBS}
)

# In src/CMakeLists.txt
target_include_directories(6DTeleOp PRIVATE 
    # ${CMAKE_CURRENT_SOURCE_DIR}
    # ${CMAKE_BINARY_DIR}/extern/Imath/src/
    # ${CMAKE_CURRENT_SOURCE_DIR}/../extern/Imath/src/Imath
    ${PROJECT_SOURCE_DIR}/extern/Imath/src/
)