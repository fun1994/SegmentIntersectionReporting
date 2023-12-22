#pragma once
#include "EventQueue.h"
#include "StatusStructure.h"

class SegmentIntersectionReporting {
	double area2(Point& p, Point& q, Point& r) {
		return p.x * q.y - p.y * q.x + q.x * r.y - q.y * r.x + r.x * p.y - r.y * p.x;
	}
	bool toLeft(Point& p, Point& q, Point& r) {
		return area2(p, q, r) > 0;
	}
	bool intersect(std::vector<Point>& P, std::vector<Segment>& S, int i, int j) {
		return toLeft(P[S[i].first], P[S[i].second], P[S[j].first]) != toLeft(P[S[i].first], P[S[i].second], P[S[j].second]) && toLeft(P[S[j].first], P[S[j].second], P[S[i].first]) != toLeft(P[S[j].first], P[S[j].second], P[S[i].second]);
	}
	Point intersectionPoint(std::vector<Point>& P, std::vector<Segment>& S, int i, int j) {
		double a1 = area2(P[S[i].first], P[S[j].first], P[S[j].second]);
		double a2 = area2(P[S[i].second], P[S[j].first], P[S[j].second]);
		Point p;
		p.x = a2 / (a2 - a1) * P[S[i].first].x + a1 / (a1 - a2) * P[S[i].second].x;
		p.y = a2 / (a2 - a1) * P[S[i].first].y + a1 / (a1 - a2) * P[S[i].second].y;
		return p;
	}
	void initializeEventQueue(std::vector<Point>& P, std::vector<Segment>& S, EventQueue& Q) {
		for (int i = 0; i < S.size(); i++) {
			if (P[S[i].first].y > P[S[i].second].y) {
				P[S[i].first].U.push_back(i);
			}
			else {
				P[S[i].second].U.push_back(i);
			}
		}
		for (int i = 0; i < P.size(); i++) {
			Q.push(P[i]);
		}
	}
	void handleEventPoint(std::vector<Point>& P, std::vector<Segment>& S, EventQueue& Q, StatusStructure& T, std::vector<Point>& I, Point& p) {
		BinNode<int>* left = T.leftmost(P, S, p);
		BinNode<int>* right = T.rightmost(P, S, p);
		if (left) {
			right = right->succ();
			BinNode<int>* v = left;
			while (v != right) {
				if (P[S[v->data].first].y > P[S[v->data].second].y) {
					if (abs(p.x - P[S[v->data].second].x) < EPS && abs(p.y - P[S[v->data].second].y) < EPS) {
						p.L.push_back(v->data);
					}
					else {
						p.C.push_back(v->data);
					}
				}
				else {
					if (abs(p.x - P[S[v->data].first].x) < EPS && abs(p.y - P[S[v->data].first].y) < EPS) {
						p.L.push_back(v->data);
					}
					else {
						p.C.push_back(v->data);
					}
				}
				v = v->succ();
			}
		}
		if (1 < p.L.size() + p.U.size() + p.C.size()) {
			I.push_back(p);
		}
		for (int i = 0; i < p.L.size(); i++) {
			T.remove(P, S, p.L[i], p.y + EPS);
		}
		for (int i = 0; i < p.C.size(); i++) {
			T.remove(P, S, p.C[i], p.y + EPS);
		}
		for (int i = 0; i < p.U.size(); i++) {
			T.insert(P, S, p.U[i], p.y - EPS);
		}
		for (int i = 0; i < p.C.size(); i++) {
			T.insert(P, S, p.C[i], p.y - EPS);
		}
		if (p.U.empty() && p.C.empty()) {
			left = T.left(P, S, p);
			right = T.right(P, S, p);
			if (left && right) {
				findNewEvent(P, S, Q, left->data, right->data, p);
			}
		}
		else {
			left = T.leftmost(P, S, p);
			BinNode<int>* prec = left->prec();
			if (prec) {
				findNewEvent(P, S, Q, prec->data, left->data, p);
			}
			right = T.rightmost(P, S, p);
			BinNode<int>* succ = right->succ();
			if (succ) {
				findNewEvent(P, S, Q, right->data, succ->data, p);
			}
		}
	}
	void findNewEvent(std::vector<Point>& P, std::vector<Segment>& S, EventQueue& Q, int l, int r, Point& p) {
		if (intersect(P, S, l, r)) {
			Point q = intersectionPoint(P, S, l, r);
			if (q.y < p.y) {
				Q.push(q);
			}
		}
	}
public:
	std::vector<Point> BentleyOttmann(std::vector<Point>& P, std::vector<Segment>& S) {
		std::vector<Point> I;
		EventQueue Q;
		initializeEventQueue(P, S, Q);
		StatusStructure T;
		while (!Q.empty()) {
			Point p = Q.top->data;
			Q.pop();
			handleEventPoint(P, S, Q, T, I, p);
		}
		return I;
	}
};
