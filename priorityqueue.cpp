//  priorityqueue.cpp
//  Created by Ian Hegstrom on 11/5/18.
//  Copyright © 2018 Ian Hegstrom. All rights reserved.
//


#include <iostream>
#include <vector>
#include "PriorityQueue.hpp"

using namespace std;

   PriorityQueue::PriorityQueue(int _arraySize)
   {
       currentQueueSize = 0;
       maxQueueSize = _arraySize;
       priorityQueue = new PatientNode[_arraySize+1];
   }

   PriorityQueue::~PriorityQueue()
   {
       delete [] priorityQueue;
   }

   void PriorityQueue::enqueue (std::string _name, int _injurySeverity, int _treatmentTime)
   {
       if(!isFull())
       {
           PatientNode newPatient;
           //assign the inputs to the variables
           newPatient.name = _name;
           newPatient.injurySeverity = _injurySeverity;
           newPatient.treatmentTime = _treatmentTime;

           //remember the +1
           priorityQueue[currentQueueSize + 1 ] = newPatient;
           currentQueueSize = currentQueueSize + 1;
           repairUpward(currentQueueSize);
       }
   }

   string PriorityQueue::peekName()
   {
       return priorityQueue[1].name;
   }

   int PriorityQueue::peekInjurySeverity()
   {
       return priorityQueue[1].injurySeverity;
   }

   int PriorityQueue::peekTreatmentTime()
   {
       return priorityQueue[1].treatmentTime;
   }

   bool PriorityQueue::isFull()
   {
       return(currentQueueSize==maxQueueSize);
   }

   bool PriorityQueue::isEmpty()
   {
       return (currentQueueSize == 0);
   }

   void  PriorityQueue::repairUpward(int nodeIndex)
   {
           if(nodeIndex != 1){
         //initializing parent node
           int parentNode1 = nodeIndex / 2;
           //check the different possible cases
           if (priorityQueue[parentNode1].injurySeverity < priorityQueue[nodeIndex].injurySeverity || (priorityQueue[parentNode1].injurySeverity == priorityQueue[nodeIndex].injurySeverity && priorityQueue[parentNode1].treatmentTime > priorityQueue[nodeIndex].treatmentTime)) {
               PatientNode current = priorityQueue[parentNode1];
               priorityQueue[parentNode1] = priorityQueue[nodeIndex];
               priorityQueue[nodeIndex] = current;
               //run repairupward on the parent node
               repairUpward(parentNode1);
           }
       }
       return;
   }

   void  PriorityQueue::repairDownward(int nodeIndex)
   {
           if(nodeIndex < currentQueueSize){
           //initializing child nodes
           int leftChild = 2 * nodeIndex;
           int rightChild = nodeIndex*2 + 1;
           int bigChild;
           if(leftChild<currentQueueSize) {
               if(rightChild < currentQueueSize){
                   if(priorityQueue[leftChild].injurySeverity > priorityQueue[rightChild].injurySeverity || ( priorityQueue[leftChild].treatmentTime < priorityQueue[rightChild].treatmentTime && priorityQueue[leftChild].injurySeverity == priorityQueue[rightChild].injurySeverity )) {
                       bigChild = leftChild;
                   }
                   else bigChild = rightChild;
               }
               else bigChild = leftChild;


               if(priorityQueue[bigChild].injurySeverity > priorityQueue[nodeIndex].injurySeverity || ( priorityQueue[bigChild].injurySeverity == priorityQueue[nodeIndex].injurySeverity && priorityQueue[bigChild].treatmentTime < priorityQueue[nodeIndex].treatmentTime)) {
                   PatientNode current = priorityQueue[nodeIndex];
                   priorityQueue[nodeIndex] = priorityQueue[bigChild];
                   priorityQueue[bigChild] = current;
                   //run repairdownard on the bigger child
                   repairDownward(bigChild);
               }
           }
       }
       return;




   }

   void PriorityQueue::dequeue()
   {
      //can not dequeue if the queue is empty
       if(!isEmpty()){
       priorityQueue[1] = priorityQueue[currentQueueSize];
       repairDownward(1);
       //have to adjust the queue size integer
       currentQueueSize = currentQueueSize - 1;
       }

}
