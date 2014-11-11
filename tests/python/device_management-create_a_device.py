import iotkit;

print 'iotkit library version:', iotkit.iotkit_get_version();

createDeviceObj = iotkit.createDeviceCreationObject("02-a0-a7-8a-77-ff", "02-a0-a7-8a-77-ff", "anddre79");
iotkit.addLocInfo(createDeviceObj, "45.540164", "-122.926048", "55.0");
iotkit.addTagInfo(createDeviceObj, "United States");
iotkit.addTagInfo(createDeviceObj, "Oregon");
iotkit.addTagInfo(createDeviceObj, "Hillsboro");
iotkit.addAttributesInfo(createDeviceObj, "vendor", "Intel");
iotkit.addAttributesInfo(createDeviceObj, "platform", "x86");
iotkit.addAttributesInfo(createDeviceObj, "os", "Ubuntu");

response = iotkit.createADevice(createDeviceObj);
print 'Response received: ', response;
