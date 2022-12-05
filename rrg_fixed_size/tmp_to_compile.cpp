using namespace std;
#include <iostream>
#include <stdio.h>
#include <random>
#include <chrono>
#include <sys/resource.h>
#include <fstream>

class RRG095 {
private:
	static const int graphTime = 100;
	static const int bound = 100;
	static const double p = 0.95;
	int H[graphTime][2*bound+1];
	char edges[graphTime][2*bound+1];
	bool clients[graphTime][2*bound+1];
	
	int calculateMaxPath(int server_, int time_) {			
		int server = server_;
		int time = time_;
		int maxEdgePathD = 0;
		int maxEdgePathLU = 0;
		int maxEdgePathLD = 0;
		int maxEdgePathRD = 0;
		int maxEdgePathRU = 0;
		
//		iter_num++;
		
		if (H[time][server] != -1) {
			return H[time][server];
		}
		if (time > 0) {
			if (clients[time][server]) {
				maxEdgePathD = calculateMaxPath(server, time-1) + 1;
				
				if ( (server > 0) && (edges[time][server-1] == '0') ) {
					maxEdgePathLU = calculateMaxPath(server-1, time) + 1;
				}
				if ( server > 0 ) {
					if ( (clients[time][server]) ) {
						maxEdgePathLD = calculateMaxPath(server-1, time-1) + 1;
					} else {
						maxEdgePathLD = calculateMaxPath(server-1, time-1);
					}
				}
				if ( server < 2*bound ) {
					if ( (clients[time][server]) ) {
						maxEdgePathRD = calculateMaxPath(server+1, time-1) + 1;
					} else {
						maxEdgePathRD = calculateMaxPath(server+1, time-1);
					}
				}
				if (edges[time][server] == '1') {
					maxEdgePathRU = calculateMaxPath(server+1, time) + 1;
				}
			} else {
				maxEdgePathD = calculateMaxPath(server, time-1);
			}
			
			int pathLengths[5] = {maxEdgePathD, maxEdgePathLU, maxEdgePathLD, maxEdgePathRD, maxEdgePathRU};
			int edgeMaxPath = max_(pathLengths);
			H[time][server] = edgeMaxPath;
			return edgeMaxPath;
		} else {
			if (clients[time][server]) {
				int maxEdgePathLU = 0;
				int maxEdgePathRU = 0;
				if ( (server > 0) && (edges[time][server-1] == '0') ) {
					maxEdgePathLU = calculateMaxPath(server-1, time) + 1;
				}
				if ( edges[time][server] == '1' ) {
					maxEdgePathRU = calculateMaxPath(server+1, time) + 1;
				}
				int edgeMaxPath = std::max(maxEdgePathLU, maxEdgePathRU);
				if (edgeMaxPath > 0) {
					H[time][server] = edgeMaxPath;
					return edgeMaxPath;
				}
				H[time][server] = 1;
				return 1;
			}
			H[time][server] = 0;
			return 0;
		}
	}
public:
	bool log = false;
	
	RRG095() {
		auto t1 = std::chrono::steady_clock::now();
		if (log) {
			std::cout << "Start initialization:\n";
		}
		
		std::random_device rd;
		std::mt19937 gen(rd());
		std::bernoulli_distribution d(p);
		for (int time_ = 0; time_ < graphTime; time_++) {
			for(int server_ = 0; server_ < 2*bound+1; server_++) {
				H[time_][server_] = -1;
				clients[time_][server_] = d(gen);
			}
		}
		for (int time_ = 0; time_ < graphTime; time_++) {
			for(int server_ = 0; server_ < 2*bound+1; server_++) {
				if ( (server_ < 2*bound) && (clients[time_][server_]) && (clients[time_][server_+1]) ) {
					if (d(gen)) {
						edges[time_][server_] = '1';
					} else {
						edges[time_][server_] = '0';
					}
				} else {
					edges[time_][server_] = '2';
				}
			}
		}
		
		auto t2 = std::chrono::steady_clock::now();
		if (log) {
			std::chrono::duration<double> elapsed_seconds = t2-t1;
			std::cout << "Initialization performance result: " << elapsed_seconds.count() << '\n';
		}
	}
	
	~RRG095() {}

	int getMaxPath() {
		auto t1 = std::chrono::steady_clock::now();
		if (log) {
			std::cout << "Start calculating:\n";
		}
		
		int maxPath = calculateMaxPath(bound, graphTime-1);
		
		auto t2 = std::chrono::steady_clock::now();
		if (log) {
			std::chrono::duration<double> elapsed_seconds = t2-t1;
			std::cout << "Calculation performance result: " << elapsed_seconds.count() << '\n';		
		}
		
		return maxPath;
	}
};

