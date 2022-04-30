#ifndef RAINRANDOMGRAPH_HPP
#define RAINRANDOMGRAPH_HPP

int max_(int arr[5]) {
	int currentMax = arr[0];
	for (int i=1;i<5;i++) {
		if (currentMax < arr[i]) {
			currentMax = arr[i];
		}
	}
	return currentMax;
}

class RainRandomGraph {
private:
		static const int graphTime = 500;
		static const int bound = 500;
		static const double p = 0.5;
		int H[graphTime][2*bound+1];
		int edges[graphTime][2*bound+1][3];
		int clients[graphTime][2*bound+1];
		
		void generateNodeEdges(int server_, int time_) {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::bernoulli_distribution d(p);
			int nodeEdges[3] = {-1,-1,-1};
			int server = server_;
			int time = time_ - 1;
			
			if (clients[time][server] != 0) {
				if (time > 0) {
					if (server > 0) {
						if (clients[time-1][server-1] == 1) {
							nodeEdges[0] = 1;
						}
					}
					if (server < 2*bound) {
						if (clients[time-1][server+1] == 1) {
							nodeEdges[1] = 1;
						}
						if (clients[time][server+1] == 1) {
							nodeEdges[2] = int(d(gen));
						}
					}
				} else {
					if (server < 2*bound) {
						if (clients[time][server+1] == 1) {
							nodeEdges[2] = int(d(gen));
						}
					}
				}
			}
			edges[time][server][0] = nodeEdges[0];
			edges[time][server][1] = nodeEdges[1];
			edges[time][server][2] = nodeEdges[2];
		}
		
		int calculateMaxPath(int server_, int time_) {
			int server = server_;
			int time = time_;
			int maxEdgePathD = 0;
			int maxEdgePathLU = 0;
			int maxEdgePathLD = 0;
			int maxEdgePathRD = 0;
			int maxEdgePathRU = 0;
			
			if (time == -1) {
				return 0;
			}
			if (H[time][server] != -1) {
				return H[time][server];
			}
			if (time > 0) {
				if (clients[time-1][server] == 1) {
					if (clients[time][server] == 1) {
						maxEdgePathD = calculateMaxPath(server, time-1) + 1;
					} else {
						maxEdgePathD = calculateMaxPath(server, time-1);
					}
				} else {
					if (clients[time][server] == 1) {
						maxEdgePathD = calculateMaxPath(server, time-1) + 1;
					} else {
						maxEdgePathD = calculateMaxPath(server, time-1);
					}
				}
				if ( (server > 0) && (edges[time][server-1][2] == 0) ) {
					maxEdgePathLU = calculateMaxPath(server-1, time) + 1;
				}
				if (edges[time][server][0] == 1) {
					maxEdgePathLD = calculateMaxPath(server-1, time-1) + 1;
				}
				if (edges[time][server][1] == 1) {
					maxEdgePathRD = calculateMaxPath(server+1, time-1) + 1;
				}
				if (edges[time][server][2] == 1) {
					maxEdgePathRU = calculateMaxPath(server+1, time) + 1;
				}
				
				int pathLengths[5] = {maxEdgePathD, maxEdgePathLU, maxEdgePathLD, maxEdgePathRD, maxEdgePathRU};
				int edgeMaxPath = max_(pathLengths);
				H[time][server] = edgeMaxPath;
				return edgeMaxPath;
			} else {
				if (clients[time][server] == 1) {
					if ( ( (server > 0) && (edges[time][server-1][2] == 0) ) || (edges[time][server][2] == 1) ) {
						int maxEdgePathLU = 0;
						int maxEdgePathRU = 0;
						if ( (server > 0) && (edges[time][server-1][2] == 0) ) {
							maxEdgePathLU = calculateMaxPath(server-1, time) + 1;
						}
						if (edges[time][server][2] == 1) {
							maxEdgePathRU = calculateMaxPath(server+1, time) + 1;
						}
						int edgeMaxPath = std::max(maxEdgePathLU, maxEdgePathRU);
						H[time][server] = edgeMaxPath;
						return edgeMaxPath;
					}
					H[time][server] = 1;
					return 1;
				} else {
					H[time][server] = 0;
					return 0;
				}
			}
		}
	public:
		RainRandomGraph() {
			std::cout << "Start initialization:\n";
			auto t1 = std::chrono::steady_clock::now();
			
			std::random_device rd;
			std::mt19937 gen(rd());
			std::bernoulli_distribution d(p);
			for (int i=0;i<graphTime;i++) {
				for(int j=0;j<2*bound+1;j++) {
					H[i][j] = -1;
					clients[i][j] = int(d(gen));
				}
			}
			for (int i=0;i<graphTime;i++) {
				for(int j=0;j<2*bound+1;j++) {
					generateNodeEdges(j, i);
				}
			}
			
			auto t2 = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed_seconds = t2-t1;
			std::cout << "Initialization performance result: " << elapsed_seconds.count() << '\n';
		}
		
		~RainRandomGraph() {}
	
		int getMaxPath() {
			std::cout << "Start calculating:\n";
			auto t1 = std::chrono::steady_clock::now();
			
			int maxPath = calculateMaxPath(bound, graphTime-1);
			
			auto t2 = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed_seconds = t2-t1;
			std::cout << "Calculation performance result: " << elapsed_seconds.count() << '\n';
			
			return maxPath;
		}
    };

#endif // RAINRANDOMGRAPH_HPP
