#include <iostream>
#include <string>

using namespace std;

// structure for single print job
struct PrintJob {
    int jobID;
    string docName;
    int pages;
    PrintJob* next;
};


// queue class using link nodes
class PrinterQueue {
private:
    PrintJob* front;
    PrintJob* rear;
    int totalCount;

public:
    PrinterQueue() {
        front = NULL;
        rear = NULL;
        totalCount = 0;
    }

    // check if que is empty
    bool isEmpty() {
        return front == NULL;
    }

    // add job to rear of queue
    void addJob(int id, string name, int numPages) {
        PrintJob* newJob = new PrintJob();
        newJob->jobID = id;
        newJob->docName = name;
        newJob->pages = numPages;
        newJob->next = NULL;

        if (isEmpty()) {
            front = newJob;
            rear = newJob;
        } else {
            rear->next = newJob;
            rear = newJob;
        }
        totalCount++;
        cout << "Added Job: [" << id << "] " << name << " (" << numPages << " pages)" << endl;
    }

    // process and remove job from front
    void processJob() {
        if (isEmpty()) {
            cout << "Cannot process. Printer queue is empty!" << endl;
            return;
        }

        PrintJob* temp = front;
        cout << "Processing Job: [" << temp->jobID << "] " << temp->docName << " (" << temp->pages << " pages)" << endl;

        front = front->next;
        if (front == NULL) {
            rear = NULL; // when last job removed both null
        }

        delete temp;
        totalCount--;
    }

    // view next job at front without removing
    void viewNextJob() {
        if (isEmpty()) {
            cout << "No next job. Queue is empty." << endl;
            return;
        }
        cout << "Next Job to print: [" << front->jobID << "] " << front->docName << " (" << front->pages << " pages)" << endl;
    }

    // display all waiting jobs in queue
    void displayQueue() {
        if (isEmpty()) {
            cout << "Current Queue: [Empty]" << endl;
            return;
        }

        cout << "Current Queue (Front to Rear):" << endl;
        PrintJob* curr = front;
        int index = 1;
        while (curr != NULL) {
            cout << "  " << index << ". Job ID: " << curr->jobID 
                 << " | File: " << curr->docName 
                 << " | Pages: " << curr->pages << endl;
            curr = curr->next;
            index++;
        }
    }

    // count total jobs in queue
    int countJobs() {
        return totalCount;
    }

    // clear all jobs
    void clearQueue() {
        while (!isEmpty()) {
            PrintJob* temp = front;
            front = front->next;
            delete temp;
        }
        rear = NULL;
        totalCount = 0;
    }

    ~PrinterQueue() {
        clearQueue();
    }
};


int main() {
    cout << "Task 2: Printer Job Scheduling\n\n";

    PrinterQueue pq;

    cout << "--- Step 0: Adding Initial Jobs ---" << endl;
    pq.addJob(101, "Assignment1.pdf", 10);
    pq.addJob(102, "Report.docx", 25);
    pq.addJob(103, "Notes.pdf", 5);
    pq.addJob(104, "LabTask.docx", 15);
    cout << endl;

    cout << "--- Step 1: Display all jobs ---" << endl;
    pq.displayQueue();
    cout << "Total waiting jobs: " << pq.countJobs() << endl << endl;

    cout << "--- Step 2: Process two jobs ---" << endl;
    pq.processJob();
    pq.processJob();
    cout << endl;

    cout << "--- Step 3: Display remaining jobs ---" << endl;
    pq.displayQueue();
    cout << "Total waiting jobs: " << pq.countJobs() << endl << endl;

    cout << "--- Step 4: Add a new job ---" << endl;
    pq.addJob(105, "ProjectCode.cpp", 30);
    cout << endl;

    cout << "--- Step 5: Display next job ---" << endl;
    pq.viewNextJob();
    cout << endl;

    cout << "--- Step 6: Process all remaining jobs ---" << endl;
    while (!pq.isEmpty()) {
        pq.processJob();
    }
    cout << endl;

    cout << "--- Step 7: Attempt to process from empty queue ---" << endl;
    pq.processJob();
    cout << endl;

    return 0;
}
