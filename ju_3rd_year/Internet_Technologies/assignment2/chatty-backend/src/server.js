const { signupUser , loginUser } =require("./util/auth");

const { connections , users} = require("./db");


// Patches
const {inject, errorHandler} = require('express-custom-error');
inject(); // Patch express in order to use async / await syntax

// Require Dependencies

const express = require('express');
const cookieParser = require('cookie-parser');
const cors = require('cors');
const helmet = require('helmet');
const faker = require('faker')




const PORT =8080

var Message = require('./util/Message');


const logger = require('./util/logger');



// Instantiate an Express Application
const app = express();


// Configure Express App Instance
app.use(express.json());
app.use(express.urlencoded( { extended: true} ));

// Configure custom logger middleware
// app.use(logger.dev, logger.combined);

app.use(cookieParser());
app.use((req, res, next) => {
    res.setHeader('Access-Control-Allow-Origin', '*');
    next();
})
app.use(helmet());
app.use(cors());

// This middleware adds the json header to every response
app.use('*', (req, res, next) => {
    res.setHeader('Content-Type', 'application/json');
    next();
})

// Assign Routes

// app.use('/', require('./routes/router.js'));
const http = require('http').createServer(app);
var io = require('socket.io')(http)


var sockets ={}
var rooms = {}


io.on('connection' , (socket) => {


    console.info('new client connected : ' , socket.id);

    socket.on('sign-in',  user =>{
        let username =user.username ;
        if (!username) return;
        
        socket.user_id = username;
        if ( sockets[username]){
            sockets[username].push(socket);
        }
        else{
            sockets[username] = [ socket ];
        }


    })

    // personal dms
    socket.on('message', msg => {
        let target = msg.to;
        let source = socket.user_id;

        if (users[target] &&  users[target].messages_stored){
            users[target].messages_stored.push( msg);
        }
        else{
            users[target].messages_stored = [msg];
        }

        if ( users[source] && users[source].messages_stored){
            users[source].messages_stored.push(msg);
        }
        else{
            users[source].messages_stored = [msg];
        }

        if ( target && sockets[target]){
            sockets[target].forEach( sock => {
                sock.emit('message' , msg);
             })
        }
        if ( source && sockets[source]){
            sockets[source].forEach( sock => {
                sock.emit('message' , msg);
             })
        }
    })



    socket.on('broadcast-message', msg=> {
        let source = socket.user_id;
        let filteredUsers = Object.keys(users).filter( u => u !== socket.user_id);
        filteredUsers.forEach( target => {
            var msgto = JSON.parse(JSON.stringify(msg));
            msgto.to= target;
            if ( users[target] && users[target].messages_stored){
                users[target].messages_stored.push( msgto);
            }
            else{
                users[target].messages_stored = [msgto];
            }
            if ( users[source] && users[source].messages_stored){
                users[source].messages_stored.push( msgto);
            }
            else{
                users[source].messages_stored = [msgto];
            }
            
             if ( target && sockets[target]){                
                sockets[target].forEach( sock => {
                    sock.emit('message' , msgto);
                })
            }
             if ( source && sockets[source]){                
                sockets[source].forEach( sock => {
                    sock.emit('message' , msgto);
                })
            }
        });       
    });

    socket.on('multicast-message', (msg ,multi_users) => {
        let source = socket.user_id;
        multi_users.forEach( target => {
            let msgto = msg;
            msgto.to = target;
            if ( users[target] && users[target].messages_stored){
                users[target].messages_stored.push( msgto);
            }
            else{
                users[target].messages_stored = [msgto];
            }
            if ( users[source] && users[source].messages_stored){
                users[source].messages_stored.push( msgto);
            }
            else{
                users[source].messages_stored = [msgto];
            }
            
             if ( target && sockets[target]){                
                sockets[target].forEach( sock => {
                    sock.emit('message' , msgto);
                })
            }
             if ( source && sockets[source]){                
                sockets[source].forEach( sock => {
                    sock.emit('message' , msgto);
                })
            }
        })
    })


    

    

    


    socket.on('disconnect', function(){
        if ( !socket.user_id || !sockets[socket.user_id])
            return;
        let targetClients = sockets[socket.user_id];
        for (let i = 0; i < targetClients.length; ++i) {
            if (targetClients[i] == socket) {
                targetClients.splice(i, 1);
            }
            }
    });
})






app.get('/' , (req, res) => {
    res.status(200).json({'message' : 'Hello'});
})


app.post('/signup' ,async (req, res) => { 

    const name = req.body.name;
    const username = req.body.username;
    const password = req.body.password;

    const resp = await signupUser( {
        name : name, 
        username : username, 
        password : password
    });


    if ( resp.error === false){
        res.status(200).json(resp.user);
    }
    else{
        res.status(400).json(resp);
    }


});


app.post('/login' , async(req,res) => {

    const username= req.body.username;
    const password= req.body.password;

    const resp = await loginUser( {
        username: username, 
        password: password
    });

    if ( resp.error === false ){
        res.status(200).json(resp.message);
    }
    else{
        res.status(401).json(resp.message);
    }

})


app.get('/users', (req,res)=>{

    res.status(200).json(users);
})






// Handle errors
app.use(errorHandler());

// Handle not valid route
app.use('*', (req, res) => {
    res
    .status(404)
    .json( {status: false, message: 'Endpoint Not Found'} );
})














// Open Server on selected Port
http.listen(
    PORT,
    () => console.info('Server listening on port ', PORT)
);