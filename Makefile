# CliqueLib
# Stanislav Peceny

CC = g++
CXX = g++
INCLUDES = -I ./armadillo-7.800.2/include/ -I ./source/Commons/ -I ./tests -I./source  -I ./source/Preprocessing -I ./source/KNN -I ./source/KNNStd -I ./source/LogisticRegression -I ./source/LogisticRegressionStd -I ./source/AdaBoost -I ./source/SVM -I ./source/BaggingClassifier -I ./source/VotingClassifier -I ./source/Perceptron

CXXFLAGS = -g -Wall --std=c++1z -fconcepts -o prog -O2 -DARMA_DONT_USE_WRAPPER -lblas -llapack -larmadillo $(INCLUDES) 
LDFLAGS = -L ./armadillo-7.800.2/include/armadillo
LDLIBS  =

main: tests/test_read_csv.o tests/test_split_test_train_dataset.o tests/test_knn.o tests/test_knn_std.o tests/test_logistic_regression.o tests/test_logistic_regression_std.o tests/test_adaboost.o tests/test_svm.o tests/test_perceptron.o source/Preprocessing/preprocessing_functions.o source/KNN/KNN.o source/KNNStd/knnstd.o source/LogisticRegression/logistic_regression.o source/LogisticRegressionStd/logistic_regression_std.o source/AdaBoost/Stump.o source/AdaBoost/AdaBoost.o source/SVM/SVM.o source/BaggingClassifier/BaggingClassifier.o source/VotingClassifier/VotingClassifier.o source/VotingClassifier/VotingClassifier.o source/Perceptron/Perceptron.o 

main.o: tests/tests.h

tests/test_read_csv.o: tests/tests.h

tests/test_split_test_train_dataset.o: tests/tests.h

tests/test_knn.o: tests/tests.h source/KNN/KNN.h

tests/test_knn_std.o: tests/tests.h source/KNNStd/knnstd.cpp

tests/test_logistic_regression.o: tests/tests.h source/LogisticRegression/logistic_regression.h

tests/test_logistic_regression_std.o: tests/tests.h source/LogisticRegressionStd/logistic_regression_std.h

tests/test_adaboost.o: tests/tests.h source/AdaBoost/AdaBoost.h

tests/test_svm.o: tests/tests.h source/SVM/SVM.h

tests/test_perceptron.o: tests/tests.h source/Perceptron/Perceptron.h 

tests/test_usecase1.o: tests/tests.h source/AdaBoost/AdaBoost.h

tests/test_usecase2.o: tests/tests.h source/AdaBoost/AdaBoost.h

source/Prepocessing/preprocessing_functions.o: source/Preprocessing/preprocessing_functions.h

source/KNN/KNN.o: source/KNN/KNN.h

source/KNNStd/knnstd.o: source/KNNStd/knnstd.h

source/LogisticRegression/logistic_regression.o: source/LogisticRegression/logistic_regression.h

source/LogisticRegressionStd/logistic_regression_std.o: source/LogisticRegressionStd/logistic_regression_std.h

source/AdaBoost/Stump.o: source/AdaBoost/Stump.h

source/SVM/SVM.o: source/SVM/SVM.h

source/AdaBoost/AdaBoost.o: source/AdaBoost/AdaBoost.h

source/BaggingClassifier/BaggingClassifier.o: source/BaggingClassifier/BaggingClassifier.h

source/VotingClassifier/VotingClassifier.o: source/VotingClassifier/VotingClassifier.h

source/Perceptron/Perceptron.o : source/Perceptron/Perceptron.h

.PHONY: clean
clean:
	rm -f *.o *~ tests/*.o  tests/*~ source/*.o  source/*~ source/Preprocessing/*.o source/Preprocessing/*~ source/KNN/*.o source/KNN/*~ source/KNNStd/*.o source/KNNStd/*~ source/LogisticRegression/*.o source/LogisticRegression/*~ source/LogisticRegressionStd/*.o source/LogisticRegressionStd/*~ source/AdaBoost/*.o source/AdaBoost/*~ source/BaggingClassifier/*.o source/BaggingClassifier/*~ source/VotingClassifier/*~ source/VotingClassifier/*.o source/SVM/*.o source/SVM/*~ source/Perceptron/*.o source/Perceptron/*~ a.out core main

.PHONY: all
	all: clean main

.PHONY: valgrind
valgrind: main
	valgrind -v --num-callers=20 --leak-check=yes --leak-resolution=high --show-reachable=yes ./main
