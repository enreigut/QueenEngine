#pragma once

class Manager
{
public:
	Manager() {}
	~Manager() {}

	// Getters
	inline const bool IsRunning()& { return m_isRunning; }

	// Setters
	inline void SetRunning(bool&& val) { m_isRunning = val; }

	// Derived
	virtual void Start() = 0;
	virtual void Shutdown() = 0;

private:
	bool m_isRunning = false;
};