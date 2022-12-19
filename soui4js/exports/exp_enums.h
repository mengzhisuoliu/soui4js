#pragma once

#include <qjsbind.h>
#include <event/SEvents.h>
#include <core/SDefine.h>
using namespace SOUI;

#define SEnumInt(x) module->ExportEnumInt32(#x, x)
#define SEnumUint(x) module->ExportEnumUint32(#x, x)

void Exp_SEnum(qjsbind::Module* module){
//soui events
SEnumInt(EVT_INIT);
SEnumInt(EVT_EXIT);
SEnumInt(EVT_TIMER);
SEnumInt(EVT_SETFOCUS);
SEnumInt(EVT_KILLFOCUS);
SEnumInt(EVT_CREATE);
SEnumInt(EVT_INIT_FINISH);
SEnumInt(EVT_DESTROY);
SEnumInt(EVT_SIZE);
SEnumInt(EVT_VISIBLECHANGED);
SEnumInt(EVT_STATECHANGED);
SEnumInt(EVT_LBUTTONDOWN);
SEnumInt(EVT_LBUTTONUP);
SEnumInt(EVT_UPDATE_TOOLTIP);
SEnumInt(EVT_ANIMATION_START);
SEnumInt(EVT_ANIMATION_STOP);
SEnumInt(EVT_ANIMATION_REPEAT);
SEnumInt(EVT_POS);
SEnumInt(EVT_KEYDOWN);
SEnumInt(EVT_MOUSE_HOVER);
SEnumInt(EVT_MOUSE_LEAVE);
SEnumInt(EVT_CMD);
SEnumInt(EVT_CTXMENU);
SEnumInt(EVT_SCROLLVIEW_ORIGINCHANGED);
SEnumInt(EVT_SCROLLVIEW_SIZECHANGED);
SEnumInt(EVT_SCROLL);
SEnumInt(EVT_OFEVENT);
SEnumInt(EVT_OFPANEL);
SEnumInt(EVT_ITEMPANEL_CLICK);
SEnumInt(EVT_ITEMPANEL_RCLICK);
SEnumInt(EVT_ITEMPANEL_CLICK_UP);
SEnumInt(EVT_ITEMPANEL_RCLICK_UP);
SEnumInt(EVT_ITEMPANEL_DBCLICK);
SEnumInt(EVT_ITEMPANEL_HOVER);
SEnumInt(EVT_ITEMPANEL_LEAVE);
SEnumInt(EVT_RADIOGROUP_CHECK_CHANGED);
SEnumInt(EVT_TAB_SELCHANGING);
SEnumInt(EVT_TAB_SELCHANGED);
SEnumInt(EVT_TAB_ITEMHOVER);
SEnumInt(EVT_TAB_ITEMLEAVE);
SEnumInt(EVT_LB_SELCHANGING);
SEnumInt(EVT_LB_SELCHANGED);
SEnumInt(EVT_LB_DBCLICK);
SEnumInt(EVT_LC_SELCHANGING);
SEnumInt(EVT_LC_SELCHANGED);
SEnumInt(EVT_LC_ITEMDELETED);
SEnumInt(EVT_LC_DBCLICK);
SEnumInt(EVT_TV_SELCHANGING);
SEnumInt(EVT_TV_SELCHANGED);
SEnumInt(EVT_TC_SELCHANGING);
SEnumInt(EVT_TC_SELCHANGED);
SEnumInt(EVT_TC_EXPAND);
SEnumInt(EVT_TC_CHECKSTATE);
SEnumInt(EVT_TC_DBCLICK);
SEnumInt(EVT_CB_BEFORE_CLOSEUP);
SEnumInt(EVT_LV_SELCHANGING);
SEnumInt(EVT_LV_SELCHANGED);
SEnumInt(EVT_LV_ITEMCLICK);
SEnumInt(EVT_RE_NOTIFY);
SEnumInt(EVT_RE_MENU);
SEnumInt(EVT_SLIDER_POS);
SEnumInt(EVT_HEADER_CLICK);
SEnumInt(EVT_HEADER_ITEMCHANGING);
SEnumInt(EVT_HEADER_ITEMCHANGED);
SEnumInt(EVT_HEADER_ITEMSWAP);
SEnumInt(EVT_HEADER_RELAYOUT);
SEnumInt(EVT_CB_SELCHANGE);
SEnumInt(EVT_CB_DROPDOWN);
SEnumInt(EVT_CALENDAR_SELDAY);
SEnumInt(EVT_CALENDAR_SETDATE);
SEnumInt(EVT_CALENDAREX_CHANGED);
SEnumInt(EVT_DATETIME_CHANGED);
SEnumInt(EVT_SPIN_VALUE2STRING);
SEnumInt(EVT_SPLIT_PANE_MOVED);
SEnumInt(EVT_HOT_KEY_SET);
SEnumInt(EVT_IMAGE_ANI_START);
SEnumInt(EVT_IMAGE_ANI_STOP);
SEnumInt(EVT_SELECTMENU);
SEnumInt(EVT_POPMENU);
SEnumInt(EVT_EXTERNAL_BEGIN);

SEnumUint(STVI_ROOT);
SEnumUint(STVI_FIRST);
SEnumUint(STVI_LAST);

SEnumUint(TVC_COLLAPSE);
SEnumUint(TVC_EXPAND);
SEnumUint(TVC_TOGGLE);

SEnumUint(WndState_Normal);
SEnumUint(WndState_Hover);
SEnumUint(WndState_PushDown);
SEnumUint(WndState_Check);
SEnumUint(WndState_Invisible);
SEnumUint(WndState_Disable);

SEnumUint(kAniNone);
SEnumUint(kFadeInOut);
SEnumUint(kMoveInOut);
SEnumUint(kPushInOut);

//msgbox
SEnumUint(MB_OK);
SEnumUint(MB_OKCANCEL);
SEnumUint(MB_YESNO);
SEnumUint(MB_YESNOCANCEL);
SEnumUint(MB_RETRYCANCEL);
SEnumUint(MB_ICONWARNING);
SEnumUint(MB_ICONINFORMATION);
SEnumUint(MB_ICONQUESTION);
SEnumUint(MB_ICONSTOP);
SEnumUint(MB_ICONERROR);

//show window
SEnumUint(SW_SHOW);
SEnumUint(SW_HIDE);
SEnumUint(SW_SHOWDEFAULT);
SEnumUint(SW_SHOWNORMAL);
SEnumUint(SW_SHOWNOACTIVATE);
SEnumUint(SW_SHOWMAXIMIZED);
SEnumUint(SW_SHOWMINIMIZED);
SEnumUint(SW_RESTORE);
SEnumUint(SW_MAXIMIZE);
SEnumUint(SW_MINIMIZE);

//msg
SEnumUint(WM_INITDIALOG);
SEnumUint(WM_CREATE);
SEnumUint(WM_DESTROY);
SEnumUint(WM_CLOSE);
SEnumUint(WM_COMMAND);
SEnumUint(WM_SYSCOMMAND);

}