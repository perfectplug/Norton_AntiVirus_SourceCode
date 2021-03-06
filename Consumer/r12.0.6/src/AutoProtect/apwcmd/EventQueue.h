// EventQueue.h: interface for the CEventQueue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTQUEUE_H__1155344E_1C06_4287_B948_848DF7128A06__INCLUDED_)
#define AFX_EVENTQUEUE_H__1155344E_1C06_4287_B948_848DF7128A06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Disable identifier truncation warning generated by
// standard C++ library stuff.
#pragma warning( disable: 4786 )

#include "ole2.h"
#include "SyncQueue.h"
#include "EventData.h"
#include "SAVRT32.h"
#include "VirusAlertQueue.h"

#ifdef AP_COMPRESSED_SUPPORT
    #include "BlockedAppQueue.h"
#else
    class CBlockedAppQueue;
#endif


class CEventQueue : public CSyncQueue< CEventData* >
{
public:
	CEventQueue(void);
	virtual ~CEventQueue();

    // Does the work
    void processQueue ();

    void ProcessVirusEvent (CEventData*& pEventData); // ShutdownScan needs access so it's public
    void ProcessErrorEvent (CEventData*& pEventData);

protected:
    void processContainerStop(CEventData& eventData);
    bool getContainerCookie ( CEventData& eventData, SAVRT_ROUS64& hCookie );
    bool wasCancelled (CEventData& pEventData);
    void ProcessManualScanEvent (CEventData* pEventData);

    // Pointer to Virus Alert event queue object
	std::auto_ptr<CVirusAlertQueue>     m_pVirusAlertQueue;

#ifdef AP_COMPRESSED_SUPPORT
    std::auto_ptr<CBlockedAppQueue>     m_pBlockedAppQueue;
#endif // AP_COMPRESSED_SUPPORT
};

#endif // !defined(AFX_EVENTQUEUE_H__1155344E_1C06_4287_B948_848DF7128A06__INCLUDED_)
