#include <iostream>
#include <map>

int main()
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