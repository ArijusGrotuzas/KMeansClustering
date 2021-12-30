#ifndef DATASET_H
#define DATASET_H

using namespace std;

struct point{
    vector<double> features;
    int label;
    double distance;

    point() :
        label(0),
        distance (__DBL_MAX__) {}
};

class dataset
{
    private:
        string filename;
        int lenght;
        bool readClassValues;
        vector<point> data;

    public:
        dataset(string filename, bool readClassValues);

        inline void readDataset();

        inline void printDataset(int rows);

        inline int getLenght();

        inline vector<point> getData();
};

dataset::dataset(string filename, bool readClassValues=true){
    this->filename = filename;
    this->readClassValues = readClassValues;
    lenght = 0;
}

inline void dataset::readDataset()
{
    // File pointer
    fstream file;

    // Open an existing file
    file.open(filename, ios::in);

    // Check if the file is still open
    if (file.is_open())
    {
        vector<string> row;
        string line, word, temp;
        int num = 0;

        // Get each line of the csv file
        while(getline(file, line)){

            // Clear the vector to avoid pushing previous data ontop
            row.clear();

            stringstream s(line);

            // Go through the line and and delimit each word separated by comma
            while (getline(s, word, ',')) {

                // Append each word to the vector
                row.push_back(word);
            }

            point p;

            // Add columns to a point structure
            for(int i = 0; i < row.size(); i++){
                p.features.push_back(stod(row[i]));
            }

            data.push_back(p);
            num++;
        }

        // Close the file
        file.close();
        lenght = num;
    }
}

inline void dataset::printDataset(int rows){

    if(rows > lenght){
        rows = lenght;
    }

    for (int i = 0; i < rows; i++){
        vector<double> temp = data[i].features;

        for(int j = 0; j < temp.size(); j++){
            cout << temp[j] << ", ";
        }

        if (readClassValues){
            cout << data[i].label << endl;
        }
        else{
            cout << endl;
        }
    }

    cout << endl;
}

inline int dataset::getLenght(){
    return lenght;
};

inline vector<point> dataset::getData(){

    return data;
};

#endif // DATASET_H
