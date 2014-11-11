import iotkit;

print 'iotkit library version:', iotkit.iotkit_get_version();

response = iotkit.getAccountInformation();
print 'Response received: ', response;
