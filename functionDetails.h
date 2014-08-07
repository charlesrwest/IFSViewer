#ifndef FUNCTIONDETAILSH
#define FUNCTIONDETAILSH


#include<string>
#include<vector>


/*
This class represents the details nessisary to display the parameters for a given IFS function
*/
class functionDetails
{
public:
/*
This function sets the expected return value to 0
*/
functionDetails();

std::string functionName;
std::vector<std::string> arguments;
int expectedReturnValue;
};






#endif
