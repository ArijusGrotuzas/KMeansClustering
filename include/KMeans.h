#ifndef KMEANS_H
#define KMEANS_H

#include "dataHolder.h"

struct boundaries{
    int start, stop;

    boundaries():
        start(0),
        stop(0) {}

    boundaries(int start, int stop) :
        start(start),
        stop(stop) {}
};

class KMeans
{
    public:
        static bool compareLabel(point a, point b);

        static bool compareEntry(point a, point b);

        void resetDistance(std::vector<point>* data);

        double EuclideanDistance(std::vector<double> a, std::vector<double> b);

        std::vector<double> meanVector(std::vector<point>* points, boundaries bound);

        void assignCluster(std::vector<point>* data, std::vector<point>* clusters);

        void writeToFile(std::vector<point>* data, std::string filename);

        void writeToImage(std::vector<point>* data, std::vector<point>* centroids, std::string filename);
        
        void KMeansClustering(std::vector<point>* data, int k, int epochs, std::string filename, bool writeImage);
};

#endif // KMEANS_H
