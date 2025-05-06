#pragma once

#include <ostream>

#include "decorator.h"

class TraceIt : public Decorator {
public:
	explicit TraceIt(std::ostream &stream, std::unique_ptr<Processor> proc)
		: Decorator{std::move(proc)}, stream_{stream} {
	}

	int process(int value) override {
		int rv = Decorator::process(value);
		stream_ << "process(" << value << ") returned " << rv << "\n";
		return rv;
	}

private:
	std::ostream &stream_;
};
