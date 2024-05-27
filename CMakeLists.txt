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
        Repositories/MitarbeiterRepo/TestsMitarbeiterRepo/MitarbeiterRepo.h
        Repositories/MitarbeiterRepo/TestsMitarbeiterRepo/MitarbeiterRepo.cpp
        Domain/Mitarbeiter.h
        Domain/Mitarbeiter.cpp
        Domain/Order.cpp
        Domain/Order.h
        Repositories/OrderRepo/OrderRepo.cpp
        Repositories/OrderRepo/OrderRepo.h
        Repositories/OrderRepo/TestsOrderRepo/testOrderRepo.cpp
        Repositories/OrderRepo/TestsOrderRepo/testOrderRepo.h
)

