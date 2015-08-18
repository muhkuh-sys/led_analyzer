#include "CLua.h"


int Panic(lua_State* state)
{

    wxLogMessage("LUA PANIC FUNCTION ERROR OCCURED!!!!");
    return 0;
}



CLua::CLua(const char* filename)
{
    m_pLuaState = lua_open();
    luaL_openlibs(m_pLuaState);

    /* Initially false */
    m_luaFileLoaded = false;

    /* This function will set m_luaFileLoaded to true if successful */
    if(filename != NULL) this->LoadAndRun(filename);
}



CLua::~CLua()
{
    m_luaFileLoaded = false;
    if(m_pLuaState) lua_close(m_pLuaState);
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


int  CLua::LoadAndRun(const char* pcFilename)
{
    /* Be pessimistic */
    int iRetval = 1;
    iRetval = luaL_loadfile(this->m_pLuaState, pcFilename);

    switch(iRetval)
    {
        case LUA_ERRSYNTAX:
            wxLogMessage("Lua - syntax error.");
            return iRetval;
            break;
        case LUA_ERRMEM:
            wxLogMessage("Lua - memory allocation error.");
            return iRetval;
            break;
        default:
            break;
    }

    iRetval = lua_pcall(this->m_pLuaState, 0, 3, 0);

    switch(iRetval)
    {
        case LUA_ERRRUN:
            wxLogMessage("Lua - runtime error.");
            return iRetval;
            break;
        case LUA_ERRMEM:
            wxLogMessage("Lua - memory allocation error.");
            return iRetval;
        case LUA_ERRERR:
            wxLogMessage("Lua - error while running the error handler function.");
            return iRetval;
            break;
        default:
            break;
    }

    m_luaFileLoaded = true;

    return iRetval;

}

int CLua::RunGeneratedTest(const char* pcFilename)
{
    /* Be pessimistic */
    int iRetval = 1;
    iRetval = luaL_loadfile(this->m_pLuaState, pcFilename);

    switch(iRetval)
    {
        case LUA_ERRSYNTAX:
            wxLogMessage("Lua - syntax error.");
            return iRetval;
            break;
        case LUA_ERRMEM:
            wxLogMessage("Lua - memory allocation error.");
            return iRetval;
            break;
        default:
            break;
    }

    iRetval = lua_pcall(this->m_pLuaState, 0, 1, 0);

    switch(iRetval)
    {
        case LUA_ERRRUN:
            wxLogMessage("Lua - runtime error.");
            return iRetval;
            break;
        case LUA_ERRMEM:
            wxLogMessage("Lua - memory allocation error.");
            return iRetval;
        case LUA_ERRERR:
            wxLogMessage("Lua - error while running the error handler function.");
            return iRetval;
            break;
        default:
            break;
    }

    m_luaFileLoaded = true;

    /* First return value must be a number (number of connected devices) */
    if (!lua_isnumber(this->m_pLuaState, -1))
    {
        wxLogMessage("The test had no return value .. please check.");
        return iRetval;
    }

    iRetval = lua_tonumber(this->m_pLuaState, -1);

    /* Pop the return value from the stack */
    lua_pop(this->m_pLuaState, 1);

    return iRetval;
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

    if (lua_pcall(this->m_pLuaState, 0, 3, 0) != 0)
    {
        wxLogMessage("Error Running Function %s", lua_tostring(this->m_pLuaState, -1));
        return iRetval;
    }

    /* currently the table containing serial number is on top, but as we have to read out the number of devices
    first we push a copy of that return value to the top */
    lua_pushvalue(this->m_pLuaState, -3);

    /* The number of devices */
    if (!lua_isnumber(this->m_pLuaState, -1))
    {
        wxLogMessage("Number of devices expected got sth else!");
        return iRetval;
    }

    iNumberOfDevices = lua_tonumber(this->m_pLuaState, -1);

    /* remove the numberofdevices from the stack, now the actual first return value, the table containing serial numbers
    is at top again */
    lua_pop(this->m_pLuaState, 1);

    /* First return value must be a table that contains serial numbers, its on stack top now */
    if(!lua_istable(this->m_pLuaState, -1))
    {
        wxLogMessage("Table expected, got sth else!");
        return iRetval;
    }

    for(int i = 0; i < iNumberOfDevices; i++)
    {
        aStrSerials[i] = wxString::FromUTF8(this->GetStrField(i+1));
    }

    /* Pop the table, now the xml string is on top */
    lua_pop(this->m_pLuaState, 1);

    /* Pop the xml string as we don't need it here, now the number of devices is on top */
    lua_pop(this->m_pLuaState, 1);

    /* pop the number of devices from the stack as we only removed the copy before */
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


int CLua::InitDevices(wxVector<CColorController*> vectorDevices)
{
    /* Be pessimistic */
    int iRetval = 1;

    unsigned int iNumberOfDevices = vectorDevices.size();

    if(!(this->IsLoaded()))
    {
        wxLogMessage("Color Control is not loaded!");
        return -1;
    }

    /* Load Init Function */
    lua_getglobal(this->m_pLuaState, "initDevices");

    /* Run Init Function */
    if( lua_pcall(this->m_pLuaState, 0, 1, 0) != 0)
    {
        wxLogMessage("Error Running Function %s", lua_tostring(this->m_pLuaState, -1));
        return iRetval;
    }

    /* Get the result (0 if everything fine) */
    if(!lua_isnumber(this->m_pLuaState, -1))
    {
        wxLogMessage("Retval (int) expected, got something else");
    }

    /* Get the result */
    iRetval = lua_tonumber(this->m_pLuaState, -1);

    /* Pop the result from the stack */
    lua_pop(this->m_pLuaState, 1);

    /* Now validate the errorcodes */

    lua_getglobal(this->m_pLuaState, "tColorTable");

    for(unsigned int i = 0; i < iNumberOfDevices; i++)
    {
        /* Load tColorTable[i] = device */
        this->GetTableField(i);

        /* Get retval for sensor from init function */
        vectorDevices.at(i)->SetState(this->GetIntField(7));

        /* Get the settings field (entry 6) .. contains gain and integration time */
        this->GetTableField(6);

        for(int j = 1; j <= 16; j++)
        {
            /* Get the sensor field */
            this->GetTableField(j);

            /* Get integration and gain and store it into vector testrow */
            vectorDevices.at(i)->SetGain( j-1, (tcs3472_gain_t)this->GetIntField("gain"));
            vectorDevices.at(i)->SetIntTime( j-1, (tcs3472_intTime_t)this->GetIntField("intTime"));

            /* Pop the sensor field */
            lua_pop(this->m_pLuaState, 1);
        }

        /* Pop the settings field */
        lua_pop(this->m_pLuaState, 1);

        /* Pop the device table from the stack */
        lua_pop(this->m_pLuaState, 1);
    }

    /* Pop the colorTable */
    lua_pop(this->m_pLuaState, 1);

    return iRetval;
}

int CLua::StartMeasurements()
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

    /* Run Measurement Function */
    if( lua_pcall(this->m_pLuaState, 0, 1, 0) != 0)
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

int CLua::ReadColours(wxVector<CColorController*> vectorDevices)
{
    /* Be pessimistic */
    int iRetval = 1;
    int iNumberOfDevices = vectorDevices.size();

    if(!(this->IsLoaded()))
    {
        wxLogMessage("Color Control is not loaded!");
        return -1;
    }

    /* push your global color table onto the stack */
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


        /* Get your result .. if successful it's zero, if not zero its an errorcode with flags
           indicating what kind of error occured with what sensor(s) */
        iRetval = this->GetIntField(7);
        vectorDevices.at(i)->SetState(iRetval);

        /* Pop Device Table */
        lua_pop(this->m_pLuaState, 1);
    }

    /* Pop tColorTable -- Stack should have the state it had before entering this function */
    lua_pop(this->m_pLuaState, 1);

    /* Leave */

    return iRetval;

}

/** Set either integration time or the gain of all connected sensors at once
    iSelection = 0 --> Gain
    iSelection = 1 --> Integration Time */

int CLua::FastSettings(wxVector<CColorController*> vectorDevices, unsigned char ucSetting, int iSelection)
{
    /* Be pessimistic */
    int iRetval = 1;

    if(!(this->IsLoaded()))
    {
        wxLogMessage("Color Control is not loaded!");
        return -1;
    }

    /* Get your global Set Settings Function */
    lua_getglobal(this->m_pLuaState, "setSettings");

    /* we want to set the gain */
    if(iSelection == 0)
    {
        /* Push the first argument: nil */
        lua_pushnil(this->m_pLuaState);

        /* Push the second argument: gain */
        lua_pushnumber(this->m_pLuaState, ucSetting);

    }
    /* otherwise we want to fast set the integration time */
    else if(iSelection == 1)
    {
        /* first argument: integration time */
        lua_pushnumber(this->m_pLuaState, ucSetting);

        /* second argument gain: nil */
        lua_pushnil(this->m_pLuaState);
    }

    /* now run the function */
    if (lua_pcall(this->m_pLuaState, 2, 1, 0))
    {
        wxLogMessage("Error Running Function %s", lua_tostring(this->m_pLuaState, -1));
        return iRetval;
    }

    /* get your result .. if successful it's zero */
    if(!lua_isnumber(this->m_pLuaState, -1))
    {
        wxLogMessage("Retval (int) expected, got something else!");
    }

    /* Retrieve it */
    iRetval = lua_tonumber(this->m_pLuaState, -1);

    /* Update the view if the retval is zero ... otherwise an error occured */

    if(iRetval == 0)
    {
        for(unsigned int i = 0; i < vectorDevices.size(); i++)
        {
            for(int j = 0; j < 16; j++)
            {
                /* If we edited gain */
                if(iSelection == 0)
                {
                    vectorDevices.at(i)->SetGain(j, (tcs3472_gain_t)ucSetting);
                }
                /* if we edited integration time */
                else if(iSelection == 1)
                {
                    vectorDevices.at(i)->SetIntTime(j, (tcs3472_intTime_t)ucSetting);
                }
            }
        }
    }

    /* Pop the retrieved value */
    lua_pop(this->m_pLuaState, 1);

    return iRetval;

}

/** Set the Integration time for one sensor on one device */
int CLua::SetGainX(int iDeviceIndex, int iSensorIndex, tcs3472_gain_t gain)
{
    /* Be pessimistic */
    int iRetval = 1;
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
        return iRetval;
    }

    /* Get your result .. if successful it's zero */
    if (!lua_isnumber(this->m_pLuaState, -1))
    {
        wxLogMessage("Retval (int) expected, got something else!");
    }

    /* Retrieve it */
    iRetval = lua_tonumber(this->m_pLuaState, -1);

    /* Pop the retrieved value */
    lua_pop(this->m_pLuaState, 1);

    /* return */
    return iRetval;

}

