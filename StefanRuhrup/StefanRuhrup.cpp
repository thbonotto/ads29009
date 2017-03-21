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
	Generator() {

	}

	double rand_poisson(double lambda) {
		std::uniform_real_distribution<double> distribution(0.0, 1.0);
		double L = exp(-lambda);
		int k = 0;
		double r=0;
		double p = 1.0000;
		std::cout << "k " << k << " p " << p << " r " << r << " L " << L<< std::endl;
		while (p <= L) {
			k = k + 1;
			r = distribution(generator);
			p = p * r;
			std::cout << "k " << k << " p " << p << " r " << r << " L " << L<< std::endl;
		}
		return k - 1;
	}

	std::default_random_engine generator;
};
const double T_MAX = 0.5;
double mean_arrival=0.5;
double mean_processing=0.3;
std::queue<Task> queue;
State server_state = State::IDLE;
double sim_time = 0.0;
double next_departure = HUGE_VAL; // ← set to infinity

size_t cumulated_queue_length;
double busy_time_total;
double last_event_time = 0.0;
void update_statistics() {
	double time_since_last_event = sim_time - last_event_time;
	cumulated_queue_length += queue.size() * time_since_last_event;
	if (server_state == State::BUSY)
		busy_time_total += time_since_last_event;
}

double waiting_time_total = 0.0;
int main(int argc, char** argv) {
	std::cout << "gen1: " << sim_time << std::endl;
	Generator rng1;
	std::cout << "gen2: " << sim_time << std::endl;
	Generator rng2;
	std::cout << "rand_poisson: " << sim_time << std::endl;
	double next_arrival = rng1.rand_poisson(mean_arrival);

	while (sim_time < T_MAX) {
		std::cout << "sim_time: " << sim_time << std::endl;
		std::cout << "next_arrival: " << next_arrival << std::endl;
		std::cout << "next_departure: " << next_departure << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
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
			}
		}
		last_event_time = sim_time;
	}

// at the end of the simulation:
	double avg_queue_length = cumulated_queue_length / sim_time;
	double avg_utilization = busy_time_total / sim_time;

	std::cout << "avg_queue_length: " << avg_queue_length << std::endl;
	std::cout << "avg_utilization: " << avg_utilization << std::endl;

}
