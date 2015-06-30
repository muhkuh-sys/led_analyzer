#include "CLua.h"


int Panic(lua_State* state)
{

    wxLogMessage("LUA PANIC FUNCTION ERROR OCCURED!!!!");
    return 0;
}



CLua::CLua(char* filename)
{
    m_pLuaState = lua_open();
    luaL_openlibs(m_pLuaState);

    /* Initially false */
    m_ColorControlLoaded = false;

    /* This function will set m_colorControlLoaded to true if successful */
    this->LoadAndRun(filename);

}


CLua::~CLua()
{
    this->CleanUp();
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
        return iRetval;
    }

    /* First return value must be a number (number of connected devices) */
    if (!lua_isnumber(this->m_pLuaState, -1))
    {
        wxLogMessage("Number of devices expected got sth else!");
        return iRetval;
    }

    iNumberOfDevices = lua_tonumber(this->m_pLuaState, -1);

    /* Pop number of devices, now serial number table is at top */
    lua_pop(this->m_pLuaState, 1);


    /* Second return value must be a table that contains serial numbers, its on stack top now */
    if(!lua_istable(this->m_pLuaState, -1))
    {
        wxLogMessage("Table expected, got sth else!");
        return iRetval;
    }

    for(int i = 0; i < iNumberOfDevices; i++)
    {
        aStrSerials[i] = wxString::FromUTF8(this->GetStrField(i+1));
    }

    /* Pop the table */
    lua_pop(this->m_pLuaState, 1);

    iRetval = 0;

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
        return iRetval;
    }

    /* First return value must be a number (number of device we connected to) */
    if (!lua_isnumber(this->m_pLuaState, -1))
    {
        wxLogMessage("Number of devices expected got sth else!");
        return iRetval;
    }

    iNumberOfDevices = lua_tonumber(this->m_pLuaState, -1);

    /* Pop number of devices*/
    lua_pop(this->m_pLuaState, 1);

    /* As we have no return values, we can successfully finish */
    iRetval = 0;
    return iRetval;
}


int CLua::InitDevices(int iNumberOfDevices)
{
    /* Be pessimistic */
    int iRetval = 1;

    if(!(this->IsLoaded()))
    {
        wxLogMessage("Color Control is not loaded!");
        return -1;
    }

    /* Load Init Function */
    lua_getglobal(this->m_pLuaState, "initDevices");

    /* Push number of devices as first argument onto the stack */
    lua_pushnumber(this->m_pLuaState, iNumberOfDevices);

    /* Run Init Function */
    if( lua_pcall(this->m_pLuaState, 1, 1, 0) != 0)
    {
        wxLogMessage("Error Running Function %s", lua_tostring(this->m_pLuaState, -1));
        return iRetval;
    }

    /* Get the result (0 if everything fine) */
    if(!lua_isnumber(this->m_pLuaState, -1))
    {
        wxLogMessage("Retval (int) expected, got something else");
        return iRetval;
    }

    /* Get the result */
    iRetval = lua_tonumber(this->m_pLuaState, -1);

    /* Pop the result from the stack */
    lua_pop(this->m_pLuaState, 1);

    return iRetval;
}

int CLua::StartMeasurements(int iNumberOfDevices)
{
    /* Be pessimistic */
    int iRetval = 1;

    if(!(this->IsLoaded()))
    {
        wxLogMessage("Color Control is not loaded!");
        return -1;
    }

    /* Load Measurment Function */
    lua_getglobal(this->m_pLuaState, "startMeasurements");

    /* Expected Argument: numberOfDevices ... push it onto the stack*/
    lua_pushnumber(this->m_pLuaState, iNumberOfDevices);

    /* Run Measurement Function */
    if( lua_pcall(this->m_pLuaState, 1, 1, 0) != 0)
    {
        wxLogMessage("Error Running Function %s", lua_tostring(this->m_pLuaState, -1));
        return iRetval;
    }

    /* Get the result (0 if everything fine) */
    if(!lua_isnumber(this->m_pLuaState, -1))
    {
        wxLogMessage("Retval (int) expected, got something else!");
        return iRetval;
    }

    /* Get the result */
    iRetval = lua_tonumber(this->m_pLuaState, -1);

    /* Pop the result from the stack */
    lua_pop(this->m_pLuaState, 1);


    return iRetval;


}

