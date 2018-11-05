//  priorityqueuemain.cpp
//  Created by Ian Hegstrom on 11/5/18.
//  Copyright © 2018 Ian Hegstrom. All rights reserved.
//


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "PriorityQueue.hpp"

using namespace std;

void displayMenu();

int main(int argc, char const *argv[])
{
    int cumulativeTime=0;
    PriorityQueue thisQueue(stoi(argv[1]));
    string stringValue;
    int test = 0;
    while(test!=6)
    {
        displayMenu();
        getline(cin,stringValue);
        test = stoi(stringValue);
        switch(test)
        {
            case 1:
            {
                string thisfile;
                cout << "Enter filename:" << endl;
                getline(cin, stringValue);
                fstream FileRead;
                FileRead.open(thisfile);

                if(FileRead.is_open()){

                    bool nFull = true;
                    string name1,rank1,time1,line;
                    getline(FileRead,line);

                    while(getline(FileRead,line) && nFull)
                    {
                        stringstream ss(line);
                        ss >> name1 >> rank1 >> time1;

                        if (!thisQueue.isFull()){
                            thisQueue.enqueue(name1, stoi(rank1), stoi(time1));
                        }
                        else{
                            cout << "Priority Queue full. Send remaining patients to another hospital." << endl;
                            nFull = false;
                        }
                    }
                }

                else cout << "Cannot open file" << endl;
            }
                break;
            case 2:
            {
                if (!thisQueue.isFull())
                {
                    string name2,rank2,time2;
                    int queuerank,time;

                    cout << "Enter Patient Name:" << endl;
                    getline(cin,name2);
                    cout << "Enter Injury Severity:" << endl;
                    getline(cin,rank2);
                    cout << "Enter Treatment Time:" << endl;
                    getline(cin,time2);

                    queuerank = stoi(rank2);
                    time = stoi(time2);
                    thisQueue.enqueue(name2,queuerank,time);
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
