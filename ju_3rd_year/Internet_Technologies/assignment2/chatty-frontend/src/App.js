import React, { Component } from "react";
import NavBar from "./components/NavBar";
import Grid from "react-bootstrap/lib/Grid";
import Row from "react-bootstrap/lib/Row";
import Col from "react-bootstrap/lib/Col";
import Modal from "react-bootstrap/lib/Modal";
import TextField from '@material-ui/core/TextField';
import UserList from "./components/UserList";
import ChatBox from "./components/ChatBox";
import ErrorModal from "./components/ErrorModal";
import LoadingModal from "./components/LoadingModal";
import RButton from "react-bootstrap/lib/Button";
import "react-chat-elements/dist/main.css";

import "./index.css";
import socketIOClient from "socket.io-client";
// import 'bootstrap/dist/css/bootstrap.min.css';
import SwipeableViews from 'react-swipeable-views';
import AppBar from '@material-ui/core/AppBar';
import Button from '@material-ui/core/Button';
import Tabs from '@material-ui/core/Tabs';
import Tab from '@material-ui/core/Tab';
import FormControl from "react-bootstrap/lib/FormControl";
import FormGroup from "react-bootstrap/lib/FormGroup";
import InputGroup from "react-bootstrap/lib/InputGroup";
import Select from 'react-select';
import makeAnimated from 'react-select/animated';


// import { fetchUsers } from "./requests";
import {
  NotificationContainer,
  NotificationManager
} from "react-notifications";
import "react-notifications/lib/notifications.css";
import axios from "axios";


/**
 * Fetches socket server URL from env
 */
const SOCKET_URI = "http://127.0.0.1:8080";

/**
 * App Component
 *
 * initiaites Socket connection and handle all cases like disconnected,
 * reconnected again so that user can send messages when he is back online
 *
 * handles Error scenarios if requests from Axios fails.
 *
 */
var socket;

class App extends Component {
  

  constructor(){
    super();
    this.state = {
      socket:null,
      signInModalShow: true,
      users: [], // Avaiable users for signing-in
      userChatData: [], // this contains users from which signed-in user can chat and its message data.
      user: null, // Signed-In User
      selectedUserIndex: null,
      showChatBox: false, // For small devices only
      showChatList: true, // For small devices only
      error: false,
      errorMessage: "",
      auth: 0,
      signup: {
        username :"",
        name : "",
        password:"",
      },
      login : {
        username :"",
        password :"",
      },
      randomkey : "3232",
      broadcastMessage:"",
      multicastMessage:"",
      showModal : false, 
      multicastUsers: [],
      

    };
    socket = socketIOClient(SOCKET_URI, {transports: ['websocket', 'polling', 'flashsocket'], reconnection:true});
    socket.on('connection', () => {
      console.log('conncected', socket.id);
    })
    console.info(socket);

  }

  

  /**
   *
   * Setups Axios to monitor XHR errors.
   * Initiates and listen to socket.
   * fetches User's list from backend to populate.
   */

  componentDidMount() {
    this.initAxios();
    // this.initSocketConnection();
    // fetchUsers().then(users => this.setState({ users, signInModalShow: true }));
    this.setupSocketListeners();
  }

  initSocketConnection() {
    // let socket = SocketClient(SOCKET_URI);
    // console.log(socket.id);
    // this.setState({socket : socket});
  }

  /**
   *
   * Checks if request from axios fails
   * and if it does then shows error modal.
   */
  initAxios() {
    axios.interceptors.request.use(
      config => {
        this.setState({ loading: true });
        return config;
      },
      error => {
        this.setState({ loading: false });
        this.setState({
          errorMessage: `Couldn't connect to server. try refreshing the page.`,
          error: true
        });
        setTimeout(()=>this.setState({
          errorMessage:"",
          error:false
        }), 3000);
        return Promise.reject(error);
      }
    );
    axios.interceptors.response.use(
      response => {
        this.setState({ loading: false });
        return response;
      },
      error => {
        this.setState({ loading: false });
        this.setState({
          errorMessage: `Some error occured. try after sometime`,
          error: true
        });
        setTimeout(()=>this.setState({
          errorMessage:"",
          error:false
        }), 3000);
        return Promise.reject(error);
      }
    );
  }



  

  /**
   *
   * Shows error if client gets disconnected.
   */
  onClientDisconnected() {
    NotificationManager.error(
      "Connection Lost from server please check your connection.",
      "Error!"
    );
  }

  /**
   *
   * Established new connection if reconnected.
   */
  onReconnection() {
    if (this.state.user) {
      socket.emit("sign-in", this.state.user);
      NotificationManager.success("Connection Established.", "Reconnected!");
    }
  }

