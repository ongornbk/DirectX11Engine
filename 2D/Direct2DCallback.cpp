#include "Direct2DCallback.h"

void (*Direct2DCallback::m_renderCallback)(void) = nullptr;
void(*Direct2DCallback::m_updateCallback)(void) = nullptr;