cmake_minimum_required(VERSION 2.8)
project(hello_world)

### Dependencies: ###

  # ROS
  find_package(catkin REQUIRED COMPONENTS
    rtt_ros
    roscpp
    std_msgs
    rtt_rosparam
    )

  # BOOST
  find_package(Boost REQUIRED COMPONENTS
    program_options
    )

  # Eigen
  find_package(Eigen3 REQUIRED)

  # Orocos
  use_orocos()
  orocos_use_package(ocl-deployment)
  orocos_use_package(ocl-taskbrowser)

### Includes: ###
  include_directories(include)
  include_directories(SYSTEM
    ${catkin_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${USE_OROCOS_INCLUDE_DIRS}
  )

### Orocos Targets ###

  ### Components: ###
    # orocos_component(my_component src/my_component.cpp)
    # target_link_libraries(my_component ${catkin_LIBRARIES} ${USE_OROCOS_LIBRARIES})
    orocos_component(HelloWorld 
          src/HelloWorld-component.cpp)
    target_link_libraries(HelloWorld ${catkin_LIBRARIES} ${USE_OROCOS_LIBRARIES} ${OROCOS-RTT_RTT-SCRIPTING_LIBRARY})

  ### Libraries: ###
    # orocos_library(my_library src/my_library.cpp)
    # target_link_libraries(my_library ${catkin_LIBRARIES} ${USE_OROCOS_LIBRARIES})

  ### Services: ###
    orocos_service(HelloWorld-service src/HelloWorld-service.cpp)
    target_link_libraries(HelloWorld-service ${catkin_LIBRARIES} ${USE_OROCOS_LIBRARIES})

  ### Plugins: ###
    orocos_plugin(HelloWorld-plugin src/HelloWorld-plugin.cpp)
    target_link_libraries(HelloWorld-plugin ${catkin_LIBRARIES} ${USE_OROCOS_LIBRARIES})

  ### Typekits: ###
    # orocos_typekit(my_typekit src/my_typekit.cpp)
    # target_link_libraries(my_typekit ${catkin_LIBRARIES} ${USE_OROCOS_LIBRARIES})

  ### Executables: ###
    orocos_executable(deploy_helloworld src/orocos_deploy.cpp)
    target_link_libraries(deploy_helloworld ${Boost_LIBRARIES} HelloWorld)


### Orocos Package Exports and Install Targets ###

  install(
    TARGETS
      deploy_helloworld
    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  )

  install(DIRECTORY include/${PROJECT_NAME}/
    DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  )

  install(DIRECTORY launch
    DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  )

  # Generate install targets for header files
  orocos_install_headers(DIRECTORY include/${PROJECT_NAME})

  # Export package information (replaces catkin_package() macro)
  orocos_generate_package(
    INCLUDE_DIRS include
    DEPENDS rtt_ros
  )
