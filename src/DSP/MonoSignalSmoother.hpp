#pragma once

template <typename T>
class MonoSignalSmoother
{
public:
	MonoSignalSmoother() : target(0), forward_weight(0.9f), intertia_weight(0.1f), memory(0) {};

	void set_target(T target) { this->target = target; }
	void advance() { memory = forward_weight * target + intertia_weight * memory; }
	T get() { advance(); return memory; }

private:
	T target;
	float forward_weight;
	float intertia_weight;
	T memory;
};
