#pragma once

template <typename T>
class MonoSignalSmoother
{
public:
	MonoSignalSmoother() : target(0), forward_weight(0.9f), memory(0) {};
	MonoSignalSmoother(float forward_weight) : target(0), forward_weight(forward_weight), memory(0) {};

	void set_target(T target) { this->target = target; }
	void advance() { memory = forward_weight * target + (1.0f - forward_weight) * memory; }
	T get() { advance(); return memory; }

private:
	T target;
	float forward_weight;
	T memory;
};
