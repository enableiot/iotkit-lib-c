import iotkit;

print 'iotkit library version:', iotkit.iotkit_get_version();

response = iotkit.acceptTermsAndConditions("545aebf56329f63c4518b1ab", True);
print 'Response received: ', response;
