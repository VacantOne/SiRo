#include "MySystem.h"


void UMySystem::TickCheck(float DeltaSeconds)
{
	// if (0 == m_fTickInterval)
	// 	return;
	// if (m_fCurrentTick + DeltaSeconds < m_fTickInterval)
	// {
	// 	m_fCurrentTick += DeltaSeconds;
	// 	return;
	// }
	NativeTick(DeltaSeconds);
	Tick(DeltaSeconds);
	// m_fCurrentTick = 0;
}

void UMySystem::SetTickInterval(float fTickInterval)
{
	m_fTickInterval = fTickInterval;
}
