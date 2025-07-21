const app = require('express')();
const express = require('express');
const server = require('http').createServer(app);
const io = require('socket.io')(server);
const notifier = require('node-notifier');//Desktop notifications

const { saveDB, readDB } = require('./src/helpers/database');
const { decodeData } = require('./src/utils/utils')
const Users = require('./src/models/users');

/**
 * Main function
 */
const main = async () => {

  const users = new Users(); //Instance to Users
  const usersDB = readDB();  //Instance to DataBase

  /**
   * Read the users db
   * if the users db exists load from Array
   * to manage the information
   */
  if (usersDB) {
    users.loadUsersFromArray(usersDB);
  }

  app.set("view engine", "ejs"); //Front ejs
  app.set("views", "./src/views"); // view routes

  app.use(express.static("./public")); //front css, js

  /**
   * Index page without params
   * show the main frontPage 
   */
  app.get("/", (req, res) => {
    res.render("index", { id: '' });
  });

  /**
   * Open the page with the params sent by
   * Danmcode all information
   * is manage with the identification
   */
  app.get("/inicio", (req, res) => {
    const data = req.query.data;
    let dataRequest = decodeData(data);
    res.render("index", { id: dataRequest });
  });

  /**
   * Open the sockect server, for manage the
   * realtime information beteween the
   * biometric device and computer
   */
  io.on('connection', (socket) => {

    console.log("Client connected"); //Show when a new clean has been conected

    /**
     * Show when a client goes offline
     */
    socket.on("disconnect", () => {
      console.log("user disconnected");
    });

    /**
     * Show main Topic named danmcode through
     * this topic the biometric device and
     * computer server will registes user
     * @param{identification, instance, database, name, 
     * lastName, userId, biometricId, type } msg
     * 
     * the param type will indicate to biometric device
     * the action that will have to do.
     */
    socket.on("danmcode", (msg) => {

      //Search if the user exists
      let [user] = users.userListArray.filter((user) => {
        return user.identificacion == msg.identification;
      });

      //If the user exists
      if (user != undefined) {
        //change state to enrroll
        users.editUserState(user.userId);
        /**
         * NOTE: Verify if the biometricId in not empty
         * and verify if the biometricId length 
         * is greater than 4 because the
         * biometric capacity is 1000
         */
        if (msg.biometricId == "" || msg.biometricId.length > 4) {
          msg.biometricId = String(users.newBiometricId);
        }
      } else {
        // If users don't exist then it should be created
        const biometricId = users.newBiometricId; //get the biometric id
        msg.biometricId = String(biometricId); // set the biometriv id to msg 

        /**
         * Create new user
         */
        users.createNewUser(
          msg.userId,
          msg.identification,
          msg.name,
          msg.lastName,
          biometricId,
          new Date().toISOString(),
          'enrolling'
        );

        //Save in db the new id
        saveDB(users.userListArray);
      }

      console.log("Send to arduino: ", msg);

      /**
       * Send the message information to danmcode channel
       * to arduino
       */
      io.emit("danmcode", msg);
    });

    /**
     * Show notifications when the biometric device
     * detect successfully to user
     */
    socket.on("danmcodeInOut", (msg) => {
      //console.log(`InOut : ${msg.type} ${msg.person}`);
      notifier.notify(
        {
          title: msg.type,
          message: `${msg.person}`,
          icon: './public/images/logo.png',
          sound: true,
        });
    });


    /**
     * Socket that comunicate to biometric device message
     * with the frontend tha show the information to 
     * user
     */
    socket.on("consoleEvt", (msg) => {
      let personBiometricId
      let personIdentification;

      //If the register was suceesfull write in data base
      if (msg.type == "SUCCESS") {
        console.log("Message", msg);
        let personSplit = msg.person.split(':');
        personBiometricId = personSplit[0];
        personIdentification = personSplit[1];

        console.log("data to write", `${personBiometricId} ${personIdentification}`);

        let [user] = users.userListArray.filter((user) => {
          return user.identificacion == personIdentification;
        });

        //Write information to objet and later to dataBase
        users.saveUserBiometricIdAndStatus(
          user.userId,
          personBiometricId
        );

        saveDB(users.userListArray);
      }
      // else{
      //   Error when save the biometric id
      //   users.editUserState(personIdentification, "Error");

      //   saveDB(users.userListArray);
      // }

      /**
       * Emit a message to console event
       */
      io.emit("consoleEvt", msg);
    });

  }); //Ends Socket Instance

  /**
   * Start the http server
   */
  server.listen(3000, () => {
    console.log(`Escuchando puerto :3000`);
  });
}

main();

