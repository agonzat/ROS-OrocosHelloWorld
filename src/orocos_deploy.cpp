#include <boost/program_options.hpp>
#include <iostream>
#include <rtt/os/main.h>
#include <ocl/DeploymentComponent.hpp>
#include <ocl/TaskBrowser.hpp>
#include <rtt/internal/GlobalService.hpp>
#include <ros/ros.h>
#include <HelloWorld/HelloWorld-component.hpp>

int ORO_main(int argc, char* argv[])
{
		if(!ros::isInitialized()){
			RTT::log(RTT::LoggerLevel::Error) << "ROS Node not initialized" << RTT::endlog();
			return 1;
		}

		ros::NodeHandle nh("");

		std::string component_name;
		std::string component_type = "HelloWorld";
		std::string component_package = "HelloWorld";
		float period = 1;
    boost::program_options::options_description description("Simple application for executing HelloWorld.");
		
    description.add_options()
				("help,h", 
					"Display help options")
        ("name,n", 
					boost::program_options::value<std::string>(&component_name)->required()->default_value("simple"),
					"The name of the RTT component and ROS namespace.");

    boost::program_options::variables_map command_line_args;

    try
    {
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, description), command_line_args);
        boost::program_options::notify(command_line_args);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        std::cout << description << std::endl;
        return 1;
    }

    if (command_line_args.count("help"))
    {
        std::cout << description << std::endl;
        return 0;
    }

    RTT::Service::shared_ptr global_service = RTT::internal::GlobalService::Instance();
    if (not global_service)
    {
        std::cerr << "Could not aquire pointer to RTT GlobalService." << std::endl;
        return 1;
    }

    OCL::DeploymentComponent deployer;

    if (not deployer.import("rtt_ros"))
    {
        std::cerr << "Orocos package rtt_ros could not be imported." << std::endl;
        return 1;
    }

    if (not global_service->provides("ros"))
    {
        std::cerr << "Global Service could not find [ros] service." << std::endl;
        return 1;
    }

    RTT::OperationCaller<bool(std::string)> ros_import = global_service->provides("ros")->getOperation("import");

    if (not ros_import(component_package))
    {
        std::cerr << "Failed to import [" << component_package << "]." << std::endl;
        return 1;
    }

    if (not deployer.loadComponent(component_name, component_type))
    {
        std::cerr << "Failed to load ["<< component_type <<"]." << std::endl;
        return 1;
    }

    if (not deployer.loadService(component_name, "rosparam"))
    {
        std::cerr << "Failed to load [rosparam] service in [" << component_name << "]." << std::endl;
        return 1;
    }

    if (not deployer.loadService(component_name, "rosservice"))
    {
        std::cerr << "Failed to load [rosservice] service in [" << component_name << "]." << std::endl;
        return 1;
    }

    RTT::TaskContext* simple_ros = deployer.getPeer(component_name);
    if (not simple_ros)
    {
        std::cerr << "Could not aquire pointer to [" << component_name << "]." << std::endl;
        return 1;
    }

    if (not simple_ros->configure())
    {
        std::cerr << "Could not configure [" << component_name << "]." << std::endl;
        return 1;
    }

    if (not simple_ros->start())
    {
        std::cerr << "Could not start [" << component_name << "]." << std::endl;
        return 1;
    }

    if (not simple_ros->setPeriod(period))
    {
        std::cerr << "Could not set period for [" << component_name << "] to [" << period << "]." << std::endl;
        return 1;
    }

		HelloWorld hw("Hello2");
		simple_ros->addPeer(&hw);

		hw.configure();
		hw.setPeriod(2);
		hw.start();

    // Main event loop.
    // OCL::TaskBrowser browser(simple_ros);
    // browser.loop();

		while(ros::ok()){
			sleep(0.1);
		}

    deployer.kickOutAll();
    deployer.shutdownDeployment();

    return 0;
}
