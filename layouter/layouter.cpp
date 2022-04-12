#include "layouter.h"
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <utility>
#include <math.h>

const double xlength = 4000, ylength = 4000;
const double CR = 1000000;
const double CS1 = 100, CS2 = 200;
const double Cstep = 10, CU = 1000;

void layouter::randomCor(data_manager& manager) {
	double x, y;
	int nodenum = manager.get_num_node();
	srand((unsigned)time(NULL));
	for (int i = 1; i <= nodenum; i++) {
		x = (double)(rand() % ((int)xlength - 1) + 1);
		y = (double)(rand() % ((int)ylength - 1) + 1);
		NodeData node = manager.get_node(i);
		node.coordinate = std::make_pair(x, y);
		manager.set_node(i, node);
	}
}

void layouter::updateReplusion(data_manager& manager) {
	int nodenum = manager.get_num_node();
	double dx, dy, f, fx, fy, d, dsq;
	for (int i = 1; i <= nodenum; i++) {
		for (int j = i + 1; j <= nodenum; j++) {
			NodeData nodei = manager.get_node(i), nodej = manager.get_node(j);
			dx = nodej.coordinate.first - nodei.coordinate.first;
			dy = nodej.coordinate.second - nodei.coordinate.second;
			dsq = dx * dx + dy * dy;
			d = sqrt(dsq);
			if (d > 1e-6) {
				f = CR / dsq;
				fx = f * dx / d;
				fy = f * dy / d;
				forcex[i] -= fx;
				forcey[i] -= fy;
				forcex[j] += fx;
				forcey[j] += fy;
			}
		}
	}
}

void layouter::updateSpring(data_manager& manager) {
	int edgenum = manager.get_num_edge();
	double dx, dy, f, fx, fy, d;
	for (int i = 0; i < edgenum; i++) {
		EdgeData edge = manager.get_edge(i);
		NodeData nodeu = manager.get_node(edge.u), nodev = manager.get_node(edge.v);
		dx = nodev.coordinate.first - nodeu.coordinate.first;
		dy = nodev.coordinate.second - nodeu.coordinate.second;
		d = sqrt(dx * dx + dy * dy);
		if (d > 1e-6) {
			f = CS1 * (d - CS2);
			fx = f * dx / d;
			fy = f * dy / d;
			forcex[edge.u] += fx;
			forcey[edge.u] += fy;
			forcex[edge.v] -= fx;
			forcey[edge.v] -= fy;
		}
	}
}

void layouter::update(data_manager& manager) {
	int nodenum = manager.get_num_node();
	double dx, dy, dsq, s;
	for (int i = 1; i <= nodenum; i++) {
		NodeData node = manager.get_node(i);
		dx = Cstep * forcex[i];
		dy = Cstep * forcey[i];
		dsq = dx * dx + dy * dy;
		if (dsq > CU) {
			s = sqrt(CU / dsq);
			dx *= s;
			dy *= s;
		}
		node.coordinate = std::make_pair(node.coordinate.first - dx, node.coordinate.second - dy);
		manager.set_node(i, node);
	}
}

void layouter::calc(data_manager& manager, int repeats) {
	int nodenum = manager.get_num_node();
	forcex.clear(); forcex.push_back(-1);
	forcey.clear(); forcey.push_back(-1);
	for (int i = 1; i <= nodenum; i++) {
		forcex.push_back(0);
		forcey.push_back(0);
	}
	randomCor(manager);
	while (repeats--) {
		for (int i = 1; i <= nodenum; i++) {
			forcex[i] = 0;
			forcey[i] = 0;
		}
		updateReplusion(manager);
		updateSpring(manager);
		update(manager);
	}
	double xmax = -1e12, ymax = -1e12, xmin = 1e12, ymin = 1e12;
	for (int i = 1; i <= nodenum; i++) {
		NodeData node = manager.get_node(i);
		xmax = std::max(xmax, node.coordinate.first);
		xmin = std::min(xmin, node.coordinate.first);
		ymax = std::max(ymax, node.coordinate.second);
		ymin = std::min(ymin, node.coordinate.second);
	}
	for (int i = 1; i <= nodenum; i++) {
		NodeData node = manager.get_node(i);
		double x_ = (node.coordinate.first - xmin) / (xmax - xmin) * xlength;
		double y_ = (node.coordinate.second - ymin) / (ymax - ymin) * ylength;
		node.coordinate = std::make_pair(x_, y_);
		manager.set_node(i, node);
	}
}
