#pragma once
#include "Singleton.h"
#include "SFML/Graphics.hpp"

class Framework : public Singleton<Framework>
{
public:
	// Virtuals
	virtual void Init(int width, int height, const std::string& name);
	virtual void Do();
	virtual void Release();

	// Getter
	inline float GetTime() const { return time; }
	inline float GetDeltaTime() const { return deltaTime; }
	inline float GetRealTime() const { return realTime; }
	inline float GetRealDeltaTime() const { return realDeltaTime; }
	inline float GetTimeScale() const { return timeScale; }

	// Setter
	void SetTimeScale(float newTimeScale) { timeScale = newTimeScale; }
	void SetTime(float newTime) { time = newTime; }
	void SetDeltaTime(float newDeltaTime) { deltaTime = newDeltaTime; }
	void GetRealTime(float newRealTime) { realTime = newRealTime; }
	void GetRealDeltaTime(float newRealDeltaTime) { realDeltaTime = newRealDeltaTime; }

protected:
	sf::RenderWindow window;

	sf::Clock clock;
	float timeScale = 1.f;

	float time = 0.f;
	float deltaTime = 0.f;
	float realTime = 0.f;
	float realDeltaTime = 0.f;
};
