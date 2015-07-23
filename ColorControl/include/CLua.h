#ifndef CLUA_H
#define CLUA_H

extern "C"
{
    #define  lua_c
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#include "GUIFrame.h"
#include "CDevice.h"


class CLua
{
    public:
        CLua(const char* filename=NULL);
        virtual ~CLua();
        /* Color Controller related functions */
        int  ScanDevices(int &iNumberOfDevices, wxString *aStrSerials);
        int  ConnectDevices(int &iNumberOfDevices);
        int  LoadAndRun(const char* filename);
        void StackDump();
        int  SwapUp  (wxString* aStrSerials, wxString strCurSerial, int iNumberOfDevices);
        int  SwapDown(wxString* aStrSerials, wxString strCurSerial, int iNumberOfDevices);
        bool IsLoaded(){return m_luaFileLoaded;};
        int  StartMeasurements();
        int  InitDevices(wxVector<CColorController*> vectorDevices);
        int  ReadColours(wxVector<CColorController*> vectorDevices);
        int  SetGainX(int iDeviceIndex, int iSensorIndex, tcs3472_gain_t gain);
        int  SetIntTimeX(int iDeviceIndex, int iSensorIndex, tcs3472_intTime_t intTime);
        int  FastSettings(wxVector<CColorController*> vectorDevices, unsigned char ucSetting, int iSelection);

        int  GetInterfaces(wxArrayString &astrInterfaces);
        int  RunGeneratedTest(const char* pcFilename);
        void CleanUp();

    protected:
    private:
        bool m_luaFileLoaded;
        lua_State* m_pLuaState;

        lua_CFunction   Panic(){return 0;};
        char   *GetStrField  (int   iIndex);
        int     GetIntField  (const char* strKey);
        int     GetIntField  (int   iIndex);
        void    GetTableField(int iIndex);
        /* Define your panic function with CFunctions as parameters */

};

#endif // CLUA_H


