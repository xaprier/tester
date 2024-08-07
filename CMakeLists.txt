cmake_minimum_required(VERSION 3.14)

project(Tester LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib)

file(GLOB HPP_FILES include/*.hpp)
file(GLOB CPP_FILES src/*.cpp)

add_library(${PROJECT_NAME} SHARED
  ${HPP_FILES}
  ${CPP_FILES}
)

add_executable(${PROJECT_NAME}_simple_app main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)

# Installation rules
install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
)

install(FILES ${HPP_FILES} DESTINATION include/${PROJECT_NAME})

install(EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Config.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION lib/cmake/${PROJECT_NAME}
)

target_link_libraries(${PROJECT_NAME} PUBLIC Logger)
target_link_libraries(${PROJECT_NAME}_simple_app ${PROJECT_NAME})