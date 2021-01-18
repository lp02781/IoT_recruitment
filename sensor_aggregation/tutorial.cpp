#include <boost/property_tree/json_parser.hpp>
#include <fstream>
#include <iostream>
#include <map>
using boost::property_tree::ptree;

struct UDSDID {
    std::string name, did, format, expected_value;

    static UDSDID read(ptree const& node) {
        return {
            node.get_child("NAME").get_value<std::string>(),
            node.get_child("DID").get_value<std::string>(),
            node.get_child("FORMAT").get_value<std::string>(),
            node.get_child("EXPECTED_VALUE").get_value<std::string>(),
        };
    }

    friend std::ostream& operator<<(std::ostream& os, UDSDID const& u) {
        return os 
            << "{name:" << u.name
            << ",did:" << u.did
            << ",format:" << u.format
            << ",expected_value:" << u.expected_value
            << "}";
    }
};

auto read(std::string const& fname) {
    ptree pt;
    std::ifstream ifs(fname);
    read_json(ifs, pt);

    return pt;
}

int main() {
    auto data = read("tutorial.json");

    std::vector<UDSDID> udsdids;
    std::map<std::string, std::string> other;

    for (auto& node : data) {
        if (node.first == "UDSDIDS") {
            for (auto& udsdid : node.second)
                udsdids.push_back(UDSDID::read(udsdid.second));
        } else {
            other[node.first] = node.second.get_value<std::string>();
        }
    }

    for (auto& p : other) {
        std::cout << p.first << ": " << p.second << "\n";
    }
    for (auto& u : udsdids) {
        std::cout << u << "\n";
    }
}
