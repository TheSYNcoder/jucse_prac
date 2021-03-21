import React from "react";
import { ChatList } from "react-chat-elements";
import FormControl from "react-bootstrap/lib/FormControl";
import FormGroup from "react-bootstrap/lib/FormGroup";

/**
 *
 * Renders user list
 *
 * Used on both places Sign-in modal and as ChatList
 */

export default function UserList(props) {
  // state = {
  //   userData: [],
  //   searchQuery: null
  // };
  // componentDidMount() {
    
  // }
  console.log(props);


  
  // searchInput(e) {
  //   let value = e.target.value;
  //   let searchQuery = null;
  //   if (value) {
  //     searchQuery = value;
  //   }
  //   this.setState({ searchQuery });
  // }
  /**
   *
   * Implement filter logic on basis of search query.
   */
  // getFilteredUserList() {
  //   return !this.state.searchQuery
  //     ? this.props.userData
  //     : this.props.userData.filter(user =>
  //         user.username.toLowerCase().includes(this.state.searchQuery.toLowerCase())
  //       );
  // }
  
  
    let users = props.userData;
    return (
      <div>
        <FormGroup>
          <FormControl
            type="text"
            placeholder="Search for a user here..."
            // onInput={this.searchInput.bind(this)}
          />
        </FormGroup>
        {users.length ? (
          <ChatList
            className={!props.showSignInList ? "chat-list" : "user-list"}
            dataSource={users.map((f, i) => {
              let date = null;
              let subtitle = "";
              if (
                !props.showSignInList &&
                f.messages &&
                f.messages.length
              ) {
                let lastMessage = f.messages[f.messages.length - 1];
                date = new Date(lastMessage.timeStamp);
                subtitle =
                  (lastMessage.position === "right" ? "You: " : f.name + ": ") +
                  lastMessage.text;
              }
              return {
                avatar: f.avatar,
                alt: f.username,
                title: f.username,
                subtitle: subtitle,
                date: date,
                unread: f.unread,
                user: f
              };
            })}
            onClick={
              !props.showSignInList
                ? props.onChatClicked
                : props.onUserClicked
            }
          />
        ) : (
          <div className="text-center no-users">No users to show.</div>
        )}
      </div>
    );
  }

