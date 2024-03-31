#ifndef L3_Rista_Bogdan_DSM_H
#define L3_Rista_Bogdan_DSM_H

#include <string>
#include <stdexcept>

class DSM {
private:
    std::string* elementNames; // Pointer to dynamic array for element names
    int** adjacencyMatrix; // Pointer to 2D dynamic array for the adjacency matrix
    int elementCount; // Number of elements

    void initializeMatrix(); // Helper method to initialize adjacency matrix

public:
    DSM(int elementCount);
    DSM(const std::string* elementNames, int elementCount);
    DSM(const DSM& other); // Copy constructor
    DSM& operator=(const DSM& other); // Assignment operator
    ~DSM(); // Destructor

    int size() const;
    std::string getName(int index) const;
    void setElementName(int index, const std::string& elementName);
    void addLink(const std::string& fromElement, const std::string& toElement, int weight);
    void deleteLink(const std::string& fromElement, const std::string& toElement);
    bool hasLink(const std::string& fromElement, const std::string& toElement) const;
    int linkWeight(const std::string& fromElement, const std::string& toElement) const;
    int countToLinks(const std::string& elementName) const;
    int countFromLinks(const std::string& elementName) const;
    int countAllLinks() const;
};

#endif