cmake_minimum_required (VERSION 2.8) 
project (rpi_dht) 

# Make sure the compiler can find include files from our Hello library. 
include_directories("/usr/local/include") 

# Make sure the linker can find the Hello library once it is built. 
link_directories ("/usr/local/lib") 

# Add executable called "helloDemo" that is built from the source files 
# "demo.cxx" and "demo_b.cxx". The extensions are automatically found. 
add_executable (dht11 dht11.c) 

# Link the executable to the Hello library. 
target_link_libraries (dht11 wiringPi pthread) 
