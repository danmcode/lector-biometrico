const User = require('./user');

class Users {

    _userList = {}; //private user object
    

    constructor() {
        this._userList = {};
    }

    /**
     * converts the user object to user array
     * @returns userList
     */
    get userListArray() {
        let userList = [];
        Object.keys(this._userList).forEach(key => {
            const tarea = this._userList[key];
            userList.push(tarea);
        });
        return userList;
    }

     userList = () => {
        let userList = [];
        Object.keys(this._userList).forEach(key => {
            const tarea = this._userList[key];
            userList.push(tarea);
        });
        return userList;
    }
    /**
     * Return a new biometricId based on the record on 
     * Json User Local Database is a consecutive
     * @returns userList
     */
    get newBiometricId() {

        const sortUserDb = this.userList().sort((a, b) => {
            return Number.parseInt(b.biometricId) - Number.parseInt(a.biometricId);
        });

        return Number.parseInt(sortUserDb[0].biometricId) + 1;
    }

    /**
     * Load the users list 
     */
    loadUsersFromArray(users = []) {
        users.forEach(user => {
            this._userList[user.userId] = user;
        });
    }

    /**
     * Edit the user state when is enrrolling a new finger
     * @returns void change status to enrroling || active
     * @param {*} identification
     * @param {*} state Active || Error || Disabled || Enrolling
     */
    editUserState(id) {
        const user = this._userList[id];
        user.status = "Enrolling";

        console.log("====== Enrolling =======");
        console.log(this._userList[id]);
        console.log("====== END Enrolling =======");

    }

    /**
     * When the biometric device saved successfully the fingerprint
     * save into json db the status and the biometricId that saved
     * @param {*} id 
     * @param {*} biometricId 
     */
    saveUserBiometricIdAndStatus(id, biometricId){
        const user = this._userList[id];
        user.status = 'Active';
        user.biometricId = biometricId;
        user.registration_date = new Date().toISOString();
    }

    /**
     * Create a new user into json database
     * when is the first time that enroll 
     * the fingerprint
     * @param {*} userId 
     * @param {*} identificacion 
     * @param {*} nombre 
     * @param {*} apellido 
     * @param {*} biometricId 
     * @param {*} registration_date 
     * @param {*} status 
     */
    createNewUser(
        userId,
        identificacion,
        nombre,
        apellido,
        biometricId,
        registration_date,
        status
    ) {
        const user = new User(
            userId,
            identificacion,
            nombre,
            apellido,
            biometricId,
            registration_date,
            status
        );

        this._userList[user.userId] = user;
    }
}

module.exports = Users;