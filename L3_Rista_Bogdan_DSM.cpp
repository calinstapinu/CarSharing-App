#include "L3_Rista_Bogdan_DSM.h"
#include <cstring>
#include <algorithm>

using namespace std;

DSM::DSM(int count) : elementCount(count), elementNames(new ::string[count]) {
    initializeMatrix();
}

DSM::DSM(const ::string* names, int count) : elementCount(count), elementNames(new ::string[count]) {
    ::copy(names, names + count, elementNames);
    initializeMatrix();
}

DSM::DSM(const DSM& other) : elementCount(other.elementCount), elementNames(new ::string[other.elementCount]) {
    ::copy(other.elementNames, other.elementNames + other.elementCount, elementNames);
    initializeMatrix();
    for (int i = 0; i < elementCount; ++i) {
        ::copy(other.adjacencyMatrix[i], other.adjacencyMatrix[i] + elementCount, adjacencyMatrix[i]);
    }
}

DSM& DSM::operator=(const DSM& other) {
    if (this != &other) {
        delete[] elementNames;
        for (int i = 0; i < elementCount; ++i) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;

        elementCount = other.elementCount;
        elementNames = new ::string[elementCount];
        ::copy(other.elementNames, other.elementNames + elementCount, elementNames);
        initializeMatrix();
        for (int i = 0; i < elementCount; ++i) {
            ::copy(other.adjacencyMatrix[i], other.adjacencyMatrix[i] + elementCount, adjacencyMatrix[i]);
        }
    }
    return *this;
}

void DSM::initializeMatrix() {
    adjacencyMatrix = new int*[elementCount];
    for (int i = 0; i < elementCount; ++i) {
        adjacencyMatrix[i] = new int[elementCount]{};
    }
}

DSM::~DSM() {
    delete[] elementNames;
    for (int i = 0; i < elementCount; ++i) {
        delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;
}


int DSM::size() const {
    return elementCount;
}

::string DSM::getName(int index) const {
    if (index < 0 || index >= elementCount) {
        throw ::out_of_range("Index out of bounds");
    }
    return elementNames[index];
}

void DSM::setElementName(int index, const ::string& elementName) {
    if (index < 0 || index >= elementCount) {
        throw ::out_of_range("Index out of bounds");
    }
    elementNames[index] = elementName;
}

void DSM::addLink(const ::string& fromElement, const ::string& toElement, int weight) {
    int fromIndex = -1;
    int toIndex = -1;

    for (int i = 0; i < elementCount; ++i) {
        if (elementNames[i] == fromElement) {
            fromIndex = i;
        }
        if (elementNames[i] == toElement) {
            toIndex = i;
        }
    }

    if (fromIndex == -1 || toIndex == -1) {
        throw ::invalid_argument("Element name not found");
    }

    adjacencyMatrix[fromIndex][toIndex] = weight;
}

void DSM::deleteLink(const ::string& fromElement, const ::string& toElement) {
    int fromIndex = -1;
    int toIndex = -1;

    for (int i = 0; i < elementCount; ++i) {
        if (elementNames[i] == fromElement) {
            fromIndex = i;
        }
        if (elementNames[i] == toElement) {
            toIndex = i;
        }
    }

    if (fromIndex == -1 || toIndex == -1) {
        throw ::invalid_argument("Element name not found");
    }

    adjacencyMatrix[fromIndex][toIndex] = 0;
}

bool DSM::hasLink(const ::string& fromElement, const ::string& toElement) const {
    int fromIndex = -1;
    int toIndex = -1;

    for (int i = 0; i < elementCount; ++i) {
        if (elementNames[i] == fromElement) {
            fromIndex = i;
        }
        if (elementNames[i] == toElement) {
            toIndex = i;
        }
    }

    if (fromIndex == -1 || toIndex == -1) {
        return false;
    }

    return adjacencyMatrix[fromIndex][toIndex] != 0;
}

int DSM::linkWeight(const ::string& fromElement, const ::string& toElement) const {
    int fromIndex = -1;
    int toIndex = -1;

    for (int i = 0; i < elementCount; ++i) {
        if (elementNames[i] == fromElement) {
            fromIndex = i;
        }
        if (elementNames[i] == toElement) {
            toIndex = i;
        }
    }

    if (fromIndex == -1 || toIndex == -1) {
        throw ::invalid_argument("Element name not found");
    }

    return adjacencyMatrix[fromIndex][toIndex];
}

int DSM::countToLinks(const ::string& elementName) const {
    int index = -1;
    int count = 0;

    for (int i = 0; i < elementCount; ++i) {
        if (elementNames[i] == elementName) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        throw ::invalid_argument("Element name not found");
    }

    for (int i = 0; i < elementCount; ++i) {
        if (adjacencyMatrix[i][index] != 0) {
            count++;
        }
    }

    return count;
}

int DSM::countFromLinks(const ::string& elementName) const {
    int index = -1;
    int count = 0;

    for (int i = 0; i < elementCount; ++i) {
        if (elementNames[i] == elementName) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        throw ::invalid_argument("Element name not found");
    }

    for (int i = 0; i < elementCount; ++i) {
        if (adjacencyMatrix[index][i] != 0) {
            count++;
        }
    }

    return count;
}

int DSM::countAllLinks() const {
    int count = 0;

    for (int i = 0; i < elementCount; ++i) {
        for (int j = 0; j < elementCount; ++j) {
            if (adjacencyMatrix[i][j] != 0) {
                count++;
            }
        }
    }

    return count;
}