/** Set the Integration time for one sensor on one device */
int CLua::SetIntTimeX(int iDeviceIndex, int iSensorIndex, tcs3472_intTime_t intTime)
{
    /* Be pessimistic */
    int iRetval = 1;
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
        return iRetval;
    }

    /* Get your result .. if successful it's zero */
    if (!lua_isnumber(this->m_pLuaState, -1))
    {
        wxLogMessage("Retval (int) expected, got something else!");
    }

    /* Retrieve it */
    iRetval = lua_tonumber(this->m_pLuaState, -1);

    /* Pop the retrieved value */
    lua_pop(this->m_pLuaState, 1);

    /* return */
    return iRetval;
}

/* Assumes table is at top of stack, returns table[strKey] */
int CLua::GetIntField(const char* strKey)
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
    m_luaFileLoaded = false;

}

int CLua::GetInterfaces(wxArrayString &astrInterfaces)
{
    /* Be pessimistic, iRetval marks the number of interfaces found */
    int iRetval = 0;

    if(!(this->IsLoaded()))
    {
        wxLogMessage("inteface.lua is not loaded!");
        astrInterfaces.Alloc(1);
        astrInterfaces.Add("Error - interface.lua corrupted!");
        return iRetval;
    }

    /* Push your function onto the table */
    lua_getglobal(this->m_pLuaState, "getStrInterfaces");

    /* Call it with 0 arguments and 1 return value expected */
    if( lua_pcall( this->m_pLuaState, 0, 1, 0 ) != 0 )
    {
        wxLogMessage("Error Running Function %s", lua_tostring(this->m_pLuaState, -1));
        astrInterfaces.Alloc(1);
        astrInterfaces.Add("Error - interface.lua corrupted!");
        return iRetval;
    }

    /* Expected argument is a string */
    if(!lua_isstring(this->m_pLuaState, -1))
    {
        wxLogMessage("String expected, got something else.");
        astrInterfaces.Alloc(1);
        astrInterfaces.Add("Error - interface.lua corrupted!");
        return iRetval;
    }

    /* get the concat string */
    wxString strInterfaces = (wxString)lua_tostring(this->m_pLuaState, -1);
    wxString strTemp;
    wxVector<wxString> vectorString;

    size_t i = 0;
    while(i < strInterfaces.length())
    {
        if(strInterfaces[i] == ',')
        {
            vectorString.push_back(strTemp);
            strTemp.clear();
        }
        else
        {
            strTemp += strInterfaces[i];

            /* Last item must be added as well as allthough there follows no comma */
            if(i == (strInterfaces.length() - 1))
            {
                vectorString.push_back(strTemp);
                strTemp.clear();
            }
        }
        i++;
    }

    /* Fill the string array */
    astrInterfaces.Alloc(vectorString.size());
    for(unsigned int j = 0; j < vectorString.size(); j++)
    {
        astrInterfaces.Add(vectorString.at(j));
    }

    /* Pop the value from the stack */
    lua_pop(this->m_pLuaState, 1);

    /* Return the number of interfaces found */
    return astrInterfaces.Count();
}
