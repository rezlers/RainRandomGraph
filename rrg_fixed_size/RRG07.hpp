#ifndef RRG07_HPP
#define RRG07_HPP

class RRG07 {
private:
	static const int graphTime = 100;
	static const int bound = 100;
	static const double p = 0.7;
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
	
	RRG07() {
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
	
	~RRG07() {}

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

#endif // RAINRANDOMGRAPHOPT_HPP
