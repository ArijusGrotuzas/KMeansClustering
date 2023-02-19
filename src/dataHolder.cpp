#include "dataHolder.h"

using namespace std;

dataHolder::dataHolder(std::string filename, bool readClassValues){
    this->filename = filename;
    this->readClassValues = readClassValues;
    length = 0;
}

void dataHolder::readDataset()
{
    // File pointer
    fstream file;

    // Open an existing file
    file.open(filename, ios::in);

    printf("Opening a file: %s; \n", filename.c_str());

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
            for(int i = 0; i < int(row.size()); i++){
                p.features.push_back(stod(row[i]));
            }

            p.entry = num;

            data.push_back(p);
            num++;
        }

        // Close the file
        file.close();
        length = num;
    }
}

void dataHolder::printDataset(int rows){

    if(rows > length){
        rows = length;
    }

    for (int i = 0; i < rows; i++){
        vector<double> temp = data[i].features;

        for(int j = 0; j < int(temp.size()); j++){
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

int dataHolder::getLength(){
    return length;
};

vector<point>* dataHolder::getData(){
    return &data;
};