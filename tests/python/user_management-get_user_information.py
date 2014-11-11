import iotkit;

print 'iotkit library version:', iotkit.iotkit_get_version();

response = iotkit.getUserInformation("545aebf56329f63c4518b1ab");
print 'Response received: ', response;
