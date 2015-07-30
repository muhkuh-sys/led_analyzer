module("muhkuh_cli_init", package.seeall)

-- Set the search path for LUA plugins.
package.cpath = package.cpath .. ";lua_plugins/?.so;lua_plugins/?.dll;ftdi_plugins/?.dll"

-- Set the search path for LUA modules.
package.path = package.path .. ";lua/?.lua;lua/?/init.lua;ftdi_lua/?.lua"

-- Load the common romloader plugins.
require("romloader_usb")
require("romloader_uart")

-- Load the common modules for a CLI environment.
require("muhkuh")
require("select_plugin_cli")
require("tester_cli")

-- Load an easy function to show connected plugins 
require("interface")


-- This string is appended to all paths in the function "load_from_working_folder".
_G.__MUHKUH_WORKING_FOLDER = ""
