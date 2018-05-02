#include "Queue.h"

Queue::Queue() {
}

Queue::Queue(string name) {
	department_name = name;
}

Queue::~Queue() {
}

void Queue::get_options() {
	cin.clear();
	cin.ignore(256, '\n');
	int user_choice;
	cout << "Department: " << department_name << endl;
	cout << "1: Add patient" << endl;
	cout << "2: Add critically ill patient" << endl;
	cout << "3: Remove patient for operation" << endl;
	cout << "4: Cancel patient" << endl;
	cout << "5: List the current queue of patients" << endl;
	cout << "6: Change department or exit" << endl;
	cout << "Please enter your choice: ";
	cin >> user_choice;
	while (!cin || user_choice < 1 || user_choice > 6) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Please select a valid choice (1-4): ";
		cin >> user_choice;
	}
	cout << "\n";
	switch (user_choice) { // Depending on the user input, go to the correct menu.
		case 1:
			this->add_patient();
			break;
		case 2:
			this->add_critical_patient();
			break;
		case 3:
			this->remove_patient();
			break;
		case 4:
			this->cancel_patient();
			break;
		case 5:
			this->print_patient_info();
			break;
		case 6:
			break;
	}
}

Queue::Patient Queue::get_patient_info() {
	Patient current_patient;
	cin.clear();
	cin.ignore(256, '\n');
	cout << "Please enter the following information for the patient." << endl;
	cout << "First name: \n";
	getline(cin, current_patient.first_name);
	cout << "Last name: \n";
	getline(cin, current_patient.last_name);
	cout << "Social Security number: \n";
	cin >> current_patient.social_security_number;
	while (!cin) { // Ensure the social security number consists of only numbers
		cout << "Please enter a valid Social Security number: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> current_patient.social_security_number;
	}
	cout << "\n";
	return current_patient;
}

void Queue::add_patient() {
	if (department_patient_count < 100) {
		department_patient_count++;
		Patient current_patient = this->get_patient_info();
		Node* current_node = new Node;
		current_node->data = current_patient;
		current_node->next = nullptr;

		Node* next_node = new Node;
		Node* previous_node = new Node;

		if (front == nullptr) { // If there are no other patients, add the current patient to the front
			front = current_node;
		}
		else {
			next_node = front;
			while (next_node != nullptr) { // Go through the list until all patients have been passed
				previous_node = next_node;
				next_node = next_node->next;
			}
			current_node->next = nullptr;
			previous_node->next = current_node;
		}
		cout << "Patient added: " << current_node->data.last_name << ", " << current_node->data.first_name << ". Social: " << current_node->data.social_security_number << endl;
		go_to_option_screen();
	}
	else {
		cout << "Cannot add patient.  Department is full." << endl;
		go_to_option_screen();
	}
}

void Queue::add_critical_patient() {
	if (department_patient_count < 100) {
		department_patient_count++;
		Patient current_patient = this->get_patient_info();
		current_patient.is_critical = true;

		Node* current_node = new Node;
		current_node->data = current_patient;
		current_node->next = nullptr;

		Node* next_node = new Node;
		Node* previous_node = new Node;

		if (front != nullptr && front->data.is_critical) { // Check to see if the node exists, and if there are any existing critical patients
			next_node = front;
			previous_node = front;
			while (next_node != nullptr && next_node->data.is_critical) { // Move through all critical patients
				previous_node = next_node;
				next_node = next_node->next;
			}
			// Insert the node after the last critical patient, and before the first non-critical patient
			current_node->next = next_node;
			previous_node->next = current_node;
		}
		else {
			// Assign front to current node
			current_node->next = front;
			front = current_node;
		}
		cout << "Patient added: " << current_node->data.last_name << ", " << current_node->data.first_name << ". Social: " << current_node->data.social_security_number << endl;
		go_to_option_screen();
	}
	else {
		cout << "Cannot add patient.  Department is full." << endl;
		go_to_option_screen();
	}
}

void Queue::remove_patient() {
	if (front != nullptr) { // As long as there is a patient, remove one
		department_patient_count--;
		Patient current_patient = front->data;
		cout << "The following patient has been moved to operating room:" << endl;
		cout << current_patient.last_name << ", " << current_patient.first_name << ".  SSN: " << current_patient.social_security_number << endl;
		front = front->next;
		go_to_option_screen();
	}
	else {
		cout << "There are no more patients." << endl;
		go_to_option_screen();
	}
}

void Queue::cancel_patient() {
	bool found = false;
	Node* current_node = front;
	Node* previous_node = front;

	if (front == nullptr) { // Case where there are no patients
		cout << "There are no patients in the queue." << endl;;
	}
	else {
		Patient current_patient = this->get_patient_info();
		if (front->next == nullptr) { // Case where there is 1 patient
			if (current_patient.first_name == front->data.first_name
				&& current_patient.last_name == front->data.last_name
				&& current_patient.social_security_number == front->data.social_security_number) {
				department_patient_count--;
				front = nullptr;
				found = true;
				cout << "Patient removed." << endl;
			}
		}

		while (current_node != nullptr && !found) { // Case where there are multiple patients

			if (current_patient.first_name == current_node->data.first_name
				&& current_patient.last_name == current_node->data.last_name
				&& current_patient.social_security_number == current_node->data.social_security_number) {

				department_patient_count--;
				if (front != current_node) { // Update the front if it is the first patient; otherwise update the specific node
					previous_node->next = current_node->next;
					found = true;
					cout << "Patient removed." << endl;
				}
				else {
					front = front->next;
					found = true;
					cout << "Patient removed." << endl;
				}

			}
			else {
				previous_node = current_node;
				current_node = current_node->next;
			}
		}
		if (!found) {
			cout << "Patient does not exist." << endl;
		}
	}
	go_to_option_screen();
}

void Queue::print_patient_info() {
	string critical_status;  // "Y" or "N" depending on if the patient is critical
	Node* current_node = front;

	if (current_node != nullptr) { // If not at the end of the list
		while (current_node != nullptr) { // While not at the end of list
			critical_status = (current_node->data.is_critical) ? "Y" : "N";

			cout << current_node->data.last_name << ", " <<
				current_node->data.first_name <<
				". Social: " << current_node->data.social_security_number <<
				". Critical?: " << critical_status << endl; // Last, First. Social: ########.  Critical?: Y/N

			current_node = current_node->next; // Move to the next node
		}
	}
	else {
		cout << "There are currently no patients." << endl;
	}

	go_to_option_screen(); // Return to menu
}

void Queue::go_to_option_screen() {
	cout << "Press any key to return to the department menu.";
	_getch();
	clear_screen();
	this->get_options();
}

void Queue::clear_screen() {
	system("CLS");
}