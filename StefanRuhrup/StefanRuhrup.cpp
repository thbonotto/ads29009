//Source: cf. [H. Karl, Leistungsbewertung und Simulation, uni Paderborn, 2007
#include <queue>
#include <random>
#include <iostream>
#include <chrono>
#include <thread>
#include <math.h>

enum class State {
	IDLE, BUSY
};

class Task {
public:
	Task(double time) :
			mArrivaltime { time } {

	}

	const double& arrival_time() {
		return mArrivaltime;
	}

	double mArrivaltime;
};

class Generator {
	public :
	Generator(int seed) {
		generator.seed(seed);
	}

	double rand_poisson(double lambda) {
		std::uniform_int_distribution<int> distribution(0, 1);
		double ln_u = log(distribution(generator));
		return ln_u/lambda;
	}

	std::default_random_engine generator;
};
double TASKS = 0.0;
const double T_MAX = 1200;
double mean_arrival = 1.0;
double mean_processing = 0.5;
std::queue<Task> queue;
State server_state = State::IDLE;
double sim_time = 0.0;
double next_departure = HUGE_VAL; // ← set to infinity
size_t queue_counter = 0;
size_t cumulated_queue_length=0;
double busy_time_total=0;
double last_event_time = 0.0;
void update_statistics() {
	double time_since_last_event = sim_time - last_event_time;
	cumulated_queue_length += queue.size() * time_since_last_event;
	if (server_state == State::BUSY)
		busy_time_total += time_since_last_event;
}

double waiting_time_total = 0.0;
int main(int argc, char** argv) {
	Generator rng1{23};
	Generator rng2{17};
	/**
	 *  Results for 1000 tasks, A = 1, S=0.5
		Seed A Seed S Avg. Utilization Avg. Queue Length Avg. Waiting Time
		23 17 0,534 0,572 0,563
		25 89 0,496 0,478 0,479
		167 11 0,505 0,458 0,453
		235 21 0,506 0,451 0,435
	 */
	double next_arrival = rng1.rand_poisson(mean_arrival);

	while (sim_time < T_MAX) {
		/*std::cout << "sim_time: " << sim_time << std::endl;
		std::cout << "next_arrival: " << next_arrival << std::endl;
		std::cout << "next_departure: " << next_departure << std::endl;*/
		if (next_arrival < next_departure)
			sim_time = next_arrival;
		else
			sim_time = next_departure;
		update_statistics();
		if (next_arrival < next_departure) {
			if (server_state == State::IDLE) {
				server_state = State::BUSY;
				next_departure = sim_time + rng2.rand_poisson(mean_processing);
			} else {
				queue.push(Task(sim_time));
				TASKS++;
			}
			next_arrival = sim_time + rng1.rand_poisson(mean_arrival);
		} else {
			if (queue.empty()) {
				server_state = State::IDLE;
				next_departure = HUGE_VAL;
			} else {
				Task t = queue.front();
				queue.pop();
				next_departure = sim_time + rng2.rand_poisson(mean_processing);
				waiting_time_total = sim_time - t.arrival_time();
				queue_counter++;
			}
		}
		last_event_time = sim_time;
	}

// at the end of the simulation:
	double avg_queue_length = cumulated_queue_length / sim_time;
	double avg_utilization = busy_time_total / sim_time;
	double man_waiting_time = waiting_time_total / queue_counter;

	std::cout << "TASKS: " << TASKS << std::endl;
	std::cout << "avg_queue_length: " << avg_queue_length << std::endl;
	std::cout << "avg_utilization: " << avg_utilization << std::endl;
	std::cout << "man_waiting_time: " << man_waiting_time << std::endl;

}
