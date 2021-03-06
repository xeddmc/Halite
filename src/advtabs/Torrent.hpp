
//         Copyright Eóin O'Callaghan 2006 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#define HAL_PEER_INTERESTING            			40037
#define HAL_PEER_CHOKED             			    40038
#define HAL_PEER_REMOTE_INTERESTING					40039
#define HAL_PEER_REMOTE_CHOKED						40040
#define HAL_PEER_SUPPORT_EXTENSIONS					40041
#define HAL_PEER_LOCAL_CONNECTION					40042
#define HAL_PEER_HANDSHAKE							40043
#define HAL_PEER_CONNECTING							40044
#define HAL_PEER_QUEUED								40045
#define HAL_PEER_RC4_ENCRYPTED						40046
#define HAL_PEER_PLAINTEXT_ENCRYPTED				40047
#define HAL_TORRENT_QUEUED_CHECKING					40050
#define HAL_TORRENT_CHECKING_FILES					40051
#define HAL_TORRENT_CONNECTING						40052
#define HAL_TORRENT_DOWNLOADING						40053
#define HAL_TORRENT_FINISHED						40054
#define HAL_TORRENT_SEEDING							40055
#define HAL_TORRENT_ALLOCATING						40056
#define HAL_TORRENT_QUEUED							40057
#define HAL_TORRENT_STOPPED							40058
#define HAL_TORRENT_PAUSED							40059
#define HAL_PEER_ON_PAROLE      					40060
#define HAL_PEER_OPTIMISTIC_UNCHOKE				40061
#define HAL_PEER_SNUBBED						40062
#define HAL_PEER_UPLOAD_ONLY						40063
#define HAL_TORRENT_STOPPING						50000
#define HAL_TORRENT_PAUSING							50001

#ifndef RC_INVOKED

#include "stdAfx.hpp"
#include "Halite.hpp"

#include "DdxEx.hpp"
#include "global/string_conv.hpp"

#include "../HaliteTabPage.hpp"
#include "../HaliteEditCtrl.hpp"
#include "../HaliteDialogBase.hpp"

class AdvTorrentDialog :
	public CHalTabPageImpl<AdvTorrentDialog>,
	public ATL::CAutoSizeWindow<AdvTorrentDialog, false>,
	public CHaliteDialogBase<AdvTorrentDialog>,
	public WTLx::WinDataExchangeEx<AdvTorrentDialog>
{
protected:
	typedef AdvTorrentDialog this_class_t;
	typedef CHalTabPageImpl<AdvTorrentDialog> base_class_t;
	typedef ATL::CAutoSizeWindow<AdvTorrentDialog, false> autosizeClass;
	typedef CHaliteDialogBase<AdvTorrentDialog> dlg_base_class_t;

public:
	enum { IDD = HAL_ADVOVERVIEW };

	AdvTorrentDialog(HaliteWindow& HalWindow) :
		dlg_base_class_t(HalWindow)
	{}
	
	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return this->IsDialogMessage(pMsg);
	}
	
	BEGIN_MSG_MAP_EX(this_class_t)
		try
		{
		MSG_WM_INITDIALOG(onInitDialog)
		MSG_WM_CLOSE(onClose)

		MESSAGE_HANDLER_EX(WM_USER_HAL_EDITCHANGED, OnHalEditChanged)
		}
		HAL_ALL_EXCEPTION_CATCH(L"in AdvTorrentDialog MSG_MAP")

		if (uMsg == WM_FORWARDMSG)
			if (PreTranslateMessage((LPMSG)lParam)) return TRUE;

		CHAIN_MSG_MAP(dlg_base_class_t)
		CHAIN_MSG_MAP(autosizeClass)
		CHAIN_MSG_MAP(base_class_t)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	BEGIN_DDX_MAP(this_class_t)
    END_DDX_MAP()
	
	TRANSPARENT_LIST(this_class_t, HAL_GROUP_TORRENT, HAL_GROUP_TRACKER, HAL_TL, HAL_NAME_STATUS_LABEL)
	
	static CWindowMapStruct* GetWindowMap();
	
	LRESULT onInitDialog(HWND, LPARAM);
	void onClose();

	LRESULT OnHalEditChanged(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void uiUpdate(const hal::torrent_details_manager& tD);
	void uiUpdateMultiple(const hal::torrent_details_vec& torrents);
	void uiUpdateSingle(const hal::torrent_details_ptr& torrent);
	void uiUpdateNone();
	void focusChanged(const hal::torrent_details_ptr pT);

protected:
	WTL::CProgressBarCtrl m_prog;

	CHaliteEditCtrl<int> totalConnections_;
	CHaliteEditCtrl<int> uploadConnections_;
	CHaliteEditCtrl<float> downloadRate_;
	CHaliteEditCtrl<float> uploadRate_;
//	CHaliteEditCtrl<float> ratio_;
	
	string current_torrent_name_;
};

#endif // RC_INVOKED
