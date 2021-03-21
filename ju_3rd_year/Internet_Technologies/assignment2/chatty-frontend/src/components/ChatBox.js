import React, { Component } from "react";
import FormControl from "react-bootstrap/lib/FormControl";
import InputGroup from "react-bootstrap/lib/InputGroup";
import Button from "react-bootstrap/lib/Button";
import FormGroup from "react-bootstrap/lib/FormGroup";
import Col from "react-bootstrap/lib/Col";
import Jumbotron from "react-bootstrap/lib/Jumbotron";
import Glyphicon from "react-bootstrap/lib/Glyphicon";
import {
  MessageList,
  Navbar as NavbarComponent,
  Avatar
} from "react-chat-elements";
import Dialog from '@material-ui/core/Dialog';
import DialogContent from '@material-ui/core/DialogContent';
import DialogTitle from '@material-ui/core/DialogTitle';
import Picker from 'emoji-picker-react';
/**
 *
 * ChatBox Component
 *
 * displays all the messages from chat history.
 * renders message text box for input.
 */

export default class ChatBox extends Component {
  state = {
    messageText: "",
    image:"",
    file :"",
    emoji : '',
    showDialog : false,

  };

  componentDidMount(){
    // this.setState({image : faker.image.image()});
  }

  /**
   *
   * Sends a message only if it is not falsy.
   */
  onSendClicked() {
    if (!this.state.messageText) {
      return;
    }
    this.props.onSendClicked(this.state.messageText);
    this.setState({ messageText: "" });
  }
  onMessageInputChange(e) {
    this.setState({ messageText: e.target.value });
  }
  /**
   *
   * @param {KeyboardEvent} e
   *
   * listen for enter pressed and sends the message.
   */
  onMessageKeyPress(e) {
    if (e.key === "Enter") {
      this.onSendClicked();
    }
  }

  onMessageFileChange(e){
    let file = e.target.files[0];
    if ( file ){
      console.log(file);
      let reader = new FileReader();
      reader.readAsDataURL(file);
      reader.onloadend = () => {
        this.setState({
          file: file,
          image: reader.result
        },
        
        );
        this.props.onSendClicked( file.name, "photo",reader.result)
      }
      
    }
  }

  render() {

    const onEmojiClick =(e, emojiObj)=>{
      this.setState({emoji : emojiObj.emoji});
      var message = this.state.messageText;
      message += this.state.emoji;
      this.setState({messageText : message});
    }


    return (
      <div>
        {this.props.targetUser ? (
          <div>
            <NavbarComponent
              left={
                <div>
                  <Col mdHidden lgHidden>
                    <p className="navBarText">
                      <Glyphicon
                        onClick={this.props.onBackPressed}
                        glyph="chevron-left"
                      />
                    </p>
                  </Col>
                  <Avatar
                    src={this.props.targetUser.avatar}
                    alt={"logo"}
                    size="large"
                    type="circle flexible"
                  />
                  <p className="navBarText">{this.props.targetUser.username}</p>
                </div>
              }
            />
            <MessageList
              className="message-list"
              // lockable={true}
              toBottomHeight={"100%"}
              dataSource={this.props.targetUser.messages}
            />
            <FormGroup>
              <InputGroup>
                <FormControl
                  type="text"
                  value={this.state.messageText}
                  onChange={this.onMessageInputChange.bind(this)}
                  onKeyPress={this.onMessageKeyPress.bind(this)}
                  placeholder="Type a message here (Limit 3000 characters)..."
                  ref="messageTextBox"
                  className="messageTextBox"
                  maxLength="3000"
                  autoFocus
                />
               
                
                <InputGroup.Button>
                  <Button
                    disabled={!this.state.messageText}
                    className="sendButton"
                    onClick={this.onSendClicked.bind(this)}
                  >
                    Send
                  </Button>
                  <label style={{  display: "inline-block",
                   cursor: "pointer"}}>
                    <img src={require('../static/emoji.jpeg')} alt="emoji.jpeg" width={30} height={30} onClick={() => this.setState({showDialog : true})}/>                                          
                    </label>
                  <label style={{  display: "inline-block",
                   cursor: "pointer"}}>
                    <img src={require('../static/file.png')} alt="file.png" width={30} height={30}/>
                      <input type="file"  style={{display:"none"}}              // value={this.state.messageText}
                  onChange={this.onMessageFileChange.bind(this)} />
                      
                    </label>
                </InputGroup.Button>
              </InputGroup>
            </FormGroup>
          </div>
        ) : (
          <div>
            <Jumbotron>
              <h1>Hello, {(this.props.signedInUser || {}).name}!</h1>
              <p>Select a friend to start a chat.</p>
            </Jumbotron>
          </div>
        )}
        <Dialog
        open={this.state.showDialog}
        onClose={() => this.setState({showDialog : false})}
        aria-labelledby="alert-dialog-title"
        aria-describedby="alert-dialog-description"
      >
        <DialogTitle id="alert-dialog-title">Emojis</DialogTitle>
        <DialogContent>
          <Picker onEmojiClick={onEmojiClick} />
        </DialogContent>
       
      </Dialog>
      </div>
    );
  }
}
