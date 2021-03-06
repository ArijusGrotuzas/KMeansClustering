#include <bits/stdc++.h>
#include <dataset.h>
#include <KMeans.h>

int main()
{
    // Specify input and output file names
    string trainFilename = "data/iris.csv";
    string outputFilename = "data/output.csv";

    // Create dataset object and specify the file to read
    dataset train(trainFilename);

    // Read the dataset
    train.readDataset();

    // Print the number of instances in the dataset
    printf("Number of instances: %d \n", train.getLenght());
    cout << endl;

    // Print first 10 instances
    train.printDataset(10);

    // Perform K-Means Clustering on the data
    KMeansClustering(train.getData(), 3, 10, outputFilename);
}
