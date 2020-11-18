# 1. Project Name
project(src)

# 2. Env (Include/Lib Path, C/CXX/LD FLAGS)
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

# 4. Sub Projects
add_subdirectory(editor)

# 5. Project Install
