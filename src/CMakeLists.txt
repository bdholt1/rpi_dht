cmake_minimum_required (VERSION 2.8)
project (rpi_dht)

include_directories("/usr/local/include")

link_directories ("/usr/local/lib")

add_executable (dht11 dht11.c)

target_link_libraries (dht11 wiringPi pthread)
