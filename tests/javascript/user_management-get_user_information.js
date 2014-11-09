var iotkit = require('./src/javascript/iotkit');

console.log('iotkit library version:', iotkit.iotkit_get_version());

var response = iotkit.getUserInformation("545aebf56329f63c4518b1ab");
console.log(response);
