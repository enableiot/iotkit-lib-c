import iotkit;

print 'iotkit library version:', iotkit.iotkit_get_version();

response = iotkit.renewActivationCode();
print 'Response received: ', response;
