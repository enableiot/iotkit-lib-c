import iotkit;

print 'iotkit library version:', iotkit.iotkit_get_version();

response = iotkit.createAnAccount('create99');
print 'Response received: ', response;
