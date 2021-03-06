//============================================================================
// Name        : knnstd.h
// Author      : CliqueLib
// Version     :
// Copyright   : 
// Description : CliqueLib Knnstd implementation
//============================================================================

#include "knnstd.h"

//Constructor
KNNStd::KNNStd(vector<vector<float> > train_file, int k)
{
    this->k = k;
    this->train_file = train_file;
}

// calculate Euclidean Distance
float KNNStd::euclideanDistance (int num_attributes, vector<float> instance1, vector<float> instance2)
{
    //Calculate Euclidean Distance to each example
    float sum = 0.0;
    for (int j = 0; j < num_attributes; j++)
    {
        sum += pow(instance1[j] - instance2[j], 2);
    }
    return pow(sum, 0.5);
}



//Train
//Although KNNStd has no model, this function was created for consistency with other algorithms
//Easier for Machine Learning beginners 
vector<vector<float> > KNNStd::train()
{
    return train_file;
}


bool pairCompare(const pair<float, vector<float>>& firstEl, const std::pair<float, vector<float>>& secondEl) 
{
    return firstEl.first < secondEl.first;
}


//find K neighbors
vector<vector<float> > KNNStd::findNeighbors(vector<float> instance)
{
    //store the examples with their distances in a vector of tuples
    vector<pair<float, vector<float>>> distances;
    //iterate over all examples
    for (unsigned int i = 0; i < train_file.size(); i++)
    { 
	float sum = euclideanDistance(instance.size() - 1, instance, train_file[i]);
        distances.push_back(make_pair(sum, train_file[i]));
    }
    sort(distances.begin(), distances.end(), pairCompare);

    vector<vector<float> > k_neighbors;
    for (int i = 0; i < this->k; i++)
    {
        k_neighbors.push_back(distances[i].second);  
    } 
    return k_neighbors;   
}

//determine class
float KNNStd::findClass(vector<vector<float> > k_neighbors)
{
    //which class occurs most times
    map<float, int> classification;
    //class is last attribute for each neighbor
    for (unsigned int i = 0; i < k_neighbors.size(); i++) 
    {
        float neighbor_label = k_neighbors[i][k_neighbors[i].size() - 1];
        if (classification.find(neighbor_label) != classification.end())        
            classification[neighbor_label] +=1;        
        else   
            classification[neighbor_label] = 1;
    }

    //set to minimum
    int largest_val = numeric_limits<int>::min();
    float largest_class = numeric_limits<float>::min();
    for (unsigned int i = 0; i < k_neighbors.size(); i++)
    {
        if (classification[k_neighbors[i][k_neighbors[i].size() - 1]] > largest_val)
        { 
            largest_val = classification[k_neighbors[i][k_neighbors[i].size() - 1]];
            largest_class = k_neighbors[i][k_neighbors[i].size() - 1];
        }
    }
    return largest_class;
}

//Predict a single label
float KNNStd::predict_label(vector<float> instance)
{
    int num_attributes = instance.size();
    if ((unsigned) this->k > train_file.size())
    {
        cerr << "K must be smaller than number of examples";
        return 0.0;
    }
    if (train_file.size() == 0)
    {
        cerr << "Training file has 0 examples";
        return 0.0;
    }
    if ((unsigned int)num_attributes != this->train_file[0].size() - 1)
    {
        cerr << "Wrong number of attributes for the example to be classified";
        return 0.0;
    }

    //find k Nearest Neighbors
    vector<vector<float> > k_neighbors = findNeighbors(instance);

    //select the prevalent class from the neighbors
    return findClass(k_neighbors);
}

//Predict multiple labels
vector<float> KNNStd::predict(vector<vector<float> > instances)
{
    vector<float> column_vector;   
    for (auto& instance : instances)
    {
        float predicted_label = predict_label(instance);
        column_vector.push_back(predicted_label);
    }
    return column_vector;
}

