#include "HelloWorld-component.hpp"
#include <rtt/Component.hpp>
#include <iostream>

HelloWorld::HelloWorld(std::string const& name) : TaskContext(name){
  std::cout << "HelloWorld constructed !" <<std::endl;
}

bool HelloWorld::configureHook(){
  std::cout << "HelloWorld configured !" <<std::endl;
  return true;
}

bool HelloWorld::startHook(){
  std::cout << "HelloWorld started !" <<std::endl;
  return true;
}

void HelloWorld::updateHook(){
  std::cout << "HelloWorld executes updateHook !" <<std::endl;
}

void HelloWorld::stopHook() {
  std::cout << "HelloWorld executes stopping !" <<std::endl;
}

void HelloWorld::cleanupHook() {
  std::cout << "HelloWorld cleaning up !" <<std::endl;
}

// CALL THIS ONLY ONCE
ORO_CREATE_COMPONENT_LIBRARY()
ORO_LIST_COMPONENT_TYPE(HelloWorld)
