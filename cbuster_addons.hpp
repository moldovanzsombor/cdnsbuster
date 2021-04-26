#include <vector>

bool elem_in_vect(std::string element, std::vector<std::string> vect)
{
	bool ret = false;

	for(size_t i = 0; i < vect.size(); ++i)
	{
		if(element == vect[i])
		{
			ret = true;
		}
	}

	return ret;
}