int CLua::ReadColours(int iNumberOfDevices, wxVector<CColorController*> vectorDevices)
{

    /* Be pessimistic */
    int iRetVal = 1;
    /* push your global table onto the stack */

    if(!(this->IsLoaded()))
    {
        wxLogMessage("Color Control is not loaded!");
        return -1;
    }

    lua_getglobal(this->m_pLuaState, "tColorTable");

    /* check if it is a table */
    if(!lua_istable(this->m_pLuaState, -1))
    {
        wxLogMessage("'tColorTable' is not a valid color table");
    }

    /* Iterate Over Devices (THERE MUST BE DEVICES) otherwise LUA will error !!! */
    for(int i = 0; i < iNumberOfDevices; i++)
    {
        /* Load tColorTable[i] = device */
        this->GetTableField(i);

        /* Load tColorTable[i][1] = device(wavelength) */
        this->GetTableField(1);

        /* Iterate over sensors (16 per device -- sensortable index starts at 1) */
        for(int j = 1; j <= 16; j++)
        {

            /* Load tColorTable[i][1][j] = device(wavelength(sensor)) */
            this->GetTableField(j);

            /* Now Fill your vector with the retrieved Values (key: nm, sat, lux, r, g, b)*/
            vectorDevices.at(i)->SetWavelength  ( j-1, this->GetIntField("nm"));
            vectorDevices.at(i)->SetSaturation  ( j-1, this->GetIntField("sat"));
            vectorDevices.at(i)->SetIllumination( j-1, this->GetIntField("lux"));
            vectorDevices.at(i)->SetColour      ( j-1, this->GetIntField("r"),
                                                       this->GetIntField("g"),
                                                       this->GetIntField("b"));
            vectorDevices.at(i)->SetClearRatio  ( j-1, this->GetIntField("clear_ratio"));


            /* Pop sensor Table */
            lua_pop(this->m_pLuaState, 1);

        }

        /* Pop wavelength Table */
        lua_pop(this->m_pLuaState, 1);

        /* Load tColorTable[i][6] = device(settings) */
        this->GetTableField(6);

        /* Iterate over sensors (16 per device -- sensor table index starts at 1 */
        for(int j=1; j<= 16; j++)
        {
            /* Load tColorTable[i][6][j] = device(settings(sensor)) */
            this->GetTableField(j);

            /* Set your gain */
            vectorDevices.at(i)->SetGain( j-1, (tcs3472_gain_t)this->GetIntField("gain"));

            /* Set your integration time */
            vectorDevices.at(i)->SetIntTime( j-1, (tcs3472_intTime_t)this->GetIntField("intTime"));

            /* Pop current sensortable */
            lua_pop(this->m_pLuaState, 1);

        }

        /* Pop settings table */
        lua_pop(this->m_pLuaState, 1);

        /* Pop Device Table */
        lua_pop(this->m_pLuaState, 1);
    }

    /* Pop tColorTable -- Stack should have the state it had before entering this function */
    lua_pop(this->m_pLuaState, 1);

    /* Leave */

}

/** Set the Integration time for one sensor on one device */
int CLua::SetGainX(int iDeviceIndex, int iSensorIndex, tcs3472_gain_t gain)
{
    /* Be pessimistic */
    int iRetVal = 1;
    /* push your global table onto the stack */

    if(!(this->IsLoaded()))
    {
        wxLogMessage("Color Control is not loaded!");
        return -1;
    }

    /* Get your global Set Gain Function */
    lua_getglobal(this->m_pLuaState, "setGainX");

    /* Push your first argument = DeviceIndex */
    lua_pushnumber(this->m_pLuaState, iDeviceIndex);

    /* Push your second argument = SensorIndex */
    lua_pushnumber(this->m_pLuaState, iSensorIndex);

    /* Push your third argument = gain */
    lua_pushnumber(this->m_pLuaState, gain);

    /* Now run the function */
    if (lua_pcall(this->m_pLuaState, 3,1,0) != 0)
    {
        wxLogMessage("Error Running Function %s", lua_tostring(this->m_pLuaState, -1));
        return iRetVal;
    }

    /* Get your result .. if successful it's zero */
    if (!lua_isnumber(this->m_pLuaState, -1))
    {
        wxLogMessage("Retval (int) expected, got something else!");
    }

    /* Retrieve it */
    iRetVal = lua_tonumber(this->m_pLuaState, -1);

    /* Pop the retrieved value */
    lua_pop(this->m_pLuaState, 1);

    /* return */
    return iRetVal;

}

