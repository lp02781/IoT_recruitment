#include <ctime>
#include <iostream>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
using namespace boost::property_tree;
	
int id;
double timestamp;
float temperature, humidity;
string roomArea, time_now, time_before;
int count_data;

float max_hum[3];
float min_hum[3];
float max_temp[3];
float min_temp[3];
float median_hum[3];
float median_temp[3];

float hum[3];
float temp[3];
float mean_hum[3];
float mean_temp[3];

float temp_1[48];
float temp_2[48];
float temp_3[48];
float hum_1[48];
float hum_2[48];
float hum_3[48];

int arrmin(float a[],int num_elements);
int arrmax(float a[], int num_elements);

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
    read_json("../JSON_Files/sensor_data.json", pt);
	
	for (auto& node : pt.get_child("array")){
		if(node.second.get<int>("id")==1){
			timestamp = node.second.get<double>("timestamp");
		}
	}
	
	bd::date start(to_bdate(timestamp/1000));
	stringstream ss;
	ss << start;
	time_before = ss.str();	
	
    for (auto& node : pt.get_child("array")){
		id = node.second.get<int>("id");
		timestamp = node.second.get<double>("timestamp");
		temperature = node.second.get<float>("temperature");
		humidity = node.second.get<float>("humidity");
		roomArea = node.second.get<std::string>("roomArea");
		
		bd::date today(to_bdate(timestamp/1000));
		
		stringstream ss;
		ss << today;
		time_now = ss.str();		
		
		if(time_now == time_before){
			if(roomArea == "roomArea1"){
				hum[0] += humidity;
				temp[0] += temperature;
				hum_1[count_data]=humidity;
				temp_1[count_data]=temperature;
				if(max_hum[0]<humidity){max_hum[0]=humidity;}
				if(min_hum[0]>humidity){min_hum[0]=humidity;}
				if(max_temp[0]>temperature){max_temp[0]=temperature;}
				if(min_temp[0]>temperature){min_temp[0]=temperature;}
			}
			else if(roomArea == "roomArea2"){
				hum[1] += humidity;
				temp[1] += temperature;
				hum_2[count_data]=humidity;
				temp_2[count_data]=temperature;
				if(max_hum[1]<humidity){max_hum[1]=humidity;}
				if(min_hum[1]>humidity){min_hum[1]=humidity;}
				if(max_temp[1]>temperature){max_temp[1]=temperature;}
				if(min_temp[1]>temperature){min_temp[1]=temperature;}
			}
			else if(roomArea == "roomArea3"){
				hum[2] += humidity;
				temp[2] += temperature;
				hum_3[count_data]=humidity;
				temp_3[count_data]=temperature;
				if(max_hum[2]<humidity){max_hum[2]=humidity;}
				if(min_hum[2]>humidity){min_hum[2]=humidity;}
				if(max_temp[2]>temperature){max_temp[2]=temperature;}
				if(min_temp[2]>temperature){min_temp[2]=temperature;}
				count_data++;
			}	
		}
		else{ 
			int n = sizeof(temp_1) / sizeof(temp_1[0]);
			sort(temp_1, temp_1 + n);
			int o = sizeof(temp_2) / sizeof(temp_2[0]);
			sort(temp_2, temp_2 + o);
			int p = sizeof(temp_3) / sizeof(temp_3[0]);
			sort(temp_3, temp_3 + p);
			int q = sizeof(hum_1) / sizeof(hum_1[0]);
			sort(hum_1, hum_1 + q);
			int r = sizeof(hum_2) / sizeof(hum_2[0]);
			sort(hum_2, hum_2 + r);
			int s = sizeof(hum_3) / sizeof(hum_3[0]);
			sort(hum_3, hum_3 + s);
			
			median_temp[0]=temp_1[sizeof(temp_1)/2];
			median_temp[1]=temp_2[sizeof(temp_2)/2];
			median_temp[2]=temp_3[sizeof(temp_3)/2];
			
			median_hum[0]=hum_1[sizeof(hum_1)/2];
			median_hum[1]=hum_2[sizeof(hum_2)/2];
			median_hum[2]=hum_3[24];
			
			cout<<endl<<"time:"<<time_before<<endl;
			for(int j = 0; j<3;j++){
				mean_hum[j]=hum[j]/count_data;
				mean_temp[j]=temp[j]/count_data;

				cout<<"room :"<<j+1<<endl;
				cout<<"humidity avg:"<<mean_hum[j]<<"\t min:"<<min_hum[j]<<"\t max:"<<max_hum[j]<<"\t median:"<<median_hum[j]<<endl;
				cout<<"temperature avg:"<<mean_temp[j]<<"\t min:"<<min_temp[j]<<"\t max:"<<max_temp[j]<<"\t median:"<<median_temp[j]<<endl;
				
				hum[j]=humidity;
				temp[j]=temperature;
				
				max_hum[j]=humidity;
				min_hum[j]=humidity;
				max_temp[j]=temperature;
				min_temp[j]=temperature;
			}
			count_data=1;
		}
		time_before = time_now;
	}
}
