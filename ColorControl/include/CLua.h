#ifndef CLUA_H
#define CLUA_H

extern "C"
{
    #define  lua_c
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"

}

#include "../GUIFrame.h"

class CLua
{
    public:
        CLua();
        virtual ~CLua();
        int  ScanDevices(int &iNumberOfDevices, wxString *aStrSerials);
        int  ConnectDevices(int &iNumberOfDevices);
        int  LoadAndRun(char* filename);
        void StackDump();
        int  SwapUp  (wxString* aStrSerials, wxString strCurSerial, int iNumberOfDevices);
        int  SwapDown(wxString* aStrSerials, wxString strCurSerial, int iNumberOfDevices);
        bool IsLoaded(){return m_ColorControlLoaded;};


//        int lua_load
    protected:
    private:
        bool m_ColorControlLoaded;
        lua_State* m_pLuaState;


        char   *GetField(int   iIndex);
        int    GetField(char* strIndex);
        /* Define your panic function with CFunctions as parameters */
        // void Panic(){lua_atpanic(this->m_pLuaState());};
};

#endif // CLUA_H


