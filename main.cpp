#include <stdlib.h>
#include <KMeans.h>
#include <getopt.h>

using namespace std;

void PrintHelp(){
    printf(
        "--train_file, -t <fname>:   Training file in .csv format\n"
        "--output_file, -o <fname>:  Output file in .csv format\n"
        "--means, -m <n>:            Number of means (cluster) to cluster the data to\n"
        "--epochs, -m <n>:           Number of epoch the algorithm should train for\n"
        "--help, -h:                 Show help\n"
    );
    exit(1);
}

void performKMeans(string & trainFilename, string & outputFilename, int & means, int & epochs) {
    dataHolder train(trainFilename, true);

    train.readDataset();

    printf("Number of instances: %i. \n\n", train.getLenght());

    KMeans km;
    km.KMeansClustering(train.getData(), means, epochs, outputFilename, false);
}

int main(int argc, char *argv[])
{
    string trainFilename;
    string outputFilename;
    int epochs = 10;
    int means = 3;
    int input_flag = 0;
    int output_flag = 0;

    const char* const short_opts = "t:o:m:e:h";
    const option long_opts[] = {
            {"train_file", required_argument, nullptr, 't'},
            {"output_file", required_argument, nullptr, 'o'},
            {"means", required_argument, nullptr, 'm'},
            {"epochs", required_argument, nullptr, 'e'},
            {"help", no_argument, nullptr, 'h'},
            {nullptr, no_argument, nullptr, 0}
    };

    while (true)
    {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

        if (-1 == opt)
            break;

        switch (opt)
        {
            case 't':
                trainFilename = string(optarg);
                input_flag = 1;
                break;

            case 'o':
                outputFilename = string(optarg);
                output_flag = 1;
                break;

            case 'm':
                means = std::stoi(optarg);
                break;

            case 'e':
                epochs = std::stoi(optarg);
                break;

            case 'h':
            case '?':
            default:
                PrintHelp();
                exit(1);
        }
    }

    if (input_flag && output_flag){
        performKMeans(trainFilename, outputFilename, means, epochs);
    }
    else{
        PrintHelp();
        exit(1);
    }
}
