var iotkit = require('./src/javascript/iotkit');

console.log('iotkit library version:', iotkit.iotkit_get_version());

var keyValues = iotkit.createKeyValueParams("new", "next_string");
iotkit.addKeyValueParams(keyValues, "another_attribute", "another_value");
iotkit.addKeyValueParams(keyValues, "phone", "123456789");
var response = iotkit.updateUserAttributes("545aebf56329f63c4518b1ab", keyValues);

console.log(response);
