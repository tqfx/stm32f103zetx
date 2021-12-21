add_executable(list2 list2.c)
target_link_libraries(list2 task)

add_executable(test task.cpp)
target_link_libraries(test task)
if(UNIX)
  include(FindThreads)
  target_link_libraries(test ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
endif()
