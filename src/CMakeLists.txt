# default C standard
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 11)
endif()
if(NOT CMAKE_C_EXTENSIONS)
  set(CMAKE_C_EXTENSIONS OFF)
endif()
if(NOT CMAKE_C_STANDARD_REQUIRED)
  set(CMAKE_C_STANDARD_REQUIRED ON)
endif()
# default C++ standard
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
if(NOT CMAKE_CXX_EXTENSIONS)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()
if(NOT CMAKE_CXX_STANDARD_REQUIRED)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()
cmake_minimum_required(VERSION 3.10)

project(task VERSION 0.1.0)

include_directories(${CMAKE_CURRENT_LIST_DIR})
aux_source_directory(${CMAKE_CURRENT_LIST_DIR} SOURCE)

add_library(${PROJECT_NAME} ${SOURCE})
target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
  $<INSTALL_INTERFACE:include>
)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  DESTINATION include FILES_MATCHING
  REGEX ".*\.\(h\|hh\|hxx\|hpp\)$"
  REGEX ".*CMakeFiles.*" EXCLUDE
  REGEX ".*/build$" EXCLUDE
)
install(EXPORT ${PROJECT_NAME}-targets
  FILE ${PROJECT_NAME}-config.cmake
  DESTINATION lib/cmake/${PROJECT_NAME}
)
install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}-targets
  PUBLIC_HEADER DESTINATION include
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

find_package(Doxygen OPTIONAL_COMPONENTS dot mscgen dia)
if(DOXYGEN_FOUND)
  # Project related configuration options
  set(DOXYGEN_PROJECT_BRIEF "Cooperative scheduler")
  set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
  # Build related configuration options
  set(DOXYGEN_EXTRACT_ALL YES)
  set(DOXYGEN_EXTRACT_PRIVATE YES)
  set(DOXYGEN_EXTRACT_STATIC YES)
  # Configuration options related to warning and progress messages
  # Configuration options related to the input files
  set(DOXYGEN_RECURSIVE YES)
  # Configuration options related to source browsing
  set(DOXYGEN_INLINE_SOURCES YES)
  # Configuration options related to the alphabetical class index
  # Configuration options related to the HTML output
  set(DOXYGEN_GENERATE_HTML YES)
  set(DOXYGEN_USE_MATHJAX YES)
  # Configuration options related to the LaTeX output
  # Configuration options related to the RTF output
  # Configuration options related to the man page output
  # Configuration options related to the XML output
  # Configuration options related to the DOCBOOK output
  # Configuration options for the AutoGen Definitions output
  # Configuration options related to Sqlite3 output
  # Configuration options related to the Perl module output
  # Configuration options related to the preprocessor
  set(DOXYGEN_MACRO_EXPANSION YES)
  set(DOXYGEN_EXPAND_ONLY_PREDEF YES)
  set(DOXYGEN_PREDEFINED
    "__cplusplus"
    "__BEGIN_DECLS:="
    "__END_DECLS:="
    "__NONNULL():="
    "__NONNULL_ALL:="
    "__RESULT_USE_CHECK:="
    "__ALWAYS_INLINE:="
    "__WEAK:="
    "__USED:="
    "__UNUSED:="
    "__ALIGNED():="
    "__PACKED:="
    "__PACKED_STRUCT:="
    "__PACKED_UNION:="
    "__ASM:="
    "__INLINE:="
    "__RESTRICT:="
    "__STATIC_INLINE:="
    "__ATTR_PRINTF():="
  )
  # Configuration options related to external references
  # Configuration options related to the dot tool
  if(Doxygen_dot_FOUND)
    set(DOXYGEN_HAVE_DOT YES)
    set(DOXYGEN_CALL_GRAPH YES)
    set(DOXYGEN_INTERACTIVE_SVG YES)
    set(DOXYGEN_DOT_IMAGE_FORMAT svg)
  endif()
  doxygen_add_docs(docs_${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR})
endif()
