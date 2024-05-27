#include <iostream>
#include <fstream>
#include <vector>
#include "include/nlohmann/json.hpp"
#include "Repositories/AutoRepo/AutoRepo.h"
#include "Domain/Auto.h"
#include "Repositories/AutoRepo/TestsAutoRepo/testsAutoRepo.h"
#include "Controllers/AutoController/AutoController.h"

using namespace std;

int main() {
    // ruleaza testele
    run_tests_auto_repo();
    // masinile json se afla in "cars.json"
    AutoRepo cr("AutoRepo/cars.json"); // la initializare, se deschide fisierul cars.json in Repo
    AutoController cc(cr); // AutoController

    return 0;
}
