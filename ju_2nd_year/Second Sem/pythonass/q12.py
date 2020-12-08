import json
import pprint
content = open('api.json').read()
content = json.loads(content)


flattened ={}

def check_type(x):

    if type(x) == int :
        return True
    if type(x) == float:
        return True
    if type(x) == str:
        return True



def rec( tmp, key_name):
    if  check_type(tmp):
        flattened[key_name] = tmp
        return

    if type(tmp) == list or type(tmp) == tuple:
        for i , item in enumerate(tmp):
            rec( item , key_name+'_'+str(i))

    else:
        for key in tmp.keys():    
            rec( tmp[key] , key_name + '_' + str(key) )


pprint.pprint('Content : ' , content)
rec( content , '')
# print(content)
pprint.pprint('Flattened : ' , flattened)

'''
Content :{'age': 41,
 'fullname': 'Alessandra',
 'phone-numbers': ['+447421234567', '+447423456789'],
 'residence': {'address': {'first-line': 'Alexandra Rd', 'second-line': ''},
               'city': 'London',
               'country': 'UK',
               'zip': 'N8 0PP'}}
Flattened : {'_age': 41,
 '_fullname': 'Alessandra',
 '_phone-numbers_0': '+447421234567',
 '_phone-numbers_1': '+447423456789',
 '_residence_address_first-line': 'Alexandra Rd',
 '_residence_address_second-line': '',
 '_residence_city': 'London',
 '_residence_country': 'UK',
 '_residence_zip': 'N8 0PP'}

'''


