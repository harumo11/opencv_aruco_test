cmake_minimum_required(VERSION 3.5)

project(opencv_aruco_test)
find_package(OpenCV REQUIRED)

add_executable(marker_creation marker_creation.cpp)
add_executable(marker_detection marker_detection.cpp)
add_executable(calibration calibration.cpp)
add_executable(pose_estimation pose_estimation.cpp)

target_link_libraries(marker_creation ${OpenCV_LIBS})
target_link_libraries(marker_detection ${OpenCV_LIBS})
target_link_libraries(calibration ${OpenCV_LIBS})
target_link_libraries(pose_estimation ${OpenCV_LIBS})
