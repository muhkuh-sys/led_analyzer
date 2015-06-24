#include "CLua.h"

CLua::CLua()
{
    m_pLuaState = lua_open();
    luaL_openlibs(m_pLuaState);
    m_ColorControlLoaded = false;
}

CLua::~CLua()
{
    lua_close(m_pLuaState);
}

void CLua::StackDump()
{
      int i;
      int top = lua_gettop(this->m_pLuaState);
      for (i = 1; i <= top; i++) {  /* repeat for each level */
        int t = lua_type(this->m_pLuaState, i);
        switch (t) {

          case LUA_TSTRING:  /* strings */
            //wxLogMessage("%s", lua_tostring(this->m_pLuaState, i));
            cout << "isString: '" << lua_tostring(this->m_pLuaState, i) << "'";
            break;

          case LUA_TBOOLEAN:  /* booleans */
            cout << "isBoolean: " << ((bool)lua_toboolean(this->m_pLuaState, i) ? "true" : "false") << endl;
           break;

          case LUA_TNUMBER:  /* numbers */
            cout << "isNumber: " << lua_tonumber(this->m_pLuaState, i);
            break;

          default:  /* other values */
            cout << "isOther" << lua_typename(this->m_pLuaState, t);
            break;

        }
        cout << "  ";  /* put a separator */
      }
      cout << endl;
}


int  CLua::LoadAndRun(char* pcFilename)
{
    /* Be pessimistic */
    int iRetVal = 1;
    iRetVal = luaL_loadfile(this->m_pLuaState, pcFilename);

    if(iRetVal)
    {
        wxLogMessage("Couldn't load and run file: %s", pcFilename);
        return iRetVal;
    }

    iRetVal = lua_pcall(this->m_pLuaState, 0, 0, 0);

    if(iRetVal)
    {
       wxLogMessage("Couldn't run file: %s", pcFilename);
       return iRetVal;
    }


    m_ColorControlLoaded = true;

    return iRetVal;

}



int CLua::ScanDevices(int &iNumberOfDevices, wxString *aStrSerials)
{

    /* Be pessimistic */
    int iRetval = 1;

    if(!(this->IsLoaded()))
    {
        wxLogMessage("Color Control is not loaded!");
        return -1;
    }

    lua_getglobal(this->m_pLuaState, "scanDevices");

    if (lua_pcall(this->m_pLuaState, 0, 2, 0) != 0)
    {
        wxLogMessage("Error Running Function %s", lua_tostring(this->m_pLuaState, -1));
        iRetval = 1;
    }

    /* First return value must be a number (number of connected devices) */
    if (!lua_isnumber(this->m_pLuaState, -1))
    {
        wxLogMessage("Number of devices expected got sth else!");
        iRetval = 1;
    }

    iNumberOfDevices = lua_tonumber(this->m_pLuaState, -1);

    /* Pop number of devices, now serial number table is at top */
    lua_pop(this->m_pLuaState, 1);


    /* Second return value must be a table that contains serial numbers, its on stack top now */
    if(!lua_istable(this->m_pLuaState, -1))
    {
        wxLogMessage("Table expected, got sth else!");
        iRetval = 1;
    }

    for(int i = 0; i < iNumberOfDevices; i++)
    {
        aStrSerials[i] = wxString::FromUTF8(this->GetField(i+1));
    }


    /* Pop the table */
    lua_pop(this->m_pLuaState, 1);

    return iRetval;
}

int CLua::ConnectDevices(int &iNumberOfDevices)
{
    /* Be pessimistic */
    int iRetval = 1;

    if(!(this->IsLoaded()))
    {
        wxLogMessage("Color Control is not loaded!");
        return -1;
    }

    lua_getglobal(this->m_pLuaState, "connectDevices");

    if (lua_pcall(this->m_pLuaState, 0, 1, 0) != 0)
    {
        wxLogMessage("Error Running Function %s", lua_tostring(this->m_pLuaState, -1));
        iRetval = 1;
    }

    /* First return value must be a number (number of device we connected to) */
    if (!lua_isnumber(this->m_pLuaState, -1))
    {
        wxLogMessage("Number of devices expected got sth else!");
        iRetval = 1;
    }

    iNumberOfDevices = lua_tonumber(this->m_pLuaState, -1);

    /* Pop number of devices*/
    lua_pop(this->m_pLuaState, 1);

    /* As we have no return values, we can end here */


    iRetval = 0;

    return iRetval;
}

/** @brief Returns table[intIndex], assumes that table is at top of stack */
char* CLua::GetField(int iIndex)
{
    char* strValue;
    /* Now the index is at top of the stack (-1)*/
    lua_pushnumber(this->m_pLuaState, iIndex);

    lua_gettable(this->m_pLuaState, -2); /* get table[intIndex] */

    if(!lua_isstring(this->m_pLuaState, -1))
    {
        wxLogMessage("Serialnumber expected, got something else");
    }

    strValue = (char*)lua_tostring(this->m_pLuaState, -1);

    /* remove the serialnumber from stack */
    lua_pop(this->m_pLuaState, 1);

    return strValue;
}

int CLua::SwapUp(wxString* aStrSerials, wxString strCurSerial, int iNumberOfDevices)
{
    int iRetval = 1;

    if(!(this->IsLoaded()))
    {
        wxLogMessage("Color Control is not loaded!");
        return -1;
    }

    lua_getglobal(this->m_pLuaState, "swapUp");

    /* Push serial number to be swapped up */
    lua_pushstring(this->m_pLuaState, strCurSerial);

    /* Call the function with 1 argument and one return expected value */
    if (lua_pcall(this->m_pLuaState, 1, 1, 0) != 0)
    {
        wxLogMessage("Error Running Function %s", lua_tostring(this->m_pLuaState, -1));
        iRetval = 1;
    }

    /* Get your table */
    if(!lua_istable(this->m_pLuaState, -1))
    {
        wxLogMessage("Table expected, got sth else!");
        iRetval = 1;
    }

    for(int i = 0; i < iNumberOfDevices; i++)
    {
        aStrSerials[i] = wxString::FromUTF8(this->GetField(i+1));
    }

    iRetval = 0;

    /* Pop the table */
    lua_pop(this->m_pLuaState, 1);


    return iRetval;
}


int CLua::SwapDown(wxString* aStrSerials, wxString strCurSerial, int iNumberOfDevices)
{
    int iRetval = 1;

    if(!(this->IsLoaded()))
    {
        wxLogMessage("Color Control is not loaded!");
        return -1;
    }

    lua_getglobal(this->m_pLuaState, "swapDown");

    /* Push serial number to be swapped up */
    lua_pushstring(this->m_pLuaState, strCurSerial);

    /* Call the function with 1 argument and one return expected value */
    if (lua_pcall(this->m_pLuaState, 1, 1, 0) != 0)
    {
        wxLogMessage("Error Running Function %s", lua_tostring(this->m_pLuaState, -1));
        iRetval = 1;
    }

    /* Get your table */
    if(!lua_istable(this->m_pLuaState, -1))
    {
        wxLogMessage("Table expected, got sth else!");
        iRetval = 1;
    }

    for(int i = 0; i < iNumberOfDevices; i++)
    {
        aStrSerials[i] = wxString::FromUTF8(this->GetField(i+1));
    }

    iRetval = 0;

    /* Pop the table */
    lua_pop(this->m_pLuaState, 1);


    return iRetval;
}
