require("color_control")


scanDevices()

numberOfDevices = connectDevices()

setSettings(numberOfDevices, TCS3472_INTEGRATION_2_4ms, TCS3472_GAIN_60X)
led_analyzer.wait4Conversion(700)



startMeasurements(numberOfDevices)

free()