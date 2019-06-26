add_executable(${PROJECT} "main.cpp")
target_link_libraries(${PROJECT})

install(TARGETS ${PROJECT} DESTINATION ${INSTALL_NAME_DIR})