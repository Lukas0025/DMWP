void read_csv(char *filename) { 
    fstream fin; 
  
    fin.open(filename, ios::in); 

    while (fin >> temp) { 
  
        row.clear(); 

        String line;

        // read an entire row
        getline(fin, line); 
  
        // used for breaking words 
        stringstream s(line); 
  
        // read every column data of a row and 
        // store it in a string variable, 'word' 
        while (getline(s, word, ', ')) { 
  
            // add all the column data 
            // of a row to a vector 
            row.push_back(word); 
        } 
  
        // convert string to integer for comparision 
        roll2 = stoi(row[0]); 
  
        // Compare the roll number 
        if (roll2 == rollnum) { 
  
            // Print the found data 
            count = 1; 
            cout << "Details of Roll " << row[0] << " : \n"; 
            cout << "Name: " << row[1] << "\n"; 
            cout << "Maths: " << row[2] << "\n"; 
            cout << "Physics: " << row[3] << "\n"; 
            cout << "Chemistry: " << row[4] << "\n"; 
            cout << "Biology: " << row[5] << "\n"; 
            break; 
        } 
    } 
    if (count == 0) 
        cout << "Record not found\n"; 
} 