  /**
   *
   * Setup all listeners
   */

  setupSocketListeners() {
    socket.on("message", this.onMessageRecieved.bind(this));
    socket.on("reconnect", this.onReconnection.bind(this));
    socket.on("disconnect", this.onClientDisconnected.bind(this));
  }

  /**
   *
   * @param {MessageRecievedFromstate.state.state.socket} message
   *
   * Triggered when message is received.
   * It can be a message from user himself but on different session (Tab).
   * so it decides which is the position of the message "right" or "left".
   *
   * increments unread count and appends in the messages array to maintain Chat History
   */

  onMessageRecieved(message) {
    let userChatData = this.state.userChatData;
    let messageData = message.message;
    if ( [message.to, message.from].indexOf(this.state.user.username) < 0 ){
      return;
    }
    let targetId;
    if (message.from === this.state.user.username) {
      messageData.position = "right";
      targetId = message.to;
    } else {
      messageData.position = "left";
      targetId = message.from;
    }
    let targetIndex = userChatData.findIndex(u => u.username === targetId);
    console.log(userChatData);
    if (!userChatData[targetIndex] || !userChatData[targetIndex].messages) {
      userChatData[targetIndex].messages = [];
    }
    if (targetIndex !== this.state.selectedUserIndex) {
      if (!userChatData[targetIndex].unread) {
        userChatData[targetIndex].unread = 0;
      }
      userChatData[targetIndex].unread++;
    }
    userChatData[targetIndex].messages.push(messageData);
    this.setState({ userChatData });
  }

  /**
   *
   * @param {User} e
   *
   * called when user clicks to sign-in
   */
  onUserClicked(e) {
    let user = e.user;
    socket.emit("sign-in", user);
    
  }

  /**
   *
   * @param {ChatItem} e
   *
   * handles if user clickes on ChatItem on left.
   */
  onChatClicked(e) {
    this.toggleViews();
    let users = this.state.userChatData;
    for (let index = 0; index < users.length; index++) {
      if (users[index].username === e.user.username) {
        users[index].unread = 0;
        this.setState({ selectedUserIndex: index, userChatData: users });
        return;
      }
    }
  }

  /**
   *
   * @param {messageText} text
   *
   * creates message in a format in which messageList can render.
   * position is purposely omitted and will be appended when message is received.
   */
  createMessage(text, type='text', data='data') {
    let message;
    if ( type === 'text'){
         message = {
          to: this.state.userChatData[this.state.selectedUserIndex].username,
          message: {
            type: type,
            text: text,
            date: +new Date(),
            className: "message"
          },
          from: this.state.user.username
        };
      }
    else{
      message = {
        to: this.state.userChatData[this.state.selectedUserIndex].username,
        from: this.state.user.username,
        message: {
            type: type,
            data : {
              uri : data,
              height : "200px",
              width : "200px",
              // status: {
              //   click : false, 
              //   loading : 0,
              // }
            },
            text: text,
            
            date: +new Date(),
            className: "message"
          },

      }
    }
    console.log(message);
    socket.emit("message", message);
  }

  /**
   * Toggles views from 'ChatList' to 'ChatBox'
   *
   * only on Phone
   */
  toggleViews() {
    this.setState({
      showChatBox: !this.state.showChatBox,
      showChatList: !this.state.showChatList
    });
  }

  async getUsers() {
    const resp = await axios.get('http://localhost:8080/users');
    console.log(resp);
    if ( resp.status === 200){
      let users = Object.keys(resp.data).map( d => resp.data[d]);
      console.log(users);
      
      this.setState({ users : users});

      console.log(this.state.users);
    }
  }


  onInput(e){
    let value = e.target.value;
    let broadcastMessage = null;
    if (value) {
      broadcastMessage = value;
    }
    this.setState({ broadcastMessage });
  }
  onInputMulti(e){
    let value = e.target.value;
    let multicastMessage = null;
    if (value) {
      multicastMessage = value;
    }
    this.setState({ multicastMessage });
  }



