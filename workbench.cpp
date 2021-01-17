#include <iostream>
#include <map>

void map_simple_usage()
{
	std::map<int, std::string> memo;
	memo[1] = "daniel";
	memo[2] = "mariel";
	memo[3] = "marina";
	memo[4] = "ariel";
	memo[5] = "variel";
	memo[6] = "mariana";
	
	if (memo.find(3) != memo.end())
		std::cout << memo[3] << std::endl;
	else
		std:: cout << "not" << std::endl;    
}

void func_default_parameter()
{

}

void function_parameter()
{
    
}

int main()
{
    void function_parameter
}