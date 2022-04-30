using namespace std;
#include <iostream>
#include <stdio.h>
#include <random>
#include <chrono>
#include <sys/resource.h>
#include <RainRandomGraphOpt.hpp>
#include <RainRandomGraphHeap.hpp>
#include <fstream>

int main() {
	
	bool log = true;
	bool write_data = false;
	int iter_num = 100;
	ofstream myfile;
	std::chrono::duration<double> elapsed_seconds;
	
	auto t1 = std::chrono::steady_clock::now();
//	if (log) {
//		std::cout << "RainRandomGraph test:\n";
//	}
//	
//	if (write_data) {
//		myfile.open ("/Users/aleksandrrezler/Downloads/rrg_moduled_data/rrg_data_05_100000.txt");
//	}
//	
//	for (int i=0;i<1;i++) {
//		RainRandomGraphOpt rrg = RainRandomGraphOpt();
//		int max_path = rrg.getMaxPath();
//		if (log) {
//			std::cout << "Iteration: " << i + 1 << '\n' << max_path << '\n';
//		}
//		if (write_data) {
//			myfile << max_path << ',';
//		}
//	}
//	
//	if (write_data) {
//		myfile.close();
//	}
	
	auto t2 = std::chrono::steady_clock::now();
//	if (log) {
//		elapsed_seconds = t2-t1;
//		std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n' << '\n';
//	}
	
	if (log) {
		t1 = std::chrono::steady_clock::now();
	}
	
	if (write_data) {
		myfile.open("/Users/aleksandrrezler/Downloads/rrg_moduled_data/rrg_data_05_100000.txt");
	}
	
	for (int i=0;i<iter_num;i++) {
		RainRandomGraphHeap rrg_heap = RainRandomGraphHeap();
		int max_path_heap = rrg_heap.getMaxPath();
		if (log) {
			std::cout << "Iteration: " << i + 1 << '\n' << max_path_heap << '\n';
		}
		if (write_data) {
			myfile << max_path_heap << ',';
		}
	}
	
	if (log) {
		t2 = std::chrono::steady_clock::now();
		elapsed_seconds = t2-t1;
		std::cout << "Performance on heap result: " << elapsed_seconds.count() << '\n';
	}
	
	if (write_data) {
		myfile.close();
	}
	
};





