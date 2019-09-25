TESTCASE_DIR=/home/rajz/Dropbox/Rajesh-Rupesh/Implementation/t1
ANS_DIR=/home/rajz/Dropbox/Rajesh-Rupesh/Implementation/t1
all:
	g++ -Wall -o "stp-validate" "stp-validate.cpp" -std=c++14 

test: all
	$(foreach file, $(wildcard $(TESTCASE_DIR)/*.gr), echo $(file);)
