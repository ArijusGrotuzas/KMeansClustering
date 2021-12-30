#include <bits/stdc++.h>
#include <dataset.h>

struct boundaries{
    int start, stop;

    boundaries() :
        start(0),
        stop(0) {}

    boundaries(int start, int stop) :
        start(start),
        stop(stop) {}
};

bool compareLabel(point a, point b){
    return (a.label < b.label);
};

vector<double> meanVector(vector<point>* points, boundaries bound){
    vector<double> temp = points->at(0).features;
    vector<double> mean(temp.size(), 0.0);

    for (vector<point>::iterator i = bound.start + points->begin(); i != bound.stop + points->begin(); ++i){
        point p = *i;
        vector <double> feat = p.features;

        for (int j = 0; j < feat.size(); j++){
            mean[j] += feat[j];
        }
    }

    int num = 1 + bound.stop - bound.start;

    for_each(mean.begin(), mean.end(), [num](double &c){ c /= num; });

    return mean;
}

double EuclideanDistance(vector<double> a, vector<double> b){
    if (a.size() == b.size()){
        double squaredDist = 0.0;

        for(int i = 0; i < a.size(); i++){
            squaredDist += (a[i] - b[i]) * (a[i] - b[i]);
        }
        return sqrt(squaredDist);
    }
    else{
        return __DBL_MAX__;
    }
}

void assignCluster(vector<point>* data, vector<point>* clusters){

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

void resetDistance(vector<point>* data){

    for (vector<point>::iterator i = data->begin(); i != data->end(); ++i){
        point p = *i;
        p.distance = __DBL_MAX__;
        *i = p;
    }
}

void KMeansClustering(vector<point>* data, int k = 2, int epochs = 10){
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

        // Split up the dataset based labels
        vector<boundaries> bounds(k, boundaries());

        int previous = 0;
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

        //Calculate new positions for centers of clusters
        for (int i = 0; i < k; i++){
            centroids[i].features = meanVector(data, bounds[i]);
        }

        resetDistance(data);
    }

    for (vector<point>::iterator i = data->begin(); i != data->end(); ++i){
        point t = *i;
        vector<double> temp = t.features;

        for(int j = 0; j < temp.size(); j++){
            cout << temp[j] << ",";
        }

        cout << t.label << endl;
    }

    for(int i = 0; i < centroids.size(); ++i){
        vector<double> temp = centroids[i].features;
        for (int j =0; j < temp.size(); ++j){
            cout << temp[j] << ", ";
        }
        cout << endl;
    }
}

int main()
{
    string trainFilename = "old_faithful.csv";

    dataset train(trainFilename);

    train.readDataset();

    int len = train.getLenght();
    printf("Number of instances: %d \n", len);
    cout << endl;

    train.printDataset(10);

    vector<point> data = train.getData();

    KMeansClustering(&data, 2);


}
