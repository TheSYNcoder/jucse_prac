import json
import io
import struct
import sys


class Worker():
    def __init__(self,  socket ):
        self.socket = socket 
        



    
    

    def read( self , ):
        data = self.socket.recv(8196)

        header_len = 2
        if  len(data) > header_len : 
            header_length  = struct.unpack( '>H' , data[:header_len])[0]
            data = data[header_len:]
            if len(data) > header_length:
                jsonheader = self._json_decode(data[:header_length] , 'utf-8')
                data = data[header_length:]
                content_length = jsonheader['content-length']
                data  = data[:content_length]
                if jsonheader['content-type']== 'text/json':
                
                    print(eval(data))

    
    def _json_decode(self, json_bytes, encoding):
        tiow = io.TextIOWrapper(
            io.BytesIO(json_bytes), encoding=encoding, newline=""
        )
        obj = json.load(tiow)
        tiow.close()
        return obj




    

    def _is_ascii( self, content ):
        return len(content ) ==  len(content.encode())

    def _json_encode( self, obj , encoding):
        return json.dumps(obj,  ensure_ascii=True).encode(encoding)

    def _create_message(
        self, *, content_bytes, content_type, content_encoding
    ):
        jsonheader = {
            "byteorder": sys.byteorder,
            "content-type": content_type,
            "content-encoding": content_encoding,
            "content-length": len(content_bytes),
        }
        jsonheader_bytes = self._json_encode(jsonheader, "utf-8")
        message_hdr = struct.pack(">H", len(jsonheader_bytes))
        message = message_hdr + jsonheader_bytes + content_bytes
        return message
    
    def write(self,  request):
        
        if self._is_ascii(request):
            req ={
                "content_bytes": self._json_encode(request, 'utf-8'),
                "content_type": 'text/json',
                "content_encoding": 'utf-8',
            }
            message = self._create_message(**req)
            try:
                self.socket.send( message )
            except BlockingIOError:
                print( 'cannot send message : ' + repr(message))
                pass

        else:
            print('bad request')
        
        
        

