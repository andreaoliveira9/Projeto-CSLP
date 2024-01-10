cmake_minimum_required ( VERSION 3.22.1 )
project( main VERSION 0.0.1 )
include_directories(include)
find_package(OpenCV REQUIRED) 
include_directories( ${OpenCV_INCLUDE_DIRS} )
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

add_executable( IntraDecoderTest.out tests/IntraDecoderTest.cpp src/IntraCoding.cpp src/Golomb.cpp src/BitStream.cpp src/Converter.cpp )
target_link_libraries( IntraDecoderTest.out ${OpenCV_LIBS} )
set_target_properties( IntraDecoderTest.out PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Deliverable_4")

add_executable( IntraEncoderTest.out tests/IntraEncoderTest.cpp src/IntraCoding.cpp src/Golomb.cpp src/BitStream.cpp src/Converter.cpp)
target_link_libraries( IntraEncoderTest.out ${OpenCV_LIBS} )
set_target_properties( IntraEncoderTest.out PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Deliverable_4")

add_executable( HybridEncoderTest.out tests/HybridEncoderTest.cpp src/HybridCoding.cpp src/IntraCoding.cpp src/InterCoding.cpp src/Golomb.cpp src/BitStream.cpp src/Converter.cpp src/YUVReader.cpp)
target_link_libraries( HybridEncoderTest.out ${OpenCV_LIBS} )
set_target_properties( HybridEncoderTest.out PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Deliverable_5")

add_executable( HybridDecoderTest.out tests/HybridDecoderTest.cpp src/HybridCoding.cpp src/IntraCoding.cpp src/InterCoding.cpp src/Golomb.cpp src/BitStream.cpp src/Converter.cpp src/YUVReader.cpp)
target_link_libraries( HybridDecoderTest.out ${OpenCV_LIBS} )
set_target_properties( HybridDecoderTest.out PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Deliverable_5")

add_executable( HybridLossyEncoderTest.out tests/HybridLossyEncoderTest.cpp src/HybridCoding.cpp src/IntraCoding.cpp src/InterCoding.cpp src/Golomb.cpp src/BitStream.cpp src/Converter.cpp src/YUVReader.cpp)
target_link_libraries( HybridLossyEncoderTest.out ${OpenCV_LIBS} )
set_target_properties( HybridLossyEncoderTest.out PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Deliverable_6")

add_executable( HybridLossyDecoderTest.out tests/HybridLossyDecoderTest.cpp src/HybridCoding.cpp src/IntraCoding.cpp src/InterCoding.cpp src/Golomb.cpp src/BitStream.cpp src/Converter.cpp src/YUVReader.cpp)
target_link_libraries( HybridLossyDecoderTest.out ${OpenCV_LIBS} )
set_target_properties( HybridLossyDecoderTest.out PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Deliverable_6")
