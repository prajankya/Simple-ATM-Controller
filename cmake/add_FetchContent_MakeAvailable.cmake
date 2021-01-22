macro(FetchContent_MakeAvailable NAME)
  FetchContent_GetProperties(${NAME})
  if(NOT ${NAME}_POPULATED)
    FetchContent_Populate(${NAME})
    set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE BOOL "")
    add_subdirectory(${${NAME}_SOURCE_DIR} ${${NAME}_BINARY_DIR} EXCLUDE_FROM_ALL)
    unset(CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
  endif()
endmacro()