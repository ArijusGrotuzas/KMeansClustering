#include "KMeans.h"

using namespace std;

/**
 * Compares two <point> structs based on their label value
 * 
 * @param a First point
 * @param b Second point
 * @return True if (a.label < b.label); otherwise False
 */
inline bool KMeans::compareLabel(point a, point b){
    return (a.label < b.label);
}

/**
 * Compares two <point> structs based on their entry value
 * 
 * @param a First point
 * @param b Second point
 * @return True if (a.entry < b.entry); otherwise False
 */
inline bool KMeans::compareEntry(point a, point b){
    return (a.entry < b.entry);
}

/**
 * Resets distance field for a set of <point> structs
 * 
 * @param data A set of <point>
 */
void KMeans::resetDistance(vector<point>* data){
    for (vector<point>::iterator i = data->begin(); i != data->end(); ++i){
        point p = *i;
        p.distance = __DBL_MAX__;
        *i = p;
    }
}

/**
 * Computes an n-dimensional Euclidean distance between two vectors
 * 
 * @param a First vector
 * @param b Second vector
 * @return Euclidean distance between `a` and `b`
 */
double KMeans::EuclideanDistance(vector<double> a, vector<double> b){
    if (a.size() == b.size()){
        double squaredDist = 0.0;

        for(int i = 0; i < int(a.size()); i++){
            squaredDist += pow(a[i] - b[i], 2);
        }
        return sqrt(squaredDist);
    }
    else{
        return __DBL_MAX__;
    }
}

/**
 * Computes a mean vector given a set of n-dimensional points
 * 
 * @param points Set of points to average
 * @param bound Bounds within which to average the points
 * @return Mean vector
 */
vector<double> KMeans::meanVector(vector<point>* points, boundaries bound){
    vector<double> temp = points->at(0).features;
    vector<double> mean(temp.size(), 0.0);

    for (vector<point>::iterator i = bound.start + points->begin(); i != bound.stop + points->begin(); ++i){
        point p = *i;
        vector <double> feat = p.features;

        for (int j = 0; j < int(feat.size()); j++){
            mean[j] += feat[j];
        }
    }

    int num = 1 + bound.stop - bound.start;

    for_each(mean.begin(), mean.end(), [num](double &c){ c /= num; });

    return mean;
}

/**
 * Assigns a cluster to each point in data based on Euclidean distance
 * 
 * @param data A set of points to cluster
 * @param clusters A set of clusters
 */
void KMeans::assignCluster(vector<point>* data, vector<point>* clusters){

    for (vector<point>::iterator i = clusters->begin(); i != clusters->end(); ++i){
        int id = i - clusters->begin();
        point c = *i;

        for (vector<point>::iterator j = data->begin(); j != data->end(); ++j){
            point p = *j;

            double dist = EuclideanDistance(c.features, p.features);

            if (dist < p.distance){
                p.distance = dist;
                p.label = id;
            }

            *j = p;
        }
    }
}

/**
 * @param data
 * @param filename
 */
void KMeans::writeToFile(vector<point>* data, string filename){

    // Create a csv file into which we can write
    fstream file;
    file.open(filename, ios::out);

    // Check if file was created successfully
    if(!file)
    {
        printf("Error, creating a file...");
        return;
    }

    printf("Writing to file: %s \n", filename.c_str());

    // Iterate over all data points and write them to an output file
    for (vector<point>::iterator i = data->begin(); i != data->end(); ++i){
        point p = *i;
        vector<double> temp = p.features;

        for(int j = 0; j < int(temp.size()); j++){
            file << temp[j] << ",";
        }

        file << p.label << "\n";
    }
}

/**
 * @param data
 * @param centroids
 * @param filename
*/
void KMeans::writeToImage(vector<point>* data, vector<point>* centroids, string filename){

    // Create a ppm file into which we can write
    fstream file;
    file.open(filename, ios::out);

    // Check if file was created successfully
    if(!file)
    {
        cout << "Error, creating a file...";
        return;
    }

    // Write the size and the precision of the image
    file << "P3\n" << 150 << " " << 150 << "\n255\n";

    // Sort points in order they were read
    sort(data->begin(), data->end(), KMeans::compareEntry);

    // Go though all the points and write out the value of their centroid
    for (vector<point>::iterator i = data->begin(); i != data->end(); ++i){

        // De-pointerize a pointer and get the feature vector
        point t = *i;
        vector<double> temp = t.features;

        // Get the centroid of the point
        point centroid = *(centroids->begin() + t.label);
        vector<double> centFeatures = centroid.features;

        file << int(centFeatures[0]) << " " << int(centFeatures[1]) << " " << int(centFeatures[2]) << "\n";
    }

};

/**
 * Computes K-Means clustering on a set of data.
 *
 * @param data Data to be clustered
 * @param k Number of Clusters
 * @param epochs Number of epochs to train for
 * @param filename Output filename to which the clustered data will be written to
 * @param writeImage *Blank*
 */
void KMeans::KMeansClustering(vector<point>* data, int k, int epochs, string filename, bool writeImage){
    vector<point> centroids;
    srand(time(0));

    // Initialize random k means
    for(int i = 0; i < k; i ++){
        centroids.push_back(data->at(rand() % data->size()));
    }

    for (int j = 0; j < epochs; j++){
        // Expectation step - assigning points to their new cluster
        assignCluster(data, &centroids);

        // Sort the points in order of their assigned cluster
        sort(data->begin(), data->end(), compareLabel);

        // Split up the dataset based on labels
        vector<boundaries> bounds(k, boundaries());

        int previous = 0;

        // Iterate through data and find which points belong to which cluster
        for (vector<point>::iterator i = data->begin(); i != data->end(); ++i){
            point p = *i;
            if (p.label != previous){
                bounds[previous].stop = i - data->begin();
                previous = p.label;
                bounds[previous].start = i - data->begin();
            }
            else if (i == data->end() - 1){
                bounds[previous].stop = i - data->begin();
            }
        }

        // Maximization step - Calculate new positions for centers of clusters
        for (int i = 0; i < k; i++){
            centroids[i].features = meanVector(data, bounds[i]);
        }

        // Reset the distances of the points
        resetDistance(data);
    }

    printf("The resulting %i means: \n", k);
    for (auto i : centroids){
        for (auto j : i.features){
            cout << j << ", ";
        }
        printf("\n");
    }
    printf("\n");

    if(writeImage){
        writeToImage(data, &centroids, filename);
    }
    else if(!filename.empty()){
        writeToFile(data, filename);
    }
}
