#pragma once

class FrameLocker
{
	bool  m_state;
	double m_lock;
	double m_time;
	double m_deltaTime;
public:
	FrameLocker(const float lock);
	~FrameLocker();

	bool Run() noexcept;
	bool State() const noexcept;
	void Update(const float dt) noexcept;
	const float GetDeltaTime() noexcept;
};

