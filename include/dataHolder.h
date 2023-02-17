#ifndef DATASET_H
#define DATASET_H

#include <bits/stdc++.h>

struct point{
    std::vector<double> features;
    int label, entry;
    double distance;

    point() :
        label(0),
        entry(0),
        distance (__DBL_MAX__) {}
};

class dataHolder
{
    private:
        std::string filename;
        int lenght;
        bool readClassValues;
        std::vector<point> data;

    public:
        dataHolder(std::string filename, bool readClassValues);

        void readDataset();

        void printDataset(int rows);

        int getLenght();

        std::vector<point>* getData();
};

#endif // DATASET_H