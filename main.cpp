#include <iostream>
#include <cassert>
#include "L3_Rista_Bogdan_DSM.h"

int main() {
    // Define car parts
    const int partsCount = 8;
    std::string carParts[] = {
            "Engine", "Transmission", "Wheel", "Brake", "Headlight", "Seat", "Windshield", "Exhaust"
    };

    // Initialize DSM with car parts
    DSM carDSM(partsCount);
    for (int i = 0; i < partsCount; ++i) {
        carDSM.setElementName(i, carParts[i]);
    }

    // Add links between parts to model dependencies
    carDSM.addLink("Engine", "Transmission", 3);
    carDSM.addLink("Transmission", "Wheel", 3);
    carDSM.addLink("Wheel", "Brake", 2);
    carDSM.addLink("Headlight", "Wheel", 1);
    carDSM.addLink("Seat", "Windshield", 1);

    // Test the existence of a link
    assert(carDSM.hasLink("Engine", "Transmission") == true);
    assert(carDSM.hasLink("Wheel", "Engine") == false);

    // Test the weight of a link
    assert(carDSM.linkWeight("Engine", "Transmission") == 3);

    // Test count to and from links
    assert(carDSM.countToLinks("Wheel") == 2);
    assert(carDSM.countFromLinks("Transmission") == 1);

    // Test total number of links
    assert(carDSM.countAllLinks() == 5);

    // Test deleting a link
    carDSM.deleteLink("Headlight", "Wheel");
    assert(carDSM.hasLink("Headlight", "Wheel") == false);
    assert(carDSM.countAllLinks() == 4);

    std::cout << "All tests passed successfully." << std::endl;

    return 0; // Successful program termination
}