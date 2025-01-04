project(ch11_network)

add_executable(ch11_01_pton_ntop   01_pton_ntop.cc)
add_executable(ch11_02_sockaddr_in 02_sockaddr_in.cc)
add_executable(ch11_03_socket      03_socket.cc)
add_executable(ch11_04_getaddrinfo 04_getaddrinfo.cc)

add_executable(ch11_05_echo_client 05_echo_client.cc)
target_link_libraries(ch11_05_echo_client PRIVATE
  util
  csapp
)
add_executable(ch11_06_echo_server 06_echo_server.cc)
target_link_libraries(ch11_06_echo_server PRIVATE
  util
  csapp
)


add_subdirectory(server)
