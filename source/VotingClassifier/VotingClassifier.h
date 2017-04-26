//============================================================================
// Name        : VotingClassifier.h
// Author      : CliqueLib
// Version     : 
// Copyright   : 
// Description : CliqueLib VotingClassifier definition
//============================================================================

#ifndef __VOTINGCLASSIFIER_H__
#define __VOTINGCLASSIFIER_H__

#pragma once
#include <armadillo>
#include "BaseClassifier.h"

class VotingClassifier 
{
    private:
	std::vector<BaseClassifier*> base_estimators;

    public:
	VotingClassifier() {}
	void train(const arma::mat&, const arma::colvec&, arma::uword);
	void predict(const arma::mat&, arma::colvec&);
        void addClassifier(BaseClassifier*);
};

#endif
