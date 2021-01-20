#pragma once

class FrameLocker
{
	float m_lock;
	float m_time;
	float m_deltaTime;
public:
	FrameLocker(const float lock);
	~FrameLocker();

	bool Run() noexcept;
	void Update(const float dt) noexcept;
	const float GetDeltaTime() noexcept;
};

