//============================================================================
// Name        : BaggingClassifier.cpp
// Author      : CliqueLib
// Version     :
// Copyright   : 
// Description : CliqueLib BaggingClassifier implementation
//============================================================================

#include <iostream>
#include <cmath>
#include "AdaBoost.h"
#include "KNN.h"
#include "SVM.h"
#include "Perceptron.h"
#include "logistic_regression.h"
#include "BaggingClassifier.h"

using namespace std;
using namespace arma;

template<Classifier C>
BaggingClassifier<C>::BaggingClassifier(uword n_estimators, uword max_samples) 
{
    this->n_estimators = n_estimators;
    this->max_samples = max_samples;
}

template<Classifier C>
void BaggingClassifier<C>::train(const mat& X, const colvec& Y, uword iter) 
{
    uword n = size(X, 0);

    for (uword i = 0; i < n_estimators; i++) 
    {
	uvec randIdx = randi<uvec>(max_samples, 1, distr_param(0, n-1));
	auto clfr = make_shared<C>();
	clfr->train(X.rows(randIdx), Y.rows(randIdx), iter);
	base_estimators.push_back(clfr);
    }
}

template<Classifier C>
void BaggingClassifier<C>::predict(const mat& testX, colvec& labels) 
{
    uword n = size(testX, 0);
    mat predMat;
    predMat.zeros(n, n_estimators);
    labels.zeros(n, 1);

    auto baseIter = base_estimators.begin();
    for (uword i = 0; baseIter != base_estimators.end(); baseIter++, i++) 
    {
	auto clfr = *baseIter;
	colvec preds;
	preds.zeros(n, 1);
	clfr->predict(testX, preds);
	predMat.col(i) = preds;
    }

    uvec idx = find(mean(predMat, 1) > 0);
    labels.fill(-1);
    labels.elem(idx).fill(1);
}

template class BaggingClassifier<Perceptron>;
template class BaggingClassifier<AdaBoost>;
template class BaggingClassifier<SVM>;
template class BaggingClassifier<KNN>;
template class BaggingClassifier<Logistic>;
