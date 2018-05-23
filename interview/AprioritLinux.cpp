#include "AprioritLinux.h"
#include "2_test_1_FIXED_Kusii.h"

#include <iostream>

void AprioritLinux::Run()
{
	std::cout << "START AprioritLinux::Run()" << std::endl;
	try {
		std::shared_ptr<Request> request = std::make_shared<Request::UriForFile>("file2");
		std::string response = request->execute("91.198.174.192", 80);
	}
	catch (std::exception& exc) {
		std::cout << "ERROR: " << exc.what() << std::endl;
	}
	catch (...) {
		std::cout << "UNKNOWN ERROR" << std::endl;
	}

	std::cout << "END Inheritance::Run()" << std::endl;
}
