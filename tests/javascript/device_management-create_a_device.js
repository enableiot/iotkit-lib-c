var iotkit = require('./src/javascript/iotkit');

console.log('iotkit library version:', iotkit.iotkit_get_version());

var createDeviceObj = iotkit.createDeviceCreationObject("02-00-a7-8a-77-ff", "02-00-a7-8a-77-ff", "anddre97");
iotkit.addLocInfo(createDeviceObj, "45.540164", "-122.926048", "55.0");
iotkit.addTagInfo(createDeviceObj, "USA");
iotkit.addTagInfo(createDeviceObj, "Oregon");
iotkit.addTagInfo(createDeviceObj, "Hillsboro");
iotkit.addAttributesInfo(createDeviceObj, "vendor", "Intel");
iotkit.addAttributesInfo(createDeviceObj, "platform", "x86");
iotkit.addAttributesInfo(createDeviceObj, "os", "Ubuntu");

var response = iotkit.createADevice(createDeviceObj);
console.log(response);
