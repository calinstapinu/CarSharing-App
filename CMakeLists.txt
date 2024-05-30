cmake_minimum_required(VERSION 3.27)
project(Json_test)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(Json_test main.cpp
        include/nlohmann/adl_serializer.hpp
        Repositories/AutoRepo/AutoRepo.h
        Repositories/AutoRepo/AutoRepo.cpp
        Domain/Auto.cpp
        Repositories/AutoRepo/TestsAutoRepo/testsAutoRepo.h
        Repositories/AutoRepo/TestsAutoRepo/testsAutoRepo.cpp
        Controllers/AutoController/AutoController.cpp
        Controllers/AutoController/AutoController.h
        Domain/Order.cpp
        Domain/Order.h
        Repositories/OrderRepo/OrderRepo.cpp
        Repositories/OrderRepo/OrderRepo.h
        Repositories/OrderRepo/TestsOrderRepo/testOrderRepo.cpp
        Repositories/OrderRepo/TestsOrderRepo/testOrderRepo.h
        Controllers/OrderController/OrderController.cpp
        Controllers/OrderController/OrderController.h
        Controllers/OrderController/TestsOrderController/testOrderController.cpp
        Controllers/OrderController/TestsOrderController/testOrderController.h
        Domain/Mitarbeiter.cpp
        Domain/Mitarbeiter.h
        Repositories/MitarbeiterRepo/MitarbeiterRepo.cpp
        Repositories/MitarbeiterRepo/MitarbeiterRepo.h
        Repositories/MitarbeiterRepo/TestsMitarbeiterRepo/testMitarbeiterRepo.cpp
        Repositories/MitarbeiterRepo/TestsMitarbeiterRepo/testMitarbeiterRepo.h
        Domain/Customer.cpp
        Domain/Customer.h
        Repositories/CustomerRepo/CustomerRepo.cpp
        Repositories/CustomerRepo/CustomerRepo.h
        Repositories/CustomerRepo/TestsCustomerRepo/testCustomerRepo.cpp
        Repositories/CustomerRepo/TestsCustomerRepo/testCustomerRepo.h
        Domain/Admin.cpp
        Domain/Admin.h
        Repositories/AdminRepo/AdminRepo.cpp
        Repositories/AdminRepo/AdminRepo.h
        Repositories/AdminRepo/TestsAdminRepo/testsAdminRepo.cpp
        Repositories/AdminRepo/TestsAdminRepo/testsAdminRepo.h
        Controllers/AdminController/AdminController.cpp
        Controllers/AdminController/AdminController.h
        Controllers/AdminController/TestsAdminController/testsAdminController.cpp
        Controllers/AdminController/TestsAdminController/testsAdminController.h
        Controllers/CustomerController/CustomerController.cpp
        Controllers/CustomerController/CustomerController.h
)
