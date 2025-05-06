#pragma once

#include <memory>
#include <stdexcept>

#include "processor.h"

class Decorator : public Processor {
public:
	explicit Decorator(std::unique_ptr<Processor> proc)
		: proc_{std::move(proc)} {
		if (!proc_) {
			throw std::invalid_argument{"Processor is empty"};
		}
	}

	int process(int value) override {
		return proc_->process(value);
	}

private:
	std::unique_ptr<Processor> proc_;
};