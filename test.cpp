#include <iostream>
#include <map>

int main() {
    std::map<int, std::string> myMap;
    
    // Insert some values
    myMap[1] = "one";
    myMap[2] = "two";
    myMap[3] = "three";
    
    // Erase the key-value pair with key = 2
    std::map<int, std::string>::iterator it ;
    for ( it = myMap.begin(); it != myMap.end(); ++it) {
        if (it->second == "two")
            break;
    }
    //itp = myMap.find("two");
    myMap.erase(it);
    
    // Print the remaining key-value pairs
    for (std::map<int, std::string>::iterator it = myMap.begin(); it != myMap.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }
    
    return 0;
}