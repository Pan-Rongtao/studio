# 1. Project Name
project(editor)

# 2. Project Env (Include/Lib Path, C/CXX/LD FLAGS)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(imgui)
include_directories(rcf/include)
add_definitions("-D_WIN32_WINNT=0x0601")

#src_dir：目录前缀。结果为移除此前缀后的分组
function(group_by_dir src_dir)
  foreach(FILE ${ARGN})
    # 获取文件绝对路径
    get_filename_component(FULL_NAME "${FILE}" ABSOLUTE)
    # 获取文件父路径
    get_filename_component(PARENT_DIR "${FULL_NAME}" PATH)
    # 移除父路径中的源码根路径
    string(REPLACE "${ARGV0}" "" GROUP "${PARENT_DIR}")
    # 确保路径使用windows路径符号
    string(REPLACE "/" "\\" GROUP "${GROUP}")
    # 将文件归组到 "Source Files" 和 "Header Files"
    if("${FILE}" MATCHES ".*\\.h" OR "${FILE}" MATCHES ".*\\.hpp")
      set(GROUP "${GROUP}")
    else()
      set(GROUP "${GROUP}")
    endif()
    source_group("${GROUP}" FILES "${FILE}")
  endforeach()
endfunction(group_by_dir)

# 3. Project Build
set(INCLUDE_PREFIX ${CMAKE_SOURCE_DIR}/editor)
file(GLOB_RECURSE INC_LIST ${INCLUDE_PREFIX}/*.h ${INCLUDE_PREFIX}/*.hpp)
file(GLOB_RECURSE SRC_LIST *.cpp *.c)

set(FILETER_SRC_LIST "")
FOREACH(src ${INC_LIST} ${SRC_LIST})
    IF(NOT (src MATCHES "rcf") OR src MATCHES "RCF.cpp")
		set(FILETER_SRC_LIST ${FILETER_SRC_LIST} ${src})
	ENDIF() 
ENDFOREACH()

if(WIN32)
	group_by_dir(${INCLUDE_PREFIX} ${FILETER_SRC_LIST})
endif()

add_executable(${PROJECT_NAME}  ${FILETER_SRC_LIST})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} glfw3 optimized rttr_core debug rttr_core_d)

# 4. Project Install
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
