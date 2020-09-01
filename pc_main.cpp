#include <cstdio>
#include <unistd.h>
#include <stdlib.h>
#include "models/spark.cpp"

std::vector<std::vector<float>> cellOrient(std::vector<std::vector<float>> vector) {

    int cells = vector[0].size;

    std::vector<std::vector<float>> out;

    //inner scructure
    for (int i = 0; i < cells; ++i)  {
        cout << *i << " "; 
    }

    for (auto i = vector.begin(); i != vector.end(); ++i)  {
        cout << *i << " "; 
    }
}

std::vector<std::vector<float>> parseCSV(char *file_name) {
    std::ifstream  data(file_name);
    std::string line;
    std::vector<std::vector<float> > parsedCsv;

    while(std::getline(data,line)) {
        std::stringstream lineStream(line);
        std::string cell;
        std::vector<float> parsedRow;
        while(std::getline(lineStream,cell,',')) {
            parsedRow.push_back(std::stof(cell));
        }

        parsedCsv.push_back(parsedRow);
    }

    return parsedCsv;
};

spark loadModel(char* name) {
    return spark();
}

int main(int argc, char** argv) {
    spark model = spark();
    
    int job;
    char *file_name;

    while ((opt = getopt(argc, argv, "mpt:")) != -1) {
        switch (opt) {
            case 'm':
                auto using_model = loadModel(optarg);
                break;
            case 'p':
                job = 1;
                break;
            case 't':
                job = 2;
                file_name = optarg;
            default:
                fprintf(stderr, "Usage: %s [-m model] [-p datain] [-t csvfile]\n",
                        argv[0]);
                return 1;
        }
    }
    

    if (job == 1) {
        //prediction job
        
    } else if(job == 2) {
        auto parsedCSV = parseCSV();

    }
    
    return 0; 
} 