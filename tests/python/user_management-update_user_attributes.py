import iotkit;

print 'iotkit library version:', iotkit.iotkit_get_version();

keyValues = iotkit.createKeyValueParams("new", "next_string");
iotkit.addKeyValueParams(keyValues, "another_attribute", "another_value");
iotkit.addKeyValueParams(keyValues, "phone", "123456789");
response = iotkit.updateUserAttributes("545aebf56329f63c4518b1ab", keyValues);

print 'Response received: ', response;
