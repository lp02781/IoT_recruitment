#include <ctime>
#include <iostream>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace boost::property_tree;
	
int id;
double timestamp;
float temperature, humidity;
string roomArea;

boost::gregorian::date to_bdate(time_t time) {
	return boost::posix_time::from_time_t(time).date();
}

time_t to_time_t(const boost::gregorian::date& date ){
	using namespace boost::posix_time;
	static ptime epoch(boost::gregorian::date(1970, 1, 1));
	time_duration::sec_type secs = (ptime(date,seconds(0)) - epoch).total_seconds();
	return time_t(secs);
}

namespace bd = boost::gregorian;
namespace pt = boost::posix_time;

int main()
{
    ptree pt;
    read_json("/home/mfikih15/IoT_recruitment/JSON_Files/sensor_data.json", pt);

    for (auto& node : pt.get_child("array")){
		if(node.second.get<double>("timestamp") <= 1593671400221){
			id = node.second.get<int>("id");
			timestamp = node.second.get<double>("timestamp");
			temperature = node.second.get<float>("temperature");
			humidity = node.second.get<float>("humidity");
			roomArea = node.second.get<std::string>("roomArea");
			//cout<< id<<":"<<timestamp<<":"<<temperature<<":"<<humidity<<":"<<roomArea<<":"<<endl;
			
			time_t nowtime;
			time(&nowtime);
			cout << "Unix timestamp of now:          " << nowtime << endl;

			// conversion time_t -> boost date
			bd::date today(to_bdate(nowtime));
			cout << "Timestamp converted to date:   " << today << endl;

			// conversion boost date -> time_t
			time_t thismorning = to_time_t(today);
			cout << "Date converted back to time_t:  " << thismorning << endl;
		}
	}
}
