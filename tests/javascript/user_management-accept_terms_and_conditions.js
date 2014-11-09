var iotkit = require('./src/javascript/iotkit');

console.log('iotkit library version:', iotkit.iotkit_get_version());

var response = iotkit.acceptTermsAndConditions("545aebf56329f63c4518b1ab", false);
console.log(response);
