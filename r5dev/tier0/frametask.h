#ifndef TIER0_FRAMETASK_H
#define TIER0_FRAMETASK_H

#include "public/iframetask.h"

//=============================================================================//
// This class is set up to run before each frame (main thread).
// Commited tasks are scheduled to execute after 'i' frames.
// ----------------------------------------------------------------------------
// A usecase for scheduling tasks in the main thread would be (for example)
// calling 'KeyValues::ParsePlaylists(...)' from the render thread.
//=============================================================================//
class CFrameTask : public IFrameTask
{
public:
    virtual ~CFrameTask() {}
    virtual void RunFrame();
    virtual bool IsFinished() const;

    void Dispatch(std::function<void()> functor, int frames);

private:
    mutable std::mutex m_Mutex;
    std::list<DelayedCall_s> m_DelayedCalls;
};

extern std::list<IFrameTask*> g_FrameTasks;
extern CFrameTask* g_TaskScheduler;

#endif // TIER0_FRAMETASK_H
