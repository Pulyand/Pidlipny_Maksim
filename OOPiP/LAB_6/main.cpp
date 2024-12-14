#include <iostream>
#include <list>
#include <queue>

using namespace std;

class Graph {
public:
	virtual void addEdge(int v, int w) = 0;
	virtual list<int> getNeighbors(int v) const = 0;
	virtual int size() const = 0;
	virtual ~Graph() = default;
};

class SimpleGraph : public Graph {
private:
	int V;
	list<int>* adj;

public:
	SimpleGraph(int V) : V(V) {
		adj = new list<int>[V];
	}

	~SimpleGraph() {
		delete[] adj;
	}

	void addEdge(int v, int w) override {
		adj[v].push_back(w);
	}

	list<int> getNeighbors(int v) const override {
		return adj[v];
	}

	int size() const override {
		return V;
	}
};

class GraphTraversal {
public:
	virtual void beginTraversal() = 0;
	virtual void endTraversal() = 0;
	virtual void visitVertex(int v) = 0;
	virtual void visitEdge(int v, int w) = 0;
	virtual ~GraphTraversal() = default;

	void traverse(Graph& graph, int start) {
		beginTraversal();
		doTraverse(graph, start);
		endTraversal();
	}

protected:
	virtual void doTraverse(Graph& graph, int start) = 0;
};

class DFS : public GraphTraversal {
private:
	bool* visited;

public:
	DFS() : visited(nullptr) {}

	~DFS() {
		delete[] visited;
	}

	void doTraverse(Graph& graph, int v) override {
		int N = graph.size();
		visited = new bool[N];
		for (int i = 0; i < N; ++i) {
			visited[i] = false;
		}
		dfs(graph, v);
	}

	void dfs(Graph& graph, int v) {
		visited[v] = true;
		visitVertex(v);

		for (int neighbor : graph.getNeighbors(v)) {
			visitEdge(v, neighbor);
			if (!visited[neighbor]) {
				dfs(graph, neighbor);
			}
		}
	}

	void beginTraversal() override {
		cout << "Начало обхода DFS\n";
	}

	void endTraversal() override {
		cout << "Конец обхода DFS\n";
	}

	void visitVertex(int v) override {
		cout << "Посещение вершины " << v << "\n";
	}

	void visitEdge(int v, int w) override {
		cout << "Посещение ребра " << v << " -> " << w << "\n";
	}
};

class BFS : public GraphTraversal {
private:
	bool* visited;

public:
	BFS() : visited(nullptr) {}

	~BFS() {
		delete[] visited;
	}

	void doTraverse(Graph& graph, int start) override {
		int N = graph.size();
		visited = new bool[N];
		for (int i = 0; i < N; ++i) {
			visited[i] = false;
		}
		
		list<int> quene;
		visited[start] = true;
		quene.push_back(start);

		while (!quene.empty()) {
			int v = quene.front();
			quene.pop_front();
			visitVertex(v);

			for (int neigbor : graph.getNeighbors(v)) {
				visitEdge(v, neigbor);
				if (!visited[neigbor]) {
					visited[neigbor] = true;
					quene.push_back(neigbor);
				}
			}
		}
	}

	void beginTraversal() override {
		cout << "Начало обхода BFS\n";
	}

	void endTraversal() override {
		cout << "Конец обхода BFS\n";
	}

	void visitVertex(int v) override {
		cout << "Посещение вершины " << v << "\n";
	}

	void visitEdge(int v, int w) override {
		cout << "Посещение ребра " << v << " -> " << w << "\n";
	}
};

int main() {
	setlocale(LC_ALL, "RU");

	SimpleGraph graph(5);
	graph.addEdge(0, 1);
	graph.addEdge(0, 3);
	graph.addEdge(1, 4);
	graph.addEdge(2, 4);

	DFS dfs;
	BFS bfs;

	cout << "DFS обход:\n";
	dfs.traverse(graph, 0);

	cout << "\nBFS обход:\n";
	bfs.traverse(graph, 0);

	return 0;
}
