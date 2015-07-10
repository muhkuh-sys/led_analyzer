require("color_control")


scanDevices()

numberOfDevices = connectDevices()

initDevices(numberOfDevices, TCS3472_GAIN_1X, TCS3472_INTEGRATION_700ms)
led_analyzer.wait4Conversion(700)



startMeasurements(numberOfDevices)

free()