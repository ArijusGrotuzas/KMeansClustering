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
    private:
        static inline bool compareLabel(point a, point b);

        static inline bool compareEntry(point a, point b);

        static void resetDistance(std::vector<point>* data);

        static std::vector<double> meanVector(std::vector<point>* points, boundaries bound);

        static void assignCluster(std::vector<point>* data, std::vector<point>* clusters);

        static void writeToFile(std::vector<point>* data, std::string filename);

        static void writeToImage(std::vector<point>* data, std::vector<point>* centroids, std::string filename);

    public:
        static double EuclideanDistance(std::vector<double> a, std::vector<double> b);

        static void KMeansClustering(std::vector<point>* data, int k, int epochs, std::string filename, bool writeImage);
};

#endif // KMEANS_H
