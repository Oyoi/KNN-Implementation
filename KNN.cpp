#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class Names 
{
    public:

        Names(int count, float probability, std::string name, char gender)
            {
                this->count = count;
                this->probability = probability;
                this->name = name;
                this->gender = gender;
            }

        float distance;

        int count;
        float probability;
        std::string name;
        char gender;

};

class CSVReader 
{
public:
	CSVReader(const std::string& fileName, const std::string& delimeter = ",") :
		fileName(fileName),
		delimeter(delimeter)
	{}

	std::vector<std::vector<std::string>> getData() {

		std::ifstream file(this->fileName);
		std::vector<std::vector<std::string>> data;
		std::string line = "";

		while (getline(file, line)) {
			std::vector<std::string> tmp;
			tmp = this->split(line, ",");
			data.push_back(tmp);
		}
		file.close();
		return data;
	}

private:
	std::string fileName;
	std::string delimeter;

	/*
	* Function used to split each line by the delim
	*/
	std::vector<std::string> split(std::string target, std::string delim)
	{
		std::vector<std::string> v;
		if (!target.empty()) {
			size_t start = 0;
			do {
				size_t x = target.find(delim, start);
				// a check whether the target is found
				if (x == -1)
				{
					break;
				}
				std::string tmp = target.substr(start, x - start);
				v.push_back(tmp);
				start += delim.size() + tmp.size();
			} while (true);

			v.push_back(target.substr(start));
		}
		return v;
	}
};

// function used to compare two companies when sorting
bool comparison(Names& lhs, Names& rhs) {
	return lhs.distance < rhs.distance;
}

float euclideanDistance(Names& lhs, Names& test) 
{
	//Come up with fast square root function
}

int main()
{
    std::cin.get();
    return 0;
}