int main() {
	
//	std::cout << "FOR COMPILE REASONS, NOT NEEDED FOR THIS PROGRAMM";
	
	string folder_to_store_data = "moduled_data";

	bool log = true;
	bool write_data = false;
	int iter_num = 1;
	ofstream myfile;
	std::chrono::duration<double> elapsed_seconds;
	
	auto t1 = std::chrono::steady_clock::now();
	
	auto t2 = std::chrono::steady_clock::now();
	
	// RRG095
	if (log) {
		t1 = std::chrono::steady_clock::now();
	}
	
	if (write_data) {
		myfile.open(folder_to_store_data + "/rrg_data_095_1000.txt");
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
	
	
	// // RRG09
	// if (log) {
	// 	t1 = std::chrono::steady_clock::now();
	// }
	
	// if (write_data) {
	// 	myfile.open(folder_to_store_data + "/rrg_data_09_1000.txt");
	// }
	
	// for (int i=0;i<iter_num;i++) {
	// 	RRG09 rrg_inst = RRG09();
	// 	int max_path = rrg_inst.getMaxPath();
	// 	if (log) {
	// 		std::cout << "Iteration: " << i + 1 << '\n' << max_path << '\n';
	// 	}
	// 	if (write_data) {
	// 		myfile << max_path << ',';
	// 	}
	// }
	
	// if (log) {
	// 	t2 = std::chrono::steady_clock::now();
	// 	elapsed_seconds = t2-t1;
	// 	std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n';
	// }
	
	// if (write_data) {
	// 	myfile.close();
	// }
	
	
	// // RRG08
	// if (log) {
	// 	t1 = std::chrono::steady_clock::now();
	// }
	
	// if (write_data) {
	// 	myfile.open(folder_to_store_data + "/rrg_data_08_1000.txt");
	// }
	
	// for (int i=0;i<iter_num;i++) {
	// 	RRG08 rrg_inst = RRG08();
	// 	int max_path = rrg_inst.getMaxPath();
	// 	if (log) {
	// 		std::cout << "Iteration: " << i + 1 << '\n' << max_path << '\n';
	// 	}
	// 	if (write_data) {
	// 		myfile << max_path << ',';
	// 	}
	// }
	
	// if (log) {
	// 	t2 = std::chrono::steady_clock::now();
	// 	elapsed_seconds = t2-t1;
	// 	std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n';
	// }
	
	// if (write_data) {
	// 	myfile.close();
	// }
	
	
	// // RRG07
	// if (log) {
	// 	t1 = std::chrono::steady_clock::now();
	// }
	
	// if (write_data) {
	// 	myfile.open(folder_to_store_data + "/rrg_data_07_1000.txt");
	// }
	
	// for (int i=0;i<iter_num;i++) {
	// 	RRG07 rrg_inst = RRG07();
	// 	int max_path = rrg_inst.getMaxPath();
	// 	if (log) {
	// 		std::cout << "Iteration: " << i + 1 << '\n' << max_path << '\n';
	// 	}
	// 	if (write_data) {
	// 		myfile << max_path << ',';
	// 	}
	// }
	
	// if (log) {
	// 	t2 = std::chrono::steady_clock::now();
	// 	elapsed_seconds = t2-t1;
	// 	std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n';
	// }
	
	// if (write_data) {
	// 	myfile.close();
	// }
	
	
	// // RRG06
	// if (log) {
	// 	t1 = std::chrono::steady_clock::now();
	// }
	
	// if (write_data) {
	// 	myfile.open(folder_to_store_data + "/rrg_data_06_1000.txt");
	// }
	
	// for (int i=0;i<iter_num;i++) {
	// 	RRG06 rrg_inst = RRG06();
	// 	int max_path = rrg_inst.getMaxPath();
	// 	if (log) {
	// 		std::cout << "Iteration: " << i + 1 << '\n' << max_path << '\n';
	// 	}
	// 	if (write_data) {
	// 		myfile << max_path << ',';
	// 	}
	// }
	
	// if (log) {
	// 	t2 = std::chrono::steady_clock::now();
	// 	elapsed_seconds = t2-t1;
	// 	std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n';
	// }
	
	// if (write_data) {
	// 	myfile.close();
	// }
	
	
	// // RRG05
	// if (log) {
	// 	t1 = std::chrono::steady_clock::now();
	// }
	
	// if (write_data) {
	// 	myfile.open(folder_to_store_data + "/rrg_data_05_1000.txt");
	// }
	
	// for (int i=0;i<iter_num;i++) {
	// 	RRG05 rrg_inst = RRG05();
	// 	int max_path = rrg_inst.getMaxPath();
	// 	if (log) {
	// 		std::cout << "Iteration: " << i + 1 << '\n' << max_path << '\n';
	// 	}
	// 	if (write_data) {
	// 		myfile << max_path << ',';
	// 	}
	// }
	
	// if (log) {
	// 	t2 = std::chrono::steady_clock::now();
	// 	elapsed_seconds = t2-t1;
	// 	std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n';
	// }
	
	// if (write_data) {
	// 	myfile.close();
	// }
	
	
	// // RRG04
	// if (log) {
	// 	t1 = std::chrono::steady_clock::now();
	// }
	
	// if (write_data) {
	// 	myfile.open(folder_to_store_data + "/rrg_data_04_1000.txt");
	// }
	
	// for (int i=0;i<iter_num;i++) {
	// 	RRG04 rrg_inst = RRG04();
	// 	int max_path = rrg_inst.getMaxPath();
	// 	if (log) {
	// 		std::cout << "Iteration: " << i + 1 << '\n' << max_path << '\n';
	// 	}
	// 	if (write_data) {
	// 		myfile << max_path << ',';
	// 	}
	// }
	
	// if (log) {
	// 	t2 = std::chrono::steady_clock::now();
	// 	elapsed_seconds = t2-t1;
	// 	std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n';
	// }
	
	// if (write_data) {
	// 	myfile.close();
	// }
	
	
	// // RRG03
	// if (log) {
	// 	t1 = std::chrono::steady_clock::now();
	// }
	
	// if (write_data) {
	// 	myfile.open(folder_to_store_data + "/rrg_data_03_1000.txt");
	// }
	
	// for (int i=0;i<iter_num;i++) {
	// 	RRG03 rrg_inst = RRG03();
	// 	int max_path = rrg_inst.getMaxPath();
	// 	if (log) {
	// 		std::cout << "Iteration: " << i + 1 << '\n' << max_path << '\n';
	// 	}
	// 	if (write_data) {
	// 		myfile << max_path << ',';
	// 	}
	// }
	
	// if (log) {
	// 	t2 = std::chrono::steady_clock::now();
	// 	elapsed_seconds = t2-t1;
	// 	std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n';
	// }
	
	// if (write_data) {
	// 	myfile.close();
	// }
	
	
	// // RRG02
	// if (log) {
	// 	t1 = std::chrono::steady_clock::now();
	// }
	
	// if (write_data) {
	// 	myfile.open(folder_to_store_data + "/rrg_data_02_1000.txt");
	// }
	
	// for (int i=0;i<iter_num;i++) {
	// 	RRG02 rrg_inst = RRG02();
	// 	int max_path = rrg_inst.getMaxPath();
	// 	if (log) {
	// 		std::cout << "Iteration: " << i + 1 << '\n' << max_path << '\n';
	// 	}
	// 	if (write_data) {
	// 		myfile << max_path << ',';
	// 	}
	// }
	
	// if (log) {
	// 	t2 = std::chrono::steady_clock::now();
	// 	elapsed_seconds = t2-t1;
	// 	std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n';
	// }
	
	// if (write_data) {
	// 	myfile.close();
	// }
	
	
	// // RRG01
	// if (log) {
	// 	t1 = std::chrono::steady_clock::now();
	// }
	
	// if (write_data) {
	// 	myfile.open(folder_to_store_data + "/rrg_data_01_1000.txt");
	// }
	
	// for (int i=0;i<iter_num;i++) {
	// 	RRG01 rrg_inst = RRG01();
	// 	int max_path = rrg_inst.getMaxPath();
	// 	if (log) {
	// 		std::cout << "Iteration: " << i + 1 << '\n' << max_path << '\n';
	// 	}
	// 	if (write_data) {
	// 		myfile << max_path << ',';
	// 	}
	// }
	
	// if (log) {
	// 	t2 = std::chrono::steady_clock::now();
	// 	elapsed_seconds = t2-t1;
	// 	std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n';
	// }
	
	// if (write_data) {
	// 	myfile.close();
	// }
	
	
	// // RRG005
	// if (log) {
	// 	t1 = std::chrono::steady_clock::now();
	// }
	
	// if (write_data) {
	// 	myfile.open(folder_to_store_data + "/rrg_data_005_1000.txt");
	// }
	
	// for (int i=0;i<iter_num;i++) {
	// 	RRG005 rrg_inst = RRG005();
	// 	int max_path = rrg_inst.getMaxPath();
	// 	if (log) {
	// 		std::cout << "Iteration: " << i + 1 << '\n' << max_path << '\n';
	// 	}
	// 	if (write_data) {
	// 		myfile << max_path << ',';
	// 	}
	// }
	
	// if (log) {
	// 	t2 = std::chrono::steady_clock::now();
	// 	elapsed_seconds = t2-t1;
	// 	std::cout << "Performance on stack result: " << elapsed_seconds.count() << '\n';
	// }
	
	// if (write_data) {
	// 	myfile.close();
	// }
	
};





