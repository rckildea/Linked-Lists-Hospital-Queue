/*	Name: Ryan Kildea
Date: 05/04/2018
Class: CS 201
Assignment 7

This assignment uses queues to create a menu and check-in/out system for a hospital.
Three departments' patients are tracked separately and can be added or removed from the queue with
functions provided in the menu.
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include "Queue.h"
using namespace std;

int get_user_choice() {
	int user_choice;
	cin >> user_choice;
	while (!cin || user_choice < 1 || user_choice > 4) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Please select a valid choice (1-4): ";
		cin >> user_choice;
	}
	return user_choice;
}

void print_welcome_screen() {
	cout << "Welcome to Starling City Hospital" << endl;
	cout << "1: Heart Clinic" << endl;
	cout << "2: Lung Clinic" << endl;
	cout << "3: Plastic Surgery" << endl;
	cout << "4: Exit" << endl;
	cout << "Please enter your choice: ";
}

void clear_screen() {
	system("CLS");
}

int main() {
	int user_choice = 0;
	Queue heart_clinic("Heart Cinic");
	Queue lung_clinic("Lung Cinic");
	Queue plastic_surgery("Plastic Surgery");

	while (user_choice != 4) { // Exit the program once the user enters "4"
		clear_screen();
		print_welcome_screen();
		user_choice = get_user_choice();
		clear_screen();
		// Select the correct queue to work with
		if (user_choice == 1) {
			heart_clinic.get_options();
		}
		else if (user_choice == 2) {
			lung_clinic.get_options();
		}
		else if (user_choice == 3) {
			plastic_surgery.get_options();
		}
	}

	cout << "Thank you for using the application!" << endl;

	return 0;
}