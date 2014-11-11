import iotkit;

print 'iotkit library version:', iotkit.iotkit_get_version();

response = iotkit.getUserJwtTokenInfo();
print 'Response received: ', response;
