import iotkit;

print 'iotkit library version:', iotkit.iotkit_get_version();

response = iotkit.getUserJwtToken('pradeep.chenthati@aricent.com', 'Password1');
print 'Response received: ', response;
