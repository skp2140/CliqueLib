/**
naive_bayes.h
Stan Peceny
skp2140
4/20/2017
*/

#ifndef __NAIVE_BAYES_H__
#define __NAIVE_BAYES_H__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <numeric>
#include <utility>

using namespace std;

class NaiveBayes
{
    public:

        //constructor
        NaiveBayes(vector<vector<float> > train_file);

        //separate the examples by class
        map<float, vector<vector<float> > > separate_each_class(); 

	//Mean
	float mean_average(vector<float> attributes);

	//Standard deviation
	float standard_deviation(vector<float> attributes);

        //Summary 
        vector<pair<float, float> > summary(vector<vector<float> > class_dataset);

	//Gaussian Probability Density function
	float probability(float mean_average, float standard_deviation, float attribute_value);

	//Probability of instance being member of class
	map<float, float> probabilities_class(vector<pair<float, float> > summary, vector<float> instance);

        //Train 
        map<float, vector<pair<float, float> > > train();

        //Classify
        float classify(vector<pair<float, float> > summary, vector<float> instance);
       
    private:

        vector<vector<float> > train_file;
};

#endif
