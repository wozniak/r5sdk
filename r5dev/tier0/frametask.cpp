//=============================================================================//
//
// Purpose: 
// 
//-----------------------------------------------------------------------------
//
//=============================================================================//
#include "core/stdafx.h"
#include "tier0/frametask.h"

//-----------------------------------------------------------------------------
// Purpose: run frame task and process queued calls
//-----------------------------------------------------------------------------
void CFrameTask::RunFrame()
{
    std::lock_guard<std::mutex> l(m_Mutex);
    for (auto& delay : m_DelayedCalls)
    {
        delay.m_nDelayedFrames = (std::max)(delay.m_nDelayedFrames - 1, 0);
        if (delay.m_nDelayedFrames == 0)
        {
            delay.m_rFunctor();
        }
    }

    auto newEnd = std::remove_if(m_DelayedCalls.begin(), m_DelayedCalls.end(), [](const DelayedCall_s& delay)
        {
            return delay.m_nDelayedFrames == 0;
        });
    m_DelayedCalls.erase(newEnd, m_DelayedCalls.end());
}

//-----------------------------------------------------------------------------
// Purpose: is the task finished
// Output : true if finished, false otherwise
//-----------------------------------------------------------------------------
bool CFrameTask::IsFinished() const
{
    return false;
}

//-----------------------------------------------------------------------------
// Purpose: adds function to list, to be called after 'i' frames.
// Input  : functor - 
//          frames - 
//-----------------------------------------------------------------------------
void CFrameTask::Dispatch(std::function<void()> functor, int frames)
{
    std::lock_guard<std::mutex> l(m_Mutex);
    m_DelayedCalls.emplace_back(frames, functor);
}

//-----------------------------------------------------------------------------
std::list<IFrameTask*> g_FrameTasks;
CFrameTask* g_TaskScheduler = new CFrameTask();
