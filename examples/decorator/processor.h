#pragma once

class Processor {
public:
	virtual ~Processor() = default;

	virtual int process(int value) = 0;
};

class CountPrimesProcessor : public Processor {
public:
	CountPrimesProcessor(){};

	int process(int value) override {
		int counter = 0;
		for (int i = 0; i < value; ++i) {
			counter += is_prime(i);
		}
		return counter;
	}

protected:
	static bool is_prime(int value) {
		if (value < 2) {
			return false;
		}

		for (int i = 2; i < value; ++i) {
			if (value % i == 0) {
				return false;
			}
		}
		return true;
	}
};