/** Set the Integration time for one sensor on one device */
int CLua::SetIntTimeX(int iDeviceIndex, int iSensorIndex, tcs3472_intTime_t intTime)
{
    /* Be pessimistic */
    int iRetVal = 1;
    /* push your global table onto the stack */

    if(!(this->IsLoaded()))
    {
        wxLogMessage("Color Control is not loaded!");
        return -1;
    }

    /* Get your global Set Gain Function */
    lua_getglobal(this->m_pLuaState, "setIntTimeX");

    /* Push your first argument = DeviceIndex */
    lua_pushnumber(this->m_pLuaState, iDeviceIndex);

    /* Push your second argument = SensorIndex */
    lua_pushnumber(this->m_pLuaState, iSensorIndex);

    /* Push your third argument = gain */
    lua_pushnumber(this->m_pLuaState, intTime);

    /* Now run the function */
    if (lua_pcall(this->m_pLuaState, 3,1,0) != 0)
    {
        wxLogMessage("Error Running Function %s", lua_tostring(this->m_pLuaState, -1));
        return iRetVal;
    }

    /* Get your result .. if successful it's zero */
    if (!lua_isnumber(this->m_pLuaState, -1))
    {
        wxLogMessage("Retval (int) expected, got something else!");
    }

    /* Retrieve it */
    iRetVal = lua_tonumber(this->m_pLuaState, -1);

    /* Pop the retrieved value */
    lua_pop(this->m_pLuaState, 1);

    /* return */
    return iRetVal;
}

/* Assumes table is at top of stack, returns table[strKey] */
int CLua::GetIntField(char* strKey)
{
    int iValue;
    /* push your key onto the stack */
    lua_pushstring(this->m_pLuaState, strKey);

    /* Get your table[strKey] */
    lua_gettable(this->m_pLuaState, -2);

    /* Check if you really got an integer */
    if(!lua_isnumber(this->m_pLuaState, -1))
    {
        wxLogMessage("Number expected, got sth else!");
    }

    /* Get your integer */
    iValue = round(lua_tonumber(this->m_pLuaState, -1));

    /* Pop the retrieved integer from the stack -> table at top */
    lua_pop(this->m_pLuaState, 1);

    /* Return your integer */
    return iValue;
}


/** @brief Pushes anothertable = table[index] onto the stack
    at entry table must be at top of stack
    at exit  table[index] is at top of stack
    @param iIndex index of the table to be retrieved
*/
void CLua::GetTableField(int iIndex)
{
    lua_pushnumber(this->m_pLuaState, iIndex);

    lua_gettable(this->m_pLuaState, -2); /* Get table[iIndex] */

    if(!lua_istable(this->m_pLuaState, -1))
    {
        wxLogMessage("Table expected, got something else");
    }

    /* Do not remove the retrieved table from the stack to make it available
        for the calling function ! */


}

/** @brief Returns table[intIndex] (expected string), assumes that table is at top of stack */
char* CLua::GetStrField(int iIndex)
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

    /* remove the retrieved serialnumber from stack */
    lua_pop(this->m_pLuaState, 1);

    return strValue;
}

/** @brief Returns table[intIndex] (expected integer), assumes that table is at top of stack */
int CLua::GetIntField(int iIndex)
{
    int iValue;
    /* Now the index is at top of the stack (-1)*/
    lua_pushnumber(this->m_pLuaState, iIndex);

    lua_gettable(this->m_pLuaState, -2); /* get table[intIndex] */

    if(!lua_isnumber(this->m_pLuaState, -1))
    {
        wxLogMessage("Number expected, got something else");
    }

    iValue = (int)lua_tonumber(this->m_pLuaState, -1);

    /* remove the retrieved value from stack */
    lua_pop(this->m_pLuaState, 1);

    return iValue;
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
        return iRetval;
    }

    /* Get your table */
    if(!lua_istable(this->m_pLuaState, -1))
    {
        wxLogMessage("Table expected, got sth else!");
        return iRetval;
    }

    for(int i = 0; i < iNumberOfDevices; i++)
    {
        aStrSerials[i] = wxString::FromUTF8(this->GetStrField(i+1));
    }

    /* Pop the table */
    lua_pop(this->m_pLuaState, 1);

    iRetval = 0;
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
        aStrSerials[i] = wxString::FromUTF8(this->GetStrField(i+1));
    }

    iRetval = 0;

    /* Pop the table */
    lua_pop(this->m_pLuaState, 1);


    return iRetval;
}

void CLua::CleanUp()
{

    if(!(this->IsLoaded()))
    {
        wxLogMessage("Color Control is not loaded!");
    }

    lua_getglobal(this->m_pLuaState, "free");

    /* Call the function with 0 argument and zero return values */
    if (lua_pcall(this->m_pLuaState, 0, 0, 0) != 0)
    {
        wxLogMessage("Error Running Function %s", lua_tostring(this->m_pLuaState, -1));
    }

    /* Set it the attribute to unloaded */
    m_ColorControlLoaded = false;

}
