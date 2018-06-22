#define TSP_N 200 // Number of desired points in the TSP model
#include <sstream>
#include <vector>
#include <cstdlib> // for rand() and srand()
#include <cmath> // for sqrt()

using namespace std;

class TSPPoint {
    protected:
        double x;
        double y;
    public:
        TSPPoint() { this->x=0; this->y=0; }
        TSPPoint(double x, double y) { this->x=x; this->y=y; }
        double getX(void) { return x; }
        double getY(void) { return y; }
        double getDistanceTo(double x, double y) {
            double dx = this->x - x;
            double dy = this->y - y;
            return sqrt(dx*dx + dy*dy);
        }
        double getDistanceTo(TSPPoint other) { return getDistanceTo(other.getX(), other.getY()); }

    // allow the following funcation to access private elements:
    friend ostream& operator<<(ostream& os, TSPPoint const& p);
};

ostream& operator<<(ostream& os, TSPPoint const& p) {
    os << "TSPPoint(" << p.x << ";" << p.y << ")";
    return os;
}

class TSPRoutingTable {
    private:
        int n;
        double distances[TSP_N][TSP_N];
    public:
        TSPRoutingTable(vector<TSPPoint> points) {
            if (points.size() > TSP_N) {
                cout << "Too many points in constructor of TSPRoutingTable!" << endl;
                exit(1);
            }
            n = points.size();
            for (int i=0; i<points.size(); i++) {
                for (int j=i+1; j<points.size(); j++) {
                    distances[i][j] = points[i].getDistanceTo(points[j]);
                }
            }
        }
        double getDistance(int i, int j) {
            if (i<j) return distances[i][j];
            if (i==j) return 0;
            if (i>j) return distances[j][i];
        }
        string debug(void) {
            stringstream s("");
            s << "TSPRoutingTable for " << n << " points, i.e. " << (n*(n-1)/2) << " relations." << endl;
            return s.str();
        }
};

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// GLOBAL VARIABLES:                                                       //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

vector<TSPPoint> points(TSP_N);
TSPRoutingTable * routingTable;




/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// STAND-ALONE FUNCTIONS                                                   //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

double randomDouble(void) {
    long max = RAND_MAX;
    return (double)rand() / max;
}

void createPoints(void) {
    srand(0); // use a fixed random seed, so the point configuration becomes predictable

    for (int i=0; i<TSP_N; i++) {
        double x = 0;
        for (int j=0; j<12; j++) x += randomDouble();
        x = (x / 3) - 2; // -2..+2;

        double y = 0;
        for (int j=0; j<12; j++) y += randomDouble();
        y = (y / 3) - 2; // -2..+2;

        TSPPoint p(x,y);
        try{
            points.at(i) = p;
        } catch(out_of_range ex) {
            cout << ex.what() << endl;
        }
    }
}

void deletePoints(void) {
//    for (int i=0; i<points.size(); i++) {
//        delete(points[i]);
//    }
}

void createRoutingTable() {
    routingTable = new TSPRoutingTable(points);
}

void deleteRoutingTable() { delete(routingTable); routingTable = NULL; }


int findClosestPointIdx(double x, double y) {
    double minD = 1e100;
    double minIdx = -1;

    // iterate all points, remember the one with the least distance to x;y
    for (int i=0; i<points.size(); i++) {
        double d = points[i].getDistanceTo(x,y);
        if (d < minD) {
            minD = d;
            minIdx = i;
        }
    }

    return minIdx;
}