  render() {

    const animatedComponents = makeAnimated();

    const users = this.state.userChatData;
    const dataoptions = users.map( d => ({
      value : d.username, 
      label : d.username,
    }));

    let chatBoxProps = this.state.showChatBox
      ? {
          xs: 12,
          sm: 12
        }
      : {
          xsHidden: true,
          smHidden: true
        };

    let chatListProps = this.state.showChatList
      ? {
          xs: 12,
          sm: 12
        }
      : {
          xsHidden: true,
          smHidden: true
        };

    const handleSelect = (index) => {
      this.setState({auth:index});
    }
    const handleChange = (event, newValue) => {
      this.setState({auth:newValue})
    };

  // const styles = {
  //   '& .MuiTextField-root': {
  //     margin: '2px',
  //     width: 200,
  //   },
  // }

  const setUpChat = async ()=> {
      await this.getUsers();
      // console.log(this.state.user);
      // console.log(this.state.users);
      let userChatData = this.state.users.filter(u => u.username !== this.state.user.username);
      // let userChatData = this.state.users;
      console.log(userChatData);
      this.setState({signInModalShow: false, userChatData });
      this.setState({randomkey: Math.random()})
      // console.log(this.state.userChatData);
      var usernames = new Set();
      if ( this.state.users ){
        this.state.users.forEach( user => {
          if ( usernames.has( user.username)) {
            return;
          }
          if ( user.messages_stored){
            user.messages_stored.forEach( message => {
              usernames.add( message.to);
              usernames.add(message.from);
              this.onMessageRecieved(message);
            })
          }
        });
      }
      this.forceUpdate();
      


  }

  const onSignUpClicked = async () => {
      const user={
        name : this.state.signup.name,
        username : this.state.signup.username,
        password : this.state.signup.password,
      }

      const resp = await axios.post('http://localhost:8080/signup', user);
      this.setState({ user: resp.data} );
      socket.emit("sign-in", user);
      setUpChat();
      
  }
  const onLoginClicked = async () => {
      const user={
        username : this.state.login.username,
        password : this.state.login.password,
      }
      let resp = await axios.post('http://localhost:8080/login', user);
      if ( resp.status === 200 ){
        this.setState({user});
        socket.emit("sign-in", user);
        setUpChat();
      }
  }

  const onBroadCastSend = () => {
    let message = {
      to: "",
      message: {
        type: 'text',
        text: this.state.broadcastMessage,
        date: +new Date(),
        className: "message"
      },
      from: this.state.user.username
    };
    socket.emit('broadcast-message' , message);
  }

  const onMultiCastSend = () => {
    let message = {
      to: "",
      message: {
        type: 'text',
        text: this.state.multicastMessage,
        date: +new Date(),
        className: "message"
      },
      from: this.state.user.username
    };
    socket.emit('multicast-message' , message, this.state.multicastUsers);
  }

  

    return (
      <div >
        <NavBar signedInUser={this.state.user} />
        <Grid>
          <Row className="show-grid">
            <Col {...chatListProps} md={4}>
              { this.state.userChatData === [] ?  <div className="text-center no-users">No users to show.</div>:
              <UserList
                key={this.state.randomkey}
                userData={this.state.userChatData}
                onChatClicked={this.onChatClicked.bind(this)}
              />}
              <div style={{ height : "auto", width:"100%"
               }}>
               <Row>
                 <Col >
                  <FormGroup>
                    <InputGroup>
                  <FormControl
                    type="text"
                    placeholder="Broadcast your message ..."
                    onInput={this.onInput.bind(this)}
                  />
                  <InputGroup.Button>
                    <Button 
                    variant="contained"
                    color="primary"
                    onClick={onBroadCastSend}>
                      Send
                  </Button>
                  </InputGroup.Button>
                  </InputGroup>
                </FormGroup>
                </Col>
                 <Col >
                  <FormGroup>
                    <InputGroup>
                  <FormControl
                    type="text"
                    placeholder="Multicast your message ..."
                    onInput={this.onInputMulti.bind(this)}
                  />
                  <InputGroup.Button>
                    <Button 
                    variant="contained"
                    color="secondary"
                    onClick={()=> this.setState({showModal :true})}>
                      Select users
                  </Button>
                    <Button 
                    variant="contained"
                    color="primary"
                    onClick={onMultiCastSend}>
                      Send
                  </Button>
                  </InputGroup.Button>
                  </InputGroup>
                </FormGroup>
                </Col>
                </Row>
              </div>
            </Col>
            <Col {...chatBoxProps} md={8}>
              <ChatBox
                signedInUser={this.state.user}
                onSendClicked={this.createMessage.bind(this)}
                onBackPressed={this.toggleViews.bind(this)}
                targetUser={
                  this.state.userChatData[this.state.selectedUserIndex]
                }
              />
            </Col>
          </Row>
        </Grid>
        <Modal show={this.state.signInModalShow} >
          <Modal.Header >
            
            <Modal.Title><AppBar color="default">
                <Tabs
                  value={this.state.auth}
                  onChange={handleChange}
                  indicatorColor="primary"
                  textColor="primary"
                  variant="fullWidth"
                  aria-label="full width tabs example"
                >
                  <Tab label="SignUp" id="full0" style={{padding :"2em", fontSize :"0.8em"}}/>
                  <Tab label="Login" id="full1" style={{padding :"2em", fontSize :"0.8em"}}/>
                  
                </Tabs>
              </AppBar></Modal.Title>
          
            </Modal.Header>
          
            
          

          <Modal.Body style={{marginTop :"6em", fontSize :"0.6em"}}>
            
              <SwipeableViews
                axis={'x'}
                index={this.state.auth}
                onChangeIndex={handleSelect}
              >
                {this.state.auth === 0 ? <div style={{display:"flex", width:"100%",
                height:"auto", justifyContent:"center", padding :"2em",
                
              }}>
                    <form  noValidate autoComplete="off">
                      <div style={{margin:"1em"}}>
                        <TextField  
                        id="usernames" 
                        label="username" 
                        placeholder="Username"
                        value={this.state.signup.username}
                        onChange={e => {
                          var state = this.state.signup;
                          state.username = e.target.value;
                          this.setState({signup:state});
                        }}
                        variant="outlined" />
                      </div>
                       <div style={{margin:"1em"}}>
                        <TextField
                          
                          id="names"
                          label="name"
                          placeholder="Your name"
                          value={this.state.signup.name}
                        onChange={e => {
                          var state = this.state.signup;
                          state.name = e.target.value;
                          this.setState({signup:state});
                        }}
                          // helperText="Enter your full name."
                          variant="outlined"
                        />
                        </div>
                         <div style={{margin:"1em"}}>
                        <TextField
                          type="password"
                          id="passwords"
                          label="password"
                          placeholder="password"
                          value={this.state.signup.password}
                        onChange={e => {
                          var state = this.state.signup;
                          state.password = e.target.value;
                          this.setState({signup:state});
                        }}
                          // helperText="Enter your full name."
                          variant="outlined"
                          
                        />
                      </div>
                       <Button style={{marginLeft:"5em"}}
                       onClick={onSignUpClicked}
                       variant="contained" color="primary">
                            Submit
                       </Button>
                      </form>
                     
                  
                  </div>:<div></div>}
                {this.state.auth === 1 ? <div style={{display:"flex", width:"100%",
                height:"auto", justifyContent:"center", padding :"2em",
              }}>
                    <form  noValidate autoComplete="off">
                      <div style={{margin:"1em"}}>
                        <TextField  
                        id="usernamel" 
                        label="username" 
                        placeholder="Username"
                        value={this.state.login.username}
                        onChange={e => {
                          var state = this.state.login;
                          state.username = e.target.value;
                          this.setState({login:state});
                        }}
                        variant="outlined" />
                      </div>
                       
                         <div style={{margin:"1em"}}>
                        <TextField
                          type="password"
                          id="passwordl"
                          label="password"
                          placeholder="password"
                          value={this.state.login.password}
                        onChange={e => {
                          var state = this.state.login;
                          state.password= e.target.value;
                          this.setState({login:state});
                        }}
                          // helperText="Enter your full name."
                          variant="outlined"
                          
                        />
                      </div>
                       <Button style={{marginLeft:"5em"}} 
                       onClick={onLoginClicked}
                       variant="contained" color="primary">
                            Submit
                       </Button>
                      </form>
                     
                  
                  </div>:<div></div>}
              
              </SwipeableViews>
           
          </Modal.Body>
        </Modal>
        <Modal show={this.state.showModal} onHide={() => this.setState({showModal : false})}>
          <Modal.Header closeButton>
            <Modal.Title>Select Users for multicasting</Modal.Title>
          </Modal.Header>
          <Modal.Body>
              <Select
                  closeMenuOnSelect={false}
              components={ animatedComponents }
              // defaultValue={[]}
              isMulti
              options={dataoptions}
              onChange={ e => this.setState({ multicastUsers : e.map( user => user.value)})}
              value={this.state.multicastUsers.map( d => ({ label :d, value : d}) )}
                />
           </Modal.Body>
          <Modal.Footer>
            <RButton variant="secondary" onClick={() => this.setState({showModal : false})}>
              Close
            </RButton>
          </Modal.Footer>
        </Modal>
        
        <ErrorModal
          show={this.state.error}
          errorMessage={this.state.errorMessage}
        />
        <LoadingModal show={this.state.loading} />
        <NotificationContainer />
      </div>
    );
  }
}

export default App;
