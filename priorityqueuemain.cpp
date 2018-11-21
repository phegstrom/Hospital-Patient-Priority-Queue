//  priorityqueuemain.cpp
//  Created by Ian Hegstrom on 11/5/18.
//  Copyright © 2018 Ian Hegstrom. All rights reserved.


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "PriorityQueue.hpp"

using namespace std;

void displayMenu();

int main(int argc, char const *argv[])
{
    int cumulativeTime = 0;
    PriorityQueue thisQueue(stoi(argv[1]));
    string stringValue;
    int selectedValue = 0;
    while(selectedValue != 6)
    {
        displayMenu();
        getline(cin,stringValue);
        selectedValue = stoi(stringValue);
        switch(selectedValue)
        {
            case 1:
            {
                string filePath;
                fstream fileStream;
                cout << "Enter filename:" << endl;
                getline(cin, stringValue);
                fileStream.open(filePath);

                if(fileStream.is_open()){
                    string name, rank, time, line;
                    getline(fileStream,line);

                    while(getline(fileStream,line) && !thisQueue.isFull())
                    {
                        stringstream ss(line);
                        ss >> name >> rank >> time;
                        thisQueue.enqueue(name, stoi(rank), stoi(time));
                    }
                    cout << "Priority Queue full. Send remaining patients to another hospital." << endl;
                } else {
                    cout << "Cannot open file" << endl;  
                }

                break;
            }
            case 2:
            {
                if (!thisQueue.isFull())
                {
                    string name, rank, time;
                    int queuerank, time;

                    cout << "Enter Patient Name:" << endl;
                    getline(cin,name);
                    cout << "Enter Injury Severity:" << endl;
                    getline(cin,rank);
                    cout << "Enter Treatment Time:" << endl;
                    getline(cin,time);

                    queuerank = stoi(rank);
                    time = stoi(time);

                    thisQueue.enqueue(name,queuerank,time);
                    cout << "Successfull addition of patient to the PQ" << endl;
                }
                else cout << "Priority Queue full. Send Patient to another hospital." << endl;
            }
                break;
            case 3:
            {
              //only perform if queue is not empty
                if(!thisQueue.isEmpty()){
                    cout << "Patient Name: " << thisQueue.peekName() << endl;
                    cout << "Injury Severity: " << thisQueue.peekInjurySeverity() << endl;
                    cout << "Treatment Time: " << thisQueue.peekTreatmentTime() << endl;
                }
                else cout << "Queue empty." << endl;
            }
                break;

            case 4:
            {
                if(thisQueue.isEmpty()) cout << "Queue empty." << endl;
                else
                {
                    cumulativeTime += thisQueue.peekTreatmentTime();
                    cout << "Patient Name: " << thisQueue.peekName() << " - Total Time Treating Patients: " << cumulativeTime << endl;
                    thisQueue.dequeue();
                }
            }
                break;
            case 5:
            {
                if(thisQueue.isEmpty()) cout << "Queue empty." << endl;
                else
                {
                    while(!thisQueue.isEmpty())
                    {
                        cumulativeTime += thisQueue.peekTreatmentTime();
                        cout << "Patient Name: " << thisQueue.peekName() << " - Total Time Treating Patients: " << cumulativeTime << endl;
                        thisQueue.dequeue();
                    }
                }
            }
                break;
            case 6:
            {
              cout << "Goodbye!" << endl;
            }
                break;


        }
    }

    return 0;
}

void displayMenu()
{
    cout << "======Main Menu======" << endl;
    cout << "1. Get Patient Information from File" << endl;
    cout << "2. Add Patient to Priority Queue" << endl;
    cout << "3. Show Next Patient" << endl;
    cout << "4. Treat Next Patient" << endl;
    cout << "5. Treat Entire Queue" << endl;
    cout << "6. Quit" << endl;

}
