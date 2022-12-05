#ifndef RAINRANDOMGRAPHHEAP_HPP
#define RAINRANDOMGRAPHHEAP_HPP

int max_h(int arr[5]) {
	int currentMax = arr[0];
	for (int i=1;i<5;i++) {
		if (currentMax < arr[i]) {
			currentMax = arr[i];
		}
	}
	return currentMax;
}

class RainRandomGraphHeap {
private:
	static const int graphTime = 5000;
	static const int bound = 1000;
	static const double p = 0.95;
	int* H = new int[graphTime*(2*bound+1)];
	char* edges = new char[graphTime*(2*bound+1)];
	bool* clients = new bool[graphTime*(2*bound+1)];
	
	int calculateMaxPath(int server_, int time_) {			
		int server = server_;
		int time = time_;
		int maxEdgePathD = 0;
		int maxEdgePathLU = 0;
		int maxEdgePathLD = 0;
		int maxEdgePathRD = 0;
		int maxEdgePathRU = 0;
		
//		iter_num++;
		
		if (H[index(time,server)] != -1) {
			return H[index(time,server)];
		}
		if (time > 0) {
			if (clients[index(time,server)]) {
				maxEdgePathD = calculateMaxPath(server, time-1) + 1;
				
				if ( (server > 0) && (edges[index(time,server-1)] == '0') ) {
					maxEdgePathLU = calculateMaxPath(server-1, time) + 1;
				}
				if ( (server > 0) && (clients[index(time-1,server-1)]) ) {
					maxEdgePathLD = calculateMaxPath(server-1, time-1) + 1;
				}
				if ( (server < 2*bound) && (clients[index(time-1,server+1)]) ) {
					maxEdgePathRD = calculateMaxPath(server+1, time-1) + 1;
				}
				if (edges[index(time,server)] == '1') {
					maxEdgePathRU = calculateMaxPath(server+1, time) + 1;
				}
			} else {
				maxEdgePathD = calculateMaxPath(server, time-1);
			}
			
			int pathLengths[5] = {maxEdgePathD, maxEdgePathLU, maxEdgePathLD, maxEdgePathRD, maxEdgePathRU};
			int edgeMaxPath = max_h(pathLengths);
			H[index(time,server)] = edgeMaxPath;
			return edgeMaxPath;
		} else {
			if (clients[index(time,server)]) {
				int maxEdgePathLU = 0;
				int maxEdgePathRU = 0;
				if ( (server > 0) && (edges[index(time,server-1)] == '0') ) {
					maxEdgePathLU = calculateMaxPath(server-1, time) + 1;
				}
				if ( edges[index(time,server)] == '1' ) {
					maxEdgePathRU = calculateMaxPath(server+1, time) + 1;
				}
				int edgeMaxPath = std::max(maxEdgePathLU, maxEdgePathRU);
				if (edgeMaxPath > 0) {
					H[index(time,server)] = edgeMaxPath;
					return edgeMaxPath;
				}
				H[index(time,server)] = 1;
				return 1;
			}
			H[index(time,server)] = 0;
			return 0;
		}
	}
	
	size_t index(int x, int y) {
		return x + graphTime * y;
	}
public:
	bool log = true;
	
	RainRandomGraphHeap() {
		auto t1 = std::chrono::steady_clock::now();
		if (log) {
			std::cout << "Start initialization:\n";
		}
		
		std::random_device rd;
		std::mt19937 gen(rd());
		std::bernoulli_distribution d(p);
		
		for (int time_ = 0; time_ < graphTime; time_++) {
			for(int server_ = 0; server_ < 2*bound+1; server_++) {
				H[index(time_,server_)] = -1;
				clients[index(time_,server_)] = d(gen);
			}
		}
		for (int time_ = 0; time_ < graphTime; time_++) {
			for(int server_ = 0; server_ < 2*bound+1; server_++) {
				if ( (server_ < 2*bound) && (clients[index(time_,server_)]) && (clients[index(time_,server_+1)]) ) {
					if (d(gen)) {
						edges[index(time_,server_)] = '1';
					} else {
						edges[index(time_,server_)] = '0';
					}
				} else {
					edges[index(time_,server_)] = '2';
				}
			}
		}
		
		auto t2 = std::chrono::steady_clock::now();
		if (log) {
			std::chrono::duration<double> elapsed_seconds = t2-t1;
			std::cout << "Initialization performance result: " << elapsed_seconds.count() << '\n';
		}
	}
	
	~RainRandomGraphHeap() {
		delete[] H;
		delete[] clients;
		delete[] edges;
	}

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


#endif // RAINRANDOMGRAPHHEAP_HPP
