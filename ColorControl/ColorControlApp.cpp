/***************************************************************
 * Name:      ColorControlApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Subhan Waizi (swaizi@hilscher.com)
 * Created:   2015-06-16
 * Copyright: Subhan Waizi ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "ColorControlApp.h"
#include "ColorControlMain.h"


IMPLEMENT_APP(ColorControlApp);

bool ColorControlApp::OnInit()
{


    ColorControlFrame* frame = new ColorControlFrame(0L);
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();

    return true;
}
