#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>

#define MAX_PROBABILTY 0.014516787
#define MIN_PROBABILTY 0.00000000273674
#define MAX_COUNT 5304407
#define MIN_COUNT 1

class Names 
{
    public:
        Names() {}
        Names(std::string name, char gender, double count, double probability)
        {
            this->name= name;
            this->gender = gender;
            this->count = count;
            this->probability = probability;
        }
        std::string name;
        char gender;
        double count;
        double probability;
        ~Names() {}
};

class Training_Data 
{
    public:
        Training_Data() {}
        Training_Data(std::string name, double count, double probability)
        {
            this->name= name;
            this->count = count;
            this->probability = probability;
        }
        std::string name;
        double count;
        double probability;
        ~Training_Data() {}
};

void read_data_to_file(std::vector<Names>& dataset, Names& data, const char* filename)
{
    std::ifstream csv_file(filename);
    std::string line;
    int i = 0;
    std::cout << std::fixed << "\n" << std::setw(10) << "Instance" << "\t | \t" << std::setprecision(30) << std::setw(20) << "Name" << "\t | \t" << "Gender" << "\t | \t" << "Count" << std::setw(35) << "\t | \t" << "Probrability" << "\n";
    while(getline(csv_file, line))
    {
        std::stringstream ss(line);
        
        std::string char_to_string = std::string(1, data.gender);
        std::string double_to_string;
        std::string int_to_string;

        getline(ss, data.name, ',');
        getline(ss, char_to_string, ',');
        getline(ss, int_to_string, ',');
        getline(ss, double_to_string, '\n'); 

        data.gender = char_to_string[0];
        data.count = stod(int_to_string);
        data.probability = stod(double_to_string);
        
        //Normalize data
        data.count = (data.count - MIN_COUNT) / (MAX_COUNT - MIN_COUNT);
        data.probability = (data.probability - MIN_PROBABILTY) / (MAX_PROBABILTY - MIN_PROBABILTY);

        dataset.push_back(data);
        std::cout << std::fixed << std::setw(10) << (i + 1) << "\t | \t" << std::setprecision(30) << std::setw(20) << dataset[i].name << "\t | \t" << dataset[i].gender << "\t | \t" << dataset[i].count << "\t | \t" << dataset[i].probability << "\n";
        i++;
    }
    csv_file.close();
}

int get_index(std::vector<double> indices, double value)
{
    int index;
    std::vector<double>::iterator it;
    it = std::find (indices.begin(), indices.end(), value);
    if(it != indices.end())
    {
        index = it - indices.begin();
    }
    
    return index;
}

//Probability(y) vs Count(x)
std::vector<int> k_nearest_neighbor(std::vector<Names> dataset, Training_Data& data, int k)
{
    data.count = (data.count - MIN_COUNT) / (MAX_COUNT - MIN_COUNT);
    data.probability = (data.probability - MIN_PROBABILTY) / (MAX_PROBABILTY - MIN_PROBABILTY);
    
    std::vector<double> nearest(k);
    std::vector<double> distances;
    std::vector<int> indices;
    
    double euclidean_distance;

    for(int i = 0; i < dataset.size(); i++)
    {
        euclidean_distance = sqrtf( 
            ( (dataset[i].probability - data.probability) * (dataset[i].probability - data.probability) ) 
            + ( (dataset[i].count - data.count) * (dataset[i].count - data.count) ) );
        distances.push_back(euclidean_distance);
        if(i < k)
        {   
            nearest[i] = euclidean_distance;
        }
        else
        {
            sort(nearest.begin(),nearest.end());
            if(euclidean_distance < nearest[k - 1])
            {   
                nearest[k - 1] = euclidean_distance;
            }
        }
    }

    for(int i = 0; i < nearest.size(); i++)
    {
        int index = get_index(distances, nearest[i]);
        indices.push_back(index);
    }
    std::cout << "\n" << data.name << "'s " << k << " nearest neighbors are:\n\n";
    for(int i = 0; i < nearest.size(); i++)
    {
        std::cout << dataset[indices[i]].name << " with distance: " << nearest[i] << "\n";
    }
    return indices;
}

void classify(std::vector<int> knn, std::vector<Names> dataset, Training_Data& values)
{
    int counter = 0;
    for(int i = 0; i < knn.size(); i++)
    {
        std::cout << "\n" << dataset[knn[i]].name << " is of gender: " << dataset[knn[i]].gender;
        if(dataset[knn[i]].gender == 'M')
        {
            counter++;
        }
        else
        {
            counter--;
        }
    }

    if(counter > 0)
    {
        std::cout << "\n\nTherefore, " << values.name << " is of gender: ";
        std::cout << 'M' << "\n\n";
    }
    else
    {
        std::cout << "\n\nTherefore, " << values.name << " is of gender: ";
        std::cout << 'F' << "\n\n";
    }
}

int main()
{
    int k;
    Names data;
    std::vector<Names> dataset;
    //Training_Data values("Kevin", 1234567, 0.012345);
    Training_Data name_data;
    std::cout << "\nEnter (Name, Count, Probability, k):\n";
    std::cin >> name_data.name >> name_data.count >> name_data.probability >> k;
    //read_data_to_file(dataset, data, "test.csv");
    //read_data_to_file(dataset, data, "notbsing.csv");
    read_data_to_file(dataset, data, "name_gender_dataset.csv");
    //classify(k_nearest_neighbor(dataset, values, 3), dataset, values);
    //classify(k_nearest_neighbor(dataset, values, 5), dataset, values);
    //classify(k_nearest_neighbor(dataset, values, 15), dataset, values);
    classify(k_nearest_neighbor(dataset, name_data, k), dataset, name_data);
    return 0;
}