/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "random.h"
using namespace std;

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */

void clearMemory(Grid<NodeT*>& nodes) {
	for (int i = 0; i < nodes.numRows(); i++)
		for (int j = 0; j < nodes.numCols(); j++)
			delete nodes[i][j];
}

void initGridOfNodes(Grid<NodeT*>& nodes) {
	for (int i = 0; i < nodes.numRows(); i++) {
		for (int j = 0; j < nodes.numCols(); j++) {
			nodes[i][j] = new NodeT;
			nodes[i][j]->parent = NULL;

			nodes[i][j]->loc = makeLoc(i, j);
			nodes[i][j]->color = GRAY;
		}
	}
}

void checkEdges(NodeT*& curr, Grid<NodeT*>& nodes, Grid<double>& world, NodeT*& last,
				TrailblazerPQueue<NodeT*>& pq, double costFn(Loc from, Loc to, Grid<double>& world),
				double heuristic(Loc start, Loc end, Grid<double>& world)) {

	for (int i = curr->loc.row - 1; i <= curr->loc.row + 1; i++)
		for (int j = curr->loc.col - 1; j <= curr->loc.col + 1; j++)
			if (world.inBounds(i, j) && (curr->loc.row != i || curr->loc.col != j))
				if (nodes[i][j]->color == GRAY) {
					nodes[i][j]->color = YELLOW;
					nodes[i][j]->cost = curr->cost + costFn(curr->loc, nodes[i][j]->loc, world);

					pq.enqueue(nodes[i][j], nodes[i][j]->cost + heuristic(nodes[i][j]->loc, last->loc, world));
					nodes[i][j]->parent = curr;
					colorCell(world, nodes[i][j]->loc, YELLOW);
				} else {
					double newCost = curr->cost + costFn(curr->loc, nodes[i][j]->loc, world);
					if (nodes[i][j]->color == YELLOW && nodes[i][j]->cost > newCost) {
						nodes[i][j]->cost = newCost;
						pq.decreaseKey(nodes[i][j], newCost + heuristic(nodes[i][j]->loc, last->loc, world));
						nodes[i][j]->parent = curr;
					}
				}
}

void getAnswer(NodeT* curr, Vector<Loc>& ans) {
	if (!curr) return;
	getAnswer(curr->parent, ans);
	ans.push_back(curr->loc);
}

Vector<Loc> getResult(Grid<NodeT*>& nodes, Grid<double>& world, NodeT*& last,
				TrailblazerPQueue<NodeT*>& pq, double costFn(Loc from, Loc to, Grid<double>& world),
				double heuristic(Loc start, Loc end, Grid<double>& world)) {

	Vector<Loc> ans;
	while (!pq.isEmpty()) {
		NodeT* curr = pq.dequeueMin();
		curr->color = GREEN;
		colorCell(world, curr->loc, GREEN);

		if (curr->loc == last->loc) {
			getAnswer(curr, ans);
			break;
		}
		checkEdges(curr, nodes, world, last, pq, costFn, heuristic);
	}

//	clearMemory(nodes);
	return ans;
}

Vector<Loc> shortestPath(Loc start, Loc end, Grid<double>& world, 
			double costFn(Loc from, Loc to, Grid<double>& world),
			double heuristic(Loc start, Loc end, Grid<double>& world)) {

	Grid<NodeT*> nodes(world.numRows(), world.numCols());
	initGridOfNodes(nodes);

	NodeT* first = nodes[start.row][start.col];
	NodeT* last = nodes[end.row][end.col];

	first->color = YELLOW;
	first->cost = 0;

	TrailblazerPQueue<NodeT*> pq;
	pq.enqueue(first, heuristic(first->loc, last->loc, world));
	return getResult(nodes, world, last, pq, costFn, heuristic);
}

// -----------------------------------------------------------------
// -----------------------------------------------------------------

void getClusters(Map<Loc, int>& cluster, int rows, int cols) {
	int k = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			cluster[makeLoc(i, j)] = k++;
}

void getPQueue(TrailblazerPQueue<Edge>& pq, int rows, int cols) {
	Loc end, start;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++) {
			start = makeLoc(i, j);

			end = makeLoc(i - 1, j);
			if (end.row >= 0 && end.row < rows && end.col >= 0 && end.col < cols) 
				pq.enqueue(makeEdge(start, end), randomReal(0, 1));
			
			end = makeLoc(i + 1, j);
			if (end.row >= 0 && end.row < rows && end.col >= 0 && end.col < cols) 
				pq.enqueue(makeEdge(start, end), randomReal(0, 1));

			end = makeLoc(i, j - 1);
			if (end.row >= 0 && end.row < rows && end.col >= 0 && end.col < cols) 
				pq.enqueue(makeEdge(start, end), randomReal(0, 1));
			
			end = makeLoc(i, j + 1);
			if (end.row >= 0 && end.row < rows && end.col >= 0 && end.col < cols) 
				pq.enqueue(makeEdge(start, end), randomReal(0, 1));
		}
}

void changeClusters(Map<Loc, int>& cluster, int a, int b) {
	foreach(Loc l in cluster)
		if (cluster[l] == a) cluster[l] = b;
}

void useKruskal(Set<Edge>& ans, TrailblazerPQueue<Edge>& pq, Map<Loc, int>& cluster) {
	int numClusters = cluster.size();
	while (numClusters > 1) {
		Edge e = pq.dequeueMin();
		if (cluster[e.start] != cluster[e.end]) {
			ans.add(e);
			changeClusters(cluster, cluster[e.start], cluster[e.end]);
			numClusters--;
		}
	}
}

Set<Edge> createMaze(int numRows, int numCols) {
	Map<Loc, int> cluster;
	getClusters(cluster, numRows, numCols);
	
	TrailblazerPQueue<Edge> pq;
	getPQueue(pq, numRows, numCols);
	
	Set<Edge> ans;
	useKruskal(ans, pq, cluster);
	return ans;
}
