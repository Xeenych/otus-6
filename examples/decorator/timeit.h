#pragma once

#include "decorator.h"
#include <chrono>
#include <ostream>
#include <stdexcept>

class TimeIt : public Decorator {
public:
	explicit TimeIt(std::ostream &stream, std::unique_ptr<Processor> proc)
		: Decorator{std::move(proc)}, stream_{stream} {
	}

	int process(int value) override {
		auto start = std::chrono::high_resolution_clock::now();
		int rv = Decorator::process(value);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = end - start;
		stream_ << "process took " << elapsed.count() << "s\n";
		return rv;
	}

private:
	std::ostream &stream_;
};