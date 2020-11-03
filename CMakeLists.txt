#
# The find_package macro for Orocos-RTT requires
# cmake >= 2.8
#
cmake_minimum_required(VERSION 2.8)

#
# This creates a standard cmake project. You may extend this file with
# any cmake macro you see fit.
#
project(HelloWorld)

### ROS Dependencies ###
# Find the RTT-ROS package (this transitively includes the Orocos CMake macros)
find_package(catkin REQUIRED COMPONENTS
  rtt_ros
  # ADDITIONAL ROS PACKAGES
  )

include_directories(${catkin_INCLUDE_DIRS})

### Orocos Targets ###

# orocos_component(my_component src/my_component.cpp)
# target_link_libraries(my_component ${catkin_LIBRARIES} ${USE_OROCOS_LIBRARIES})
orocos_component(HelloWorld src/HelloWorld-component.cpp)
target_link_libraries(HelloWorld ${catkin_LIBRARIES} ${USE_OROCOS_LIBRARIES})

# orocos_library(my_library src/my_library.cpp)
# target_link_libraries(my_library ${catkin_LIBRARIES} ${USE_OROCOS_LIBRARIES})

# orocos_service(my_service src/my_service.cpp)
# target_link_libraries(my_service ${catkin_LIBRARIES} ${USE_OROCOS_LIBRARIES})
orocos_service(HelloWorld-service src/HelloWorld-service.cpp)
target_link_libraries(HelloWorld-service ${catkin_LIBRARIES} ${USE_OROCOS_LIBRARIES})

# orocos_plugin(my_plugin src/my_plugin.cpp)
# target_link_libraries(my_plugin ${catkin_LIBRARIES} ${USE_OROCOS_LIBRARIES})
orocos_plugin(HelloWorld-plugin src/HelloWorld-plugin.cpp)
target_link_libraries(HelloWorld-plugin ${catkin_LIBRARIES} ${USE_OROCOS_LIBRARIES})

# orocos_typekit(my_typekit src/my_typekit.cpp)
# target_link_libraries(my_typekit ${catkin_LIBRARIES} ${USE_OROCOS_LIBRARIES})

### Orocos Package Exports and Install Targets ###

# Generate install targets for header files

orocos_install_headers(DIRECTORY include/${PROJECT_NAME})

# Export package information (replaces catkin_package() macro) 
orocos_generate_package(
  INCLUDE_DIRS include
  DEPENDS rtt_ros
)
