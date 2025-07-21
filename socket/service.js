let Service = require('node-windows').Service;
let svc = new Service({
    name: 'Servicio registro Danmcode',
    description: 'Servicio que permite el registro de las huellas digitales',
    script: 'C:\\lector-biometrico-arduino-biometric-socket-release\\index.js'
});

svc.on('install', function () {
    svc.start();
});

svc.install();