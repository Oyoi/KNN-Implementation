#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

#define MAX_PROBABILTY 0.014516787
#define MIN_PROBABILTY 0.00000000273674
#define MAX_COUNT 5304407
#define MIN_COUNT 1

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

        int count;
        float probability;
        std::string name;
        char gender;

};

void read_csv_file(std::vector<Names>& dataset, std::string filename)
{
    std::ifstream csv_file;
    csv_file.open(filename);

    while(csv_file.good())
    {
        std::string line;
        getline(csv_file, line, ',');
        int i = 0;
        std::cin >> dataset[i].name >> dataset[i].gender >> dataset[i].count >> dataset[i].probability; 
        i++;
    }

}

void normalize_count(std::vector<Names>& dataset) 
{
    for(int i = 0; i < dataset.size(); i++)
    {
        dataset[i].count = (dataset[i].count - MIN_COUNT) / (MAX_COUNT - MIN_COUNT);
    }
}

void normalize_probability(std::vector<Names>& dataset) 
{
    for(int i = 0; i < dataset.size(); i++)
    {
        dataset[i].probability = (dataset[i].probability - MIN_PROBABILTY) / (MAX_PROBABILTY - MIN_PROBABILTY);
    }
}

float euclidean_distance(float p1, float p2)
{
    float distance;
    distance = sqrtf( (p2 * p2) - (p1 * p1) );
    return distance;
}

int main()
{
    std::vector<Names> dataset;
    Names data1(69, 0.001, "SFDGFNP", 'M');
    Names data2(69420, 0.69, "Jimbo", 'M');
    dataset = {data1, data2};

    std::cin.get();
    return 0;
}