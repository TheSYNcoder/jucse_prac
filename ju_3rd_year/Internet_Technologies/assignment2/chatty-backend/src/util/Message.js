
module.exports = class Message{

    constructor( socket_id, name,  time,  content ){
        this.socket_id = socket_id;
        this.time = time;
        this.content = content;
    }
}