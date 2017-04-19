//============================================================================
// Name        : AdaBoost.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : CliqueLib AdaBoost implementation
//============================================================================

#include <iostream>
#include <armadillo>
#include <math.h>
#include "Stump.h"

using namespace std;
using namespace arma;

Stump* buildStump(const mat& X, const colvec& y, const colvec& weight) {
	uword d = size(X, 1);
	vector<Stump*> stumps;
	rowvec errors;
	errors.zeros(1, d);
	for (unsigned int i = 0; i < d; i++) {
		Stump* s = new Stump(i);
		stumps.push_back(s);
		s->buildOneDStump(X.col(i), y, weight);
		errors(0, i) = s->getError();
	}
	uword min_idx = index_min(errors);
	return stumps[min_idx];
}

class AdaBoost {
	vector<Stump*> weakClassifiers;
	vector<double> weights;
public:
	AdaBoost() {
	}

	void fit(const mat& X, const colvec& Y, uword iter) {
		uword n = size(X, 0); //no. of samples
		colvec sampleWts(n);
		double initWt = 1.0 / n;
		cout << "fit: initWt:" << initWt << endl;
		sampleWts.fill(initWt);
		cout << "fit: sampleWts:" << sampleWts << endl;

		for (uword i = 0; i < iter; i++) {
			Stump* clfr = buildStump(X, Y, sampleWts);
			double err = clfr->getError();
			double alpha = 0.5*log((1 - err) / err);

			//cout << "fit: :" << << endl;
			cout << "fit: err:" << err << endl;
			cout << "fit: alpha:" << alpha << endl;

			colvec preds(n);
			preds.zeros();
			clfr->predictStump(X, preds);

			sampleWts = sampleWts % exp(-alpha * Y % preds);
			cout << "fit: before sampleWts:" << sampleWts << endl;
			sampleWts = sampleWts / accu(sampleWts);
			cout << "fit: after sampleWts:" << sampleWts << endl;

			weakClassifiers.push_back(clfr);
			weights.push_back(alpha);
		}
	}

	void predict(const mat& testX, colvec& preds) {
		uword n = size(testX, 0); //no. of samples
		colvec labels;
		colvec sum;
		sum.zeros(n, 1);
		labels.zeros(n, 1);
		preds.zeros(n, 1);

		auto weakIter = weakClassifiers.begin();
		auto wtIter = weights.begin();
		for (; weakIter != weakClassifiers.end(); weakIter++, wtIter++) {
			Stump* clfr = *weakIter;
			double wt = *wtIter;

			clfr->predictStump(testX, labels);
			sum += wt*labels;
		}
		preds.fill(-1);
		uvec idx = find(sum > 0);
		preds.elem(idx).fill(1);
	}
};

int main()
{
	//cout << "it begins !!!" << endl;
	mat x;
	x << 1 << 2 << endr
		<< 2 << 4 << endr
		<< 3 << 6 << endr
		<< 4 << 8 << endr
		<< 1 << 10 << endr;

	mat xTest;
	xTest << 2 << 1 << 3 << 4 << endr
		<< 1 << 2 << 3 << 4 << endr
		<< 3 << 2 << 3 << 4 << endr;

	//cout << "size(x)" << arma::size(x) << " x.size()" << x.size() << endl;
	uword N = size(x, 0);
	colvec w;
	w.ones(N, 1);
	w.fill(0.2);

	colvec y;
	y << 1.0 << endr
		<< -1.0 << endr
		<< 1.0 << endr
		<< -1.0 << endr
		<< -1.0 << endr;

	auto z = x.col(0) % w;
	//cout << "z:" << z << endl;

	//cout << "x:" << x << endl;
	//cout << "y:" << y << endl;

	vector<double> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);

	mat a(v);
	a.reshape(3, 2);
	a = a.t();

	//cout << "a:" << a << endl;
	//cout << "size(a)" << arma::size(a) << " size(a, 0):" << size(a, 0) << " size(a, 1):" << size(a, 1) << endl;

	//Stump* s = new Stump(0);
	//double error, thres;
	//s->calculateThreshold(x.col(1), y, w, "lesser", error, thres);
	//s->buildOneDStump(x.col(1), y, w);
	//AdaBoost ad;
	//Stump* s = buildStump(x, y, w);
	//cout << s;

	
	AdaBoost ad;
	uword iter = 2;
	ad.fit(x, y, iter);
	
	colvec labels(arma::size(y));
	//cout << "here!" << endl;

	ad.predict(x, labels);

	//s->predictStump(x, labels);
	cout << "labels:" << labels;

	getchar();
	return 0;
}