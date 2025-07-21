
class User {

    userId = '';
    identificacion = '';
    nombre = '';
    apellido = '';
    biometricId = '';
    registration_date = '';
    removal_date = '';
    status = '';

    constructor(
        userId, 
        identificacion,
        nombre,
        apellido,
        biometricId,
        registration_date,
        status,
    ){
        this.userId = userId,
        this.identificacion = identificacion,
        this.nombre = nombre,
        this.apellido = apellido,
        this.biometricId = biometricId,
        this.registration_date = registration_date,
        this.status = status
    }
}

module.exports = User;