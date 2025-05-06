#include <iostream>
#include <memory>

#include "processor.h"
#include "timeit.h"
#include "traceit.h"

int main() {
	bool traceit = true;
	bool timeit = true;

	if (traceit) {
		std::unique_ptr<Processor> proc = std::make_unique<CountPrimesProcessor>();
		proc = std::make_unique<TraceIt>(std::cout, std::move(proc));
		std::cout << proc->process(100'000) << '\n';
	}
	if (timeit) {
		std::unique_ptr<Processor> proc = std::make_unique<CountPrimesProcessor>();
		proc = std::make_unique<TimeIt>(std::cout, std::move(proc));
		std::cout << proc->process(100'000) << '\n';
	}

	return 0;
}