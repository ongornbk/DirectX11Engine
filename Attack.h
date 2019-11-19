#pragma once

struct Attack
{
	Attack(void);
	Attack(const float _range);


	float range;
	mutable bool active;
};