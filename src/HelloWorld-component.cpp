#include "HelloWorld/HelloWorld-component.hpp"
#include <rtt/Component.hpp>
#include <rtt_rosparam/rosparam.h>
#include <iostream>
#include <ros/ros.h>
#include <rtt/Logger.hpp>
#include <ocl/DeploymentComponent.hpp>


HelloWorld::HelloWorld(std::string const& name) : TaskContext(name){
	RTT::Logger::In in("HelloWorld");

	this->addProperty("parameter_txt", parameter_txt_);

	RTT::log(RTT::LoggerLevel::Warning) << "HelloWorld constructed !" << RTT::endlog();
}

bool HelloWorld::configureHook(){
	RTT::Logger::In in("HelloWorld::configure");
	bool all_params_found = true;
	
	boost::shared_ptr<rtt_rosparam::ROSParam> rosparam =
		this->getProvider<rtt_rosparam::ROSParam>("rosparam");

	// Get the parameters
	if(rosparam) {
		all_params_found &= rosparam->getComponentPrivate("parameter_txt");
	}

	RTT::log(RTT::LoggerLevel::Warning)
		<< (all_params_found ? "HelloWorld configured !" : "Could not find all ROS parameters, configure failed")
		<< RTT::endlog();
	
	return all_params_found;
}

bool HelloWorld::startHook(){
	RTT::Logger::In in("HelloWorld::start");

	RTT::log(RTT::LoggerLevel::Info) << "HelloWorld started !" << RTT::endlog();
	return true;
}

void HelloWorld::updateHook(){
	if (!ros::ok()) this->error();
	RTT::Logger::In in("HelloWorld::update");
	
	
	RTT::log(RTT::LoggerLevel::Info) << "HelloWorld executes updateHook !" << RTT::endlog();
	RTT::log(RTT::LoggerLevel::Info) << "And now say: " << parameter_txt_ << RTT::endlog();

	static char a = 'x';
	static char b = 'X';
	std::swap(a,b);
	std::replace( parameter_txt_.begin(), parameter_txt_.end(), a, b);

}

void HelloWorld::stopHook() {
	RTT::Logger::In in("HelloWorld::stop");
	RTT::log(RTT::LoggerLevel::Info) << "HelloWorld executes stopping !" << RTT::endlog();
}

void HelloWorld::cleanupHook() {
	RTT::Logger::In in("HelloWorld::cleanup");
	RTT::log(RTT::LoggerLevel::Info) << "HelloWorld cleaning up !" << RTT::endlog();
}

// CALL THIS ONLY ONCE
ORO_CREATE_COMPONENT_LIBRARY()
ORO_LIST_COMPONENT_TYPE(HelloWorld)
