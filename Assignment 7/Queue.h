#pragma once
#include <string>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
using namespace std;

// A queue is a linked list of objects that have a "first-in, first-out" quality.  For the most part, objects get added to the back of the line
// and exit from the front of the line

class Queue {
private:
	string department_name;
	int department_patient_count = 0;
	struct Patient {
		string first_name;
		string last_name;
		int social_security_number;
		bool is_critical = false;
	};
	struct Node {
		Patient data;
		Node *next;
	}*front = nullptr;
public:
	Queue();
	Queue(string name);
	virtual ~Queue(); // Destructor
	void get_options(); // Print the options for the user, and get the user's option
	Patient get_patient_info(); // Create a patient object after a user inputs the patient's information
	void add_patient(); // Add a non-critical patient to the end of the queue
	void add_critical_patient(); // Add a patient to the "critical" part of the queue.  Critical patients get added before all non-critical patients, but after already queued critical patients.
	void remove_patient(); // Remove the patient at the front of the queue and output their information
	void cancel_patient(); // User inputs information about a patient.  If a match is found in the queue, the patient is removed.
	void print_patient_info(); // Output (in order) all patients in the department queue
	void go_to_option_screen(); // Waits for user input before returning to the option screen.
	void clear_screen(); // Empties the console
};

