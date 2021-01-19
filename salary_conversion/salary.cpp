#include <iostream>
#include "restc-cpp/restc-cpp.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <vector>
#include "json.hpp"

using namespace std;
using namespace restc_cpp;

using namespace boost::property_tree;

ptree pt;
ptree salary;

ptree complete;
ptree children;
ptree child[10];

int idr_id;
float idr_salary;

int id;
string name;
string username;
string email;
string phone;
string address;
string suite;
string city;
string zipcode;

void DoSomethingInteresting(Context& ctx) {
    auto reply = ctx.Get("http://jsonplaceholder.typicode.com/users");
	//cout<<reply["id"]<<endl;
}

int main() {
    auto rest_client = RestClient::Create();
    rest_client->Process(DoSomethingInteresting);
    rest_client->CloseWhenReady(true);
	
	read_json("../JSON_Files/salary_data.json", salary);
	
	for (auto& node : salary.get_child("array")){
		idr_id = node.second.get<int>("id");
		idr_salary = node.second.get<float>("salaryInIDR");
		
		child[idr_id-1].put("id", idr_id);
		child[idr_id-1].put("IDR", idr_salary);
		
		//id, name, username, email, address, phone, salary
		//in IDR and salary in USD
		
		
		children.push_back(std::make_pair("", child[idr_id-1]));
		//cout<<"id:"<<idr_id<<"\t IDR:"<<idr_salary<<endl;
	}
	complete.add_child("MyArray", children);
	write_json("test2.json", complete);
}
