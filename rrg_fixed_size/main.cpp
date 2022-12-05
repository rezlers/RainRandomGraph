using namespace std;
#include <iostream>
#include <stdio.h>
#include <random>
#include <chrono>
#include <sys/resource.h>
#include <RainRandomGraphHeap.hpp>
#include <RainRandomGraphOpt.hpp>
#include <RRG005.hpp>
#include <RRG01.hpp>
#include <RRG02.hpp>
#include <RRG03.hpp>
#include <RRG04.hpp>
#include <RRG05.hpp>
#include <RRG06.hpp>
#include <RRG07.hpp>
#include <RRG08.hpp>
#include <RRG09.hpp>
#include <RRG095.hpp>
#include <fstream>

int main() {
	
//	std::cout << "FOR COMPILE REASONS, NOT NEEDED FOR THIS PROGRAMM";
	
	bool log = true;
	bool write_data = false;
	int iter_num = 1;
	ofstream myfile;
	std::chrono::duration<double> elapsed_seconds;
	
	auto t1 = std::chrono::steady_clock::now();
	
	auto t2 = std::chrono::steady_clock::now();
	
	// RRGHEAP
	if (log) {
		t1 = std::chrono::steady_clock::now();
	}
	
	if (write_data) {
		myfile.open("/drive/MyDrive/RainRandomGraph/moduled_data/rrg_data_095_1000.txt");
	}
	
	for (int i=0;i<iter_num;i++) {
		if (log) {
			std::cout << "Iteration: " << i + 1 << '\n';
		}
		
		RainRandomGraphHeap rrg_inst = RainRandomGraphHeap();
		
		int max_path = rrg_inst.getMaxPath();
		
		if (log) {
			std::cout << max_path << '\n';
		}
		
		if (write_data) {
			myfile << max_path << ',';
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
	
	
	// RRG095
	if (log) {
		t1 = std::chrono::steady_clock::now();
	}
	
	if (write_data) {
		myfile.open("/drive/MyDrive/RainRandomGraph/moduled_data/rrg_data_095_1000.txt");
	}
	
	for (int i=0;i<iter_num;i++) {
		if (log) {
			std::cout << "Iteration: " << i + 1 << '\n';
		}
		
		RRG095 rrg_inst = RRG095();
		
		int max_path = rrg_inst.getMaxPath();
		
		if (log) {
			std::cout << max_path << '\n';
		}
		
		if (write_data) {
			myfile << max_path << ',';
		}
	}
	
	if (log) {
		t2 = std::chrono::steady_clock::now();
		elapsed_seconds = t2-t1;
		std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n';
	}
	
	if (write_data) {
		myfile.close();
	}
	
	
	// RRG09
	if (log) {
		t1 = std::chrono::steady_clock::now();
	}
	
	if (write_data) {
		myfile.open("/drive/MyDrive/RainRandomGraph/moduled_data/rrg_data_09_1000.txt");
	}
	
	for (int i=0;i<iter_num;i++) {
		RRG09 rrg_inst = RRG09();
		int max_path = rrg_inst.getMaxPath();
		if (log) {
			std::cout << "Iteration: " << i + 1 << '\n' << max_path << '\n';
		}
		if (write_data) {
			myfile << max_path << ',';
		}
	}
	
	if (log) {
		t2 = std::chrono::steady_clock::now();
		elapsed_seconds = t2-t1;
		std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n';
	}
	
	if (write_data) {
		myfile.close();
	}
	
	
	// RRG08
	if (log) {
		t1 = std::chrono::steady_clock::now();
	}
	
	if (write_data) {
		myfile.open("/drive/MyDrive/RainRandomGraph/moduled_data/rrg_data_08_1000.txt");
	}
	
	for (int i=0;i<iter_num;i++) {
		RRG08 rrg_inst = RRG08();
		int max_path = rrg_inst.getMaxPath();
		if (log) {
			std::cout << "Iteration: " << i + 1 << '\n' << max_path << '\n';
		}
		if (write_data) {
			myfile << max_path << ',';
		}
	}
	
	if (log) {
		t2 = std::chrono::steady_clock::now();
		elapsed_seconds = t2-t1;
		std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n';
	}
	
	if (write_data) {
		myfile.close();
	}
	
	
	// RRG07
	if (log) {
		t1 = std::chrono::steady_clock::now();
	}
	
	if (write_data) {
		myfile.open("/drive/MyDrive/RainRandomGraph/moduled_data/rrg_data_07_1000.txt");
	}
	
	for (int i=0;i<iter_num;i++) {
		RRG07 rrg_inst = RRG07();
		int max_path = rrg_inst.getMaxPath();
		if (log) {
			std::cout << "Iteration: " << i + 1 << '\n' << max_path << '\n';
		}
		if (write_data) {
			myfile << max_path << ',';
		}
	}
	
	if (log) {
		t2 = std::chrono::steady_clock::now();
		elapsed_seconds = t2-t1;
		std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n';
	}
	
	if (write_data) {
		myfile.close();
	}
	
	
	// RRG06
	if (log) {
		t1 = std::chrono::steady_clock::now();
	}
	
	if (write_data) {
		myfile.open("/drive/MyDrive/RainRandomGraph/moduled_data/rrg_data_06_1000.txt");
	}
	
	for (int i=0;i<iter_num;i++) {
		RRG06 rrg_inst = RRG06();
		int max_path = rrg_inst.getMaxPath();
		if (log) {
			std::cout << "Iteration: " << i + 1 << '\n' << max_path << '\n';
		}
		if (write_data) {
			myfile << max_path << ',';
		}
	}
	
	if (log) {
		t2 = std::chrono::steady_clock::now();
		elapsed_seconds = t2-t1;
		std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n';
	}
	
	if (write_data) {
		myfile.close();
	}
	
	
	// RRG05
	if (log) {
		t1 = std::chrono::steady_clock::now();
	}
	
	if (write_data) {
		myfile.open("/drive/MyDrive/RainRandomGraph/moduled_data/rrg_data_05_1000.txt");
	}
	
	for (int i=0;i<iter_num;i++) {
		RRG05 rrg_inst = RRG05();
		int max_path = rrg_inst.getMaxPath();
		if (log) {
			std::cout << "Iteration: " << i + 1 << '\n' << max_path << '\n';
		}
		if (write_data) {
			myfile << max_path << ',';
		}
	}
	
	if (log) {
		t2 = std::chrono::steady_clock::now();
		elapsed_seconds = t2-t1;
		std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n';
	}
	
	if (write_data) {
		myfile.close();
	}
	
	
	// RRG04
	if (log) {
		t1 = std::chrono::steady_clock::now();
	}
	
	if (write_data) {
		myfile.open("/drive/MyDrive/RainRandomGraph/moduled_data/rrg_data_04_1000.txt");
	}
	
	for (int i=0;i<iter_num;i++) {
		RRG04 rrg_inst = RRG04();
		int max_path = rrg_inst.getMaxPath();
		if (log) {
			std::cout << "Iteration: " << i + 1 << '\n' << max_path << '\n';
		}
		if (write_data) {
			myfile << max_path << ',';
		}
	}
	
	if (log) {
		t2 = std::chrono::steady_clock::now();
		elapsed_seconds = t2-t1;
		std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n';
	}
	
	if (write_data) {
		myfile.close();
	}
	
	
	// RRG03
	if (log) {
		t1 = std::chrono::steady_clock::now();
	}
	
	if (write_data) {
		myfile.open("/drive/MyDrive/RainRandomGraph/moduled_data/rrg_data_03_1000.txt");
	}
	
	for (int i=0;i<iter_num;i++) {
		RRG03 rrg_inst = RRG03();
		int max_path = rrg_inst.getMaxPath();
		if (log) {
			std::cout << "Iteration: " << i + 1 << '\n' << max_path << '\n';
		}
		if (write_data) {
			myfile << max_path << ',';
		}
	}
	
	if (log) {
		t2 = std::chrono::steady_clock::now();
		elapsed_seconds = t2-t1;
		std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n';
	}
	
	if (write_data) {
		myfile.close();
	}
	
	
	// RRG02
	if (log) {
		t1 = std::chrono::steady_clock::now();
	}
	
	if (write_data) {
		myfile.open("/drive/MyDrive/RainRandomGraph/moduled_data/rrg_data_02_1000.txt");
	}
	
	for (int i=0;i<iter_num;i++) {
		RRG02 rrg_inst = RRG02();
		int max_path = rrg_inst.getMaxPath();
		if (log) {
			std::cout << "Iteration: " << i + 1 << '\n' << max_path << '\n';
		}
		if (write_data) {
			myfile << max_path << ',';
		}
	}
	
	if (log) {
		t2 = std::chrono::steady_clock::now();
		elapsed_seconds = t2-t1;
		std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n';
	}
	
	if (write_data) {
		myfile.close();
	}
	
	
	// RRG01
	if (log) {
		t1 = std::chrono::steady_clock::now();
	}
	
	if (write_data) {
		myfile.open("/drive/MyDrive/RainRandomGraph/moduled_data/rrg_data_01_1000.txt");
	}
	
	for (int i=0;i<iter_num;i++) {
		RRG01 rrg_inst = RRG01();
		int max_path = rrg_inst.getMaxPath();
		if (log) {
			std::cout << "Iteration: " << i + 1 << '\n' << max_path << '\n';
		}
		if (write_data) {
			myfile << max_path << ',';
		}
	}
	
	if (log) {
		t2 = std::chrono::steady_clock::now();
		elapsed_seconds = t2-t1;
		std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n';
	}
	
	if (write_data) {
		myfile.close();
	}
	
	
	// RRG005
	if (log) {
		t1 = std::chrono::steady_clock::now();
	}
	
	if (write_data) {
		myfile.open("/drive/MyDrive/RainRandomGraph/moduled_data/rrg_data_005_1000.txt");
	}
	
	for (int i=0;i<iter_num;i++) {
		RRG005 rrg_inst = RRG005();
		int max_path = rrg_inst.getMaxPath();
		if (log) {
			std::cout << "Iteration: " << i + 1 << '\n' << max_path << '\n';
		}
		if (write_data) {
			myfile << max_path << ',';
		}
	}
	
	if (log) {
		t2 = std::chrono::steady_clock::now();
		elapsed_seconds = t2-t1;
		std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n';
	}
	
	if (write_data) {
		myfile.close();
	}
	
};





