const getIdentification = (id) => {

    let socket = io();
    let msg = {};

    let dataSplit = id.split(',');

    let sendObject = {
        "identification": dataSplit[0],
        "instance": dataSplit[1],
        "dataBase": dataSplit[2],
        "name": dataSplit[3],
        "lastName": dataSplit[4],
        "userId": dataSplit[5],
        "biometricId": dataSplit[6],
        "type": "registro",
    };

    switch (dataSplit[6]) {
        case "":
            $('#arduinoMessage').append($('<li class="alert alert-primary">').text("Registrar un usuario con nuevo id"));
            break;
        default:
            $('#arduinoMessage').append($('<li class="alert alert-warning">').text(`Se Sobreescribira la huella registrada con el id: ${dataSplit[6]}`));
            break;
    }

    socket.emit('danmcode', sendObject);
};

const cancelEvent = () => {
    console.log('evento de cancelar');

    let socket = io();
    let sendObject = {
        "identification": "",
        "instance": "",
        "dataBase": "",
        "type": "cancel",
    };
    socket.emit('danmcode', sendObject);
};

const socket = io();

socket.on('danmcodeInOut', (msg) => {
    Push.create("Sensor Biometrico", {
        body: `${msg.type} : ${msg.person}`,
        icon: "images/logo.png",
        timeout: 4000,
    });
});

socket.on('consoleEvt', (msg) => {
    switch (msg.type) {

        case "SUCCESS":
            let msgSplit = msg.person.split(':');
            $('#arduinoMessage').append($('<li class="alert alert-success">').text(`Se ha registrado el ID: ${msgSplit[0]}`));
            break;
        case "ERROR":
            $('#arduinoMessage').append($('<li class="alert alert-danger">').text(`No se pudo registrar en el id ${msg.person}`));
            break;
        default:
            $('#arduinoMessage').append($('<li>').text(msg.type));
            break;
    }
});