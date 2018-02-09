//test for error conditions in programs
#ifndef REQUIRE_H
#define REQUIRE_H

#include<cstdio> 
#include<cstdlib>
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
using std::stringstream;

inline void require(bool requirement,
//					const std::string& msg="requirement failed")
					stringstream &ss)
{
	using namespace std;
	if(!requirement){
		cout<<ss.str()<<endl;
		exit(1);
	}
}

inline void require(bool requirement,
					const std::string& msg="requirement failed")
//					stringstream &ss)
{
	using namespace std;
	if(!requirement){
		cout<<msg<<endl;
		exit(1);
	}
}

inline void requireArgs(int argc,int args,
						const std::string& msg="Must use %d arguments")
{
	if(argc != args+1){
		printf(msg.c_str(),args);
		puts("");
		exit(1);
	}
}

inline void requireMinArgs(int argc,int minArgs,
						const std::string& msg="Must use at least %d arguments")
{
	
	if(argc < minArgs+1){
		printf(msg.c_str(),minArgs);
		puts("");
		exit(1);
	}
}
//insure that the input/output file opened successfully
inline void assure(std::ifstream& in,const std::string& filename=""){
	if(!in){
		printf("Could not open file %s\n",filename.c_str());
		exit(1);
	}
}
inline void assure(std::ofstream& out,const std::string& filename=""){
	if(!out){
		printf("Could not open file %s\n",filename.c_str());
		exit(1);
	} 
} 
inline void assure(std::fstream& inout,const std::string& filename=""){
	if(!inout){
		printf("Could not open file %s\n",filename.c_str());
		exit(1);
	} 
} 

#endif
