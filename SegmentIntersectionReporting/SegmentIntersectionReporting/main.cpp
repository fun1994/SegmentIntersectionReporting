#include "SegmentIntersectionReporting.h"

void generateSegments(std::vector<Point>& P, std::vector<Segment>& S) {
	P.resize(12);
	S.resize(7);
	P[0].x = 153;
	P[0].y = -8;
	P[1].x = 238;
	P[1].y = -280;
	P[2].x = 203;
	P[2].y = -168;
	P[3].x = 183;
	P[3].y = -324;
	P[4].x = 303;
	P[4].y = -58;
	P[5].x = 133;
	P[5].y = -245;
	P[6].x = 90;
	P[6].y = -48;
	P[7].x = 91;
	P[7].y = -142;
	P[8].x = 39;
	P[8].y = -89;
	P[9].x = 64;
	P[9].y = -233;
	P[10].x = 316;
	P[10].y = -114;
	P[11].x = 296;
	P[11].y = -232;
	S[0].first = 0;
	S[0].second = 1;
	S[1].first = 2;
	S[1].second = 3;
	S[2].first = 4;
	S[2].second = 5;
	S[3].first = 2;
	S[3].second = 6;
	S[4].first = 2;
	S[4].second = 7;
	S[5].first = 8;
	S[5].second = 9;
	S[6].first = 10;
	S[6].second = 11;
}

void test() {
	SegmentIntersectionReporting SIR;
	std::vector<Point> P;
	std::vector<Segment> S;
	generateSegments(P, S);
	std::vector<Point> I = SIR.BentleyOttmann(P, S);
}

int main() {
	test();
	return 0;
}
