#include <ctime>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace boost::property_tree;
	
	
int main()
{
    ptree pt;
    read_json("http://jsonplaceholder.typicode.com/users", pt);
	
    for (auto& node : pt.get_child("1")){
		int id = node.second.get<int>("id");
		cout<<id<<endl;
	}
}
