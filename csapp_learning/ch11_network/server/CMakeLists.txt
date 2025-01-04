project(tiny)

set(TINY_SRC_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/godzilla.gif
  ${CMAKE_CURRENT_SOURCE_DIR}/godzilla.jpg
  ${CMAKE_CURRENT_SOURCE_DIR}/home.html
)

add_executable(tiny tiny.c)
target_link_libraries(tiny PRIVATE csapp)
add_custom_command(TARGET tiny POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${TINY_SRC_FILES}
  $<TARGET_FILE_DIR:tiny>
)

add_executable(addr cgi-bin/addr.c)
target_link_libraries(addr PRIVATE csapp)
add_custom_command(TARGET addr POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:tiny>/cgi-bin
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:addr> $<TARGET_FILE_DIR:tiny>/cgi-bin
)