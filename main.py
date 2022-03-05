import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
from IPython.display import clear_output
from collections import Counter
from collections import deque


class Node:
    def __init__(self, status, time, server, max_path, direction, edges=None):
        self.status = status
        self.time = time
        self.server = server
        self.edges = edges
        self.max_path = max_path
        self.direction = direction
        self.leaf = None
        self.directions = {
            'lu': 0,
            'ld': 1,
            'rd': 2,
            'ru': 3,
        }

    def get_status(self):
        return self.status

    def get_time(self):
        return self.time

    def get_server(self):
        return self.server

    def get_max_path(self):
        return self.max_path

    def get_direction(self):
        return self.direction

    def get_edge(self, direction):
        if self.edges is None:
            return None
        return self.edges[self.directions[direction]]

    def is_leaf(self):
        if self.leaf is None:
            self.leaf = (self.edges is not None and
                         self.time == 0 and
                         (self.edges[0] == 1 or self.edges[0] is None) and
                         (self.edges[3] == 0 or self.edges[3] is None))
        return self.leaf


class RainRandomGraph:
    def __init__(self, p, bound=None, time=-1, lazy=False):
        self.time = time
        self.p = p
        self.lazy = lazy
        if self.lazy:
            self.coords = {
                self.time: {
                    0: Node(status=1, time=time, server=0, max_path=0, direction=None)
                }
            }
        else:
            self.bound = bound
            self.H = []
            self.clients = []
            self.edges = []
            if self.time != -1 and self.time > 0:
                self.clients = [np.random.binomial(1, self.p, 2 * self.bound + 1) for _ in range(time)]
                self.edges = [np.full(2 * self.bound + 1, None) for _ in range(time)]
                for i in range(1, self.time + 1):
                    for j in range(2 * bound + 1):
                        self.generate_node_edges([j, i])
                self.H = [np.full(2 * self.bound + 1, None) for _ in range(time)]
            self.arrow_width = 0.001
            self.arrow_head_width = 0.2
            self.arrow_head_length = 0.2
            self.EPS = 0.23

    def generate_clients(self):
        self.clients.append(np.random.binomial(1, self.p, 2 * self.bound))
        self.edges.append([np.full(2 * self.bound, None) for _ in range(self.time)])

    def generate_node_edges(self, grid_index):
        server = grid_index[0]
        time = grid_index[1] - 1
        node_edges = []
        if not self.lazy:
            server = grid_index[0]
            time = grid_index[1] - 1
            if self.clients[time][server] == 0:
                node_edges = [None, None, None, None]
            else:
                if time > 0:
                    if server > 0:
                        if self.clients[time - 1][server - 1] == 1:
                            node_edges.append(1)
                        else:
                            node_edges.append(None)
                    else:
                        node_edges.append(None)
                        node_edges.append(None)
                    if server < 2 * self.bound:
                        if self.clients[time - 1][server + 1] == 1:
                            node_edges.append(1)
                        else:
                            node_edges.append(None)
                        if self.clients[time][server + 1] == 1:
                            node_edges.append(np.random.binomial(1, 0.5))
                        else:
                            node_edges.append(None)
                    else:
                        node_edges.append(None)
                        node_edges.append(None)
                else:
                    node_edges.append(None)
                    if server < 2 * self.bound:
                        if self.clients[time][server + 1] == 1:
                            node_edges.append(None)
                            node_edges.append(np.random.binomial(1, 0.5))
                        else:
                            node_edges.append(None)
                            node_edges.append(None)
                    else:
                        node_edges.append(None)
                        node_edges.append(None)
            self.edges[time][server] = node_edges

    def generate_edges(self):
        for i in range(2 * self.bound):
            self.generate_node_edges([i, len(self.edges)])

    def max_path(self, edge_coord=None):
        if edge_coord is None:
            edge_coord = [self.bound, self.time - 1]
        server = edge_coord[0]
        time = edge_coord[1]
        if time == -1:
            return 0
        else:
            max_edge_path_d = 0
            max_edge_path_l_u = 0
            max_edge_path_l_d = 0
            max_edge_path_r_d = 0
            max_edge_path_r_u = 0
            if self.H[time][server] is not None:
                return self.H[time][server]
            if time > 0:
                if self.clients[time - 1][server] == 1:
                    if self.clients[time][server] == 1:
                        max_edge_path_d = self.max_path([server, time - 1]) + 1
                    else:
                        max_edge_path_d = self.max_path([server, time - 1])
                else:
                    if self.clients[time][server] == 1:
                        max_edge_path_d = self.max_path([server, time - 1]) + 1
                    else:
                        max_edge_path_d = self.max_path([server, time - 1])
                if server > 0 and self.edges[time][server - 1][2] == 0:
                    max_edge_path_l_u = self.max_path([server - 1, time]) + 1
                if self.edges[time][server][0] is not None:
                    max_edge_path_l_d = self.max_path([server - 1, time - 1]) + 1
                if self.edges[time][server][1] is not None:
                    max_edge_path_r_d = self.max_path([server + 1, time - 1]) + 1
                if self.edges[time][server][2] == 1:
                    max_edge_path_r_u = self.max_path([server + 1, time]) + 1
                self.H[time][server] = max(max_edge_path_d,
                                           max_edge_path_l_u,
                                           max_edge_path_l_d,
                                           max_edge_path_r_d,
                                           max_edge_path_r_u)
                return self.H[time][server]
            else:
                if self.clients[time][server] == 1:
                    if not (server > 0 and self.edges[time][server - 1][2] == 0) and not self.edges[time][server][
                                                                                             2] == 1:
                        self.H[time][server] = 1
                        return self.H[time][server]
                    else:
                        max_edge_path_l_u = 0
                        max_edge_path_r_u = 0
                        if server > 0 and self.edges[time][server - 1][2] == 0:
                            max_edge_path_l_u = self.max_path([server - 1, time]) + 1
                        if self.edges[time][server][2] == 1:
                            max_edge_path_r_u = self.max_path([server + 1, time]) + 1
                        self.H[time][server] = max(max_edge_path_l_u, max_edge_path_r_u)
                        return self.H[time][server]
                else:
                    self.H[time][server] = 0
                    return self.max_path([server, time - 1])

    def draw_graph(self, max_path_coord=None):
        plt.rcParams['figure.figsize'] = [20, 10]
        fig = plt.figure()
        ax = fig.add_subplot(1, 1, 1)
        ax.spines['left'].set_position('center')
        ax.spines['right'].set_color('none')
        ax.spines['top'].set_color('none')
        ax.xaxis.set_ticks_position('bottom')
        ax.yaxis.set_ticks_position('left')
        ax.set_xticks(np.arange(-self.bound, self.bound + 1, 1))
        ax.set_yticks(np.arange(0, self.time + 1, 1))
        arrow_width = self.arrow_width
        arrow_head_width = self.arrow_head_width
        arrow_head_length = self.arrow_head_length
        EPS = self.EPS
        for i in range(2 * self.bound + 1):
            for j in range(self.time):
                if self.clients[j][i] == 1:
                    ax.plot([i - self.bound], [j + 1], marker="o", markersize=10, markeredgecolor="black",
                            markerfacecolor="black")
                else:
                    ax.plot([i - self.bound], [j + 1], marker="o", markersize=10, markeredgecolor="black",
                            markerfacecolor="white")
        for i in range(2 * self.bound + 1):
            for j in range(self.time):
                if j != 0:
                    ax.arrow(i - self.bound, j + 1, 0, -1, width=arrow_width,
                             head_width=0, head_length=0, overhang=1, ec='blue')
                if self.edges[j][i][0] is not None:
                    ax.arrow(i - self.bound, j + 1, -1, -1, width=arrow_width,
                             head_width=0, head_length=0, overhang=1, ec='blue')
                if self.edges[j][i][1] is not None:
                    ax.arrow(i - self.bound, j + 1, 1, -1, width=arrow_width,
                             head_width=0, head_length=0, overhang=1, ec='blue')
                if self.edges[j][i][2] is not None:
                    if self.edges[j][i][2] == 1:
                        ax.arrow(i - self.bound, j + 1, (1 - EPS), 0, width=arrow_width,
                                 head_width=arrow_head_width, head_length=arrow_head_length, overhang=1, ec='blue')
                    else:
                        ax.arrow(i - self.bound + 1, j + 1, -(1 - EPS), 0, width=arrow_width,
                                 head_width=arrow_head_width, head_length=arrow_head_length, overhang=1, ec='blue')

        if max_path_coord is not None:
            self.max_path([max_path_coord[0] + self.bound, max_path_coord[1] - 1])
            server = max_path_coord[0] + self.bound
            time = max_path_coord[1] - 1
            while time >= 0:
                if server > 0 and self.edges[time][server - 1][2] == 0 and self.H[time][server - 1] == self.H[time][
                    server] - 1:
                    ax.arrow(server - self.bound, time + 1, -(1 - EPS), 0, width=arrow_width,
                             head_width=arrow_head_width, head_length=arrow_head_length / 4, overhang=4, ec='red')
                    server = server - 1
                    continue
                if server > 0 and time > 0 and self.edges[time][server][0] is not None and self.H[time - 1][
                    server - 1] == self.H[time][server] - 1:
                    ax.arrow(server - self.bound, time + 1, -(1 - EPS), -(1 - EPS), width=arrow_width,
                             head_width=arrow_head_width, head_length=arrow_head_length / 4, overhang=4, ec='red')
                    server = server - 1
                    time = time - 1
                    continue
                if server < 2 * self.bound and time > 0 and self.edges[time][server][1] is not None and \
                        self.H[time - 1][server + 1] == self.H[time][server] - 1:
                    ax.arrow(server - self.bound, time + 1, (1 - EPS), -(1 - EPS), width=arrow_width,
                             head_width=arrow_head_width, head_length=arrow_head_length / 4, overhang=4, ec='red')
                    server = server + 1
                    time = time - 1
                    continue
                if server < 2 * self.bound and self.edges[time][server][2] is not None and self.H[time][server + 1] == \
                        self.H[time][server] - 1:
                    ax.arrow(server - self.bound, time + 1, (1 - EPS), 0, width=arrow_width,
                             head_width=arrow_head_width, head_length=arrow_head_length / 4, overhang=4, ec='red')
                    server = server + 1
                    continue
                if time > 0:
                    ax.arrow(server - self.bound, time + 1, 0, -(1 - 1.2 * EPS), width=arrow_width,
                             head_width=arrow_head_width, head_length=arrow_head_length / 4, overhang=4, ec='red')
                    time = time - 1
                    continue
                time = time - 1

        plt.show()

    def model_node_edges(self, node):
        node_edges = [None, None, None, None]
        server = node.get_server()
        time = node.get_time()
        if node.get_status() == 1:
            if server - 1 in self.coords[time].keys():
                if self.coords[time][server - 1].get_edge('ru') is None:
                    if self.coords[time][server - 1].get_status() == 1:
                        node_edges[0] = np.random.binomial(1, 0.5)
                else:
                    node_edges[0] = self.coords[time][server - 1].get_edge('ru')
            if time > 0 and server - 1 in self.coords[time - 1].keys():
                if self.coords[time - 1][server - 1].get_status() == 1:
                    node_edges[1] = 1
            if time > 0 and server + 1 in self.coords[time - 1].keys():
                if self.coords[time - 1][server + 1].get_status() == 1:
                    node_edges[2] = 1
            if server + 1 in self.coords[time].keys():
                if self.coords[time][server + 1].get_edge('lu') is None:
                    if self.coords[time][server + 1].get_status() == 1:
                        node_edges[3] = np.random.binomial(1, 0.5)
                else:
                    node_edges[3] = self.coords[time][server + 1].get_edge('lu')
        node.edges = node_edges

    def generate_neighbors(self, node):
        server = node.get_server()
        time = node.get_time()
        if server - 1 not in self.coords[time].keys():
            self.coords[time][server - 1] = Node(status=np.random.binomial(1, self.p), time=time, server=server - 1,
                                                 max_path=0, direction=None)
        if server + 1 not in self.coords[time].keys():
            self.coords[time][server + 1] = Node(status=np.random.binomial(1, self.p), time=time, server=server + 1,
                                                 max_path=0, direction=None)
        if time - 1 in self.coords.keys():
            if server not in self.coords[time - 1].keys():
                self.coords[time - 1][server] = Node(status=np.random.binomial(1, self.p), time=time - 1, server=server,
                                                     max_path=0, direction=None)
            if server - 1 not in self.coords[time - 1].keys():
                self.coords[time - 1][server - 1] = Node(status=np.random.binomial(1, self.p), time=time - 1,
                                                         server=server - 1, max_path=0, direction=None)
            if server + 1 not in self.coords[time - 1].keys():
                self.coords[time - 1][server + 1] = Node(status=np.random.binomial(1, self.p), time=time - 1,
                                                         server=server + 1, max_path=0, direction=None)
        else:
            if time > 0:
                self.coords[time - 1] = dict()
                self.coords[time - 1][server] = Node(status=np.random.binomial(1, self.p), time=time - 1, server=server,
                                                     max_path=0, direction=None)
                self.coords[time - 1][server - 1] = Node(status=np.random.binomial(1, self.p), time=time - 1,
                                                         server=server - 1, max_path=0, direction=None)
                self.coords[time - 1][server + 1] = Node(status=np.random.binomial(1, self.p), time=time - 1,
                                                         server=server + 1, max_path=0, direction=None)

    def lazy_max_path(self, log=False):
        stack = deque()
        stack.append(self.coords[self.time][0])
        while stack:
            self.handle_stack(stack)
            if log:
                clear_output(wait=True)
                print(len(stack))

        return self.get_lazy_max_path_node()

    def handle_stack(self, stack):
        current_node = stack[-1]
        time = current_node.get_time()
        server = current_node.get_server()
        node_max_path = current_node.get_max_path()
        direction_status = current_node.get_direction()
        if direction_status is None:
            direction_status = 0
            self.generate_neighbors(current_node)
            self.model_node_edges(current_node)
        if current_node.is_leaf():
            direction_status = -1
        if direction_status == 0:
            if current_node.get_edge('lu') == 0:
                next_node = self.coords[time][server - 1]
                current_node.direction = direction_status + 1
                if self.coords[time][server - 1].get_direction() == -1:
                    current_node.max_path = max(next_node.get_max_path() + current_node.get_status(),
                                                current_node.get_max_path())
                else:
                    stack.append(next_node)
                    return
            else:
                direction_status += 1
        if direction_status == 1:
            if current_node.get_edge('ld') == 1:
                next_node = self.coords[time - 1][server - 1]
                current_node.direction = direction_status + 1
                if next_node.get_status() == -1:
                    current_node.max_path = max(next_node.get_max_path() + current_node.get_status(),
                                                current_node.get_max_path())
                else:
                    stack.append(next_node)
                    return
            else:
                direction_status += 1
        if direction_status == 2:
            if time > 0:
                next_node = self.coords[time - 1][server]
                current_node.direction = direction_status + 1
                if next_node.direction == -1:
                    current_node.max_path = max(next_node.get_max_path() + current_node.get_status(),
                                                current_node.get_max_path())
                else:
                    stack.append(next_node)
                    return
            else:
                direction_status += 1
        if direction_status == 3:
            if current_node.get_edge('rd') == 1:
                next_node = self.coords[time - 1][server + 1]
                current_node.direction = direction_status + 1
                if next_node.get_direction() == -1:
                    current_node.max_path = max(next_node.get_max_path() + current_node.get_status(),
                                                current_node.get_max_path())
                else:
                    stack.append(next_node)
                    return
            else:
                direction_status += 1
        if direction_status == 4:
            if current_node.get_edge('ru') == 1:
                next_node = self.coords[time][server + 1]
                current_node.direction = -1
                if next_node.get_direction() == -1:
                    current_node.max_path = max(next_node.get_max_path() + current_node.get_status(),
                                                current_node.get_max_path())
                else:
                    stack.append(next_node)
                    return
            else:
                direction_status = -1
        if direction_status == -1:
            current_node = stack.pop()
            current_node.direction_status = -1
            if stack:
                next_node = stack[-1]
                if current_node.is_leaf():
                    current_node.max_path = current_node.get_status()
                    next_node.max_path = max(current_node.get_max_path() + next_node.get_status(),
                                             next_node.get_max_path())
                    return
                next_node.max_path = max(current_node.get_max_path() + next_node.get_status(),
                                         next_node.get_max_path())

    def get_lazy_max_path_node(self):
        return self.coords[self.time][0]

    def print_lazy_max_path(self):
        node = self.get_lazy_max_path_node()
        server = node.get_server()
        time = node.get_time()
        path_nodes = []
        while time >= 0:
            node = self.coords[time][server]
            path_nodes.append([time,
                               server,
                               node.get_status(),
                               node.get_max_path(),
                               node.get_edge('lu'),
                               node.get_edge('ru')])
            if time == 0 and node.is_leaf():
                print(np.array(path_nodes))
                break
            if (server - 1 in self.coords[time].keys() and
                    node.get_edge('lu') == 0 and
                    self.coords[time][server - 1].get_max_path() == node.get_max_path() - 1):
                server = server - 1
                continue
            if (time > 0 and server - 1 in self.coords[time - 1].keys() and
                    node.get_edge('ld') is not None and
                    self.coords[time - 1][server - 1].get_max_path() == node.get_max_path() - 1):
                server = server - 1
                time = time - 1
                continue
            if (time > 0 and server + 1 in self.coords[time - 1].keys() and
                    node.get_edge('rd') is not None and
                    self.coords[time - 1][server + 1].get_max_path() == node.get_max_path() - 1):
                server = server + 1
                time = time - 1
                continue
            if (server + 1 in self.coords[time].keys() and
                    node.get_edge('ru') == 1 and
                    self.coords[time][server + 1].get_max_path() == node.get_max_path() - 1):
                server = server + 1
                continue
            if time > 0 and server in self.coords[time - 1].keys():
                time = time - 1
                continue


rrg_t = RainRandomGraph(p=0.5, time=10, lazy=True)
max_path = rrg_t.lazy_max_path(log=True)
max_path.get_max_path()
