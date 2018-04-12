var jsRR = require('./build/Release/jsRR');

for (var prop in jsRR) {
    if (jsRR.hasOwnProperty(prop)) {
        exports[prop] = jsRR[prop];
    }
}