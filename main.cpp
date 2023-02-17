#include <stdlib.h>
#include <KMeans.h>

using namespace std;

int main()
{
    // Specify input and output file names
    string trainFilename = "data/iris.csv";
    string outputFilename = "data/output.csv";

    // Create dataset object and specify the file to read
    dataHolder train(trainFilename, true);

    // Read the dataset
    train.readDataset();

    // Print the number of instances in the dataset
    printf("Number of instances: %d \n", train.getLenght());
    cout << endl;

    // Print first 10 instances
    train.printDataset(10);

    // Perform K-Means Clustering on the data
    KMeans km;
    km.KMeansClustering(train.getData(), 3, 10, outputFilename, false);
}
