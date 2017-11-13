#include <iostream>
using namespace std;

class Controller {
	static const float Kp = 0.01;
	static const float Ki = 0.1;
	static const float Kd = 0.01;
	float old_e=0;
	float E =0;
	float desired_output_level; // this is the desired output level that you want
	public:
		Controller(float desired_output_level);
		void controller_output(float input, float* control);
};

Controller::Controller(float desired_output) {
	desired_output_level = desired_output;
}

void Controller::controller_output(float input, float* control){
	// input is input to controller. control is the variable we have control over
    // takes a pointer to the input and returns the new input based on control change

    // proportional
	float error = desired_output_level - input;
	float kp_input = (error * Kp);
	float ed = (error - old_e);
	E += ed;
	// differential
	float kd_input = ed * Kd;
	// integral
	float ki_input = (E * Ki);
	*control = *control + kp_input + ki_input + kd_input;
	old_e = error;
}



class Model {
	static const int c = 100; // transmission coefficient
	static const int m = 90; // mass
	static const float wind = 0.001; // wind resistance
	float velocity; // this is the signal we are measuring
	float input_velocity; // this is the variable we are controlling
	int time;
	Controller controller;
public:
	Model(Controller c);
	void timestep();
	void modelCalculation();
};


Model::Model(Controller c) : controller(60) {
	time = 0;
	velocity = 0;
	input_velocity =0;
	controller = c;
	cout << "Initializing Model.\n";
}

void Model::timestep() {
	time +=1;
	controller.controller_output(velocity , &input_velocity);
	cout << "Current Time " << time << "\n";
	modelCalculation();
}

void Model::modelCalculation() {
	cout << "Velocity " << velocity << "\n";
	velocity = (c * input_velocity / m ) - ((wind * velocity * velocity) /2);
	
}



int main() {
   cout << "Hello World\n";
   Controller c = *(new Controller(70));
   Model m = *(new Model(c));
   for (int i=0; i< 1000; i++){
   		(m).timestep();   	
	}
   return 0;
} 