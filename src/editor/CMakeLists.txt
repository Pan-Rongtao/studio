# 1. Project Name
project(editor)

# 2. Project Env (Include/Lib Path, C/CXX/LD FLAGS)
include_directories(imgui)

# 3. Project Build
set(INCLUDE_PREFIX ${CMAKE_SOURCE_DIR}/src/${PROJECT_NAME})
file(GLOB_RECURSE INC_LIST ${INCLUDE_PREFIX}/*.h)
file(GLOB_RECURSE SRC_LIST *.cpp)

if(WIN32)
	group_by_dir(${INCLUDE_PREFIX} ${INC_LIST})
	group_by_dir(${CMAKE_CURRENT_SOURCE_DIR} ${SRC_LIST})
endif()

add_executable(${PROJECT_NAME} ${INC_LIST} ${SRC_LIST})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} glfw3 opengl32)

# 4. Project Install
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
