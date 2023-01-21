#include <string>
#include <fstream> // std::ifstream
#include <sstream> // std::istringstream

using std::string;

string read_key_value(string path, string target_key){
    string value_found{"not found"}; // initialize output
    string line, key, value; // string to hold each streamed line
    std::ifstream filestream(path); // create stream from file to parse
    if (filestream.is_open()) { // only parse if filestream open
        while (std::getline(filestream, line)) { // parse file line-wise
            std::istringstream linestream(line);
            while (linestream >> key >> value){  // each line has key-value pair separated by spaces
                if (key == target_key) {
                    value_found = value;
                    // return value_found;
                }
            } 
        }
    }
return value_found;
};

