import json
class MemoryDatabase():

    def __init__(self , write=True):
        self.db = {}
        self.roles={}
        self.password = 'memory'
        self.write= write

    def add(self, addr,  key ,value):
        '''
            Adds the key value for respective key value pairs
        '''
        if addr[1] not in self.db:
            self.db[addr[1]] ={}
        self.db[addr[1]][key] = value
    
    def _get(self,addr , key ):

        if addr[1] in self.db:
            if key in self.db[addr[1]]:
                return str(self.db[addr[1]][key])
            else:
                return '<blank>'
        else:
            return '<blank>'

    def _search_entire_db( self , key, multiple=None):
        keys = list(self.db.keys())
        result = []
        for db_key in keys:
            if key in self.db[db_key]:
                result.append(self.db[db_key][key])
        
        if multiple is not True:
            if len(result)> 0:
                return str(result[0])
            else:
                return '<blank>'
        else:
            if len(result) > 0:
                return '\n'.join(str(v) for v in result)
            else:
                return '<blank>'

    def _make_admin( self, addr):
        self.roles[addr[1]] = 'manager'

    def _make_guest(self, addr):
        self.roles[addr[1]] ='guest'
        
    
    def get( self, addr , key , password=None, multiple=None):

        # check role db
        if addr[1] in self.roles:
            if self.roles[addr[1]] == 'manager':
                return self._search_entire_db(key, multiple)
        
        if password is None:
            self._make_guest(addr)
            return self._get( addr, key)
        
        if password == self.password:
            self._make_admin(addr)
            return self._search_entire_db(key , multiple)
        else:
            self._make_guest(addr)
            message = 'Password incorrect, access denied to manager account\n'
            message += str(self._get(addr , key))
            return message





    def analyse_and_return(self, args ,addr):
        args = args.split()
        message=''
        multiple=False
        password=None
        if len(args) > 0:
            start = 0
            if args[0] == 'multiple':
                multiple=True
                start += 1
            if args[start] == 'password':
                password = args[start+1]
                if password == 'memory':
                    self._make_admin(addr)                    
                start += 2
            i = start
            while i < len(args):
                # print(args[i].lower())
                if args[i].lower() == 'get':
                    message += self.get(addr, args[i+1] , password=password , multiple=multiple)
                    message = message.replace('<blank>' , '\nNo key found for {} in memory db\n'.format(args[i+1]))
                    message += ' 200 O.K. \n'
                    i += 1
                elif args[i].lower() == 'put':
                    self.add( addr, args[i+1], args[i+2] )
                    message += ' 200 O.K. \n'
                    i += 2
                i += 1
        if self.write:
            with open('db.json', 'w') as f:
                f.write(json.dumps(self.db, indent=4))
            with open('roles.json' , 'w') as f:
                f.write(json.dumps(self.roles , indent=4))
        return message


