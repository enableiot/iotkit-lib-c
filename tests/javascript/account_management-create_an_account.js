var iotkit = require('./src/javascript/iotkit');

console.log('iotkit library version:', iotkit.iotkit_get_version());

var response = iotkit.createAnAccount('create7');
console.log(response);
